//----------------------------------------------------------//
//											LCD.cpp File 
//						Easy to use LCD 3.2' with easy Function
//			Written By Ali Fallah (Kashan) at 95/06/28 (2016)
//----------------------------------------------------------//

#include "AF_sys.h"
#include "AF_Font_24x16.h"
#include "AF_LCD.h"
#include <lpc17xx.h>
#include "AF_va_list.h"
#include "AF_stdarg.h"
#include "..\AF_LIB\AF_string.h"
#include "..\AF_LIB\AF_size_t.h"
#include "B_Roya24h.h"

static volatile unsigned short TextColor = White, BackColor = Black;

	static u8 _curX;
	static u16 _curY;
	
	

	
	
	u8 GetX (void) {return _curX;}
	u16 GetY (void) {return _curY;}

/************************ Local auxiliary functions ***************************/

/*******************************************************************************
* Delay in while loop cycles                                                   *
*   Parameter:    cnt:    number of while cycles to delay                      *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD ::delay  (int cnt) 
{

  cnt <<= DELAY_2N;
  while (cnt--);
}

__asm void wait()
{
    nop
    BX lr
}

void AF_LCD :: wait_delay(int count)
{
  while(count--);
}




void AF_LCD :: changeXY (void)
{
	_curX+=8;
	if(_curX==240){
		_curY+=16;
		_curX=0;
	}
}

/*******************************************************************************
* Send 1 byte over serial communication                                        *
*   Parameter:    byte:   byte to be sent                                      *
*   Return:                                                                    *
*******************************************************************************/

static __inline unsigned char lcd_send (unsigned short byte) 
{
  u32 data ;
  DATA_MSB_Nibble_GPIO->FIODIR |= (0xff<<LCD_MSB_Nibble_OFFSET);  
	DATA_LSB_Nibble_GPIO->FIODIR |= (0xff<<LCD_LSB_Nibble_OFFSET); 
  data = (byte>>8)&0xff;
	DATA_MSB_Nibble_GPIO->FIOCLR |= (0xff<<LCD_MSB_Nibble_OFFSET);
  DATA_MSB_Nibble_GPIO->FIOSET |= data<<LCD_MSB_Nibble_OFFSET;
	wait();
	data = byte & 0xff;
	DATA_LSB_Nibble_GPIO->FIOCLR |= (0xff<<LCD_LSB_Nibble_OFFSET);
	DATA_LSB_Nibble_GPIO->FIOSET |= data<<LCD_LSB_Nibble_OFFSET;
  wait();

  return(1);
}


/*******************************************************************************
* read 1 byte over serial communication                                        *
*   Parameter:    byte:   byte to be sent                                      *
*   Return:                                                                    *
*******************************************************************************/

__inline unsigned short AF_LCD :: lcd_read (void) 
{
  unsigned short id1,id2,id;
  DATA_MSB_Nibble_GPIO->FIODIR &= (~(0xff<<LCD_MSB_Nibble_OFFSET));  
	DATA_LSB_Nibble_GPIO->FIODIR &= (~(0xff<<LCD_LSB_Nibble_OFFSET));
  delay(50);							      //delay some times ///////////////////////////////////////////////////////////////////////////////////////////////
	id1=(DATA_MSB_Nibble_GPIO->FIOPIN >>LCD_MSB_Nibble_OFFSET)&0xFF;
  id2=(DATA_LSB_Nibble_GPIO->FIOPIN >>LCD_LSB_Nibble_OFFSET)&0xFF;
	id = id2|(id1<<8);
  return(id); 
}

/*******************************************************************************
* Write command to LCD controller                                              *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_cmd (unsigned char c) 
{
  LCD_RS(0)
  LCD_RD(1)
  lcd_send(c);
  LCD_WR(0)
  wait();
  LCD_WR(1)
}


/*******************************************************************************
* Write data to LCD controller                                                 *
*   Parameter:    c:      data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_dat (unsigned short c) 
{
  LCD_RS(1)
  LCD_RD(1)
  lcd_send(c);
  LCD_WR(0)
  wait();
  LCD_WR(1)
}

/*******************************************************************************
* Read data from LCD controller                                                *
*   Parameter:                                                                 *
*   Return:               read data                                            *
*******************************************************************************/

__inline unsigned short AF_LCD::rd_dat (void) 
{
  unsigned short val = 0;

  LCD_RS(1)
  LCD_WR(1)
  LCD_RD(0)
  val = lcd_read();
  LCD_RD(1)
  return val;
}

/*******************************************************************************
* Start of data writing to LCD controller                                      *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

__inline void AF_LCD:: wr_dat_start (void) 
{
  LCD_RS(1)
}


/*******************************************************************************
* Stop of data writing to LCD controller                                       *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

__inline void AF_LCD :: wr_dat_stop (void) 
{
  LCD_CS(1)
}


/*******************************************************************************
* Data writing to LCD controller                                               *
*   Parameter:    c:      data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/

__inline void AF_LCD :: wr_dat_only  (unsigned short c) 
{
  lcd_send(c);
  LCD_WR(0)
  wait();
  LCD_WR(1)
}


/*******************************************************************************
* Write to LCD register                                                        *
*   Parameter:    reg:    register to be read                                  *
*                 val:    value to write to register                           *
*******************************************************************************/

__inline void AF_LCD :: wr_reg (unsigned char reg, unsigned short val) 
{
  LCD_CS(0)
  wr_cmd(reg);
  wr_dat(val);
  LCD_CS(1)
}


/*******************************************************************************
* Read from LCD register                                                       *
*   Parameter:    reg:    register to be read                                  *
*   Return:               value read from register                             *
*******************************************************************************/

unsigned short AF_LCD ::rd_reg  (unsigned short reg) 
{
  unsigned short val = 0;

  LCD_CS(0)
  wr_cmd(reg);
  val = rd_dat(); 
  LCD_CS(1)
  return (val);
}


/************************ Exported functions **********************************/

/*******************************************************************************
* Initialize the Graphic LCD controller                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: Init (void) 
{
  /* Configure the LCD Control pins */
  DATA_MSB_Nibble_GPIO->FIODIR |= (0xFF<<LCD_MSB_Nibble_OFFSET);
	DATA_LSB_Nibble_GPIO->FIODIR |= (0xFF<<LCD_LSB_Nibble_OFFSET);
  CONTROL_GPIO_DIR |= PIN_CS | PIN_RS | PIN_WR | PIN_RD | PIN_RST;					
  CONTROL_GPIO_SET  = PIN_CS | PIN_RS | PIN_WR | PIN_RD | PIN_RST;
	
	CONTROL_GPIO_CLR |= PIN_RST;
  delay(5);                            				 	/* Delay 50 ms             		*/
	CONTROL_GPIO_SET |= PIN_RST;
	
  DeviceCode = rd_reg(0x00);

	if(DeviceCode==0x9325||DeviceCode==0x9328)		
	{
				wr_reg(0x00e7,0x0010);      
        wr_reg(0x0000,0x0001);
        wr_reg(0x0001,0x0100);     
        wr_reg(0x0002,0x0700);                   
        wr_reg(0x0003,(1<<12)|(3<<4)|(0<<3));    
        wr_reg(0x0004,0x0000);                                   
        wr_reg(0x0008,0x0207);	           
        wr_reg(0x0009,0x0000);         
        wr_reg(0x000a,0x0000);         
        wr_reg(0x000c,0x0001);         
        wr_reg(0x000d,0x0000);          
        wr_reg(0x000f,0x0000);

        wr_reg(0x0010,0x0000);   
        wr_reg(0x0011,0x0007);
        wr_reg(0x0012,0x0000);                                                                 
        wr_reg(0x0013,0x0000);                 
        delay(5); 
        wr_reg(0x0010,0x1590);   
        wr_reg(0x0011,0x0227);
        delay(5); 
        wr_reg(0x0012,0x009c);                  
        delay(5); 
        wr_reg(0x0013,0x1900);   
        wr_reg(0x0029,0x0023);
        wr_reg(0x002b,0x000e);
        delay(5); 
        wr_reg(0x0020,0x0000);                                                            
        wr_reg(0x0021,0x013f);           
				delay(5); 
        wr_reg(0x0030,0x0007); 
        wr_reg(0x0031,0x0707);   
        wr_reg(0x0032,0x0006);
        wr_reg(0x0035,0x0704);
        wr_reg(0x0036,0x1f04); 
        wr_reg(0x0037,0x0004);
        wr_reg(0x0038,0x0000);        
        wr_reg(0x0039,0x0706);     
        wr_reg(0x003c,0x0701);
        wr_reg(0x003d,0x000f);
        delay(5); 

        wr_reg(0x0050,0x0000);
        wr_reg(0x0051,0x00ef);                   
        wr_reg(0x0052,0x0000);                   
        wr_reg(0x0053,0x013f); 
        
        wr_reg(0x0060,0xa700);        
        wr_reg(0x0061,0x0001); 
        wr_reg(0x006a,0x0000);
        wr_reg(0x0080,0x0000);
        wr_reg(0x0081,0x0000);
        wr_reg(0x0082,0x0000);
        wr_reg(0x0083,0x0000);
        wr_reg(0x0084,0x0000);
        wr_reg(0x0085,0x0000);
      
        wr_reg(0x0090,0x0010);     
        wr_reg(0x0092,0x0000);  
        wr_reg(0x0093,0x0003);
        wr_reg(0x0095,0x0110);
        wr_reg(0x0097,0x0000);        
        wr_reg(0x0098,0x0000);  
		   
        wr_reg(0x0007,0x0133);   
        wr_reg(0x0020,0x0000);                                                            
        wr_reg(0x0021,0x013f); 
	}else if(DeviceCode==0x9320||DeviceCode==0x9300)
	{
		wr_reg(0x00,0x0000);
		wr_reg(0x01,0x0100);								//Driver Output Contral.
		wr_reg(0x02,0x0700);								//LCD Driver Waveform Contral.
		wr_reg(0x03,0x1030);								//Entry Mode Set.

	
		wr_reg(0x04,0x0000);								//Scalling Contral.
		wr_reg(0x08,0x0202);								//Display Contral 2.(0x0207)
		wr_reg(0x09,0x0000);								//Display Contral 3.(0x0000)
		wr_reg(0x0a,0x0000);								//Frame Cycle Contal.(0x0000)
		wr_reg(0x0c,(1<<0));								//Extern Display Interface Contral 1.(0x0000)
		wr_reg(0x0d,0x0000);								//Frame Maker Position.
		wr_reg(0x0f,0x0000);								//Extern Display Interface Contral 2.	    
		delay(5); 
		wr_reg(0x07,0x0101);								//Display Contral.
		delay(5); 								  
		wr_reg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		wr_reg(0x11,0x0007);								//Power Control 2.(0x0001)
		wr_reg(0x12,(1<<8)|(1<<4)|(0<<0));					//Power Control 3.(0x0138)
		wr_reg(0x13,0x0b00);								//Power Control 4.
		wr_reg(0x29,0x0000);								//Power Control 7.
	
		wr_reg(0x2b,(1<<14)|(1<<4));	    
		wr_reg(0x50,0);									  	//Set X Star
		wr_reg(0x51,239);									  //Set X End.
		wr_reg(0x52,0);									  	//Set Y Star
		wr_reg(0x53,319);                   //Set Y End.t.
	
		wr_reg(0x60,0x2700);								//Driver Output Control.
		wr_reg(0x61,0x0001);								//Driver Output Control.
		wr_reg(0x6a,0x0000);								//Vertical Srcoll Control.
	
		wr_reg(0x80,0x0000);								//Display Position? Partial Display 1.
		wr_reg(0x81,0x0000);								//RAM Address Start? Partial Display 1.
		wr_reg(0x82,0x0000);								//RAM Address End-Partial Display 1.
		wr_reg(0x83,0x0000);								//Displsy Position? Partial Display 2.
		wr_reg(0x84,0x0000);								//RAM Address Start? Partial Display 2.
		wr_reg(0x85,0x0000);								//RAM Address End? Partial Display 2.
	
		wr_reg(0x90,(0<<7)|(16<<0));				//Frame Cycle Contral.(0x0013)
		wr_reg(0x92,0x0000);								//Panel Interface Contral 2.(0x0000)
		wr_reg(0x93,0x0001);								//Panel Interface Contral 3.
		wr_reg(0x95,0x0110);								//Frame Cycle Contral.(0x0110)
		wr_reg(0x97,(0<<8));
		wr_reg(0x98,0x0000);								//Frame Cycle Contral.	   
		wr_reg(0x07,0x0173);
	}
	else if(DeviceCode==0x8999)	   //SSD1289
	{
		//************* Start Initial Sequence **********//
		wr_reg(0x00, 0x0001); // Start internal OSC.
		wr_reg(0x01, 0x3B3F); // Driver output control, RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
		wr_reg(0x02, 0x0600); // set 1 line inversion
		//************* Power control setup ************/
		wr_reg(0x0C, 0x0007); // Adjust VCIX2 output voltage
		wr_reg(0x0D, 0x0006); // Set amplitude magnification of VLCD63
		wr_reg(0x0E, 0x3200); // Set alternating amplitude of VCOM
		wr_reg(0x1E, 0x00BB); // Set VcomH voltage
		wr_reg(0x03, 0x6A64); // Step-up factor/cycle setting  7b30
		//************ RAM position control **********/
		wr_reg(0x0F, 0x0000); // Gate scan position start at G0.
		wr_reg(0x44, 0xEF00); // Horizontal RAM address position
		wr_reg(0x45, 0x0000); // Vertical RAM address start position
		wr_reg(0x46, 0x013F); // Vertical RAM address end position
		// ----------- Adjust the Gamma Curve ----------//
		wr_reg(0x30, 0x0000);
		wr_reg(0x31, 0x0706);
		wr_reg(0x32, 0x0206);
		wr_reg(0x33, 0x0300);
		wr_reg(0x34, 0x0002);
		wr_reg(0x35, 0x0000);
		wr_reg(0x36, 0x0707);
		wr_reg(0x37, 0x0200);
		wr_reg(0x3A, 0x0908);
		wr_reg(0x3B, 0x0F0D);
		//************* Special command **************/
		wr_reg(0x28, 0x0006); // Enable test command
		wr_reg(0x2F, 0x12EB); // RAM speed tuning
		wr_reg(0x26, 0x7000); // Internal Bandgap strength
		wr_reg(0x20, 0xB0E3); // Internal Vcom strength
		wr_reg(0x27, 0x0044); // Internal Vcomh/VcomL timing
		wr_reg(0x2E, 0x7E45); // VCOM charge sharing time  
		//************* Turn On display ******************/
		wr_reg(0x10, 0x0000); // Sleep mode off.
		delay(8); // Wait 30mS
		wr_reg(0x11, 0x6870); // Entry mode setup. 262K type B, take care on the data bus with 16it only 
		wr_reg(0x07, 0x0033); // Display ON	*/
	}
else if(DeviceCode==0x8989)
	{
    wr_reg(0x0007,0x0021);
    wr_reg(0x0000,0x0001);
    wr_reg(0x0007,0x0023);
    wr_reg(0x0010,0x0000);
    delay(5);
    wr_reg(0x0007,0x0033);
    wr_reg(0x0011,0x6070);
    wr_reg(0x0002,0x0600);
    wr_reg(0x0003,0x0804);
    wr_reg(0x000C,0x0000);
    wr_reg(0x000D,0x0808);
    wr_reg(0x000E,0x2900);
    wr_reg(0x001E,0x00B8);
    wr_reg(0x0001,0x2B3F);
    wr_reg(0x0010,0x0000);
    wr_reg(0x0005,0x0000);
    wr_reg(0x0006,0x0000);
    wr_reg(0x0016,0xEF1C);
    wr_reg(0x0017,0x0003);
    wr_reg(0x0007,0x0233);
    wr_reg(0x000B,0x01C0);
    wr_reg(0x000F,0x0000);
    wr_reg(0x0041,0x0000);
    wr_reg(0x0042,0x0000);
    wr_reg(0x0048,0x0000);
    wr_reg(0x0049,0x013F);
    wr_reg(0x004A,0x0000);
    wr_reg(0x004B,0x0000);
    wr_reg(0x0044,0xEF00);
    wr_reg(0x0045,0x0000);
    wr_reg(0x0046,0x013F);
    wr_reg(0x0030,0x0707);
    wr_reg(0x0031,0x0204);
    wr_reg(0x0032,0x0204);
    wr_reg(0x0033,0x0502);
    wr_reg(0x0034,0x0507);
    wr_reg(0x0035,0x0204);
    wr_reg(0x0036,0x0204);
    wr_reg(0x0037,0x0502);
    wr_reg(0x003A,0x0302);
    wr_reg(0x003B,0x0302);
    wr_reg(0x0023,0x0000);
    wr_reg(0x0024,0x0000);
    wr_reg(0x0025,0x8000);  
    wr_reg(0x004f,0x0000);      
    wr_reg(0x004e,0x0000);        
	}
}


/*******************************************************************************
* Set draw window region to whole screen                                       *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: WindowMax (void) 
{
  wr_reg(0x50, 0);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, HEIGHT-1);               /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, 0);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, WIDTH-1);                /* Vertical   GRAM End   Address (-1) */
}
/*
*********************************************************************************************************
* Description: 	Setting the coordinate of cursor
* Arguments  : 	(Xpos , Ypos) the coordinate
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: SetCursor(u8 Xpos, u16 Ypos)
{
 	if(DeviceCode==0x8999||DeviceCode==0x9919||DeviceCode==0x8989)
	{
		wr_reg(0x004E, Xpos);
		wr_reg(0X004F, Ypos);
	}
	else 
	{
	wr_reg(R32, Xpos);
	wr_reg(R33, Ypos);
	}
}
/*******************************************************************************
* Clear display                                                                *
*   Parameter:      color:    display clearing color                           *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: Clear (unsigned short color) 
{
  unsigned int   i;

  WindowMax();

  SetCursor(0,0);
  LCD_CS(0)			  
  wr_cmd(0x22);
  wr_dat_start();
  for(i = 0; i < (WIDTH*HEIGHT); i++)
    wr_dat_only(color);
  wr_dat_stop();
}
/*******************************************************************************
* Draw a pixel in foreground color                                             *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: PutPixel (unsigned int x, unsigned int y) 
{
  SetCursor(WIDTH-1-x,y);	   
  LCD_CS(0)
  wr_cmd(0x22);				 
  wr_dat(TextColor);	
  LCD_CS(1)
}


/*******************************************************************************
* Set foreground color                                                         *
*   Parameter:      color:    foreground color                                 *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD ::  SetTextColor (unsigned short color) 
{
  TextColor  = color;
}


/*******************************************************************************
* Set background color                                                         *
*   Parameter:      color:    background color                                 *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: SetBackColor (unsigned short color) 
{
  BackColor  = color;
}
/*******************************************************************************
* Draw character on given position                                             *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   c:        pointer to character bitmap                      *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: DrawChar  (unsigned int x, unsigned int y, unsigned short *c) 
{
  int idx = 0, i, j;

  x = WIDTH-x-CHAR_W;
  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+CHAR_H-1);             /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+CHAR_W-1);             /* Vertical   GRAM End   Address (-1) */

  SetCursor(0,0);					
  LCD_CS(0)								
  wr_cmd(0x22);						
  wr_dat_start();					
  for (j = 0; j < CHAR_H; j++) {
    for (i = CHAR_W-1; i >= 0; i--) {
      if((c[idx] & (1 << i)) == 0x00) {
        wr_dat_only(BackColor);
      } else {
        wr_dat_only(TextColor);
      }
    }
    c++;
  }
  wr_dat_stop();
}


/*******************************************************************************
* Disply character on given line                                               *
*   Parameter:      ln:       line number                                      *
*                   col:      column number                                    *
*                   c:        ascii character                                  *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: DisplayChar  (unsigned int ln, unsigned int col, unsigned char c) 
{
  c -= 32;
  DrawChar(col * CHAR_W, ln * CHAR_H, (unsigned short *)&Font_24x16[c * CHAR_H]);
}


/*******************************************************************************
* Disply string on given line                                                  *
*   Parameter:      ln:       line number                                      *
*                   col:      column number                                    *
*                   s:        pointer to string                                *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: DisplayString  (unsigned int ln, unsigned int col, unsigned char *s) 
{
  WindowMax();
  while (*s) 
  {
    DisplayChar(ln, col++, *s++);
  }
}


/*******************************************************************************
* Clear given line                                                             *
*   Parameter:      ln:       line number                                      *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: ClearLn (unsigned int ln) 
{
  WindowMax();
 // LCD_DisplayString(ln, 0, "                    ");
}

/*******************************************************************************
* Draw bargraph                                                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        maximum width of bargraph (in pixels)            *
*                   val:      value of active bargraph (in 1/1024)             *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: Bargraph (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val) 
{
  int i,j;

  x = WIDTH-x-w;
  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+CHAR_H-1);             /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  val = (val * w) >> 10;                /* Scale value for 24x12 characters   */
  SetCursor(0,0);
  LCD_CS(0)
  wr_cmd(0x22);
  wr_dat_start();
  for (i = 0; i < h; i++) {
    for (j = w-1; j >= 0; j--) {
      if(j >= val) {
        wr_dat_only(BackColor);
      } else {
        wr_dat_only(TextColor);
      }
    }
  }
  wr_dat_stop();
}


/*******************************************************************************
* Display graphical bitmap image at position x horizontally and y vertically   *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bitmap:   address at which the bitmap data resides         *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD :: Bitmap  (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) 
{
  unsigned int    i, j;
  unsigned short *bitmap_ptr = (unsigned short *)bitmap;

  x = WIDTH-x-w;
  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+h-1);                  /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  wr_reg(0x20, y);
  wr_reg(0x21, x);
  LCD_CS(0)
  wr_cmd(0x22);
  wr_dat_start();
  for (j = 0; j < h; j++) {
    bitmap_ptr += w-1;
    for (i = 0; i < w; i++) {
      wr_dat_only(*bitmap_ptr--);
    }
    bitmap_ptr += w+1;
  }
  wr_dat_stop();
}


/*******************************************************************************
* Display graphical bmp file image at position x horizontally and y vertically *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bmp:      address at which the bmp data resides            *
*   Return:                                                                    *
*******************************************************************************/

void AF_LCD ::Bmp  (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bmp) 
{
  unsigned int    i, j;
  unsigned short *bitmap_ptr = (unsigned short *)bmp;

  x = WIDTH-x-w;
  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+h-1);                  /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  wr_reg(0x20, y);
  wr_reg(0x21, x);
  LCD_CS(0)
  wr_cmd(0x22);
  wr_dat_start();
  bitmap_ptr += (h*w)-1;
  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      wr_dat_only(*bitmap_ptr--);
    }
  }
  wr_dat_stop();
}
/******************************************************************************/

 
/*
*********************************************************************************************************
* Description: 	Write start GRAM Command
* Arguments  : 	None
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: WriteRAM_Prepare(void)
{
	wr_cmd(R34);
}
/*
*********************************************************************************************************
* Description: 	In designated areas within the specified color display 
* Arguments  : 	(xsta ,ysta) start coordinate
*				(xend ,yend) end   coordinate
*				color        I don't know  (¡¦-¡¦£©
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: Fill (u8 xsta,u16 ysta,u8 xend,u16 yend,u16 color)
{                    
    u32 n;
											
	wr_reg(R80, xsta); 						
	wr_reg(R81, xend); 							
	wr_reg(R82, ysta); 						
	wr_reg(R83, yend); 						
	SetCursor(xsta,ysta);				
  LCD_CS(0)	  
	WriteRAM_Prepare();  					
  wr_dat_start();	 	   	   
	n=(u32)(yend-ysta+1)*(xend-xsta+1);    
	while(n--){wr_dat_only(color);}			

	wr_reg(R80, 0x0000); 						
	wr_reg(R81, 0x00EF); 						
	wr_reg(R82, 0x0000); 					
	wr_reg(R83, 0x013F); 				
} 
/*
*********************************************************************************************************
* Description: 	DrawPoint
* Arguments  : 	(x ,y) The coordinate
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: DrawPoint  (u16 x,u16 y ) 
{

  WindowMax();

  SetCursor(x,y);
  LCD_CS(0)
  wr_cmd(0x22);
  wr_dat_start();
  wr_dat_only(TextColor );
  wr_dat_stop();
}
/*
*********************************************************************************************************
* Description: 	Draw lines 
* Arguments  : 	(x1 ,y1) start coordinate
*				(x2 ,y2) end   coordinate
* Returns    : 	None
*********************************************************************************************************
*/ 
void AF_LCD :: DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; 											
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 									
	else if(delta_x==0)incx=0;								
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;							
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; 					
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )							
	{  
		DrawPoint(uRow,uCol);						
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   
/*
*********************************************************************************************************
* Description: 	Draw rectanguar 
* Arguments  : 	(x1 ,y1) (x2 ,y2) The diagonal Level vertical 
* Returns    : 	None
*********************************************************************************************************
*/ 
void AF_LCD :: DrawRectangle (u8 x1, u16 y1, u8 x2, u16 y2)
{
	DrawLine(x1,y1,x2,y1);
	DrawLine(x1,y1,x1,y2);
	DrawLine(x1,y2,x2,y2);
	DrawLine(x2,y1,x2,y2);
}

/*
*********************************************************************************************************
* Description: 	In designated areas within the specified circle 
* Arguments  : 	(x0 ,y0) center coordinate
*				 r       radius coordinate
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: Draw_Circle(u8 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             								
	while(a<=b)
	{
		DrawPoint(x0-b,y0-a);                 
		DrawPoint(x0+b,y0-a);                    
		DrawPoint(x0-a,y0+b);                
		DrawPoint(x0-b,y0-a);                    
		DrawPoint(x0-a,y0-b);                    
		DrawPoint(x0+b,y0+a);                      
		DrawPoint(x0+a,y0-b);          
		DrawPoint(x0+a,y0+b);          
		DrawPoint(x0-b,y0+a);             
		a++;
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		DrawPoint(x0+a,y0+b);
	}
} 
/*
*********************************************************************************************************
* Description: 	DrawPoint or white
* Arguments  : 	(x ,y) The coordinate
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: DrawPoint1  (u16 x,u16 y ,u16 color) 
{

  WindowMax();

  SetCursor(x,y);
  LCD_CS(0)
  wr_cmd(0x22);
  wr_dat_start();
  wr_dat_only(color);
  wr_dat_stop();
}
/*
*********************************************************************************************************
* Description: 	In designated areas within the specified character 
* Arguments  : 	(x0 ,y0) The coordinate
*				 num     The value
*				size     size (16 or 12)
*               mode     superposition(1) or not 0
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: ShowChar(char ch)
{      
	
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304 
    u8 temp;
    u8 pos,t;      
		u8 size=16;
		u8 mode=0;
		u8 x = _curX;
		u16 y = _curY;
	
    if(_curX>MAX_CHAR_POSX||_curY>MAX_CHAR_POSY)return;	    
											
	wr_reg(R80,_curX);           							
	wr_reg(R81,_curX+(size/2-1));							
	wr_reg(R82,_curY);           							
	wr_reg(R83,_curY+size-1);    							
	SetCursor(_curX,_curY);            						
	WriteRAM_Prepare();        						
	ch=ch-' ';										
	if(!mode) 											
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[ch][pos];
			else temp=asc2_1608[ch][pos];		 
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)
				{
       				DrawPoint1(x+t,y+pos,TextColor);
				}
				else
				{
       				DrawPoint1(x+t,y+pos,BackColor);			
				}
		        temp>>=1; 
		    }
		}	
	}else											
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[ch][pos];		
			else temp=asc2_1608[ch][pos];		 		
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)DrawPoint(x+t,y+pos);	
		        temp>>=1; 
		    }
		}
	}	    
	
	wr_reg(R80, 0x0000); 								
	wr_reg(R81, 0x00EF); 								
	wr_reg(R82, 0x0000); 					
	wr_reg(R83, 0x013F); 				
	changeXY();	
}
  
/*
*********************************************************************************************************
* Description: 	m^n function
* Arguments  : 	m n
* Returns    : 	None
*********************************************************************************************************
*/
u32 AF_LCD :: mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

/*
*********************************************************************************************************
* Description: 	Show num (from 0 to 4294967295)
* Arguments  : 	(x ,y) The coordinate
*				 num     The value
*				 len	 The number of num
*				size     size (16 or 12)
* Returns    : 	None
*********************************************************************************************************
*/	 
void AF_LCD ::  ShowNum(u8 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
			//	ShowChar(x+(size/2)*t,y,' ',size,1);
				ShowChar(' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	//ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
		ShowChar(temp+'0');
	}
} 
/*
*********************************************************************************************************
* Description: 	Show string (from 0 to 4294967295)
* Arguments  : 	(x ,y) The coordinate
*				 *p    The value
* Returns    : 	None
*********************************************************************************************************
*/	
void AF_LCD :: ShowString(char *p)
{         
    while(*p!='\0')
    {    
			  if(_curX>MAX_CHAR_POSX){_curX=0;_curY+=16;}
        if(_curY>MAX_CHAR_POSY){_curY=_curX=0;Clear(BackColor );}
				ShowChar(*p);
        p++;
    }  
}
/*
*********************************************************************************************************
* Description: 	Show num (from 0 to 99)
* Arguments  : 	(x ,y) The coordinate
*				 num     The value
*				 len	 The number of num
*				size     size (16 or 12)
*				mode     superposition(1) or not 0
* Returns    : 	None
*********************************************************************************************************
*/	 
void AF_LCD :: Show2Num(u8 x,u16 y,u16 num,u8 len,u8 size,u8 mode)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 //	ShowChar(x+(size/2)*t,y,temp+'0',size,mode); 
		ShowChar(temp+'0');
	}
}
/*
*********************************************************************************************************
* Description: 	write picture 
* Arguments  : 	(x0 ,y0) The start point
*               image    pointer of image array
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: write_pic(int x0, int y0 , const unsigned short *image){
static unsigned int x,y;
	for(y=y0;y<320 && y<image[1];y++) {
		for (x=x0;x<240 && x<image[0];x++)	 {
			SetTextColor(image[(y-y0)*240+(x-x0)+2]);
			PutPixel(319-x,y);
		}
	}
}
/*
*********************************************************************************************************
* Description: 	write picture fast
* Arguments  : 	image : pointer of image array
*                
* Returns    : 	None
*********************************************************************************************************
*/
void AF_LCD :: write_pic_fast (const unsigned short *image) 
{
  unsigned int   i;

  WindowMax();
  SetCursor(0,0);
  LCD_CS(0)			  
  wr_cmd(0x22);
  wr_dat_start();
  for(i = 0; i < (WIDTH*HEIGHT); i++)
    wr_dat_only(image[i+2]);
  wr_dat_stop();
}



int AF_LCD :: printf (const char* str, ...) {

	if (!str)
		return 0;

	va_list		args;
	va_start(args, str);
	size_t i;
	for (i = 0; i<strlen(str); i++) {

		switch (str[i]) {

		case '%':

			switch (str[i + 1]) {

				/*** characters ***/
			case 'c': {
				char c = va_arg(args, char);
				ShowChar(c);
				i++;		// go to next character
				break;
			}

					  /*** address of ***/
			case 's': {
				int c = (int&)va_arg(args, char);
				char str[64];
				strcpy(str, (const char*)c);
				ShowString(str);
				i++;		// go to next character
				break;
			}

					  /*** integers ***/
			case 'd':
			case 'i': {
						int c = va_arg (args, int);
						char str[32]={0};
						itoa_s (c, 10, str);
				ShowString(str);
				i++;		// go to next character
				break;
			}

					  /*** display in hex ***/
			case 'X':
			case 'x': {
					int c = va_arg (args, int);
					char str[32]={0};
					itoa_s (c, 16, str);
				ShowString(str);
				i++;		// go to next character
				break;
			}

			default:
				va_end(args);
				return 1;
			}

			break;

		default:
			ShowChar(str[i]);
			break;
		}

	}

	va_end(args);
	return i;
}




//======================================================================================================
//======================================================================================================
//======================================================================================================
//======================================================================================================




void AF_FLCD :: changeXY (void)
{
	_curX+=8;
	if(_curX==240){
		_curY+=16;
		_curX=0;
	}
}


void AF_FLCD :: ShowCharF (u16 ch,u16 offset , u8 width)
{
	start:
#define MAX_CHAR_POSX_F 240
#define MAX_CHAR_POSY_F 320 
    u8 temp;     
		u8 _chX = 240-_curX;
		_chX-=width;
	
    if(_chX<0||_chX>MAX_CHAR_POSX_F||_curY>MAX_CHAR_POSY_F){
				_curY+=24;
				_curX=0;
				//isStick=false;
				goto start;	
		}			
		

	wr_reg(R80,_chX);           							
	wr_reg(R81,_chX+(24/2-1));							
	wr_reg(R82,_curY);           							
	wr_reg(R83,_curY+24-1);    							
	SetCursor(_chX,_curY);            						
	WriteRAM_Prepare();        						
	

	

			
		for(u8 pos=0;pos<width*3;pos+=3)
		{
			for (u8 i=0;i<3;i++){
			temp=fontB_Roya24h_data_table[offset+pos+i]; 
			for(u8 t=0;t<8;t++)
		    {                 
		       
				 if(temp&0x01)
       				DrawPoint1(_chX+(pos/3),_curY+t+(8*i),TextColor);
				   else
							DrawPoint1(_chX+(pos/3),_curY+t+(8*i),BackColor);

		        temp>>=1; 
					 
		    }
			}
		}	
	
	
	wr_reg(R80, 0x0000); 								
	wr_reg(R81, 0x00EF); 								
	wr_reg(R82, 0x0000); 					
	wr_reg(R83, 0x013F); 				
	
//	printf("%x - %x | ",index,ch);
		_curX+=width;
	if(_curX>=240){
		_curY+=24;
		_curX=0;
	if (_curY>MAX_CHAR_POSY_F){_curY=_curX=0;Clear(BackColor);}
	}

}



/*
*********************************************************************************************************
* Description: 	Show string (from 0 to 4294967295)
* Arguments  : 	(x ,y) The coordinate
*				 *p    The value
* Returns    : 	None
*********************************************************************************************************
*/	
static u8 irecycle=0;
u8 AF_FLCD :: recycle (char *ch)
{
	ch++;
	irecycle++;
	if (*ch< 0x7f)
		recycle(ch);
	ch--;
	u16 charc=*ch;
	u16 index = GetExtendedIndex_roya(charc,&fontB_Roya24h);
	uint16_t offset= fontB_Roya24h_offset_table[index];
	uint8_t width = fontB_Roya24h_width_table[index];	
	ShowCharF(charc,offset,width);
	return irecycle;
}

void AF_FLCD :: ShowString(char *p)
{     
		static bool isStick=false;
    while(*p!='\0')
    {  		
			if (*p == '\n')
			{
				_curY+=24;
				_curX=0;
				isStick=false;
			}
			if (*p < 0x7f){	
			u16 index = GetExtendedIndex_roya(*p,&fontB_Roya24h);
			uint16_t offset= fontB_Roya24h_offset_table[index];
			uint8_t width = fontB_Roya24h_width_table[index];	
			ShowCharF(*p,offset,width);
			p++;
			isStick=false;
			}
			
		else {
		
		u16 ch;
		ch=(*p << 8);
		p++;
		ch|=*p;
			

		u8 byteL=	(ch &0x3f);		//(10)111111	
		u8 byteH=((ch >>8 )&0x1f);		//(110)11111
		u16 bb=(byteH<<6);
		bb|=byteL;
		ch=bb;
		
					
	u16 index = GetExtendedIndex_roya(ch,&fontB_Roya24h);
	uint16_t formII = fontB_Roya24h_arabic2_table[index];
			
	if (ch==0x627 || ch == 0x62F || ch == 0x630 || ch == 0x631 || ch == 0x632 || ch == 0x648){
		if (isStick==true && *(p-2)!=32)
		formII++;
			goto exception;	
	}
			
	if (isStick==true && *(p-2)!=32)
		formII++;
	
	if (*(p+1) != 32)
		formII+=2;
	
	exception:
	
	index = GetExtendedIndex_roya (formII,&fontB_Roya24h);
	uint16_t offset= fontB_Roya24h_offset_table[index];
	uint8_t width = fontB_Roya24h_width_table[index];	
	ShowCharF(ch,offset,width);	
	
	if (ch==0x627 || ch == 0x62F || ch == 0x630 || ch == 0x631 || ch == 0x632 || ch == 0x648)
		isStick = false;
	else
		isStick=true;
	
	p++;
    }  
}
}

