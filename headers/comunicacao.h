#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include "FreeRTOS.h"
#include "queue.h"

// Estrutura que será enviada pela fila
typedef struct {
    uint8_t x;
    uint8_t y;
} Coordenada;

// Declaração da fila que será usada entre tasks
extern QueueHandle_t xFila;

#endif // COMUNICACAO_H
