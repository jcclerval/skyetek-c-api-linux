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
 * USBDevice.h
 *
 */
#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include "../SkyeTekAPI.h"

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* This structure is used internally by the USBDevice driver */
typedef struct USB_DEVICE {
	unsigned int packetParity;
	unsigned char* sendBufferWritePtr;
	unsigned char* endOfSendBuffer;
	unsigned char* receiveBufferWritePtr;
	unsigned char* receiveBufferReadPtr;
	unsigned char* endOfReceiveBuffer;
	MUTEX(sendBufferMutex);
	MUTEX(receiveBufferMutex);
#ifdef HAVE_LIBUSB
	struct usb_dev_handle* usbDevHandle;
#endif
	unsigned char sendBuffer[63];
	unsigned char receiveBuffer[63];
} USB_DEVICE, *LPUSB_DEVICE;

/**
 * Initializes the newly created USB device by 
 * setting up its function table.
 * @param device The device
 */
void USBDevice_InitDevice(
  LPSKYETEK_DEVICE device
  );

/**
 * Frees any resources used internally by the device
 * @param device The device to destroy
 */
int 
USBDevice_Free(
  LPSKYETEK_DEVICE    device
  );


#ifdef __cplusplus
}
#endif


#endif
