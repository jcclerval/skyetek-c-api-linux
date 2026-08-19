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
 * SerialDevice.h
 *
 */
#ifndef SKYETEK_SERIAL_DEVICE_H
#define SKYETEK_SERIAL_DEVICE_H

#include "../SkyeTekAPI.h"
#include "../SkyeTekProtocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Sets the serial device communication options.
 * @param device The device
 * @param settings The settings
 * @return Status
 */
SKYETEK_API SKYETEK_STATUS 
SerialDevice_SetOptions(
  LPSKYETEK_DEVICE            device, 
  LPSKYETEK_SERIAL_SETTINGS   lpSettings
  );

/** 
 * Gets the serial device communication options.
 * @param device The device
 * @param settings The settings
 * @return Status
 */
SKYETEK_STATUS 
SerialDevice_GetOptions(
  LPSKYETEK_DEVICE            device, 
  LPSKYETEK_SERIAL_SETTINGS   lpSettings
  );

/**
 * Initializes the device.
 * @param device The device to initialize.
 */
void 
SerialDevice_InitDevice(
  LPSKYETEK_DEVICE    device
  );

/**
 * Frees the device.
 * @param device The device to free.
 */
int 
SerialDevice_Free(
  LPSKYETEK_DEVICE device
  );


static SKYETEK_SERIAL_SETTINGS SerialDiscoverySettings [] = {
  {38400, 8, NONE, ONE},
  {9600, 8, NONE, ONE},
  {19200, 8, NONE, ONE},
  {57600, 8, NONE, ONE},
  {115200, 8, NONE, ONE}
};

#define NUM_SERIAL_DISCOVERY_SETTINGS (sizeof(SerialDiscoverySettings)/sizeof(SKYETEK_SERIAL_SETTINGS))

#ifdef __cplusplus
}
#endif


#endif
