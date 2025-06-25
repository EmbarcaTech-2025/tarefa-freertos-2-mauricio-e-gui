#include <string.h>
#include "../FreeRTOS-Kernel/include/FreeRTOS.h"
#include "../FreeRTOS-Kernel/include/queue.h"
#include <stdio.h>
#include "comunicacao.h"
#include "display.h"
#include "pico/stdlib.h"
#include "buzzer.h"

extern QueueHandle_t xFila;
extern QueueHandle_t xFilaBuzzer;

static int nota_atual = 0;

// Buffer para o display
static uint8_t ssd[ssd1306_buffer_length];

// Área de renderização
static struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

void display_clear() {
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}

void display_init() {
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    display_clear();
}

Coordenada alvo;

void gerar_alvo_aleatorio() {
    alvo.x = rand() % 128;
    alvo.y = rand() % 64;
}

bool acertou_alvo(Coordenada jogador, Coordenada alvo) {
    return abs(jogador.x - alvo.x) <= 1 && abs(jogador.y - alvo.y) <= 1;
}

void vDisplayTask(void *pvParameters) {
    display_init();
    Coordenada jogador;

    gerar_alvo_aleatorio();

    while (1) {
        if (xQueueReceive(xFila, &jogador, portMAX_DELAY) == pdPASS) {
            memset(ssd, 0, ssd1306_buffer_length);
            ssd1306_set_pixel(ssd, jogador.x, jogador.y, true);
            ssd1306_set_pixel(ssd, alvo.x, alvo.y, true);

            if (acertou_alvo(jogador, alvo)) {
                gerar_alvo_aleatorio();

                Nota nota = mario_melodia[nota_atual];
                xQueueSend(xFilaBuzzer, &nota, 0);

                nota_atual++;
                if (nota_atual >= total_notas) {
                    nota_atual = 0;

                    Nota nota_sinal = { .frequencia = -1, .duracao_ms = 0 };
                    xQueueSend(xFilaBuzzer, &nota_sinal, 0);
                }
            }

            render_on_display(ssd, &frame_area);
        }
    }
}
