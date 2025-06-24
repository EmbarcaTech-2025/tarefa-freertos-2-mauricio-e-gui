#include "buzzer.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "comunicacao.h"

static uint pwm_slice;

void buzzer_init(void)
{
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    pwm_slice = pwm_gpio_to_slice_num(PWM_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, PWM_WRAP);
    pwm_config_set_clkdiv(&config, 1.f); // Sem divisão de clock
    pwm_init(pwm_slice, &config, false);
}

void buzzer_start(void)
{
    pwm_set_enabled(pwm_slice, true);
}

void buzzer_stop(void)
{
    pwm_set_enabled(pwm_slice, false);
}

void buzzer_play_sample(uint16_t sample)
{
    uint16_t pwm_val = (sample * PWM_WRAP) / 4095;
    pwm_set_chan_level(pwm_slice, PWM_CHAN_A, pwm_val);
}

void buzzer_bip(void *pvParameters)
{
    int recebida;
    buzzer_init();
    buzzer_start();
    while(true){
        if (xQueueReceive(xFilaBuzzer, &recebida, portMAX_DELAY) == pdPASS){
            pwm_set_chan_level(pwm_slice, PWM_CHAN_A, PWM_WRAP / 2); // Toca o buzzer
            vTaskDelay(pdMS_TO_TICKS(recebida));
            pwm_set_chan_level(pwm_slice, PWM_CHAN_A, 0); // Toca o buzzer;
        }
    }

}