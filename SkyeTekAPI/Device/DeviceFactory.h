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
 * DeviceFactory.h
 *
 * Discovers and creates devices.
 */
#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "../SkyeTekAPI.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * The factory object for devices.
 */
typedef struct DEVICE_FACTORY
{
  /**
   * ID of this factory.
   */
  TCHAR *id;

  /**
   * Performs auto-discovery of devices.  Auto-discovery is optional
   */
  unsigned int 
  (*DiscoverDevices)(
    LPSKYETEK_DEVICE    **lpDevices
    );

  /**
   * Frees devices.
   */
  void 
  (*FreeDevices)(
    LPSKYETEK_DEVICE    *lpDevices,
    unsigned int        count
    );

  /**
   * Creates a device for a specific device address.
   */
  SKYETEK_STATUS 
  (*CreateDevice)(
    TCHAR              *addr, 
    LPSKYETEK_DEVICE  *lpDevice
    );

  /**
   * Frees a device.
   */
  int 
  (*FreeDevice)(
    LPSKYETEK_DEVICE  lpDevice
    );


} DEVICE_FACTORY, *LPDEVICE_FACTORY;

extern DEVICE_FACTORY SerialDeviceFactory;
extern DEVICE_FACTORY USBDeviceFactory;
#if defined(WIN32) && !defined(WINCE)
extern DEVICE_FACTORY SPIDeviceFactory;
#endif

/**
 * Returns the number of registered device factories
 */
unsigned int 
DeviceFactory_GetCount(void);

/**
 * Retrieves the ith DeviceFactory
 */
LPDEVICE_FACTORY 
DeviceFactory_GetFactory(
  unsigned int    i
  );

/**
 * This discovers all of the devices connected to the host that might
 * have readers attached to them.
 * @param devices Pointer to array to popluate.  This function will allocate memory.
 * @return Number of devices found (size of devices array) 
 */
unsigned int 
DiscoverDevicesImpl(
  LPSKYETEK_DEVICE  **lpDevices
  );

/**
 * Frees the devices.
 * @param devices Devices to free
 */
void 
FreeDevicesImpl(
  LPSKYETEK_DEVICE  *lpDevices,
  unsigned int      count
  );

/**
 * Creates a device from the given deviceAddress
 */
SKYETEK_STATUS 
CreateDeviceImpl(
  TCHAR              *addr, 
  LPSKYETEK_DEVICE  *lpDevice
  );

/**
 * Frees the devices.
 * @param devices Devices to free
 */
void 
FreeDeviceImpl(
  LPSKYETEK_DEVICE lpDevice
  );




#ifdef __cplusplus
}
#endif

#endif 



