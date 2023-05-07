/**********************************************************************************/
/* Author : Saied Kamara

/* SWC:     CAN
/* Version: V01
/***********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MCP2515T_interface.h"
#include "MCP2515T_private.h"

#include "SPI_interface.h"

u8 MCP2515_u8ReadRegister(u8 Copy_u8address){
	u8 ReadValue=0;
	u8 value=0;
	MSPI1_voidSendReciveSynchronus(MCP2515_INST_READ,&value); //Send Read instruction
	MSPI1_voidSendReciveSynchronus(Copy_u8address,&value); //send register address
	MSPI1_voidSendReciveSynchronus(0b00000011,&ReadValue); //read value of register
	return ReadValue;
}

void MCP2515_voidWriteRegister(u8 Copy_u8address, u8 Copy_u8RegisterValue){
	u8 value=0;
	MSPI1_voidSendReciveSynchronus(MCP2515_INST_WRITE,&value); //Send Write instruction
	MSPI1_voidSendReciveSynchronus(Copy_u8address,&value); //send register address
    MSPI1_voidSendReciveSynchronus(Copy_u8RegisterValue,&value); //send value of register
}

void MCP2515_voidResetRegister(u8 Copy_u8address){
	u8 value=0;
	MSPI1_voidSendReciveSynchronus(MCP2515_INST_RESET,&value); //Send Write instruction
	MSPI1_voidSendReciveSynchronus(Copy_u8address,&value); //send register address
}

void MCP2515_voidModifyBitRegister(u8 Copy_u8address, u8 Copy_u8ByteMASK,u8 Copy_u8Value){
	u8 value=0;
	MSPI1_voidSendReciveSynchronus(MCP2515_INST_MODIFY,&value); //Send Modify bit instruction
	MSPI1_voidSendReciveSynchronus(Copy_u8address,&value); //send register address
    MSPI1_voidSendReciveSynchronus(Copy_u8ByteMASK,&value); //send value of MASK
    MSPI1_voidSendReciveSynchronus(Copy_u8Value,&value);  //send new value of bit
}


void MCP2515_voidSetBitTiming(u8 Copy_u8CNF1VAL ,u8 Copy_u8CNF2VAL,u8 Copy_u8CNF3VAL){
MCP2515_voidWriteRegister(CNF1,Copy_u8CNF1VAL); //Write CNF registers' Values
MCP2515_voidWriteRegister(CNF2,Copy_u8CNF2VAL);
MCP2515_voidWriteRegister(CNF3,Copy_u8CNF3VAL);

}

void MCP2515_voidSetMode(u8 Copy_u8Mode){
	u8 Timeout=0;
		MCP2515_voidModifyBitRegister(CANCTRL,0xE0,(Copy_u8Mode<<5)); //Set required mode in last 3 bits(REQOP) of CANCTRL
		/* Check mode is written correctly */
		while(MCP2515_u8ReadRegister(CANSTAT>>5) != Copy_u8Mode){
			Timeout++;
			if(Timeout == 10000){
				Timeout=0;
				break;
			}
			else{
				//return error
			}
		}
}

void MCP2515_voidInit(){
	/* Init SPI */
	MSPI1_voidInit();
	/* Reset MCP */
	MCP2515_voidReset();
	/*Enter confiuration Mode  and enable CAN clk*/
	MCP2515_voidWriteRegister(CANCTRL,0x84);

	/*SET bit timing */
	MCP2515_voidSetBitTiming(0x80,0xB1,0x05);

	/*Get back to normal Mode */
	MCP2515_voidSetMode(MCP2515_MODE_Normal);
}

void MCP2515_voidSendMessage(u8 Copy_u8BufferNum ,u32 Copy_u8MsgID ,u8 Copy_u8DLC , u8 *Copy_pu8Data ){
	u8 temp=0;
	/* Only one write instruction as for each write the register address is automatically incremented by MCP */
	MSPI1_voidSendReciveSynchronus(MCP2515_INST_WRITE,&temp); //Send Write instruction
	MSPI1_voidSendReciveSynchronus(TXB0CTRL,&temp); //send register address
	MSPI1_voidSendReciveSynchronus(0x03,&temp);     //write on TXB0CTRL a priorty of "Highest"
	MSPI1_voidSendReciveSynchronus((u8)(Copy_u8MsgID>>3),&temp);     //write on TXB0SIDH higher side of ID
	MSPI1_voidSendReciveSynchronus((u8)(Copy_u8MsgID<<5),&temp);     //write on TXB0SIDL Lower side of ID
	MSPI1_voidSendReciveSynchronus(0,&temp); //Write 0 ( no ID extention ) on TXB0EID8 and TXB0EID0
	MSPI1_voidSendReciveSynchronus(0,&temp);
	MSPI1_voidSendReciveSynchronus(Copy_u8DLC,&temp); //Write Data length code on TXB0DLC and RTR=0 for Data frame
	/* Send Data */
	for (u8 TempCounter =0 ; TempCounter<8 ; TempCounter++){
		MSPI1_voidSendReciveSynchronus(Copy_pu8Data[TempCounter],&temp);
	}
	MSPI1_voidSendReciveSynchronus(MCP2515_INST_RTSB0,&temp); //Request to Send on the buffer
}
