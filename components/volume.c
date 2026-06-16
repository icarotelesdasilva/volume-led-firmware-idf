#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "volumev.h"

// Implementação da inicialização do hardware
void inicializar_hardware(void) {
    // 1. Configura o Botão como entrada com Pull-up interno
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // 2. Configura o Timer do PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = PWM_MODO,
        .timer_num        = PWM_TIMER,
        .duty_resolution  = PWM_RES,
        .freq_hz          = PWM_FREQ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // 3. Configura o Canal do PWM e liga ao pino do LED
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = PWM_MODO,
        .channel        = PWM_CANAL,
        .timer_sel      = PWM_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LED_PIN,
        .duty           = VOL_DESLIGADO,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

// Implementação da lógica de clique e troca de volume
void alterar_volume(ControleVolume *vol) {
    int leitura = gpio_get_level(BUTTON_PIN);

    // Se detectou o clique (borda de descida)
    if (leitura == 0 && vol->estado_botao == 0) {
        vol->estado_botao = 1;

        // Máquina de estados dos níveis de volume
        if (vol->nivel_atual == VOL_DESLIGADO) {
            vol->nivel_atual = VOL_FRACO;
        } else if (vol->nivel_atual == VOL_FRACO) {
            vol->nivel_atual = VOL_MEDIO;
        } else if (vol->nivel_atual == VOL_MEDIO) {
            vol->nivel_atual = VOL_FORTE;
        } else {
            vol->nivel_atual = VOL_DESLIGADO;
        }

        // Atualiza o brilho do LED
        ledc_set_duty(PWM_MODO, PWM_CANAL, vol->nivel_atual);
        ledc_update_duty(PWM_MODO, PWM_CANAL);

        // Debounce (espera 150ms)
        vTaskDelay(pdMS_TO_TICKS(150));

    } else if (leitura == 1) {
        vol->estado_botao = 0; // Botão foi solto
    }
}
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "volumev.h"

// Implementação da inicialização do hardware
void inicializar_hardware(void) {
    // 1. Configura o Botão como entrada com Pull-up interno
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // 2. Configura o Timer do PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = PWM_MODO,
        .timer_num        = PWM_TIMER,
        .duty_resolution  = PWM_RES,
        .freq_hz          = PWM_FREQ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // 3. Configura o Canal do PWM e liga ao pino do LED
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = PWM_MODO,
        .channel        = PWM_CANAL,
        .timer_sel      = PWM_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LED_PIN,
        .duty           = VOL_DESLIGADO,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

// Implementação da lógica de clique e troca de volume
void alterar_volume(ControleVolume *vol) {
    int leitura = gpio_get_level(BUTTON_PIN);

    // Se detectou o clique (borda de descida)
    if (leitura == 0 && vol->estado_botao == 0) {
        vol->estado_botao = 1;

        // Máquina de estados dos níveis de volume
        if (vol->nivel_atual == VOL_DESLIGADO) {
            vol->nivel_atual = VOL_FRACO;
        } else if (vol->nivel_atual == VOL_FRACO) {
            vol->nivel_atual = VOL_MEDIO;
        } else if (vol->nivel_atual == VOL_MEDIO) {
            vol->nivel_atual = VOL_FORTE;
        } else {
            vol->nivel_atual = VOL_DESLIGADO;
        }

        // Atualiza o brilho do LED
        ledc_set_duty(PWM_MODO, PWM_CANAL, vol->nivel_atual);
        ledc_update_duty(PWM_MODO, PWM_CANAL);

        // Debounce (espera 150ms)
        vTaskDelay(pdMS_TO_TICKS(150));

    } else if (leitura == 1) {
        vol->estado_botao = 0; // Botão foi solto
    }
}
