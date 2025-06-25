# FreeRTOS Joystick + OLED + Buzzer Demo 🎮📟🔊

Este projeto demonstra a integração de periféricos no Raspberry Pi Pico W com FreeRTOS, onde um jogador controla um cursor com um joystick para acertar um ponto aleatório em um display OLED. Ao acertar o ponto, um buzzer toca uma nota da melodia do Mario. Ao completar a melodia, a música inteira é reproduzida automaticamente.

---

## 🚀 Funcionalidades

- Leitura assíncrona do joystick com fila de eventos.
- Renderização do cursor e alvo no display OLED via protocolo I2C.
- Geração de som com buzzer via PWM.
- Tocar nota por nota ao acertar o alvo.
- Reprodução completa da melodia do Mario ao final.
- Gerenciamento multitarefa com FreeRTOS.

---

## 🧠 Estrutura do Projeto

FreeRTOS/
├── CMakeLists.txt
├── build/                  # Diretório de build
├── drivers/                # Drivers de hardware (display, buzzer, etc)
│   ├── buzzer.c
│   ├── display.c
├── headers/                # Arquivos de cabeçalho
│   ├── buzzer.h
│   ├── display.h
│   ├── comunicacao.h
├── main.c                  # Entrada principal do projeto
└── .vscode/
    └── tasks.json          # Configuração de build e flash no VSCode
