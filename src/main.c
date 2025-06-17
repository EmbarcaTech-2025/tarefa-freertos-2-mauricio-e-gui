#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "FreeRTOS-Kernel/include/queue.h"
#include "FreeRTOS-Kernel/include/task.h"

QueueHandle_t joystickQueue;


int main()
{
    stdio_init_all();  
    joystickQueue = xQueueCreate(10, sizeof(int));                          
    while (true) {
        
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
