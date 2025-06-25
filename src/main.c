#include <stdio.h>
#include "pico/stdlib.h"
#include "joystick.h"


#define RGB_LED_G 11

void blink_task(void *params) {
    const uint LED_PIN = RGB_LED_G;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_put(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void joystick_oled_task(void *params) {
    uint16_t x_read, y_read;
    uint8_t x_pos = 64; // centro X (128/2)
    uint8_t y_pos = 32; // centro Y (64/2)

    display_init();

    while (1) {
        x_read = get_average_reading(0); // X = ADC0
        y_read = get_average_reading(1); // Y = ADC1

        // Aplica zona morta (opcional)
        x_read = apply_dead_zone(x_read);
        y_read = apply_dead_zone(y_read);

        // Mapeia para coordenadas da tela
        x_pos = (x_read * 128) / 4095;
        y_pos = (y_read * 64) / 4095;

        // Limpa e desenha
        display_clear();
        draw_pixel(x_pos, y_pos, true);
        render();

        vTaskDelay(pdMS_TO_TICKS(100)); // delay FreeRTOS
    }
}


int main()
{
    stdio_init_all();
    init_joystick_adc();

    // Cria as duas tasks
    xTaskCreate(blink_task, "Blink", 256, NULL, 1, NULL);
    xTaskCreate(joystick_oled_task, "JoyOLED", 512, NULL, 1, NULL);

    vTaskStartScheduler(); // Inicia o agendador

    // Não será mais executado
    while (true) {}
}
