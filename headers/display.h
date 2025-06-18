#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "task.h"
#include "queue.h"
#include "joystick.h"

// Configuração dos pinos I2C
#define I2C_SDA 14
#define I2C_SCL 15

// Tarefa RTOS
void vDisplayTask(void *pvParameters);

// Limpa o display
void display_clear();

#endif