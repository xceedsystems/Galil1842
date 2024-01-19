/********************************************************************

           Galil 1842       

   This file contains defintions for all of the common structures 
   and type definitions necessary to describe our hardware

**********************************************************************/



void Interactive();
int SendReceive( char str[] );
int SendString(char *str);
char * GetResponse();
int WaitForResponse();
void ClearBuffer();
void SetAddress(UINT32 addr);
int CheckResponse();

#define COMMAND_OK			-1
#define COMMAND_ERROR		-2
#define COMMAND_NOT_READY	-3
#define COMMAND_TIMEOUT		-4

