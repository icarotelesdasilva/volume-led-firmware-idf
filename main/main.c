#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "volumev.h"

void app_main(void) {
    // Cria e limpa as variáveis da nossa estrutura
    ControleVolume meuVolume = {
        .nivel_atual = VOL_DESLIGADO,
        .estado_botao = 0
    };

    // Chama a função de configuração que está no volume.c
    inicializar_hardware();

    // Loop infinito do FreeRTOS
    while (1) {
        // Monitora o botão e muda o volume continuamente
        alterar_volume(&meuVolume);

        // Descanso de 10ms obrigatório para o sistema operacional do ESP32
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
