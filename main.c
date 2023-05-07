/**********************************************************************************/
/* Author : Saied Kamara
/* Version: V01
/***********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

#include "SPI_interface.h"
#include <MCP2515R_interface.h>

/*You Can Use your own SPI driver but make sure to replace its TransmitRecive function with
 * MSPI1_voidSendReciveSynchronus(u8 Copy_u8DataToTransmit , u8 * Copy_pu8DataToRecive)
 */
/* No ID extention is used in this driver */
/* you can check RCC_config.h for further clock configuraion */
/* This MCP driver is designed to operate at 8MHZ external clock */

extern u8 RecivedArray[14]; //extern the recived buffer

void main (void){
  RCC_voidInitSysClock();      //initalize System clock = 8MHZ
  RCC_voidEnableClock(RCC_APB2,2);    /* GPIOA */
  RCC_voidEnableClock(RCC_APB2,12);   /* SPI1  */

  GPIO_voidSetPinDirection(GPIOA,0,OUTPUT_SPEED_2MHZ_PP);    // set A0 to be SlaveSelect pin
  GPIO_voidSetPinDirection(GPIOA,1,INPUT_PULL);              // set A1 to be Interrupt pin
  GPIO_voidSetPinDirection(GPIOA,5,OUTPUT_SPEED_10MHZ_AFPP); // set A5 to be AF of SPI clk
  GPIO_voidSetPinDirection(GPIOA,7,OUTPUT_SPEED_10MHZ_AFPP); // set A7 to be AF of SPI MOSI
  GPIO_voidSetPinDirection(GPIOA,7,OUTPUT_SPEED_10MHZ_AFPP); // set A6 to be AF of SPI MISO

  /*    Receive Example   */
  /*
   MCP2515_voidReciveInit();
   u8 Data[8];
   while(1){

 if(GPIO_voidGetPinValue(GPIOA,1) == 0){
 for (u8 i=0 ; i <8 ; i++){
 Data[i]=RecivedArray[i+6]
 }
 }
 }
   */



}
