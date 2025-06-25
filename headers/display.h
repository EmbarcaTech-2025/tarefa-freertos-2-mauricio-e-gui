#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "task.h"
#include "queue.h"
#include "joystick.h"
#include "comunicacao.h"
#include "FreeRTOS.h"
#include "queue.h"

#define ssd1306_width 128
#define ssd1306_height 64

#define ssd1306_i2c_clock 400


// Configuração dos pinos I2C
#define I2C_SDA 14
#define I2C_SCL 15

typedef struct {
    uint8_t x;
    uint8_t y;
} Coordenada;


void display_init();

// Tarefa RTOS
void vDisplayTask(void *pvParameters);

// Limpa o display
void display_clear();

#endif