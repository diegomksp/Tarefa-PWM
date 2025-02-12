# README - Controle de Servo Motor com Raspberry Pi Pico

## Descrição
Este projeto controla um servo motor usando um Raspberry Pi Pico. O código configura um sinal PWM na GPIO 22 para mover o servo motor entre as posições de 0° a 180° de forma contínua.

## Hardware Necessário
- Raspberry Pi Pico
- Servo motor (exemplo: SG90)
- Fonte de alimentação adequada para o servo motor
- Fios de conexão

## Conexão do Servo Motor
- **VCC** do servo ao **3.3V ou 5V** do Raspberry Pi Pico (dependendo do modelo do servo)
- **GND** do servo ao **GND** do Raspberry Pi Pico
- **Sinal (PWM)** do servo à **GPIO 22** do Raspberry Pi Pico

## Como Funciona
1. O código configura a GPIO 22 para gerar um sinal PWM.
2. A posição inicial do servo é definida no centro (90°).
3. O servo se move para 180°, depois volta para 90° e, em seguida, para 0°.
4. O loop principal oscila o servo entre 0° e 180° continuamente com passos de 50 unidades PWM e um pequeno delay para suavizar o movimento.

## Compilação e Execução
1. Instale o **Raspberry Pi Pico SDK** e configure seu ambiente de desenvolvimento no **Visual Studio Code**.
2. Compile o programa utilizando **CMake** e **Make**.
3. Carregue o binário gerado no Raspberry Pi Pico.
4. Conecte o servo motor conforme descrito e execute o programa.

## Ajustes Possíveis
- Alterar os valores de **SERVO_MIN**, **SERVO_MID** e **SERVO_MAX** para calibrar os limites do servo.
- Modificar **SERVO_STEP** para aumentar ou reduzir a velocidade do movimento.
- Ajustar **PWM_DIVISOR** e **wrap** caso utilize uma frequência PWM diferente.

## Licença
Este projeto é de uso livre para fins educacionais e experimentação.

## Demonstração
https://youtube.com/shorts/XXPFORQckoc?si=5L9jszZ9pxvdHL4w

