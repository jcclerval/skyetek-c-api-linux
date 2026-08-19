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
 * ReaderFactory.h
 *
 * Creates reader objects.
 */
#ifndef READER_FACTORY_H
#define READER_FACTORY_H

#include "../SkyeTekAPI.h"
#include "Reader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct READER_FACTORY {

  /**
   * Performs auto-discovery of readers.  Auto-discovery is optional
   */
  unsigned int 
  (*DiscoverReaders)(
    LPSKYETEK_DEVICE    *devices, 
    unsigned int        deviceCount, 
    LPSKYETEK_READER    **readers
    );

  /**
   * Frees the readers returns by discover readers.
   */
  void 
  (*FreeReaders)(
    LPSKYETEK_READER *readers,
    unsigned int count
    );

  /**
   * Creates a reader with a given device.
   * The device/address string is ReaderFactory specific.
   */
  SKYETEK_STATUS 
  (*CreateReader)(
    LPSKYETEK_DEVICE  device, 
    LPSKYETEK_READER* reader
    );

  /**
   * Frees the reader returned by create reader.
   */
  int 
  (*FreeReader)(
    LPSKYETEK_READER reader
    );


} READER_FACTORY, *LPREADER_FACTORY;

extern READER_FACTORY SkyetekReaderFactory;
extern READER_FACTORY DemoReaderFactory;

/**
 * Returns the number of registered reader factories
 */
unsigned int 
ReaderFactory_GetCount(void);

/**
 * Retrieves the ith ReaderFactory
 */
LPREADER_FACTORY 
ReaderFactory_GetFactory(
  unsigned int i
  );

/**
 * This discovers all of the readers to be found on the devices that
 * are passed in.
 * @param devices Point to an array of devices
 * @param deviceCount Count of devices in the array
 * @param readers Pointer to array to popluate.  This function will allocate memory.
 * @return Number of readers found (size of readers array) 
 */
unsigned int 
DiscoverReadersImpl(
  LPSKYETEK_DEVICE    *devices, 
  unsigned int        deviceCount, 
  LPSKYETEK_READER    **readers
  );

/**
 * Frees the readers.
 * @param readers Readers to free
 */
void FreeReadersImpl(
  LPSKYETEK_READER    *readers,
  unsigned int        count
  );

/**
 * Creates a reader from the given device.
 */
SKYETEK_STATUS CreateReaderImpl(
  LPSKYETEK_DEVICE    device, 
  LPSKYETEK_READER    *reader
  );

/**
 * Frees a reader.
 */
void FreeReaderImpl(
  LPSKYETEK_READER    reader
  );

#ifdef __cplusplus
}
#endif

#endif 



