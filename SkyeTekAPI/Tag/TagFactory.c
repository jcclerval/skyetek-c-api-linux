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
 * TagFactory.c
 *
 * Implementation of the TagFactory.
 */
#include "../SkyeTekAPI.h"
#include "Tag.h"
#include "TagFactory.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


/* NOTE: We can add factories for each tag type 
 *       later if there is tag-specific data that
 *       needs to be stored. For now, it's overkill.
 */
SKYETEK_STATUS CreateTagImpl(SKYETEK_TAGTYPE type, LPSKYETEK_ID lpId, LPSKYETEK_TAG* tag)
{
  LPSKYETEK_TAG t;
  unsigned int ix;
  TCHAR *str = NULL;
  
  if( tag == NULL )
    return SKYETEK_INVALID_PARAMETER;

  t = *tag = (LPSKYETEK_TAG)malloc(sizeof(SKYETEK_TAG));
  if( t == NULL )
    return SKYETEK_OUT_OF_MEMORY;

  memset(t,0,sizeof(SKYETEK_TAG));
  t->type = type;
  InitializeTagType(t);

  if( lpId != NULL && lpId->id != NULL && lpId->length > 0 && lpId->length < SKYETEK_MAX_TAG_LENGTH )
  {
    t->id = SkyeTek_AllocateID(lpId->length);
    if( t->id == NULL )
    {
      free(t);
      return SKYETEK_OUT_OF_MEMORY;
    }
    for(ix = 0; ix < lpId->length; ix++)
      t->id->id[ix] = lpId->id[ix];
  }

  str = SkyeTek_GetStringFromID(t->id);
  if( str != NULL )
  {
    _tcscpy(t->friendly, str);
    SkyeTek_FreeString(str);
  }
  else
  {
    _tcscpy(t->friendly, _T("unknown"));
  }

  return SKYETEK_SUCCESS;
}

SKYETEK_STATUS InitializeTagType(LPSKYETEK_TAG tag)
{
  unsigned int ix = 0;

  if( tag == NULL )
    return SKYETEK_INVALID_PARAMETER;

  ix = tag->type >> 8;
  switch(ix)
  {
    case 0x00:
      if( tag->type == ISO_14443A_AUTO_DETECT || tag->type == ISO_MIFARE_ULTRALIGHT )
        tag->internal = &Iso14443ATagImpl;
      else if( tag->type == ISO_14443B_AUTO_DETECT )
        tag->internal = &Iso14443BTagImpl;
      else
        tag->internal = &GenericTagImpl;
      break;
    case 0x02:
      if( tag->type == MIFARE_DESFIRE )
        tag->internal = &DesfireTagImpl;
      else 
        tag->internal = &Iso14443ATagImpl;
      break;
    case 0x03:
      tag->internal = &Iso14443BTagImpl;
      break;
    default:
      tag->internal = &GenericTagImpl;
      break;
  }
  return SKYETEK_SUCCESS;
}

void FreeTagImpl(LPSKYETEK_TAG tag)
{
  if( tag == NULL )
    return;
  if( tag->id != NULL )
    SkyeTek_FreeID(tag->id);
  free(tag);
}

LPSKYETEK_TAG DuplicateTagImpl(LPSKYETEK_TAG tag)
{
  LPSKYETEK_TAG t = NULL;
  TCHAR *str = NULL;
  unsigned int ix = 0;

  if( tag == NULL )
    return NULL;

  t = (LPSKYETEK_TAG)malloc(sizeof(SKYETEK_TAG));
  if( t == NULL )
    return NULL;

  memset(t,0,sizeof(SKYETEK_TAG));
  
  t->type = tag->type;
  t->afi = tag->afi;
  t->rf = tag->rf;
  t->session = tag->session;

  InitializeTagType(t);

  if( tag->id != NULL )
  {
    t->id = SkyeTek_AllocateID(tag->id->length);
    if( t->id == NULL )
    {
      free(t);
      return NULL;
    }
    for(ix = 0; ix < tag->id->length; ix++)
      t->id->id[ix] = tag->id->id[ix];
  }

  str = SkyeTek_GetStringFromID(t->id);
  if( str != NULL )
  {
    _tcscpy(t->friendly, str);
    SkyeTek_FreeString(str);
  }


  return t;
}

