#include "buzzer.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "comunicacao.h"

#define NOTE_E 659
#define NOTE_F 698
#define NOTE_G 784
#define NOTE_D 587
#define NOTE_C 523

extern QueueHandle_t xFilaBuzzer;

const Nota mario_melodia[] = {
    {NOTE_E, 150}, {NOTE_E, 150}, {NOTE_F, 150}, {NOTE_G, 150},
    {NOTE_G, 150}, {NOTE_F, 150}, {NOTE_E, 150}, {NOTE_D, 150},
    {NOTE_C, 150}, {NOTE_C, 150}, {NOTE_D, 150}, {NOTE_E, 150},
    {NOTE_E, 150}, {NOTE_D, 150}, {NOTE_D, 150}
};

const int total_notas = sizeof(mario_melodia) / sizeof(Nota);

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

void tocar_frequencia(uint buzzer_pin, uint16_t freq, uint16_t duracao_ms) {
    gpio_set_function(buzzer_pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(buzzer_pin);

    uint32_t clock_freq = 125000000;
    uint32_t top = 12500;
    float div = (float)clock_freq / (top * freq);
    if (div < 1.0f) div = 1.0f;

    pwm_set_wrap(slice, top);
    pwm_set_clkdiv(slice, div);
    pwm_set_chan_level(slice, PWM_CHAN_A, top / 2);
    pwm_set_enabled(slice, true);
    sleep_ms(duracao_ms);
    pwm_set_enabled(slice, false);
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

void buzzer_bip(void *pvParameters) {
    const uint BUZZER_PIN = PWM_PIN;
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    Nota evento;

    while (1) {
        if (xQueueReceive(xFilaBuzzer, &evento, portMAX_DELAY) == pdPASS) {
            if (evento.frequencia == -1) {
                for (int i = 0; i < total_notas; i++) {
                    tocar_frequencia(BUZZER_PIN, mario_melodia[i].frequencia, mario_melodia[i].duracao_ms);
                    sleep_ms(30);
                }
            } else {
                tocar_frequencia(BUZZER_PIN, evento.frequencia, evento.duracao_ms);
            }
        }
    }
}
