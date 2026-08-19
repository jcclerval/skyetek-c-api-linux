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
 * Reader.h
 *
 * Reader implementation.
 */
#ifndef SKYETEK_READER_H
#define SKYETEK_READER_H

#include "../SkyeTekAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct READER_IMPL
{
  SKYETEK_STATUS 
  (*SelectTags)(
      LPSKYETEK_READER            lpReader, 
      SKYETEK_TAGTYPE             tagType, 
      SKYETEK_TAG_SELECT_CALLBACK callback, 
      unsigned char               inv, 
      unsigned char               loop, 
      void                        *user
      );

  SKYETEK_STATUS 
  (*GetTags)(
      LPSKYETEK_READER   lpReader, 
      SKYETEK_TAGTYPE    tagType, 
      LPSKYETEK_TAG      **lpTags, 
      unsigned short     *count
      );

  SKYETEK_STATUS 
  (*GetTagsWithMask)(
      LPSKYETEK_READER   lpReader, 
      SKYETEK_TAGTYPE    tagType, 
	  LPSKYETEK_ID		 lpTagIdMask,
      LPSKYETEK_TAG      **lpTags, 
      unsigned short     *count
      );

  SKYETEK_STATUS 
  (*FreeTags)(
      LPSKYETEK_READER   lpReader, 
      LPSKYETEK_TAG      *lpTags, 
      unsigned short     count
      );

  SKYETEK_STATUS 
  (*StoreKey)(
      LPSKYETEK_READER     lpReader,
      SKYETEK_TAGTYPE      type,
      LPSKYETEK_KEY        lpKey
      );

  SKYETEK_STATUS 
  (*LoadKey)(
      LPSKYETEK_READER     lpReader, 
      LPSKYETEK_KEY        lpKey
      );


  SKYETEK_STATUS 
  (*LoadDefaults)(
      LPSKYETEK_READER     lpReader
      );

  SKYETEK_STATUS 
  (*ResetDevice)(
      LPSKYETEK_READER     lpReader
      );

  SKYETEK_STATUS 
  (*Bootload)(
      LPSKYETEK_READER     lpReader
      );

  SKYETEK_STATUS 
  (*GetSystemParameter)(
      LPSKYETEK_READER             lpReader, 
      SKYETEK_SYSTEM_PARAMETER     parameter,
      LPSKYETEK_DATA               *lpData
      );

  SKYETEK_STATUS 
  (*SetSystemParameter)(
      LPSKYETEK_READER             lpReader, 
      SKYETEK_SYSTEM_PARAMETER     parameter, 
      LPSKYETEK_DATA               lpData
      );

  SKYETEK_STATUS 
  (*GetDefaultSystemParameter)(
      LPSKYETEK_READER             lpReader, 
      SKYETEK_SYSTEM_PARAMETER     parameter, 
      LPSKYETEK_DATA               *lpData
      );

  SKYETEK_STATUS 
  (*SetDefaultSystemParameter)(
      LPSKYETEK_READER             lpReader, 
      SKYETEK_SYSTEM_PARAMETER     parameter, 
      LPSKYETEK_DATA               lpData
      );

  SKYETEK_STATUS 
  (*AuthenticateReader)(
      LPSKYETEK_READER     lpReader, 
      LPSKYETEK_KEY        lpKey
      );

  SKYETEK_STATUS 
  (*EnableDebug)(
      LPSKYETEK_READER     lpReader
      );

  SKYETEK_STATUS 
  (*DisableDebug)(
      LPSKYETEK_READER     lpReader
      );

  SKYETEK_STATUS 
  (*UploadFirmware)(
      LPSKYETEK_READER                      lpReader, 
      TCHAR                                  *file, 
      unsigned char                         defaultsOnly,
      SKYETEK_FIRMWARE_UPLOAD_CALLBACK      callback, 
      void                                  *user
      );

  SKYETEK_STATUS 
  (*GetDebugMessages)(
      LPSKYETEK_READER     lpReader,
      LPSKYETEK_DATA      *lpData
      );

  int
  (*DoesRIDMatch)(
      LPSKYETEK_READER      lpReader,
      const unsigned char   *id
      );

  void
  (*CopyRIDToBuffer)(
      LPSKYETEK_READER      lpReader,
      unsigned char   *id
      );

  SKYETEK_STATUS 
  (*EnterPaymentScanMode)(
      LPSKYETEK_READER     lpReader
      );

  SKYETEK_STATUS 
  (*ScanPayments)(
    LPSKYETEK_READER              lpReader,
    SKYETEK_PAYMENT_SCAN_CALLBACK callback,
    void                          *user
    );

  SKYETEK_STATUS
  (*RunAntennaTune)(
    LPSKYETEK_READER            lpReader,
  	SKYETEK_ANTENNA_TUNE_CALLBACK callback,
    void                        *user,
  	unsigned char               isVerbose
    );

} READER_IMPL, *LPREADER_IMPL;

extern READER_IMPL SkyetekReaderImpl;

#ifdef __cplusplus
}
#endif

#endif 

