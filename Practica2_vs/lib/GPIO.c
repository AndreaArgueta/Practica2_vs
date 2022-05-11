/*
 * GPIO.c
 *
 *  k6=Bot�n y q1=led
 *
 *  Created on: 20 abr 2022
 *      Author: andya
 */
#include "include.h"

extern void Configurar_GPIO_K(void)
{
                            // K
        SYSCTL->RCGCGPIO |= (1<<9);
        while((SYSCTL->PRGPIO&0x00000200) == 0){;} // allow time for clock to stabilize (Al relog de RCGCGPIO)
        //Entrada
                        //  K6
        GPIOK->DIR |= (0<<6);
        //Estado alto
        GPIOK->PUR  |= (1<<6);
        //Funciones alternativas
        GPIOK->AFSEL |= 0x00;
        //Tabla con GPIOCTL
        GPIOK->PCTL |= 0x00;
        //Habilitarlos como digitales
        GPIOK->DEN |= (1<<6);
}

extern void Configurar_GPIO_Q(void)
{
                            // Q
        SYSCTL->RCGCGPIO |= (1<<14);
        while((SYSCTL->PRGPIO&0x00004000) == 0){;} // allow time for clock to stabilize (Al relog de RCGCGPIO)
        //Salidas
                        //  Q1
        GPIOQ->DIR |= (1<<1);
        //Funciones alternativas
        GPIOQ->AFSEL |= 0x00;
        //Tabla con GPIOCTL
        GPIOQ->PCTL |= 0x00;
        //Habilitarlos como digitales
        GPIOQ->DEN |= (1<<1);
}

extern void Boton_int(void)
{
    GPIOK->IM |=(0<<6);     //Deshabilitar para configurar
    GPIOK->IS |=(0<<6);     //Detectar bordes
    GPIOK->IBE |=(0<<6);      //Solo 1 borde
    GPIOK->IEV |=(1<<6);    //Bajada o subida -> 0=bajada/nivel bajo  1=subida/nivel alto
    GPIOK->RIS |=(0<<6);      //Limpiarlo
    GPIOK->IM |=(1<<6);     //Habilitar

    // Numero de interrupci�n:52
    // Prioridad=52/4=13
    //[4n+3][4n+2][4n+1][4n]   <- n=prioridad
    //  55    54    53   52
    //  FF    FF    FF   00    <- MASCARA
    // PRIORIDAD MAS ALTA=0, PROPRIDAD MAS BAJA=7
    NVIC->IP[13] = (NVIC->IP[13] & 0xFFFFFF00)|0x80000000;     //Prioridad y mascara
    //NVIC EN1
    NVIC->ISER[1] = 0x100000;
}

extern void blink(void)
{
    uint32_t i;
        if(GPIOK->RIS == (1<<6)){
            i=0;
            GPIOQ->DATA = (1<<1);
            for(i=0;i<1000000;i++){}
            //i=0;
            GPIOQ->DATA = (0<<1);
            //for(i=0;i<1000000;i++){}
        }
        GPIOK->ICR |= (1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
}