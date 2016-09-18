//----------------------------------------------------------//
//												UART.h File 
//							C++ UART for LPC1768 (eca rev A)
//		Written By Ali Fallah (Kashan) at 95/06/22 (2016)
//----------------------------------------------------------//

#ifndef _UART_H
#define _UART_H

#include <lpc17XX.h>
#include "AF_define.h"
#include "AF_CPU.h"

#define LCR_8bit (3<<0)
#define Enable_DLAB (1<<7)
#define Disable_DLAB ~(1<<7)

#define RBR_Status (1<<0)
#define THR_Status (1<<0)

#define ENABLE_FIFO (1<<0)
#define RESET_RXFIFO (1<<1)
#define RESET_TXFIFO (1<<2)

#define ENABLE_RBR_IRQ (1<<0)
#define ENABLE_THR_IRQ (1<<1)

#define DEFAULT_DIV_PCLK_UART 4

class UART {
	
	private: 
	int8_t _uartnumber;
	int32_t _pclk;
	int _dll;
	void uart0_init();
	void uart1_init();
	void uart2_init();
	void uart3_init();
	unsigned char getchar0 (void);
	unsigned char getchar1 (void);
	unsigned char getchar2 (void);
	unsigned char getchar3 (void);
	void sendchar0 (unsigned char ch);
	void sendchar1 (unsigned char ch);
	void sendchar2 (unsigned char ch);
	void sendchar3 (unsigned char ch);
	
	void _get_dll(int baudrate){
			CPU cpuclk;
		_pclk=cpuclk.GetCpuClk()/DEFAULT_DIV_PCLK_UART; // Pherpheral Clock (UART) --need to change
		_dll=_pclk/(16*baudrate);
	}
	
	public:
		
	int printf (const char* str, ...);
	
	UART (int8_t uart_number){
		_uartnumber=uart_number;
		if (_uartnumber > 3)
			return;
		
		_get_dll(115200);
		
	if (_uartnumber==0)
		uart0_init();
	
	else if (_uartnumber==1)
		uart1_init();
	
	else if (_uartnumber==2)
		uart2_init();
	
	else if (_uartnumber==3)
		uart3_init();
	}
	
		UART (int8_t uart_number,int baudrate){
		_uartnumber=uart_number;
		if (_uartnumber > 3)
			return;
		
		_get_dll(baudrate);
		
	if (_uartnumber==0)
		uart0_init();
	
	else if (_uartnumber==1)
		uart1_init();
	
	else if (_uartnumber==2)
		uart2_init();
	
	else if (_uartnumber==3)
		uart3_init();
	}

	UART(void){
		_uartnumber=0;
		_get_dll(115200);
		uart0_init();
	}
	

unsigned char getchar (void)  // Get Character from Uart
{
		if (_uartnumber==0)
		return getchar0();
		else if (_uartnumber==1)
		return getchar1();
		else if (_uartnumber==2)
		return getchar2();
		else if (_uartnumber==3)
		return getchar3();
		else 
			return 'Q';
}

void sendchar (unsigned char ch){
	  if (_uartnumber==0)
		sendchar0(ch);
		else if (_uartnumber==1)
		sendchar1(ch);
		else if (_uartnumber==2)
		sendchar2(ch);
	  else	if (_uartnumber==3)
		sendchar3(ch);
}

void sendstring (char* str)
{
	for (int i=0;str[i]!='\0';i++)
	{
		sendchar(str[i]);
	}
}

};




#endif




