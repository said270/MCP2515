/**********************************************************************************/
/* Author : Saied Kamara
/* SWC:     CAN
/* Version: V01
/***********************************************************************************/
#ifndef MCP2515T_PRIVATE_H
#define MCP2515T_PRIVATE_H

/*Instruction Functions Declaration */
extern u8 MCP2515_u8ReadRegister(u8 Copy_u8address);
extern void MCP2515_voidWriteRegister(u8 Copy_u8address, u8 Copy_u8RegisterValue);
extern void MCP2515_voidResetRegister(u8 Copy_u8address);
extern void MCP2515_voidModifyBitRegister(u8 Copy_u8address, u8 Copy_u8ByteMASK,u8 Copy_u8Value);

/* Registers Defenitions */
#define CNF1         0x2A
#define CNF2         0x29
#define CNF3         0x28
#define CANCTRL      0xF0
#define CANSTAT      0xE0

/* RX buffers register*/
#define RXB0CTRL     0x60
#define CANINTE      0x2B
#define CANINTF      0x2C
#endif
