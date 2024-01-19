/********************************************************************

                                Card.c

    Interface specific code. 
    This file only should touch the hardware.

*********************************************************************/

#include "stdafx.h"

#include <rt.h>
#include <string.h>     // strlen()
#include <stdio.h>      // sprintf()
#include <stdlib.h>


#include "vlcport.h"
#include "dcflat.h"     // EROP()
#include "driver.h"     /* SEMAPHORE */
#include "errors.h"     /* IDS_RT_DP_RW_TEST                     */
#include "auxrut.h"     /* StartTimeout(), IsTimeout(), EROP     */
#include "card.h"       /* Init()                                */


static char command[120];
static char response_string[120];

static UINT32 address;


void DataInit()
{
///any static var to init
}


/*   not use yet can used to read file data from win side
int FileLoad(char *fname)
{
FILE *fp;
char txt[30];
	fp=fopen(fname,"r");
	if(fp==NULL) return(-1);	
	fscanf(fp,"%s\n",txt);	
	fscanf(fp,"%s\n",txt);
	strcpy(m_BoardName,txt);
	fscanf(fp,"%d:%s\n",&m_BoardType,txt);
	fscanf(fp,"%d:%s\n",&m_IrqNo,txt);
	fscanf(fp,"%lx:%s\n",&m_Address,txt);
	fscanf(fp,"%d:%s\n",&m_PciIndex,txt);
	fscanf(fp,"%d:%s\n",&m_Sys.EsLog,txt);
	for(int axis=0;axis<4;axis++){
		fscanf(fp,"%d:%s\n",&m_Sys.SpdMode[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.AlmLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.NearLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ZLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.OverLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.InpLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.PlsLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ForDir[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ClkType[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.MotType[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.HomeSeq[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ZCnt[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.EncdMul[axis],txt);
		//S----- Add by CKTan-----
		fscanf(fp,"%d:%s\n",&m_Sys.HomeMode[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.Encoder[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.Deviation[axis],txt);
		//E----- Add by CKTan-----
		fscanf(fp,"%f:%s\n",&m_Sys.PlsUnit[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.SType[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.SCRes[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.MaxSpd[axis],txt);
	}
	fclose(fp);
	return(0); // ok
} */

/******************* Card specific  Functions  *******************************/


/******************* Initialization  *******************************/


static int TestAndFill(UINT8* pc, const int Size, const int test, const int fill)   /* test == 1  --> no test */
{
    int i  = 0;
    for(; i < Size;  *pc++ = fill, i++)
    {
        int c = *pc & 255;
        if(test != 1  &&  test != c)
        {
            EROP("Ram Error.  Address %p, is 0x%02x, and should be 0x%02x", pc, c, test, 0);
            return IDS_HWCARD_HW_TEST;
        }
    }
    return SUCCESS;
}


int  Init( LPDRIVER_INST pNet, P_ERR_PARAM const lpErrors)
{
    int rc = SUCCESS;

    return rc;
}



/****************************************************************************************
    IN:     pName   --> pointer to the device user name
            Address --> device's network address
            pBuf    --> pointer to the destination buffer
            szBuf   --> size of the destination buffer

    OUT:    *pBuf   <-- "Address xx (usr_name)".  
    Note:   The device user name may be truncated!
*/
static void LoadDeviceName( char* pName, UINT16 Address, char* pBuf, size_t szBuf )
{
    if( szBuf && (pBuf != NULL) )
    {
        char* format = "Address %d";

        *pBuf = '\0';

        if( szBuf > (strlen(format)+3) )    /* Address may need more digits */
        {
            size_t  len;

            sprintf(pBuf, format, Address & 0xffff);

            len = strlen( pBuf ); 

            if( pName && ((szBuf - len) > 10) )     /* if we still have 10 free bytes  */
            {
                strcat(pBuf, " (");
                len += 2;
                strncat( pBuf, pName, szBuf-len-2 );
                *(pBuf + szBuf - 2) = '\0';
                strcat( pBuf, ")" );
            }
        }
    }
}



int  TestConfig( LPDRIVER_INST const pNet, P_ERR_PARAM const lpErrors )
{
    int rc = SUCCESS;

    return rc;
}


/********************* runtime specific card access functions ********************/

///not used
int	DoCollect( LPDRIVER_INST pNet, LPSPECIAL_INST pData)
{
    int     rc       = SUCCESS;
//	int		channel;
//	UINT16	*ChanBuff[16];
//	UINT16	NumSamples = pData->Work.paramCommand.NumSamps;
	UINT16* pResult = BuildUiotPointer( pData->Work.paramHeader.ofsResult );
   
//	for (channel = 0; (channel < 16) && (rc == SUCCESS); channel++)
//	{
//		LPPTBUFFER pRBuffer = &pData->Work.paramCommand.Buffers[channel];

//		printf("Channel %d  Length %d  Offset %d\n", 
//			channel, pRBuffer->Size, pRBuffer->Offset);

//		ChanBuff[channel] = BuildUiotPointer( pRBuffer->Offset );
//		if( pRBuffer->Size > NumSamples)
//		{
//			rc = IDS_MCI0410_READ_SIZE;
//		}
//	}

	// At this time, ChanBuf[i] is a pointer to the buffer area for channel i.
	// Insert your code here.
	*pResult = rc;
	return  (rc);
}


void    PortGalilTx(SPECIAL_INST_PORT_GALIL_SPLIT* const pData,  LPDRIVER_INST const pNet)
{
    int   rc  = SUCCESS;


	UINT8* TxValue = BuildUiotPointer(pData->ofsGalilValue );    // Tx string pointer 

	UINT16* pResult   = BuildUiotPointer( pData->Header.ofsResult );

	if( pNet->PhyAddr !=0 )
    {
		address= pNet->PhyAddr;
		ClearBuffer();
		rc = SendString(TxValue);
		//printf("galil tx <%s>", TxValue);
	}
    else 
        rc = IDS_HWCARD_INVALID_ADDERSS;

    *pResult = rc;



}

void    PortGalilRx( SPECIAL_INST_PORT_GALIL_SPLIT* const pData,  LPDRIVER_INST const pNet)
{
	char  rx[256];
	int   result;
	int   rc  = SUCCESS;
	int   i;

	UINT8* RxValue = BuildUiotPointer(pData->ofsGalilValue );    // Tx string pointer 
	UINT16* pResult   = BuildUiotPointer( pData->Header.ofsResult );


	if( pNet->PhyAddr !=0 )
    {
			//RxValue="ahkait was here \0";

		address= pNet->PhyAddr;
		result = CheckResponse();
			if(result == COMMAND_OK)
			{
                result = WaitForResponse();
                if(result==COMMAND_OK)
                {
						for(i=0; i<10; i++)
							*(RxValue+1) = 0;

                        // need to check len(<255) and time out and update rc
                        // return string needs null termination
                         strcpy(rx,GetResponse());
						 if(strcmp(rx, "")==0)
						 {
							// instead of sending "", send back the result code in string
							itoa(result, RxValue, 10);
						 }
						 else
						 {
							 rx[strlen(rx)-2]='\0';
							 strcpy(RxValue, &rx[1]);
						 }
						 //printf("addr <%d> rx <%s> RX <%s>", Addr, rx, RxValue);
						 rc = result;
				}
				else
				{
					itoa(rc, RxValue, 10);
					rc = result;
				}
			}
			else
			{
				itoa(rc, RxValue, 10);
				rc = result;

			}
			//printf("galil rx <%s> <%d>", RxValue, rc);
	}
    else 
		rc=IDS_HWCARD_INVALID_ADDERSS;

    *pResult = rc;
}



void    PortGalil( SPECIAL_INST_PORT_GALIL* const pData, LPDRIVER_INST const pNet)
{
//    char	str[256];
	char	rx[256];
    int   rc  = SUCCESS;
//	int	  i;

	UINT8* OutValue = BuildUiotPointer(pData->ofsTxValue);                // string pointer 
	UINT8* InValue  = BuildUiotPointer(pData->ofsRxValue);                // 

	UINT16* pResult   = BuildUiotPointer( pData->Header.ofsResult );



	if( pNet->PhyAddr !=0 )
    {
		address= pNet->PhyAddr;

                ClearBuffer();

                SendString(OutValue);
                rc = WaitForResponse();
                if(rc==0)
                {
						strcpy(InValue, "                ");

                        // need to check len(<255) and time out and update rc
                        // return string needs null termination
                         strcpy(rx,GetResponse());
						 if(strcmp(rx, "")==0)
						 {
							 rx[0]=0;
							 strcpy(InValue, "");
						 }
						 else
						 {
							 rx[strlen(rx)-2]='\0';
							 strcpy(InValue, &rx[1]);
							
						 }
// debug
//						 printf("addr <%d> tx <%s> rx <%s>", Addr, OutValue, InValue);

                }
	}
    else 
        rc = IDS_HWCARD_INVALID_ADDERSS;

    *pResult = rc;
}


void ClearBuffer()
{
	char ch; 		// clear buffer
	while(CharAvailable(&ch)==COMMAND_OK)
		;
		
}

//***********************************
//	check for character availability
//***********************************
int CheckResponse()
{


	// is there a byte waiting for us?
	if ( (dmcInportb(address+4) & RX_READY) == 0)
		return COMMAND_OK;
	else
		return COMMAND_NOT_READY;
}



//***********************************
//	check for character availability
//***********************************
int CharAvailable(char *ch)
{
	*ch = 0;
	// is there a byte waiting for us?
	if ( (dmcInportb(address+4) & RX_READY) == 0)
	{
		*ch = dmcInportb(address);
		return COMMAND_OK;
	}
	else
		return COMMAND_TIMEOUT;
}


//***********************************
//	A character received from DMC
//***********************************
int CharReceive(char *ch)
{
	long timeout = 20000L;
	while (--timeout > 0)
		if(CharAvailable(ch)==COMMAND_OK)
			return COMMAND_OK;

	return COMMAND_TIMEOUT;
}

//***********************************
//	Send a character to DMC
//***********************************
int CharSend(char ch)
{

	long	timeout = 20000L;

	while((dmcInportb(address+4) & TX_READY)!= 0)
		if(--timeout < 0)
			return COMMAND_TIMEOUT;

	dmcOutportb( address, ch);	// send the byte

	return COMMAND_OK;
}

//***********************************
//	Send a string to DMC
//***********************************
int SendString(char *str)
{
	int i;
	strcpy(command, str);

	for(i=0; command[i]; i++)
	{
		if( CharSend(command[i]) == COMMAND_TIMEOUT)
			return COMMAND_TIMEOUT;
	}

	// send a CR to simulate RETURN key
	if(str[strlen(command)-1]!='\r')
		if(CharSend('\r')==COMMAND_TIMEOUT)
			return COMMAND_TIMEOUT;

	return COMMAND_OK;
}

int SendReceive(char *str)
{
	int result;
	SendString(str);

	result = WaitForResponse();
	if(result == COMMAND_ERROR)
	{
		// the reason is not to use the SendReceive function recursively
		CharSend('T');
		CharSend('C');
		CharSend('1');
		CharSend('\r');

		WaitForResponse();
		return COMMAND_ERROR;
	}

	return COMMAND_OK;
}

char * GetResponse()
{
	return response_string;
}

//***********************************
//	Receive response from DMC
//***********************************
int WaitForResponse()
{
	char ch;
	int i=0;
	int result;
	response_string[0]='\0';

	do
	{
		result = CharReceive(&ch);
		if(result == COMMAND_OK)
		{
			if(ch=='?')
				return COMMAND_ERROR;
			else if(ch!=':')
				response_string[i++]=ch;
		}
		else
			return result;

	}while(ch!=':');
	response_string[i]='\0';
	return COMMAND_OK;
}


unsigned char dmcInportb (UINT32 portid)
{
	return inbyte (portid);
}

void dmcOutportb(UINT32 portid, unsigned char value)
{
	outbyte(portid, value);
}


