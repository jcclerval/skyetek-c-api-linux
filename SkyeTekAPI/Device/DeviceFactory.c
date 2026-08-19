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
 * DeviceFactory.c
 *
 * Implementation of the DeviceFactory.
 */

#include "../SkyeTekAPI.h"
#include "../SkyeTekProtocol.h"
#include "DeviceFactory.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

static LPDEVICE_FACTORY DeviceFactories[] = {
#if defined(WIN32) && !defined(WINCE) && defined(STAPI_SPI)
  &SPIDeviceFactory,
#endif
#if defined(LINUX) && defined(STAPI_USB)
  &USBDeviceFactory,
#endif
#if defined(WIN32) && defined(STAPI_USB)
  &USBDeviceFactory,
#endif
#if defined(STAPI_SERIAL)
  &SerialDeviceFactory
#endif
};

#define DEVICEFACTORIES_COUNT sizeof(DeviceFactories)/sizeof(LPDEVICE_FACTORY)


unsigned int 
DeviceFactory_GetCount(void)
{
  return DEVICEFACTORIES_COUNT; 
}

LPDEVICE_FACTORY 
DeviceFactory_GetFactory(
  unsigned int i
  )
{
  if(i > DEVICEFACTORIES_COUNT)
    return NULL;
  else
    return DeviceFactories[i];
}

unsigned int 
DiscoverDevicesImpl(
  LPSKYETEK_DEVICE    **lpDevices
  )
{
  LPDEVICE_FACTORY pDeviceFactory = NULL;
  unsigned int ix, deviceCount, localCount;
  LPSKYETEK_DEVICE *localDevices = NULL;
  
  deviceCount = 0;
  
  for(ix = 0; ix < DeviceFactory_GetCount(); ix++) 
  {
    pDeviceFactory = DeviceFactory_GetFactory(ix);
    localDevices = NULL;
    localCount = pDeviceFactory->DiscoverDevices(&localDevices);
  
    if(localCount > 0) 
    {
      *lpDevices = (LPSKYETEK_DEVICE*)realloc(*lpDevices, (deviceCount + localCount) * sizeof(LPSKYETEK_DEVICE));
      memcpy(((*lpDevices) + deviceCount), localDevices, localCount*sizeof(LPSKYETEK_DEVICE));
      free(localDevices);
      deviceCount += localCount;
    }
  }
  
  return deviceCount;
}

void FreeDevicesImpl(
  LPSKYETEK_DEVICE    *lpDevices,
  unsigned int        count
  )
{
  LPDEVICE_FACTORY pDeviceFactory;
  unsigned int ix;
  for(ix = 0; ix < DeviceFactory_GetCount(); ix++) 
  {
    pDeviceFactory = DeviceFactory_GetFactory(ix);
    pDeviceFactory->FreeDevices(lpDevices,count);
  }
}

SKYETEK_STATUS 
CreateDeviceImpl(
  TCHAR              *addr, 
  LPSKYETEK_DEVICE  *lpDevice
  )
{
  LPDEVICE_FACTORY pDeviceFactory;
  unsigned int ix;
  
  for(ix = 0; ix < DeviceFactory_GetCount(); ix++) 
    {
      pDeviceFactory = DeviceFactory_GetFactory(ix);
      if(pDeviceFactory->CreateDevice(addr, lpDevice) == SKYETEK_SUCCESS)
      {
        return SkyeTek_OpenDevice(*lpDevice);
      }
    }

  return SKYETEK_FAILURE;
}

void 
FreeDeviceImpl(
  LPSKYETEK_DEVICE lpDevice
  )
{
  LPDEVICE_FACTORY pDeviceFactory;
  unsigned int ix;

  for(ix = 0; ix < DeviceFactory_GetCount(); ix++) 
  {
    pDeviceFactory = DeviceFactory_GetFactory(ix);
    if( pDeviceFactory->FreeDevice(lpDevice) )
      break;
  }
}

