#include <stdio.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "hardware/adc.h"

#define JOY_X 26 // GPIO26 -> ADC0
#define JOY_Y 27 // GPIO27 -> ADC1
#define SAMPLES 10 // Número de amostras para a média
#define DEAD_ZONE 50 // Zona morta para o repouso (em torno do valor médio)

void init_joystick_adc() {
    adc_init();
    adc_gpio_init(JOY_Y); // canal 0
    adc_gpio_init(JOY_X); // canal 1
}

uint16_t read_axis(uint input) {
    adc_select_input(input);
    return adc_read(); // 0 a 4095
}

uint16_t get_average_reading(uint input) {
    uint32_t sum = 0;
    for (int i = 0; i < SAMPLES; i++) {
        sum += read_axis(input);
        sleep_ms(10); // Delay pequeno entre as leituras
    }
    return sum / SAMPLES;
}

uint16_t apply_dead_zone(uint16_t value) {
    // Se o valor estiver dentro da zona morta, consideramos o valor como repouso
    if (value < DEAD_ZONE) {
        return 0;
    }
    return value;
}

