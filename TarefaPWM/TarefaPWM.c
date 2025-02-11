#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_MOTOR 22  // Pino GPIO conectado ao servo motor
#define SERVO_MIN 1000  // Posição mínima do servo (~0 graus)
#define SERVO_MID 2850  // Posição mínima do servo (~90 graus)
#define SERVO_MAX 4620 // Posição mínima do servo (~180 graus)
#define SERVO_STEP 50  // Passo de variação do PWM ao movimentar o servo

uint16_t wrap = 20000;    // Período PWM para 50 Hz (20 ms)
float PWM_DIVISOR = 64.0; // Divisor para gerar a frequência correta

// Configura o PWM no pino especificado
void setPWM(uint16_t intensidade)
{
    gpio_set_function(SERVO_MOTOR, GPIO_FUNC_PWM); // Configura o pino como saída PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_MOTOR); // Obtém o slice do PWM associado ao pino
    pwm_set_clkdiv(slice, PWM_DIVISOR); // Define o divisor de clock do PWM
    pwm_set_wrap(slice, wrap); // Define o valor máximo do contador PWM
    pwm_set_gpio_level(SERVO_MOTOR, intensidade); // Define o nível do PWM (largura do pulso)
    pwm_set_enabled(slice, 1);  // Habilita o PWM
}

// Move o servo para a posição desejada
void move_servo(uint16_t pos)
{
    pwm_set_gpio_level(SERVO_MOTOR, pos); // Define a largura do pulso PWM para a posição desejada
    sleep_ms(50); // Tempo de espera para o servo chegar à posição
}

int main()
{
    stdio_init_all();

    // Inicializa o PWM na posição central
    setPWM(SERVO_MID);
    
    move_servo(SERVO_MAX); //180º
    sleep_ms(5000);
    move_servo(SERVO_MID); //90º
    sleep_ms(5000);
    move_servo(SERVO_MIN); //0º
    sleep_ms(5000);

    // Oscilação contínua entre 0° e 180°
    uint16_t pos = SERVO_MIN;
    int direction = 1;

    while (true)
    { 
        move_servo(pos);

        // Atualiza a posição do servo
        if (direction)
        {
            pos += SERVO_STEP;
            if (pos >= SERVO_MAX)
                direction = 0;
        }
        else
        {
            pos -= SERVO_STEP;
            if (pos <= SERVO_MIN)
                direction = 1;
        }
        sleep_ms(10); // Pequeno delay para suavizar o movimento
    }
}
