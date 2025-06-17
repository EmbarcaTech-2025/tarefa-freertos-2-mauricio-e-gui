#include <stdio.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "display.h"


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

    //init display
    display_init();

    //Init Joystick
    init_joystick_adc(); 
    //Init FreeRTOS
    xTaskCreate(blink_task, "Blink", 256, NULL, 1, NULL);
    xTaskCreate(vDisplayTask, "Blink", 256, NULL, 1, NULL);    //Task, name, quantidade_max_recursos?,?, prioridade, handler
    vTaskStartScheduler();                                  // Inicia agendador   
                          
    
    stdio_init_all();  
                   
    while (true) {

    }
}
