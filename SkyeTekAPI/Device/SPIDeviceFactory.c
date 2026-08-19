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

/**
 * SPIDeviceFactory.c
 *
 * Implementation of the SPIDeviceFactory.
 */
#include "../SkyeTekAPI.h"
#include "Device.h"
#include "DeviceFactory.h"
#include "SPIDevice.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

static unsigned int g_spiDevCount = 0;

SKYETEK_STATUS 
SPIDeviceFactory_CreateDevice(
  TCHAR              *address, 
  LPSKYETEK_DEVICE  *lpDevice
  )
{
	if( lpDevice == NULL )
		return SKYETEK_INVALID_PARAMETER;
  
	if(_tcsstr(address, _T("SPI")) == NULL && _tcsstr(address, _T("I2C")) == NULL)
		return SKYETEK_INVALID_PARAMETER;

	*lpDevice = (LPSKYETEK_DEVICE)malloc(sizeof(SKYETEK_DEVICE));
	memset((*lpDevice),0,sizeof(SKYETEK_DEVICE));
	_tcscpy((*lpDevice)->address,address);
	_tcscpy((*lpDevice)->type,SKYETEK_SPI_DEVICE_TYPE);
	_tcscpy((*lpDevice)->friendly,address);
	SPIDevice_InitDevice(*lpDevice);
	
	return SKYETEK_SUCCESS;
}

int 
SPIDeviceFactory_FreeDevice(
  LPSKYETEK_DEVICE lpDevice
  )
{
  if( lpDevice == NULL || lpDevice->internal == NULL )
    return 0;
  if( lpDevice->internal == &SPIDeviceImpl )
  {
    if( SPIDevice_Free(lpDevice) )
      return 1;
  }
  return 0;
}

unsigned int 
SPIDeviceFactory_DiscoverDevices(
  LPSKYETEK_DEVICE** lpDevices
  )
{	
  SKYETEK_STATUS status;
  int numDevices = 0;
  int numCreated = 0;
  aa_u16 devices[10];
  TCHAR address[16];
  int i;
  Aardvark a = 0;
  char isI2C = 0;

	if((lpDevices == NULL) || (*lpDevices != NULL))
		return 0;

  numDevices = aa_find_devices(10, devices);
  if( numDevices <= 0 )
    return 0;

	*lpDevices = (LPSKYETEK_DEVICE*)malloc(2*numDevices * sizeof(LPSKYETEK_DEVICE));
	memset(*lpDevices,0,(2*numDevices*sizeof(LPSKYETEK_DEVICE)));
	for ( i = 0; i < numDevices; i++ ) 
	{       
    // we create one for SPI and one for I2C here
    memset(address,0,16*sizeof(TCHAR));
    _stprintf(address,_T("%s%d"),SKYETEK_I2C_DEVICE_TYPE, devices[i]);
		status = SPIDeviceFactory_CreateDevice(address, &((*lpDevices)[numCreated]));
    if( status != SKYETEK_SUCCESS )
  		break;
    numCreated++;

    memset(address,0,16*sizeof(TCHAR));
    _stprintf(address, _T("%s%d"),SKYETEK_SPI_DEVICE_TYPE, devices[i]);
		status = SPIDeviceFactory_CreateDevice(address, &((*lpDevices)[numCreated]));
    if( status != SKYETEK_SUCCESS )
      break;
    numCreated++;
  }
	return numCreated;
}

void 
SPIDeviceFactory_FreeDevices(
  LPSKYETEK_DEVICE    *lpDevices,
  unsigned int        count
  )
{
  unsigned int ix = 0;
	if(lpDevices == NULL)
		return;
  for( ix = 0; ix < count; ix++ )
  {
    if( lpDevices[ix] != NULL )
    {
      if( lpDevices[ix]->internal == &SPIDeviceImpl )
      {
        SPIDeviceFactory_FreeDevice(lpDevices[ix]);
        lpDevices[ix] = NULL;
      }
    }
  }
}

DEVICE_FACTORY SPIDeviceFactory = {
  SKYETEK_SPI_DEVICE_TYPE,
  SPIDeviceFactory_DiscoverDevices,
  SPIDeviceFactory_FreeDevices,
  SPIDeviceFactory_CreateDevice,
  SPIDeviceFactory_FreeDevice
};

