#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_MOTOR 22
#define SERVO_MIN 1000 // Aproximadamente 0.5 ms (0 graus)
#define SERVO_MID 2850 // 90 graus
#define SERVO_MAX 4620 // Aproximadamente 2.5 ms (180 graus)
#define SERVO_STEP 50  // Passo de variação do PWM

uint16_t wrap = 20000;    // Período PWM para 50 Hz (20 ms)
float PWM_DIVISOR = 64.0; // Divisor para gerar a frequência correta

void setPWM(uint16_t intensidade)
{
    gpio_set_function(SERVO_MOTOR, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_MOTOR);
    pwm_set_clkdiv(slice, PWM_DIVISOR);
    pwm_set_wrap(slice, wrap);
    pwm_set_gpio_level(SERVO_MOTOR, intensidade);
    pwm_set_enabled(slice, 1);
}

void move_servo(uint16_t pos)
{
    pwm_set_gpio_level(SERVO_MOTOR, pos);
    sleep_ms(50); // Tempo de espera para o servo chegar à posição
}

int main()
{
    stdio_init_all();

    // Inicializa o PWM na posição central
    setPWM(SERVO_MID);
    
    move_servo(SERVO_MAX);
    sleep_ms(5000);
    move_servo(SERVO_MID);
    sleep_ms(5000);
    move_servo(SERVO_MIN);
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
