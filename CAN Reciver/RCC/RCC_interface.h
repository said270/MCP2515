/**********************************************************************************/
/* Author : Saied Kamara
/* SWC:     RCC
/* Version: V01
/***********************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Bus Macros */
#define RCC_AHB      0
#define RCC_APB1     1
#define RCC_APB2     2

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(u8 Copy_u8BusID , u8 Copy_u8PerID);
void RCC_voidDisableClock(u8 Copy_u8BusID , u8 Copy_u8PerID);

#endif