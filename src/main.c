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

int main()
{
    stdio_init_all(); 
    //Init Joystick
    init_joystick_adc(); 
    //Init FreeRTOS
    xTaskCreate(blink_task, "Blink", 256, NULL, 1, NULL);    //Task, name, quantidade_max_recursos?,?, prioridade, handler
    vTaskStartScheduler();                                  // Inicia agendador   
                          
    
    while (true) {
        uint16_t y = get_average_reading(0); // ADC0
        uint16_t x = get_average_reading(1); // ADC1

        // Aplica a zona morta
        x = apply_dead_zone(x);
        y = apply_dead_zone(y);

        printf("Joystick X: %u, Y: %u\n", x, y);
        sleep_ms(200);
    }
}
