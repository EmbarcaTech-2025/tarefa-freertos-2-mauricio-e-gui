#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "joystick.h"
#include "display.h"
#include "comunicacao.h"



#define RGB_LED_G 11


QueueHandle_t xFila;

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

void joystick_task(void *params) {
    uint16_t x_read, y_read;
    uint8_t x_pos = 64; // centro X (128/2)
    uint8_t y_pos = 32; // centro Y (64/2)
    Coordenada pos = {0, 0};

    while (1) {
        x_read = get_average_reading(0); // X = ADC0
        y_read = get_average_reading(1); // Y = ADC1

        // Aplica zona morta (opcional)
        x_read = apply_dead_zone(x_read);
        y_read = apply_dead_zone(y_read);

        // Mapeia para coordenadas da tela
        x_pos = (x_read * 128) / 4095;
        y_pos = (y_read * 64) / 4095;

        pos.x = x_pos;
        pos.y = y_pos;

        // Envia para a fila
        xQueueSend(xFila, &pos, portMAX_DELAY);

    }
}
int main()
{
    stdio_init_all(); 

    //Init Joystick
    init_joystick_adc(); 

    xFila = xQueueCreate(10, sizeof(Coordenada));
    //Init FreeRTOS
    xTaskCreate(joystick_task, "Joystick", 256, NULL, 1, NULL);
    xTaskCreate(vDisplayTask, "Display", 256, NULL, 1, NULL);    //Task, name, quantidade_max_recursos?,?, prioridade, handler
    vTaskStartScheduler();                                  // Inicia agendador   
                          
                   
    while (true);
}
