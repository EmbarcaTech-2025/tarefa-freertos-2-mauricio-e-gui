
#include <string.h>
#include "../FreeRTOS-Kernel/include/FreeRTOS.h"
#include "../FreeRTOS-Kernel/include/queue.h"
#include <stdio.h>
#include "comunicacao.h"
#include "display.h"


// Buffer para o display
static uint8_t ssd[ssd1306_buffer_length];

// Área de renderização
static struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1};


void display_clear()
{
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}

void display_init()
{
    // Inicialização do I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display
    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    display_clear();
}



void vDisplayTask(void *pvParameters) {
    display_init();
    Coordenada recebida;    
    while (1) {
        if (xQueueReceive(xFila, &recebida, portMAX_DELAY) == pdPASS){
            ssd1306_set_pixel(ssd,recebida.x,recebida.y,true);
            render_on_display(ssd,&frame_area);
        }
        
    }
}