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
 * Tag.c
 *
 * Implementation of Tag.
 */
#include "../SkyeTekAPI.h"
#include <stdlib.h>
#include "Tag.h"

unsigned char TagBlockToByte(SKYETEK_TAGTYPE type)
{
  unsigned ix;
  
  for(ix = 0; ix < NUM_TAGTYPEDESCS; ix++)
    if(TagTypeDescriptions[ix].type == type)
      return TagTypeDescriptions[ix].bytesToBlock;
  
  return 1;
}

unsigned int GetTagTypeDescriptionCount(void)
{
  return NUM_TAGTYPEDESCS;
}

LPTAGTYPEDESC GetTagTypeDescription(unsigned int index)
{
  if(index < 0 || index >= NUM_TAGTYPEDESCS)
    return NULL;
  
  return &TagTypeDescriptions[index];
}

SKYETEK_API unsigned int SkyeTek_GetTagTypeCount(void)
{
  return NUM_TAGTYPEDESCS;
}

SKYETEK_API TCHAR *SkyeTek_GetTagTypeName(unsigned int index)
{
  if(index < 0 || index >= NUM_TAGTYPEDESCS)
    return NULL;
  
  return TagTypeDescriptions[index].name;
}

SKYETEK_API SKYETEK_TAGTYPE SkyeTek_GetTagType(unsigned int index)
{
  if(index < 0 || index >= NUM_TAGTYPEDESCS)
    return (SKYETEK_TAGTYPE)NULL;

  
  return TagTypeDescriptions[index].type;
}

SKYETEK_API SKYETEK_TAGTYPE SkyeTek_GetTagTypeFromName(TCHAR *name)
{
  unsigned ix;

  if( name == NULL )
    return AUTO_DETECT;
  
  for(ix = 0; ix < NUM_TAGTYPEDESCS; ix++)
	{
    if(_tcscmp(TagTypeDescriptions[ix].name,name) == 0)
      return TagTypeDescriptions[ix].type;
	}
  return AUTO_DETECT;
}

TCHAR gTT[32];
SKYETEK_API TCHAR *SkyeTek_GetTagTypeNameFromType(SKYETEK_TAGTYPE type)
{
  unsigned ix;
  
  for(ix = 0; ix < NUM_TAGTYPEDESCS; ix++)
	{
    if(TagTypeDescriptions[ix].type == type)
      return TagTypeDescriptions[ix].name;
	}
  memset(gTT,0,32*sizeof(TCHAR));
  _stprintf(gTT,_T("0x%04X"),type);
  return gTT;
}
