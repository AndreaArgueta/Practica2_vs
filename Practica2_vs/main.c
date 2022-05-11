/**
 * main.c
 */

#include "lib/include.h"

int main(void) {
    Configurar_GPIO_K();
    Configurar_GPIO_Q();
    Boton_int();
    while(1U){
    }
}