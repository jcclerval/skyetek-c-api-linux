/*
Copyright 2006 - 2017 Skyetek, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SkyeTekAPI.h"
#include "SkyeTekProtocol.h"

#define  MAX_LEN  80

typedef struct {
	LPSKYETEK_DEVICE *devices;
	LPSKYETEK_READER *readers;
} global_ctxt_t;

static global_ctxt_t global_ctxt;

SKYETEK_STATUS start_nova_antenna_tuning(LPSKYETEK_READER *readers);

int main(int argc, char* argv[])
{
	enum SKYETEK_STATUS status;
	int numDevices = 0;
	int numReaders = 0;
	char response[MAX_LEN];
	unsigned char fQuit = 1;
	int errCount = 0;

	status = SKYETEK_FAILURE;
	global_ctxt.devices = NULL;
	global_ctxt.readers = NULL;

	printf("\n\n The Nova antenna tune process requires about 5 minutes to complete.\n\n");
	printf("Do you wish to continue? (y or n)>  ");

	scanf("%s", response);
	if (strncmp(response, "Y", MAX_LEN) == 0)
	{
		fQuit = 0;
	}
	else if (strncmp(response, "y", MAX_LEN) == 0)
	{
		fQuit = 0;
	}

	if (fQuit)
	{
		return -1;
	}

	printf("\nStarting Nova Antenna Tuning process . . .\n");

	if((numDevices = SkyeTek_DiscoverDevices(&global_ctxt.devices)) > 0)
	{
		if((numReaders = SkyeTek_DiscoverReaders(global_ctxt.devices,numDevices,&global_ctxt.readers)) > 0 )
		{
			if (strncmp(global_ctxt.readers[0]->readerName, "SkyeModule Nova", MAX_LEN) == 0)
			{
				status = start_nova_antenna_tuning(global_ctxt.readers);
				if (status != SKYETEK_SUCCESS)
				{
					errCount += 1;
				}
			}
			else
			{
				printf("Antenna tuning not supported\n");
			}
		}
		else
		{
			printf("ERROR: No readers found\n");
		}
	}
	else
	{
		printf("ERROR: No devices found\n");
	}

	SkyeTek_FreeReaders(global_ctxt.readers,numReaders);
	global_ctxt.readers = NULL;
	SkyeTek_FreeDevices(global_ctxt.devices,numDevices);
	global_ctxt.devices = NULL;

	return 0;
}

unsigned char nova_ant_tuning_callback(	LPSKYETEK_DATA lpData, void *user )
{
	unsigned int i;
	unsigned char temp;

	if (lpData)
	{
		printf("\n <Nova Response>:  ");
		for (i=0; i < lpData->size; i++)
		{
			temp = lpData->data[i];
			printf(" 0x%02x", temp);
		}
	}

	return 1;
}

SKYETEK_STATUS start_nova_antenna_tuning(LPSKYETEK_READER *readers)
{
	SKYETEK_STATUS status = SKYETEK_FAILURE;
	LPSKYETEK_READER pReader = readers[0];
	unsigned char isVerbose = 1;

	status = SkyeTek_RunAntennaTune( pReader, nova_ant_tuning_callback, &global_ctxt, isVerbose );
	if (status == SKYETEK_SUCCESS)
	{
		printf("\nNova antenna tuning is DONE.\n");
	}
	else
	{
		printf("\nNova antenna tuning FAILED!\n");
	}

	return status;
}


