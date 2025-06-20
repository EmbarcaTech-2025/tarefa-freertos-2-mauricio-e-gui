#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306_i2c.h"

// Configuração dos pinos I2C
#define I2C_SDA 14
#define I2C_SCL 15

// Inicializa o display OLED
void display_init();

// Limpa o display
void display_clear();

// Desenha um pixel na posição (x, y)
void draw_pixel(uint8_t x, uint8_t y, bool color);

// Renderiza o buffer atual na tela
void render(void);

#endif