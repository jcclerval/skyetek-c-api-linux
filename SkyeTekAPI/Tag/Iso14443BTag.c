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
 * Iso14443BTag.c
 *
 * Implementation of a Generic Tag.
 */
#include "Tag.h"
#include "GenericTag.h"
#include "../Protocol/Protocol.h"

#define ISO14443B_TIMEOUT 100

SKYETEK_STATUS 
Iso14443BTag_SendTagPassword(
    LPSKYETEK_READER     lpReader,
    LPSKYETEK_TAG        lpTag,
    LPSKYETEK_DATA       lpData
    )
{
  LPPROTOCOLIMPL lppi;
  if( lpReader == NULL || lpReader->lpProtocol == NULL || 
      lpReader->lpProtocol->internal == NULL ||
      lpReader->lpDevice == NULL || lpTag == NULL || 
      lpData == NULL || lpData->data == NULL || lpData->size == 0 )
    return SKYETEK_INVALID_PARAMETER;
  lppi = (LPPROTOCOLIMPL)lpReader->lpProtocol->internal;
  return lppi->SendTagPassword(lpReader,lpTag,lpData,ISO14443B_TIMEOUT);
}


TAGIMPL Iso14443BTagImpl = {
  GenericTag_SelectTag,
  GenericTag_ReadTagData,
  GenericTag_WriteTagData,
  GenericTag_ReadTagConfig,
  GenericTag_WriteTagConfig,
  GenericTag_LockTagBlock,
  GenericTag_ActivateTagType,
  GenericTag_DeactivateTagType,
  GenericTag_SetTagBitRate,
  GenericTag_GetTagInfo,
  GenericTag_GetLockStatus,
  GenericTag_KillTag,
  GenericTag_ReviveTag,
  GenericTag_EraseTag,
  GenericTag_FormatTag,
  GenericTag_DeselectTag,
  GenericTag_AuthenticateTag,
  Iso14443BTag_SendTagPassword,
  GenericTag_GetApplicationIDs,
  GenericTag_SelectApplication,
  GenericTag_CreateApplication,
  GenericTag_DeleteApplication,
  GenericTag_GetFileIDs,
  GenericTag_SelectFile,
  GenericTag_CreateDataFile,
  GenericTag_CreateValueFile,
  GenericTag_CreateRecordFile,
  GenericTag_GetCommonFileSettings,
  GenericTag_GetDataFileSettings,
  GenericTag_GetValueFileSettings,
  GenericTag_GetRecordFileSettings,
  GenericTag_ChangeFileSettings,
  GenericTag_ReadFile,
  GenericTag_WriteFile,
  GenericTag_DeleteFile,
  GenericTag_ClearFile,
  GenericTag_CreditValueFile,
  GenericTag_DebitValueFile,
  GenericTag_LimitedCreditValueFile,
  GenericTag_GetValue,
  GenericTag_ReadRecords,
  GenericTag_WriteRecord,
  GenericTag_CommitTransaction,
  GenericTag_AbortTransaction,
  GenericTag_EnableEAS,
  GenericTag_DisableEAS,
  GenericTag_ScanEAS,
  GenericTag_ReadAFI,
  GenericTag_WriteAFI,
  GenericTag_ReadDSFID,
  GenericTag_WriteDSFID,
  GenericTag_GetKeyVersion,
  GenericTag_ChangeKey,
  GenericTag_GetApplicationKeySettings,
  GenericTag_GetMasterKeySettings,
  GenericTag_ChangeApplicationKeySettings,
  GenericTag_ChangeMasterKeySettings,
  GenericTag_InitializeSecureMemoryTag,
  GenericTag_SetupSecureMemoryTag,
  GenericTag_InterfaceSend,
  GenericTag_TransportSend,
  GenericTag_InitiatePayment,
  GenericTag_ComputePayment
};

