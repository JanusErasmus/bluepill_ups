#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "Utils/terminal.h"
#include "Utils/cli.h"
#include "stm32f1xx_hal.h"

//static sTerminal_t *terminals[] = {0,0}; //support up to 2 terminals
#define CMD_BUFFER_SIZE     128
#define VCOM_DELAY   		2*1000 //mS

static char mCmdBuffer[CMD_BUFFER_SIZE];
static uint8_t mCmdIndex = 0;

static char *mCommand;

void terminal_run()
{
    if (mCommand)
    {
        cli_handleCommand(mCommand);

    	free(mCommand);
    	mCommand = 0;
    }
}

void terminal_handleByte(uint8_t byte)
{
    //echo typed character
	printf("%c", (char)byte);
    if (byte == '\r')
    {
    	printf("%c", '\n');
    }

    if (byte == '\r') // || (byte == '\n'))
    {
        mCmdBuffer[mCmdIndex++] = byte;
        mCmdBuffer[mCmdIndex++] = 0;
        if(mCommand)
        	return;
        mCommand = (char *)malloc(mCmdIndex);
        memcpy(mCommand, mCmdBuffer, mCmdIndex);

        mCmdIndex = 0;
    }
    else
        mCmdBuffer[mCmdIndex++] = byte;

    if (mCmdIndex > CMD_BUFFER_SIZE)
        mCmdIndex = 0;
}
