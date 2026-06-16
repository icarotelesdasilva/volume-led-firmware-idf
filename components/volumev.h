#ifndef VOLUMEV_H
#define VOLUMEV_H

#include "driver/ledc.h"
#include "driver/gpio.h"

// Definição das GPIOs
#define LED_PIN       GPIO_NUM_2
#define BUTTON_PIN    GPIO_NUM_23

// Configurações do PWM nativo (LEDC)
#define PWM_FREQ      5000
#define PWM_CANAL     LEDC_CHANNEL_0
#define PWM_RES       LEDC_TIMER_8_BIT
#define PWM_MODO      LEDC_LOW_SPEED_MODE
#define PWM_TIMER     LEDC_TIMER_0

// Níveis de "Volume" (Duty Cycle de 0 a 255)
#define VOL_DESLIGADO 0
#define VOL_FRACO     30
#define VOL_MEDIO     120
#define VOL_FORTE     255

// Estrutura para controle de estado
typedef struct {
    int nivel_atual;
    int estado_botao;
} ControleVolume;

// Declaração das funções (os protótipos)
void inicializar_hardware(void);
void alterar_volume(ControleVolume *vol);

#endif // VOLUMEV_H
