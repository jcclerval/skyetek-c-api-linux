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
 * CRC.h
 * Copyright � 2006 - 2008 Skyetek, Inc. All Rights Reserved.
 *
 * Header file for CRC funtions.
 */
#ifndef STAPI_CRC_H
#define STAPI_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * Calculates 16 bit CRC of one byte of data with starting crc
   * @param crc CRC to base calculation from
   * @param data Byte to calculate CRC with
   * @return CRC16 value
   */
  unsigned short crc16OneByte(unsigned short crc, unsigned char data);

  /**
   * Calculates 16 bit CRC over a buffer
   * @preset Start CRC calculation with this preset (usually want this to be 0x0000)
   * @param dataP Buffer
   * @param n Length of buffer
   * @return CRC16 value of the buffer
   */
  unsigned short crc16(unsigned short preset, unsigned char *dataP, unsigned short n);

  /**
   * Calculates 16 bit CRC over a buffer
   * @preset Start CRC calculation with this preset (usually want this to be 0x0000)
   * @param dataP Buffer
   * @param n Length of buffer
   * @return CRC16 value of the buffer
   */
  unsigned short crca16(unsigned short preset, unsigned char *dataP, unsigned short n);

  /**
   * Verifies the CRC16 integrity of a response
   * @param resp Buffer containing the response
   * @param len Length of the buffer to check
   * @return 1 indicates the response is valid, 0 otherwise
   */
  unsigned char verifycrc(unsigned char *resp, unsigned short len, unsigned char isV3);

  /**
   * Verifies the CRC16 integrity of an ASCII response
   * @param resp Buffer containing the response
   * @param len Length of the buffer to check
   * @return 1 indicates the response is valid, 0 otherwise
   */
   unsigned char verifyacrc(unsigned char *resp, unsigned short len, unsigned char isV3);

	/**
	 * Returns the character ASCII representation
	 * of the portion of the 2-byte hex number passed in.
	 * @param c The two-byte hex number
	 * @param upper Set to 0 for 0x000F, 1 for 0x00F0, 2 for 0x0F00 and 3 for 0xF000
	 * @return The character ASCII representation of the nibble
	 */
	unsigned char crcGetASCIIFromHex(unsigned int c, unsigned char pos);

	/**
	 * Returns the hex value for the ASCII string passed in.
	 * @param ascii The ASCII string
	 * @param len Length of the ASCII string
	 * @return The hex value
	 */
	int crcGetHexFromASCII(unsigned char *ascii, int len);

#ifdef __cplusplus
}
#endif

#endif 
