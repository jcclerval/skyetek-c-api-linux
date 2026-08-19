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
 * ReaderFactory.c
 *
 * Implementation of the ReaderFactory.
 */
#include "../SkyeTekAPI.h"
#include "Reader.h"
#include "ReaderFactory.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

static LPREADER_FACTORY ReaderFactories[] = {
  &SkyetekReaderFactory
};

#define READERFACTORIES_COUNT sizeof(ReaderFactories)/sizeof(LPREADER_FACTORY)

unsigned int 
ReaderFactory_GetCount(void)
{
  return READERFACTORIES_COUNT; 
}

LPREADER_FACTORY 
ReaderFactory_GetFactory(
  unsigned int    i
  )
{
  if(i > READERFACTORIES_COUNT)
    return NULL;
  else
    return ReaderFactories[i];
}

SKYETEK_STATUS 
CreateReaderImpl(
  LPSKYETEK_DEVICE    device, 
  LPSKYETEK_READER    *reader
  )
{
  LPREADER_FACTORY pReaderFactory;
  unsigned int ix;
  
  for(ix = 0; ix < ReaderFactory_GetCount(); ix++) 
    {
      pReaderFactory = ReaderFactory_GetFactory(ix);
    
      if(pReaderFactory->CreateReader(device, reader) == SKYETEK_SUCCESS)
        return SKYETEK_SUCCESS;
    
    }
  
  return SKYETEK_FAILURE;
}

unsigned int 
DiscoverReadersImpl(
  LPSKYETEK_DEVICE      *devices, 
  unsigned int          deviceCount, 
  LPSKYETEK_READER      **readers
  )
{
  LPREADER_FACTORY pReaderFactory;
  unsigned int ix, readerCount, localCount;
  LPSKYETEK_READER* localReaders = NULL;
  
  readerCount = 0;
  
  for(ix = 0; ix < ReaderFactory_GetCount(); ix++) 
  {
    pReaderFactory = ReaderFactory_GetFactory(ix);
    localCount = pReaderFactory->DiscoverReaders(devices, deviceCount, &localReaders);

    if(localCount > 0) 
    {
      *readers = (LPSKYETEK_READER*)realloc(*readers, (readerCount + localCount) * sizeof(LPSKYETEK_READER));
      memcpy(((*readers) + readerCount), localReaders, localCount*sizeof(LPSKYETEK_READER));

      free(localReaders);
      readerCount += localCount;
    }
  }

  return readerCount;
}

void 
FreeReadersImpl(
  LPSKYETEK_READER    *readers, 
  unsigned int        count
  )
{
  LPREADER_FACTORY pReaderFactory;
  unsigned int ix;
  for(ix = 0; ix < ReaderFactory_GetCount(); ix++) 
  {
    pReaderFactory = ReaderFactory_GetFactory(ix);
    pReaderFactory->FreeReaders(readers,count);
  }
}

void 
FreeReaderImpl(
  LPSKYETEK_READER lpReader
  )
{
  LPREADER_FACTORY pReaderFactory;
  unsigned int ix;
  for(ix = 0; ix < ReaderFactory_GetCount(); ix++) 
  {
    pReaderFactory = ReaderFactory_GetFactory(ix);
    if( pReaderFactory->FreeReader(lpReader) )
      break;
  }
}

