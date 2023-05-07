/**********************************************************************************/
/* Author : Saied Kamara
/* SWC:     CAN
/* Version: V01
/***********************************************************************************/
#ifndef MCP2515T_INTERFACE_H
#define MCP2515T_INTERFACE_H

/*Define Instructions used in registers */
#define MCP2515_INST_WRITE   0x02
#define MCP2515_INST_READ    0x03
#define MCP2515_INST_RESET   0xC0
#define MCP2515_INST_MODIFY  0x05
#define MCP2515_INST_RTSB0   0x81
#define MCP2515_INST_RTSB1   0x82
#define MCP2515_INST_RTSB2   0x84

/*Define CAN modes of operation */
#define MCP2515_MODE_Config 0x4
#define MCP2515_MODE_Normal 0x0


/* Function declaration */
void MCP2515_voidInit();
void MCP2515_voidSendMessage(u8 Copy_u8BufferNum ,u32 Copy_u8MsgID ,u8 Copy_u8DLC , u8 *Copy_pu8Data );

#endif
