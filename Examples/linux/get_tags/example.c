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

int main(int argc, char* argv[])
{
	LPSKYETEK_DEVICE *devices = NULL;
	LPSKYETEK_READER *readers = NULL;
	LPSKYETEK_TAG *tags = NULL;
	SKYETEK_STATUS status;
	unsigned short count = 0;
	int numDevices = 0;
	int numReaders = 0;
	const int delay = 400000;  	//wait at least 400ms after closing the interface before re-opening (USB enumeration)
	const int tests = 3; 		//number of open/close tests to perform
	const int iterations = 10; 	//number of select tag operations to perform for each test
	int failures = 0;
	int total = 0;

	for(int m = 0; m < tests; m++)
	{
		total ++;
		printf("\n\nTEST #%d\n", total);
		if((numDevices = SkyeTek_DiscoverDevices(&devices)) > 0)
		{
			//printf("example: devices=%d", numDevices);
			if((numReaders = SkyeTek_DiscoverReaders(devices,numDevices,&readers)) > 0 )
			{
				//printf("example: readers=%d\n", numReaders);
				for(int i = 0; i < numReaders; i++)
				{
					printf("Reader Found: %s-%s-%s on %s %s\n", 
					       readers[i]->manufacturer, readers[i]->model, readers[i]->firmware, 
					       readers[i]->lpDevice->type, readers[i]->lpDevice->address);

					for(int k = 0; k < iterations; k++)
					{
						printf("\tIteration = %d\n",k);
						status = SkyeTek_GetTags(readers[i], AUTO_DETECT, &tags, &count);
						if(status == SKYETEK_SUCCESS)
						{
							if(count == 0)
							{
								printf("\t\tNo tags found\n");
							}
							else
							{
								for(int j = 0; j < count; j++)
								{
									printf("\t\tTag Found: %s-%s\n", SkyeTek_GetTagTypeNameFromType(tags[j]->type), tags[j]->friendly);
								}
							}
						}
						else
						{
							printf("ERROR: GetTags failed: Status %d\n", status);
						}
					}
					SkyeTek_FreeTags(readers[i],tags,count);
				}
			}
			else
			{
				failures ++;
				printf("failures = %d/%d\n", failures, total);
				printf("ERROR: No readers found\n");
			}		
		}
		else
		{
			failures ++;
			printf("failures = %d/%d\n", failures, total);
			printf("ERROR: No devices found\n");
		}
		SkyeTek_FreeDevices(devices,numDevices);
		devices = NULL;
		SkyeTek_FreeReaders(readers,numReaders);
		readers = NULL;
		usleep(delay);
	}
}
