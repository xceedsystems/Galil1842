/***************************************************************

                Card.h             

   This file contains the interface to the manufacturer code

****************************************************************/


#ifndef  __CARD_H__
#define  __CARD_H__

int Init( void* const dp, P_ERR_PARAM const lpErrors);
int TestConfig( LPDRIVER_INST const pNet, P_ERR_PARAM const lpErrors);
int	DoCollect( LPDRIVER_INST pNet, LPSPECIAL_INST pData);

///low level read write here !

void    PortGalil( SPECIAL_INST_PORT_GALIL* const pData,  LPDRIVER_INST const pNet);
void    PortGalilTx(SPECIAL_INST_PORT_GALIL_SPLIT* const pData,  LPDRIVER_INST const pNet);
void    PortGalilRx(SPECIAL_INST_PORT_GALIL_SPLIT* const pData,  LPDRIVER_INST const pNet);

void Interactive();
int SendReceive( char str[] );
int SendString(char *str);
char * GetResponse();
int WaitForResponse();
void ClearBuffer();
//void SetAddress(UINT32 addr);
int CheckResponse();

unsigned char dmcInportb (UINT32 portid);
void dmcOutportb(UINT32 portid, unsigned char value);

int CharAvailable( char *ch );
int CharReceive( char *ch );
int CharSend( char ch);

#define RX_READY			2		// bit 2
#define TX_READY			0		// bit 0

#define COMMAND_OK			-1
#define COMMAND_ERROR		-2
#define COMMAND_NOT_READY	-3
#define COMMAND_TIMEOUT		-4
#define LOW_BYTE(x)         (x & 0x00FF)
#define HI_BYTE(x)          ((x & 0xFF00) >> 8)
#define PAGE(x)             ((x & 0xF000) >> 12)
#define HI_OFFSET(x)          ((x & 0x0FF0) >>4)
#define LO_OFFSET(x)          ((x & 0x000F) << 4)


#endif      /* __CARD_H__ */

