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
 * TagFactory.h
 *
 * Creates reader objects.
 */
#ifndef TAG_FACTORY_H
#define TAG_FACTORY_H

#include "../SkyeTekAPI.h"
#include "Tag.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a tag for the given tag type.
 */
SKYETEK_STATUS CreateTagImpl(SKYETEK_TAGTYPE type, LPSKYETEK_ID lpId, LPSKYETEK_TAG* tag);

/**
 * Initializes the tag type for the given tag.
 */
SKYETEK_STATUS InitializeTagType(LPSKYETEK_TAG tag);

/**
 * Frees the tag.
 * @param tag Tag to free
 */
void FreeTagImpl(LPSKYETEK_TAG tag);

/**
 * Duplicate the tag.
 * @param tag Tag to free
 */
LPSKYETEK_TAG DuplicateTagImpl(LPSKYETEK_TAG tag);

#ifdef __cplusplus
}
#endif

#endif 



