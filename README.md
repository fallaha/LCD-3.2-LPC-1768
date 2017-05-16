# LCD (ver 1.0.0)
hello all (iranian or other country)

i rewrite a project. this time for LCD (3.2')

i write two class for work with LCD. the first (LCD class) for only English language with 16*8 fix font and the other (FLCD class) for Farsi (persian) or Arabic languge.

you can change font for second class (FLCD). with a windows program -> BitFontCreator pro 3.5 (i Explanation it in below)

there are verey function in FLCD or LCD class. the FLCD class is the extend of LCD class. so all function in calss LCD existence in FLCD class.

##Usage
for use these class you should follow below code.

	AF_LCD LCD;
	AF_FLCD FLCD;
	
### Example
#### LCD class --English Language and fix font
and for print in LCD for *LCD class* you can follow below code

	LCD.printf("string is : %s and int a=%i",str,a); // English print
	
i write printf function for easy to use of print to LCD. :)

#### FLCD class --Farsi (Persian) Language with change font
this function written for print farsi language to LCD and default font is *B_roya* that support English and persian.

for print a string to LCD with class you can uae below function.

	FLCD.ShowString("\n     سلام به خداي مهربان " );
	
i write farsi language in above string.

note: now i dont Write Printf for FLCD class. but maybe i write it.

## Set A Customize Font
for set the new font and use a Special font, i used a windows program -> BitFontCreator pro 3.5

this program is very easy to use and i learn to how to use it for us LCD.

the first you should know that each character in font has two Characteristic a Width and a Height. the Height for a font is fix (e.g. 24) but the width for each char (in font) is Special (e.g. 8)

in this case i set the Height a fix number and it number is 24. it is very important for us , and you shouldn't forget this object-> that the Height fot us is a fix number 24 (it is 3 byte --3*8=24)

for creat a new special font you should download the BitFontCreator pro 3.5 Software.

![LCD](http://cdn.persiangig.com/preview/UWDqpzGkjC/soft.jpg " BitFontCreator pro 3.5")


set below option! and click Data Format ... (below pic)

![LCD](http://cdn.persiangig.com/preview/LBeIvmXTnu/2.png " BitFontCreator pro 3.5")


then set option and click ok. (below pic)

![LCD](http://cdn.persiangig.com/preview/vwFOIrfRvI/3.png " BitFontCreator pro 3.5")


dont forget, that we set Height to 24 so se it ... (below pic)

![LCD](http://cdn.persiangig.com/preview/qGScDhb65j/4.png " BitFontCreator pro 3.5")




now, we can save it .c file (below pic)

![LCD](http://cdn.persiangig.com/preview/uSuZlkSZRv/5.png " BitFontCreator pro 3.5")


we crete a new font for our LCD. now you follow command blow.

## Edit .C file for our LCD
nice, you should few edit to .c file. for it -> open the .c file that save it in ablove.

the "File_name" is the file name that you select it for save .c file


Defualt name        |       new name
 ------------- |:-------------:
fontFile_name24h_data_table        |   font24h_data_table 
fontFile_name24h_offset_table      |  font24h_offset_table 
fontFile_name24h_width_table       | font24h_width_table    
fontFile_name24h_ascii_index_table |  font24h_ascii_index_table
fontFile_name24h_glyph_ranges      |  font24h_glyph_ranges
fontFile_name24h_glyph_set         |  font24h_glyph_set
fontFile_name24h                   |  font24h

relay you can delete the file name or you can replace the file name with NULL "" 

after it. you should add a function with name *GetExtendedIndex* . for this work, add the below code to your file ( top the "/* clear pre-defines */" string in .C file)

 
	USHORT GetExtendedIndex (USHORT glyph, const FONTHEADER_BFC *pFontHeader)
    {
        if( pFontHeader == NULL )
		      return 0;

        USHORT firstChar = pFontHeader->firstChar;
        USHORT lastChar  = pFontHeader->lastChar;

        if( glyph < firstChar || glyph > lastChar )
			  return 0;  //* not found, return the first glyph index * //

        USHORT index = 0;
        GLYPH_SET *pGlyphSet = pFontHeader->extended_index_table;
        if( pGlyphSet == NULL )
			  return 0;

        GLYPH_RANGE *pRanges = pGlyphSet->pRanges;
        if( pRanges == NULL )
		      return 0;

        index = 0;
        USHORT nRanges = font24h_glyph_set->nRanges;
        for(USHORT i=0; i<nRanges; i++)
        {
            USHORT charLow = pRanges[i].charLow;
            USHORT nGlyphs = pRanges[i].nGlyphs;

            if( glyph < charLow+nGlyphs )
            {
                index += (glyph - charLow);
                return index;
            }
            else
            {
                index += nGlyphs;
            }
        }

        return 0;   //* not found, return the first glyph index * //

    }
		
and if you use farsi (persian) or Arabic language you can see *font24h_arabic2_table* in this [LINK](https://github.com/fallaha/LCD/blob/master/AF_LCD_LIB/B_Roya24h.h)  (from -> hex = 622 or dec=1570)

## Developed By
this was My Project that Write By me (ali fallah) in 19 sep 2016 (95/06/29).

i hope this my work can help you... :)

ForNOW...!

GoodBye...!
  



