
#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "TM4C1294NCPDT.h"
#include "GPIO.h"

//Macros: Etiquetas que me dan una cierta instrucción. 
//Direccionamiento en base a apuntadores de programa     
//                                      |Casteo forzado      |  |Registros |
//                                    |Convertir a un apunatador| 
//                                  |Apunto a cierta dir de memoria            
//#define GPIO_PORTF_DATA_R         (*((volatile unsigned long *)0x400253FC))



#endif /* INCLUDE_H_ */
