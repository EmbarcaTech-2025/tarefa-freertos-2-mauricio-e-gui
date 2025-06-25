#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// --- Configurações ---
#define JOY_X 26         // GPIO26 -> ADC0
#define JOY_Y 27         // GPIO27 -> ADC1
#define SAMPLES 10       // Número de amostras para média
#define DEAD_ZONE 50     // Faixa de zona morta para valores pequenos

// --- Inicialização do ADC para joystick ---
void init_joystick_adc(void);

// --- Leitura simples do eixo especificado (canal ADC 0 ou 1) ---
uint16_t read_axis(uint input);

// --- Leitura média de N amostras ---
uint16_t get_average_reading(uint input);

// --- Aplicação de zona morta ---
uint16_t apply_dead_zone(uint16_t value);


#endif