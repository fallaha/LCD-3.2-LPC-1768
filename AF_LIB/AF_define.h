//----------------------------------------------------------//
//											AF_define.h File 
//						Write for defintion LPC1768 & LPC 17xx
//				Written By Ali Fallah (Kashan) at 95/06/22 (2016)
//----------------------------------------------------------//

#ifndef _CLOCK_POWER_H
#define _CLOCK_POWER_H

#define AF_osc 12 // (MHZ)


// Power Control for Peripherals (PCONP)
#define PCTIM0 	(1<<1)
#define PCTIM1 	(1<<2)
#define PCUART0 (1<<3)
#define PCUART1 (1<<4)
#define PCPWM1 	(1<<6)
#define PCI2C0 (1<<7)
#define PCSPI (1<<8)
#define PCRTC (1<<9)
#define PCSSP1 (1<<10)
#define PCADC (1<<12)
#define PCCAN1 (1<<13)
#define PCCAN2 (1<<14)
#define PCGPIO (1<<15)
#define PCRIT (1<<16)
#define PCMCPWM (1<<17)
#define PCQEI (1<<18)
#define PCI2C1 (1<<19)
#define PCSSP0 (1<<21)
#define PCTIM2 (1<<22)
#define PCTIM3 (1<<23)
#define PCUART2 (1<<24)
#define PCUART3 (1<<25)
#define PCI2C2 (1<<26)
#define PCI2S (1<<27)
#define PCGPDMA (1<<29)
#define PCENET (1<<30)
#define PCUSB (1<<31)



// Peripheral Clock Selection 0 (PCLKSEL0)

// For set clock follow below Table

/* 00 PCLK_peripheral = CCLK/4 
// 01 PCLK_peripheral = CCLK
// 10 PCLK_peripheral = CCLK/2
// 11 PCLK_peripheral = CCLK/8, except for CAN1, CAN2, and
// 															CAN filtering when “11” selects = CCLK/6. */

#define PCLK_WDT(x) (x<<0)
#define PCLK_TIMER0(x) (x<<2)
#define PCLK_TIMER1(x) (x<<4)
#define PCLK_UART0(x) (x<<6)
#define PCLK_UART1(x) (x<<8)
#define PCLK_PWM1(x) (x<<12)
#define PCLK_I2C0(x) (x<<14)
#define PCLK_SPI(x) (x<<16)
#define PCLK_SSP1(x) (x<<20)
#define PCLK_DAC(x) (x<<22)
#define PCLK_ADC(x) (x<<24)
#define PCLK_CAN1(x) (x<<26)
#define PCLK_CAN2(x) (x<<28)
#define PCLK_ACF(x) (x<<30)
// Peripheral Clock Selection 1 (PCLKSEL1)
#define PCLK_QEI(x) (x<<0)
#define PCLK_GPIOINT(x) (x<<2)
#define PCLK_PCB(x) (x<<4)
#define PCLK_I2C1(x) (x<<6)
#define PCLK_SSP0(x) (x<<10)
#define PCLK_TIMER2(x) (x<<12)
#define PCLK_TIMER3(x) (x<<14)
#define PCLK_UART2(x) (x<<16)
#define PCLK_UART3(x) (x<<18)
#define PCLK_I2C2(x) (x<<20)
#define PCLK_I2S(x) (x<<22)
#define PCLK_RIT(x) (x<<26)
#define PCLK_SYSCON(x) (x<<28)
#define PCLK_MC(x) (x<<30)


// Pin function select register 0 (PINSEL0)
#define PINSEL0_RD1 (1<<0) //  GPIO Port 0.0
#define PINSEL0_TXD3 (2<<0)
#define PINSEL0_SDA1 (3<<0)

#define PINSEL0_TD1 (1<<2) // GPIO Port 0.1
#define PINSEL0_RXD3 (2<<2)
#define PINSEL0_SCL1 (3<<2)

#define PINSEL0_TXD0 (1<<4) //GPIO Port 0.2
#define PINSEL0_AD0_7 (2<<4)


#define PINSEL0_RXD0 (1<<6) // GPIO Port 0.3
#define PINSEL0_AD0_6 (2<<6)

#define PINSEL0_I2SRX_CLK (1<<8) // GPIO Port 0.4
#define PINSEL0_RD2 (2<<8)
#define PINSEL0_CAP2_0 (3<<8)

#define PINSEL0_I2SRX_WS (1<<10) // GPIO Port 0.5
#define PINSEL0_TD2 (2<<10)
#define PINSEL0_CAP2_1 (3<<10)

#define PINSEL0_I2SRX_SDA (1<<12) // GPIO Port 0.6
#define PINSEL0_SSEL1 (2<<12)
#define PINSEL0_MAT2_0 (3<<12)

#define PINSEL0_I2STX_CLK (1<<14) // GPIO Port 0.7
#define PINSEL0_SCK1 (2<<14)
#define PINSEL0_MAT2_1 (3<<14)

#define PINSEL0_I2STX_WS (1<<16) // GPIO Port 0.8
#define PINSEL0_MISO1 (2<<16)
#define PINSEL0_MAT2_2 (3<<16)

#define PINSEL0_I2STX_SDA (1<<18) // GPIO Port 0.9
#define PINSEL0_MOSI1 (2<<18)
#define PINSEL0_MAT2_3 (3<<18)

#define PINSEL0_TXD2 (1<<20) // GPIO Port 0.10
#define PINSEL0_SDA2 (2<<20)
#define PINSEL0_MAT3_0 (3<<20)

#define PINSEL0_RXD2 (1<<22) // GPIO Port 0.11
#define PINSEL0_SCL2 (2<<22)
#define PINSEL0_MAT3_1 (3<<22)

#define PINSEL0_TXD1 (1<<30) // GPIO Port 0.15
#define PINSEL0_SCK0 (2<<30)
#define PINSEL0_SCK (3<<30)



// Pin function select register 1 (PINSEL1)
#define PINSEL1_RXD1 (1<<0) //  GPIO Port 0.16 (P0.16)
#define PINSEL1_SSEL0 (2<<0)
#define PINSEL1_SSEL (3<<0)

#define PINSEL1_CTS1 (1<<2) // P0.17
#define PINSEL1_MISO0 (2<<2)
#define PINSEL1_MISO (3<<2)

#define PINSEL1_DCD1 (1<<4) //P0.18
#define PINSEL1_MOSI0 (2<<4)
#define PINSEL1_MOSI (3<<4)

#define PINSEL1_DSR1 (1<<6) //P0.19
#define PINSEL1_SDA1 (3<<6)

#define PINSEL1_DTR1 (1<<8) // P0.20
#define PINSEL1_SCL1 (3<<8)

#define PINSEL1_RI1 (1<<10) // P0.21
#define PINSEL1_RD1 (3<<10)

#define PINSEL1_RTS1 (1<<12) // P0.22
#define PINSEL1_TD1 (3<<12)

#define PINSEL1_AD0_0 (1<<14) // P0.23
#define PINSEL1_I2SRX_CLK (2<<14)
#define PINSEL1_CAP3_0 (3<<14)

#define PINSEL1_AD0_1 (1<<16) // P0.24
#define PINSEL1_I2SRX_WS (2<<16)
#define PINSEL1_CAP3_1 (3<<16)

#define PINSEL1_AD0_2 (1<<18) // P0.25
#define PINSEL1_I2SRX_SDA (2<<18)
#define PINSEL1_TXD3 (3<<18)

#define PINSEL1_AD0_3 (1<<20) // P0.26
#define PINSEL1_AOUT (2<<20)
#define PINSEL1_RXD3 (3<<20)

#define PINSEL1_SDA0 (1<<22) // P0.27
#define PINSEL1_USB_SDA (2<<22)

#define PINSEL1_SCL0 (1<<24) // P0.28
#define PINSEL1_USB_SCL (2<<24)

#define PINSEL1_USB_Dp (1<<26) // P0.29

#define PINSEL1_USB_Dn (1<<28) // P0.30



// Pin function select register 2 (PINSEL2)
#define PINSEL2_ENET_TXD0 (1<<0) //  P1.0

#define PINSEL2_ENET_TXD1 (1<<2) // P1.1

#define PINSEL2_ENET_TX_EN (1<<8) // P1.4

#define PINSEL2_ENET_CRS (1<<16) // P1.8

#define PINSEL2_ENET_RXD0 (1<<18) // P1.9

#define PINSEL2_ENET_RXD1 (1<<20) // P1.10

#define PINSEL2_ENET_RX_ER (1<<28) // P1.14

#define PINSEL2_ENET_REF_CLK (1<<30) // P1.15



// Pin function select register 3 (PINSEL3)
#define PINSEL3_ENET_MDC (1<<0) //  P1.16

#define PINSEL3_ENET_MDIO (1<<2) //P1.17


#define PINSEL3_USB_UP_LED (1<<4) //P1.18
#define PINSEL3_PWM1_1 (2<<4)
#define PINSEL3_CAP1_0 (3<<4)

#define PINSEL3_MCOA0 (1<<6) // P1.19
#define PINSEL3_USB_PPWR (2<<6)
#define PINSEL3_USB_CAP1_1 (3<<6)

#define PINSEL3_MCI0 (1<<8) // P1.20
#define PINSEL3_PWM1_2 (2<<8)
#define PINSEL3_SCK0 (3<<8)


#define PINSEL3_MCABORT (1<<10) // P1.21
#define PINSEL3_PWM1_3 (2<<10)
#define PINSEL3_SSEL0 (3<<10)

#define PINSEL3_MCOB0 (1<<12) // P1.22
#define PINSEL3_USB_PWRD (2<<12)
#define PINSEL3_MAT1_0 (3<<12)

#define PINSEL3_MCI1 (1<<14) // P1.23
#define PINSEL3_PWM1_4 (2<<14)
#define PINSEL3_MISO0 (3<<14)

#define PINSEL3_MCI2 (1<<16) // P1.24
#define PINSEL3_PWM1_5 (2<<16)
#define PINSEL3_MOSI0 (3<<16)

#define PINSEL3_MCOA1 (1<<18) // P1.25
#define PINSEL3_MAT1_1 (3<<18)

#define PINSEL3_MCOB1 (1<<20) // P1.26
#define PINSEL3_PWM1_6 (2<<20)
#define PINSEL3_CAP0_0 (3<<20)

#define PINSEL3_CLKOUT (1<<22) // P1.27
#define PINSEL3_USB_OVRCR (2<<22)
#define PINSEL3_CAP0_1 (3<<22)

#define PINSEL3_MCOA2 (1<<24) // P1.28
#define PINSEL3_PCAP1_0 (2<<24)
#define PINSEL3_MAT0_0 (3<<24)

#define PINSEL3_MCOB2 (1<<26) // P1.29
#define PINSEL3_PCAP1_1 (2<<26)
#define PINSEL3_MAT0_1 (3<<26)

#define PINSEL3_VBUS (2<<28) // P1.30
#define PINSEL3_AD0_4 (3<<28)

#define PINSEL3_SCK1 (2<<30) // P1.31
#define PINSEL3_AD0_5 (3<<30)




// Pin function select register 4 (PINSEL4)
#define PINSEL4_PWM1_1 (1<<0) //  P2.0
#define PINSEL4_TXD1 (2<<0) 

#define PINSEL4_PWM1_2 (1<<2) // P2.1
#define PINSEL4_RXD1 (2<<2) 

#define PINSEL4_PWM1_3 (1<<4) //P2.2
#define PINSEL4_CTS1 (2<<4)

#define PINSEL4_PWM1_4 (1<<6) // P2.3
#define PINSEL4_DCD1 (2<<6)


#define PINSEL4_PWM1_5 (1<<8) // P2.4
#define PINSEL4_DSR1 (2<<8)

#define PINSEL4_PWM1_6 (1<<10) // GP2.5
#define PINSEL4_DTR1 (2<<10)

#define PINSEL4_PCAP1_0 (1<<12) //P2.6 
#define PINSEL4_RI1 (2<<12)

#define PINSEL4_RD2 (1<<14) // P2.7
#define PINSEL4_RTS1 (2<<14)

#define PINSEL4_TD2 (1<<16) // P2.8
#define PINSEL4_TXD2 (2<<16)
#define PINSEL4_ENET_MDC (3<<16)

#define PINSEL4_USB_CONNECT (1<<18) // P2.9
#define PINSEL4_RXD2 (2<<18)
#define PINSEL4_ENET_MDIO (3<<18)

#define PINSEL4_EINT0 (1<<20) // P2.10
#define PINSEL4_NMI (2<<20)

#define PINSEL4_EINT1 (1<<22) // P2.11
#define PINSEL4_I2STX_CLK (3<<22)

#define PINSEL4_EINT2 (1<<24) // P2.12
#define PINSEL4_I2STX_WS (3<<24)

#define PINSEL4_EINT3 (1<<26) // P2.13
#define PINSEL4_I2STX_SDA (3<<26)



//Pin Function Select Register 7 (PINSEL7)
#define PINSEL7_MAT0_0 (2<<18) // P3.25
#define PINSEL7_PWM1_2 (3<<18)

#define PINSEL7_MAT0_1 (2<<20) //P3.26
#define PINSEL7_PWM1_3 (3<<20)


//Pin Function Select Register 9 (PINSEL9)
#define PINSEL9_RX_MCLK (1<<24) //P4.28
#define PINSEL9_MAT2_0 (2<<24)
#define PINSEL9_TXD3 (3<<24)

#define PINSEL9_TX_MCLK (1<<26) // P4.29
#define PINSEL9_MAT2_1 (2<<26)
#define PINSEL9_RXD3 (3<<26)

#endif

