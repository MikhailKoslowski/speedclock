# speedclock
Relógio para treino e competição de escalada de velocidade.

In english at: README.md

# Description
Escalada de velocidade é uma das 3 modalidades de competição que estará nas olimpíadas a partir de Tokio.
Cada rodada é composta de dois escaladores competindo um contra o outro em uma parede padronizada, quem faz o menor tempo ganha.
[Exemplo (YouTube)](https://www.youtube.com/watch?v=y9ZQj3758mw&t=14m00s)

As regras oficiais da competição podem ser encontradas [aqui](https://www.ifsc-climbing.org/index.php/world-competition/rules)

Para treinar para as competições os atletas devem ter uma parede o mais próximo possível da oficial e um cronômetro preciso.
Uma parede oficial, as agarras oficiais e o relógio oficial são muito caros para um atleta, especialmente em países onde a escala ainda não é popular.

Este projeto tem por objetivo um relógio que:
- Atenda as regras da IFSC
- Seja preciso em pelo menos 1ms
- Seja de baixo custo
- Seja fácil de montar/instalar por alguém com o mínimo de habilidades em solda e eletrônica.

# Motivação
Na academia onde eu escaldo havia uma parede de velocidade montada em conjunto pelos atletas que forneceram as agarras, a academia que destinou uma área da parede específica para isso e o treinador que montou a parede de acordo com a especificação e orientava os atletas.
Algumas vezes parei para ajudá-los durante os treinos auxiliando na segurança e na temporização com cronômetros comuns.
Depois de entender um pouco as necessidades e os problemas, pensei por uns dias, comprei alguns componentes e montei o primeiro protótipo.
Então fizemos algumas iterações para melhorar e finalizar uma versão.

Desde lá este relógio foi utilizado por diversos atletas para treinos e em algumas competições regionais e nacionais da [ABEE](https://abee.com.br/).

Estou atualmente trabalhando em uma versão reduzida para uma outra academia que montou uma parede de velocidade e documentando tudo para o caso de alguém querer montar o seu próprio relógio.

Caso tenha alguma dúvida fique a vontade para entrar em contato por email: mikhail.koslowski@gmail.com

# Versões
Atualmente há uma única versão disponível no branch master.
Esta versão é baseada no módulo TM1638 e tem suporte a uma pista em modo treino e duas pistas em modo competição.

# Funcionalidades
- Modo de treino individual (uma pista)
- Modo de competição (duas pistas)
- Medição do tempo de reação
- Detecção de largada queimada

# Problemas conhecidos
- Ruídos provavelmente captados nos cabos dos pedais causam ativação espúria dos mesmos. Estou testando um módulo de opto-acopladores para resolver esta questão. Uma alternativa é alimentar tudo por baterias ou testar diversas tomadas e fontes para encontrar uma que não sofra com os ruídos.
- Se os dois atletas causarem queima de largada apenas o primeiro deles será apontado.

# Atividades a serem feitas
- Diagrama esquemático
- Diagrama em blocos
- Manual/Guia do usuário
- Medir a temporização de várias placas iguais e diferentes utilizando um osciloscópio para garantir as corretas compensações em software.

# Dependências
- Biblioteca para TM1638, Testado com a versão v2.2.0: https://github.com/rjbatista/tm1638-library  

# Decisões de projeto
## Arduino
- Fácil de programar, gravar e testar.
- Disponível em diversos modelos e placas, a maioria compatível com o mesmo código fonte.
- Extensa disponibilidade de módulos e bibliotecas, facilitando o desenvolvimento.
- Baixo consumo, por consequência requer uma fonte também de baixo custo.
- Baixo custo no geral.

## TM1638
Como este módulo já possui 8 displays de 7-segmentos, 8 leds e 8 teclas, já possui tudo o que é necessário para o projeto e foi uma escolha natural.
O fato do display ser pequeno impede que a plateia acompanhe o tempo ao vivo, porém é uma escolha que foi feita em prol de simplificar o projeto.

# Materiais
- Arduino. Qualquer modelo com pelo menos 3 pinos de IO deve servir. Testado com: attiny85 (digispark), atmega328 (nano, uno e micro), atmega324 (leonardo e promicro)
- Módulo TM1638
- Pedais (2 para cada pista). O protótipo usa o [KH-8012](https://www.jng.com.br/produtos-detalhes.asp?idprod=57) e ele aguentou muito bem apesar de ser plástico. Em uma única competição realizamos mais de 120 rodadas sem qualquer falha ou quebra.
- Cabinhos "jump" para conectar as placas
- Cabos blindados para os pedais, cerca de 10m para os de largada e 20~25m para os de chegada.
- Conectores. O protótipo usa XLR, mas qualquer conector que atenda as necessidades de montagem/desmontagem e do local onde será instalado é suficiente.
- Caixas. O protótipo usa [PB112](http://www.patola.com.br/index.php?route=product/product&product_id=90) cortadas e furadas a mão, as placas foram fixadas com cola-quente.
- A fonte de alimentação utilizada é um carregador de celuar USB. a placa Nano fornece a energia para o resto do sistema.