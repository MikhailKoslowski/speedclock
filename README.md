# speedclock
Clock for speed climibing training and competition

Versão em português em: LEIAME.md

# Description
Speed climbing is one of the 3 modalities of climbing competition that will be on the olympics starting from Tokyo.
Each round of speed climbing consists of two climbers running against each other on a standard wall, they are timed and the one who reaches the end first wins.
[Example (YT video)](https://www.youtube.com/watch?v=y9ZQj3758mw&t=14m00s)

The whole set of rules can be found [here](https://www.ifsc-climbing.org/index.php/world-competition/rules)

In order to train for competitions, athletes must have a wall as close as possible to the standard and an accurate timing device.
Official walls, holds and clocks are quite expensive for athletes, specially on countries where climbing isn't popular.

This project aims to design a clock that:
- Adheres to the IFSC rules
- Is precise to at least 1ms
- Is low cost
- Is easy to implement/deploy by someone with little soldering and electronics skills

# Motivation
In the gym that I climb there was a speed training wall that was built on a cooperation between some athletes that bought the hold, the gym owners that yielded wall area and the trainer that assembled the wall according to the specs and was coaching the athletes.
Sometimes I would stop by and help them belaying and timing with a regular stopwatch.
After understanding their needs I tought about it for a few days, bought the parts, built the first prototype and we installed at the gym.
Then we iterate for a few sessions to understand what could be better and finished this version.

It was then used for several climbers for training and also used on regional and national oficial competitions held by [ABEE](https://abee.com.br/).

I'm currently working on a smaller version for another gym and documenting everything in the case someone else wants to build their own.

Should you have any question feel free to open an issue or send me an email: mikhail.koslowski@gmail.com

# Versions
Currently there is only one version on the master branch.
It is based on the TM1638 module and supports 1 lane on trainning mode and 2 lanes on competition mode

# Features
- Single lane trainnig mode
- Dual lane competition mode
- Compute and displays reaction time
- False start detection

# Known issues
- Noises/Glitches on the buttons (foot and hand) is probably being picked up by long cables. I'm currently testing an optocoupler module to solve that. Alternatively one can use batteries or test several power supplies and wall outlets to find one that does not glitch.
- If both athletes false starts, the software currently picks the first one.

# To do
- Schematic diagram
- Block diagram
- User manual
- Measure timing using an osciloscope on several boards of the same model and of different models to ensure the correct compensations needed on software.

# Dependencies
- TM1638 library, testes with v2.2.0: https://github.com/rjbatista/tm1638-library 

# Design decisions
## Arduino
- It is easy to program, to flash and test.
- Comes in several different models/boards, most compatible with the same source code.
- Have an extensible ecosystem of modules and libraries, making it easy to develop
- low power consumption, thus requiring a cheaper power supply
- low overall cost

## TM1638
Since this modules already comes with 8x 7-segment displays + 8x leds + 8x keys, it has everything needed for the project and was a natural choice.
The fact that the display is small prevent the viewers from checking the time live, but it is a compromise that we are ok with.

# Materials
- Arduino. Any model with 3 free IOs should work. Currently tested with: attiny85 (digispark), atmega328 (nano, uno and micro), atmega324 (leonardo and promicro)
- TM1638 module
- Pedals (2 for each lane). The prototype uses [KH-8012](https://www.jng.com.br/produtos-detalhes.asp?idprod=57) and it held really well although being plastic. In a single competition there was around 120 rounds on the same pedal and it never failed or broke.
- Jump wires for connecting boards
- Shielded cable for the pedals. There should be enough cable, around 10m for the foot pedals and 20~25m for the hand pedals.
- Connectors. The prototype uses XLR connectors, but you can choose any other depending on the need for assembly/disassembly and where it will be installed.
- Enclosures. The prototype uses [PB112](http://www.patola.com.br/index.php?route=product/product&product_id=90) hand cut/drilled. Boards were hot glued in place.
- For the power supply a USB phone charger was used. The Nano board supplied power to the rest of the system.