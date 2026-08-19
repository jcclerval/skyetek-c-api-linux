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
 * SPIDevice.h
 *
 */
#ifndef SPI_DEVICE_H
#define SPI_DEVICE_H

#include "../SkyeTekAPI.h"
#include "../SkyeTekProtocol.h"
#include "../Drivers/aardvark.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SPI_MSG_SIZE 2100

typedef struct SPI_INFO
{
  aa_u16 port_number;
  Aardvark spiHandle;
  int type;
  MUTEX(lock);
} SPI_INFO, *LPSPI_INFO;

/**
 * Initializes the newly created SPI device by 
 * setting up its function table.
 * @param device The device
 */
void SPIDevice_InitDevice(
  LPSKYETEK_DEVICE device
  );

/**
 * Frees any resources used internally by the device
 * @param device The device to destroy
 */
int 
SPIDevice_Free(
  LPSKYETEK_DEVICE    device
  );


#ifdef __cplusplus
}
#endif


#endif
