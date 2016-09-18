//----------------------------------------------------------//
//											main.cpp File 
//						C++ File main LPC1768 & LPC 17xx
//			Written By Ali Fallah (Kashan) at 95/06/28 (2016)
//----------------------------------------------------------//

#include <lpc17xx.h>
#include ".\AF_LIB\UART.h"
#include ".\AF_LIB\AF_string.h"
#include <stdio.h>

#include ".\AF_LCD_LIB\AF_LCD.h"
#include ".\AF_LCD_LIB\AF_image.h"



int main(){
	// ========== variable======================================
	char str[]="In The name Of God...!";
	int a=145;	
	
	// ===========================================================
	SystemInit();
	
	// ========== Defintion ======================================
	UART uart0(0,9600);
	AF_LCD LCD;
	AF_FLCD FLCD;
	
	// ========== initilize color LCD ===========================
	LCD.Clear(White);
	LCD.SetBackColor(White);
	LCD.SetTextColor(Blue);
	
	// ========== Program =======================================
	LCD.printf("string is : %s and int a=%i",str,a); // English print
	FLCD.ShowString("\n     سلام به خداي مهربان " ); // farsi (persian) print --with Font
	
			// ========== Uart & LCD ======================
	LCD.printf("%c",uart0.getchar());

		while (1);
			
}





