//----------------------------------------------------------//
//											LCD.h File 
//						Easy to use LCD 3.2' with easy Function
//			Written By Ali Fallah (Kashan) at 95/06/28 (2016)
//----------------------------------------------------------//
#ifndef _LCD_H
#define _LCD_H

#include "AF_sys.h"
#include "AF_Font_24x16.h"


// Drfine By me 
#define family_lpc17xx                    /* TFTLCD definition */
#define TFTLCD_DATA_MSB_Nibble_Port_0
#define LCD_MSB_Nibble_OFFSET          15
#define TFTLCD_DATA_LSB_Nibble_Port_0
#define LCD_LSB_Nibble_OFFSET          4
#define TFTLCD_CONTROLPORT_2
#define TFTLCD_CS                      8
#define TFTLCD_RS                      9
#define TFTLCD_WR                      10
#define TFTLCD_RD                      11
#define TFTLCD_RST                     13



static unsigned short DeviceCode;

#ifdef family_lpc17xx
	#ifdef TFTLCD_DATA_MSB_Nibble_Port_0 
			#define DATA_MSB_Nibble_GPIO          LPC_GPIO0
		#elif defined TFTLCD_DATA_MSB_Nibble_Port_1
			#define DATA_MSB_Nibble_GPIO          LPC_GPIO1
		#elif defined TFTLCD_DATA_MSB_Nibble_Port_2
			#define DATA_MSB_Nibble_GPIO          LPC_GPIO2

		#elif (defined TFTLCD_DATA_MSB_Nibble_Port_3 ||defined TFTLCD_DATA_MSB_Nibble_Port_4)
			#error : this defined port for LCD not suported 8 sequence pin for interchange of data
		#else 
			# error  : not defined LCD DATA MSB_Nibble
	#endif
	#ifdef TFTLCD_DATA_LSB_Nibble_Port_0 
			#define DATA_LSB_Nibble_GPIO          LPC_GPIO0
		#elif defined TFTLCD_DATA_LSB_Nibble_Port_1
			#define DATA_LSB_Nibble_GPIO          LPC_GPIO1
		#elif defined TFTLCD_DATA_LSB_Nibble_Port_2
			#define DATA_LSB_Nibble_GPIO          LPC_GPIO2
		#elif (defined TFTLCD_DATA_LSB_Nibble_Port_3 ||defined TFTLCD_DATA_LSB_Nibble_Port_4)
			#error : this defined port for LCD not suported 8 sequence pin for interchange of data
		#else 
			# error  : not defined LCD DATA LSB_Nibble
	#endif
		
		#ifdef TFTLCD_CONTROLPORT_0
		  #define CONTROL_GPIO_DIR   LPC_GPIO0->FIODIR
			#define CONTROL_GPIO_SET   LPC_GPIO0->FIOSET
			#define CONTROL_GPIO_CLR   LPC_GPIO0->FIOCLR
			#define CONTROL_GPIO_PIN   LPC_GPIO0->FIOPIN
		#elif defined TFTLCD_CONTROLPORT_1
		  #define CONTROL_GPIO_DIR   LPC_GPIO1->FIODIR
			#define CONTROL_GPIO_SET   LPC_GPIO1->FIOSET
			#define CONTROL_GPIO_CLR   LPC_GPIO1->FIOCLR
			#define CONTROL_GPIO_PIN   LPC_GPIO1->FIOPIN
		#elif defined TFTLCD_CONTROLPORT_2
		  #define CONTROL_GPIO_DIR   LPC_GPIO2->FIODIR
			#define CONTROL_GPIO_SET   LPC_GPIO2->FIOSET
			#define CONTROL_GPIO_CLR   LPC_GPIO2->FIOCLR
			#define CONTROL_GPIO_PIN   LPC_GPIO2->FIOPIN
    #elif (defined TFTLCD_CONTROLPORT_3 || defined TFTLCD_CONTROLPORT_4 )
			#error : this port not suported 4  pin for control signal
		#else 
			# error  : not defined LCD CONTROLPORT 
		#endif
		
#endif

#define PIN_CS    (1 << TFTLCD_CS)
#define PIN_RS		(1 << TFTLCD_RS)
#define PIN_WR		(1 << TFTLCD_WR)
#define PIN_RD		(1 << TFTLCD_RD) 
#define PIN_RST		(1 << TFTLCD_RST) 
			
/*------------------------------------------------------------------------------
  Color coding
  LCD is coded:   15..11 red, 10..5 green, 4..0 blue  (unsigned short)  LCD_R5, LCD_G6, LCD_B5   
  original coding: 17..12 red, 11..6 green, 5..0 blue                   ORG_R6, ORG_G6, ORG_B6

  ORG_R1..5 = LCD_R0..4,  ORG_R0 = LCD_R4
  ORG_G0..5 = LCD_G0..5,
  ORG_B1..5 = LCD_B0..4,  ORG_B0 = LCD_B4
 *----------------------------------------------------------------------------*/
                            
/* LCD RGB color definitions                                                 */
#define Black           0x0000		  /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */
#define WHITE           0XFFFF      /* 255, 255, 255 */   
#define RED             0xF800      /* 255,   0,   0 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define BIOS_BLUE     0x0200ac

#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53






/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N    18

/*---------------------- Graphic LCD size definitions ------------------------*/

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

/*--------------- Graphic LCD interface hardware definitions -----------------*/


/* Pin CS setting to 0 or 1                                                   */
#define LCD_CS(x)     ((x) ? (CONTROL_GPIO_SET |= PIN_CS) : (CONTROL_GPIO_CLR |= PIN_CS));
/* Pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)     ((x) ? (CONTROL_GPIO_SET |= PIN_RS) : (CONTROL_GPIO_CLR |= PIN_RS));
/* Pin WR setting to 0 or 1                                                   */
#define LCD_WR(x)     ((x) ? (CONTROL_GPIO_SET |= PIN_WR) : (CONTROL_GPIO_CLR |= PIN_WR));
/* Pin RD setting to 0 or 1                                                   */
#define LCD_RD(x)     ((x) ? (CONTROL_GPIO_SET |= PIN_RD) : (CONTROL_GPIO_CLR |= PIN_RD));
/* Pin RST setting to 0 or 1                                                   */
#define LCD_RST(x)    ((x) ? (CONTROL_GPIO_SET |= PIN_RST): (CONTROL_GPIO_CLR |= PIN_RST));



class AF_LCD{
	protected:

	
	u8 GetX (void);
	u16 GetY (void);
	int Printf(const char* str, ...);
	void wait_delay(int count);
	static __inline unsigned short lcd_read (void) ;
	u32 mypow(u8 m,u8 n);
	void DrawPoint1 (u16 x,u16 y ,u16 color) ;
	void WriteRAM_Prepare(void);
	void SetCursor(u8 Xpos, u16 Ypos);
	static unsigned short rd_reg (unsigned short reg) ;
	static __inline void wr_dat_only (unsigned short c) ;
	static __inline void wr_dat_stop (void) ;
	static __inline void wr_dat_start (void);
	static __inline unsigned short rd_dat (void) ;
	static void delay (int cnt) ;	
	static void changeXY (void);
	static __inline void wr_reg (unsigned char reg, unsigned short val);	
	
	public:
	int printf (const char* str, ...);
	void Init           (void);
	void WindowMax      (void);
	void PutPixel       (unsigned int x, unsigned int y);
	void SetTextColor   (unsigned short color);
	void SetBackColor   (unsigned short color);
	void Clear          (unsigned short color);
	void DrawChar       (unsigned int x, unsigned int y, unsigned short *c);
	void DisplayChar    (unsigned int ln, unsigned int col, unsigned char  c);
	void DisplayString  (unsigned int ln, unsigned int col, unsigned char *s);
	void ClearLn        (unsigned int ln);
	void Bargraph       (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val);
	void Bitmap         (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);
	void Bmp            (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bmp);

	void Fill           (u8 xsta,u16 ysta,u8 xend,u16 yend,u16 color);
	void DrawPoint      (u16 x,u16 y);
	void DrawLine       (u16 x1, u16 y1, u16 x2, u16 y2);
	void DrawRectangle  (u8 x1, u16 y1, u8 x2, u16 y2);
	void Draw_Circle        (u8 x0,u16 y0,u8 r);
	void ShowChar(char ch);
	void ShowNum        (u8 x,u16 y,u32 num,u8 len,u8 size);
	void ShowString(char *p);
	void Show2Num       (u8 x,u16 y,u16 num,u8 len,u8 size,u8 mode);
	void write_pic      (int x0, int y0 , const unsigned short *image);
	void write_pic_fast (const unsigned short *image); 
	
	AF_LCD (void)
	{
		Init();
	}

};





class AF_FLCD : public AF_LCD
{
	
	public:
	
	AF_FLCD (void)
	{
		Init();
	}
	
	void ShowCharF (u16 ch,u16 offset , u8 width);
	void ShowString(char *p);
	void changeXY (void);	
	u8 recycle (char *ch);
};



#endif



