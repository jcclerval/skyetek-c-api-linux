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
 * Device.h
 *
 * Defines the Device object and the global functions
 * to get the list of available devices.
 */
#ifndef SKYETEK_DEVICE_H
#define SKYETEK_DEVICE_H

#include "../SkyeTekAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Device that is connected to the host.
 */
typedef struct DEVICEIMPL 
{
  /**
   * Opens the device.
   * @param device Device to open
   */
  SKYETEK_STATUS 
  (*Open)(
    LPSKYETEK_DEVICE  lpDevice
    );

  /**
   * Closes the device and frees all resources associated with it
   * @param device Pointer to the device
   */
  SKYETEK_STATUS 
  (*Close)(
    LPSKYETEK_DEVICE  lpDevice
    );

  /**
   * Reads bytes from the device into the buffer and returns the
   * number of bytes read.
   * @param device The device to read from
   * @param buffer The buffer to read bytes into
   * @param length The length of the buffer
   */
  int (*Read)(
    LPSKYETEK_DEVICE  lpDevice,
    unsigned char     *buffer,
    unsigned int      length,
    unsigned int      timeout
    );

  /**
   * Writes the buffer to the device and returns the number of bytes
   * written.
   * @param device The device to write to
   * @param buffer The buffer to write
   * @param length The length of the buffer
   * @param timeout The milliseconds to wait before timing out or zero to block */
  int 
  (*Write)(
    LPSKYETEK_DEVICE  lpDevice,
    unsigned char     *buffer,
    unsigned int      length,
    unsigned int      timeout
    );

	/**
   * Flushes any uncommitted data
   * @param device The device to flush*/
  void 
  (*Flush)(
    LPSKYETEK_DEVICE  lpDevice
    );
	
	/**
   * Frees any resources used by this device
   * @param device The device to destroy*/
  int 
  (*Free)(
    LPSKYETEK_DEVICE  lpDevice
    );

  /**
   * Sets an additional timeout value.
   * @param timeout new timeout value
   */
  SKYETEK_STATUS
  (*SetAdditionalTimeout)(
    LPSKYETEK_DEVICE  lpDevice,
    unsigned int      timeout
    );

  /** 
   * Timeout value for the device.
   */
  unsigned int timeout;

} DEVICEIMPL, *LPDEVICEIMPL;
  
extern DEVICEIMPL SerialDeviceImpl;
extern DEVICEIMPL USBDeviceImpl;
#if defined(WIN32) && !defined(WINCE)
extern DEVICEIMPL SPIDeviceImpl;
#endif

#ifdef __cplusplus
}
#endif


#endif
