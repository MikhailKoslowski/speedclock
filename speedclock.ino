#include <TM1638.h>
// define a module on data pin 8, clock pin 9 and strobe pin 10
#define TM1638_Data 2
#define TM1638_Clock 3
#define TM1638_Strobe 4
#define BUZZER 0

TM1638 module(TM1638_Data, TM1638_Clock, TM1638_Strobe);
unsigned long a=1;

bool buttons[8];
bool trainning = true;


void readButtons()
{
  byte b = module.getButtons();
  for(int i = 0; i < 8; i++)
  {
    buttons[i] = b & 0x01<<i;
  }
  /*
  Serial.println(b, BIN);
  for(int i = 0; i < 8; i++)
  {
    Serial.print(buttons[i]);
  }
  Serial.println("");
  */
}


void setup()
{
  module.clearDisplay();
  module.setLEDs(0xFF);
  for(int i = 0; i<8; i++)
  {
    buttons[i] = false;
  }
  //Serial.begin(9600);
  pinMode(BUZZER,OUTPUT);
}

// Button map.
// 1, 2, 3 - Judge - Start/Stop/Reset
/// 5, 7 - P1 - End/Mark
/// 6, 8 - P2 - End/Mark
#define S1 0
#define S2 1
#define S3 2
#define S4 3
#define S5 4
#define S6 5
#define S7 6
#define S8 7

void loop()
{

bool start = false;
bool p1FS = false;
bool p2FS = false;
bool p1End = false;
bool p2End = false;
bool p1Start = false;
bool p2Start = false;
bool cancelled = false;

byte LEDs = 0x83; // 1000 0011 

// 0. Define mode.
while(1)
{
  // walking leds!
  switch(LEDs)
  {
    case 0x83: // 1000 0011
      LEDs = 0x07 ; // 0000 0111
      break;
    case 0xC1: // 1100 0001
      LEDs = 0x83; 
      break;
    case 0xE0: // 1110 0000
      LEDs = 0xC1; // 1100 0001 
      break;
    default:
      LEDs = LEDs << 1; // apenas faz um shift left
  }
  module.setLEDs(LEDs);
  
  if(trainning)
  {
    module.setDisplayToString("Train   "); 
  }else{
    module.setDisplayToString("Comp    ");
  }

  readButtons();
  trainning = !buttons[S2];

  if(buttons[S1])
  {
    module.clearDisplay();
    break;
  }
  delay(50);
}

// 1. Wait judge signal.
// In order to start, judge must signal while competitors are pressing on their mark signal.

while(!start)
{
  readButtons();
  bool p1ready = buttons[S7];
  bool p2ready = trainning?true:buttons[S8];
  bool judgeReady = buttons[S1];

  /*
  Serial.print(p1ready);
  Serial.print(p2ready);
  Serial.print(judgeReady);
  Serial.println("");
  */
  LEDs = p1ready<<S7 | p2ready<<S8 | judgeReady<<S1;
  module.setLEDs(LEDs);

  start = p1ready & p2ready & judgeReady;
}
// 2. Countdown.
// During countdown if any competitor let go of their mark it is a false start.
for(int i=3; i > 0; i--)
{
  // now we should delay 1sec but checking if any competitor let go of their mark.
  unsigned long t0 = millis();
  unsigned long t1 = millis();
  while(t1-t0 < 997) // compensates for 3ms delay measured by debugging
  {
    readButtons();
    bool p1ready = buttons[S7];
    bool p2ready = buttons[S8];
    p1FS = !p1ready;
    p2FS = trainning?false:!p2ready;

    if(p1FS || p2FS)
    {
      //Serial.println(p1FS);
      //Serial.println(p2FS);
      break;
    }

    t1 = millis();
  }
  if(p1FS || p2FS)
  {
    //Serial.println(p1FS);
    //Serial.println(p2FS);
    break;
  }
  module.setDisplayToDecNumber(0x00, 0x01<<(i-1), false); 
  tone(BUZZER, i>1?440:440*4,100);
  //Serial.println(millis()-t0);
}

module.setLEDs(0x00);

// 3. Running
// Update the clock until both competitors finishes or judge stops.
unsigned long t0 = millis();
unsigned long t1 = millis();
unsigned long tp1 = 0; // total time for p1
unsigned long tsp1 = 0;// startup time for p1
unsigned long tp2 = 0; // total time for p2
unsigned long tsp2 = 0;// startup time for p2

while(!(p1FS || p2FS) && !cancelled && !(p1End && p2End))
{
  // Running.
  t1 = millis();
  readButtons(); 
  p1End = buttons[S5] || p1End;
  p1Start = !buttons[S7] || p1Start;
  p2End = trainning?true:(buttons[S6] || p2End);
  p2Start = trainning?true:(!buttons[S8] || p2Start);
  
  cancelled = buttons[S2];
  unsigned long diff = (t1-t0);
  if(!p1Start) tsp1 = diff;
  if(!p1End) tp1 = diff/10;
  if(!p2Start) tsp2 = diff;
  if(!p2End) tp2 = diff/10;

  if(trainning)
  {
    module.setDisplayToDecNumber(tp1*10000+tsp1,0x48,true);
  }else{
    module.setDisplayToDecNumber(tp1*10000+tp2,0x44,true); 
  } 

  if(cancelled) break;
}

// 4. Display results, wait for the judge to clear.
// Shows "P1 FS" or "P2 FS" in case of false start.
if(p1FS || p2FS)
{
  if (p1FS) module.setDisplayToString("P1  FS  ");
  if (p2FS) module.setDisplayToString("P2  FS  ");
  if (p1FS && p2FS) module.setDisplayToString("P1 P2 FS");
}
// Shows "..." if judge cancelled the run.
else if(cancelled)
{
  module.setDisplayToString("--------");
}
else
{
  LEDs = 0x00;
  if(trainning)
  {
    module.setDisplayToDecNumber(tp1*10000 + tsp1, 0x48, true);
    LEDs = 0x55;
  }else{
    module.setDisplayToDecNumber(tp1*10000 + tp2, 0x44, true);
    LEDs = 0x00;
    if(tp1 < tp2)
    {
      LEDs = 0x0F;
    }
    else if( tp2 < tp1 )
    {
      LEDs  = 0xF0;
    }
    else
    {
      LEDs = 0xAA;
    }
  }
  module.setLEDs(LEDs);
}

// 5. Wait reset.
while(1){
  readButtons();
  if(buttons[S3]) break;
  if(!trainning && !p1FS && !p2FS && !cancelled)
  {
    if(buttons[S4])
    {
      module.setDisplayToDecNumber(tsp1*10000 + tsp2, 0x88, true);
    }else{
      module.setDisplayToDecNumber(tp1*10000 + tp2, 0x44, true);
    } 
  }
  //delay(200);
}
setup();
}
