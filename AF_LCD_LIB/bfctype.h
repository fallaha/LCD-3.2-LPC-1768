/****************************************************************************
*                                                                           *
* bfctype.h -- Basic Type Definitions                                       *
*                                                                           *
* Copyright (c) 2010, Iseatech Software. All rights reserved.				*
* website: http://www.iseasoft.com/bfc.htm									*
* email:   support@iseatech.com												*
*                                                                           *
****************************************************************************/

#define fontaa 

#ifndef _BFC_TYPE_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#define _BFC_TYPE_H_

#define UCHAR	unsigned char 
#define USHORT	unsigned short
#define ULONG	unsigned long

#define FONT_FLAG_PROP      (1<<0)      /* Is proportional */
#define FONT_FLAG_MONO      (1<<1)      /* Is monospaced */
#define FONT_FLAG_BW        (1<<2)      /* Is a monochrome(black-and-white) font, 1bpp */
#define FONT_FLAG_AA2       (1<<3)      /* Is an antialiased font, 2bpp */
#define FONT_FLAG_AA4       (1<<4)      /* Is an antialiased font, 4bpp */
#define FONT_FLAG_AA8       (1<<5)      /* Is an antialiased font, 8bpp */
#define FONT_FLAG_ASCII     (1<<6)      /* Character encoding: Ascii + ISO8859 */
#define FONT_FLAG_UNICODE   (1<<7)      /* Character encoding: Unicode */
#define FONT_FLAG_SHIFTJIS  (1<<8)      /* Character encoding: Shift_JIS */
#define FONT_FLAG_BIG5      (1<<9)      /* Character encoding: Big5 */
#define FONT_FLAG_GBK       (1<<10)     /* Character encoding: GBK */
#define FONT_FLAG_JOHAB     (1<<11)     /* Character encoding: Johab */

/*
 * .dat font file format definition
 *
 * format                              length  description
 * ----------------------           ---------  ---------------------------------------------------------------------------------------------
 * USHORT  magic                            2  magic number = 0xBFCA, created by BitFontCreator
 * USHORT  version                          2  0x100 for version 1.00, 0x210 for version 2.10  
 * USHORT  flag			                    2  font flag: monospaced or proportional, monochrome or antialiased, encoding
 *
 * USHORT  width                            2  font width in pixels, 0 for variable-width fonts
 * USHORT  height                           2  font height in pixels
 * USHORT  ascent                           2  font ascent (baseline) in pixels
 *
 * USHORT  firstchar                        2  first character code in font, Unicode
 * USHORT  lastchar                         2  last character code in font, Unicode
 * USHORT  nchars							2  # characters in font, maybe NOT equal to lastchar-firstchar+1
 *
 * UCHAR   reversed							1  1 byte, not used
 *
 * UCHAR	 bytesPerUnit					1  how many bytes(1,2 or 4) per unit in imagebits data table, see "Data Length" when export font data 
 * ULONG	 dataUnits;						4  # bytes/words/dwords(based bitsPerUnit) imagebits data in data table
 * UCHAR     *data_table                    4  pointer to the imagebits data table
 * ULONG     *offset_table;					4  pointer to the offsets of the first byte of each character. NULL if this table does not needed
 * USHORT    *width_table;					4  pointer to the width of each character. NULL for fixed width fonts
 * UCHAR     *ascii_index_table;			4  used to find the index of an ascii character[0-255]. NULL if this table does not needed
 * GLYPH_SET *extended_index_table			4  used to find the index of a character[0-65535]. NULL if this table does not needed
 * -------------------------------------------------------------------------------------------------------------------------------------------
 *
 *											   imagebits data of all characters
 * UCHAR   data_table[dataUnits]  dataUnits*1  when (Data Length = 4 or 8 bits per unit)
 *                                         or
 * USHORT  data_table[dataUnits]  dataUnits*2  when (Data Length = 16     bits per unit)
 *                                         or
 * ULONG   data_table[dataUnits]  dataUnits*4  when (Data Length = 32     bits per unit)
 *
 * ------------------------------------------------------------------------------------------------
 *                                          0  if this table does not exist
 * ULONG    offset_table[nchars]           or  ---
 *                               (nchars+1)*4  offsets of the first byte of each character
 * ------------------------------------------------------------------------------------------------
 *                                          0  for fixed width font
 * USHORT   width_table[nchars]            or  ---
 *                                   nchars*2  for variable width font
 * ------------------------------------------------------------------------------------------------
  *                                         0  if this table does not exist
 * UCHAR    ascii_index_table[256]         or  ---
 *                                        256  used to find the index of an ascii character[0-255]
 * ------------------------------------------------------------------------------------------------
 *                                          0  if this table does not exist
 * GLYPH_SET extended_index_table          or  ---
 *                                    .cbThis  used to find the index of a character[0-65535]
 * ------------------------------------------------------------------------------------------------
 */

typedef struct
{
	USHORT	charLow;		/* first character code in this range */
	USHORT	nGlyphs;		/* # characters in this range */
}GLYPH_RANGE;

typedef struct
{
	ULONG  cbThis;			/* sizeof(GLYPH_SET) + sizeof(GLYPH_RANGE)*nRanges */
	USHORT nChars;			/* total # characters in font */
	USHORT nRanges;			/* # ranges */
	GLYPH_RANGE *pRanges;	/* pointer to the first range */
}GLYPH_SET;

typedef struct {
	USHORT	magic;			/* magic number = 0xBFCA, created by BitFontCreator */
	USHORT	version;		/* version: 0x0100 for version 1.00, 0x0210 for 2.10  */
	USHORT	flag;			/* font flag: monospaced or proportional, monochrome or antialiased */

	USHORT	width;			/* font width in pixels. 0 for variable width font */
	USHORT	height;			/* font height in pixels */
	USHORT	ascent;			/* font ascent (baseline) in pixels */

	USHORT	firstChar;		/* first character code defined in font */
	USHORT	lastChar;		/* last character code defined in font */
	USHORT	nChars;			/* # characters in font, maybe not equal to (lastchar-firstchar+1) */

	UCHAR	reserved;			/* 1 byte, not used */

	UCHAR	bytesPerUnit;		/* 1, 2, 4 bytes per unit in imagebits data table, see data length when export font data */
	ULONG	dataUnits;			/* # bytes/words/dwords(based bitsPerUnit) imagebits data in data table */
	UCHAR	*data_table;		/* pointer to the imagebits data table */
	ULONG	*offset_table;		/* pointer to the offsets of the first byte of each character. NULL if this table does not needed */
	USHORT	*width_table;		/* pointer to the width of each character. NULL for fixed width fonts */
	UCHAR	*ascii_index_table;			/* used to find the index of an ascii character[0-255]. NULL if this table does not needed */
	GLYPH_SET *extended_index_table;	/* used to find the index of a character[0-65535]. NULL if this table does not needed */
} FONTHEADER_BFC;

#ifdef __cplusplus
}
#endif

#endif //#ifndef _BFC_TYPE_H_

