#include "ssd1306.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "string.h"
#include "FreeRTOS.h"
#include "../FreeRTOS-Kernel/include/task.h"
#include "../FreeRTOS-Kernel/include/queue.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

extern QueueHandle_t joystickQueue;

static int x = 0, y = 0;

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

uint8_t ssd[ssd1306_buffer_length];

void init_display(){
        // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    memset(ssd, 0, ssd1306_buffer_length);
}


void move_cursor(Direction dir) {
    switch (dir) {
        case UP:    y--; break;
        case DOWN:  y++; break;
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        default: break;
    }

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > MAX_X) x = MAX_X;
    if (y > MAX_Y) y = MAX_Y;
}

void vDisplayTask(void *pvParameters) {
    JoystickEvent evt;
    while (1) {
        if (xQueueReceive(joystickQueue, &evt, portMAX_DELAY)) {
            move_cursor(evt.dir);
            draw_point(x, y);
        }
    }
}







