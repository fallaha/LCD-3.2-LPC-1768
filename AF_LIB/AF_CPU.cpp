//----------------------------------------------------------//
//												AF_CPU.cpp File 
//									C++ for LPC1768 & LPC 17xx
//			Written By Ali Fallah (Kashan) at 95/06/22 (2016)
//----------------------------------------------------------//

#include "AF_CPU.h"
#include <lpc17XX.h>
#include "AF_define.h"

int CPU :: GetCpuClk (void)
	{
				int AF_status=LPC_SC->PLL0STAT;
		int AF_M=(AF_status&0x7fff)+1;
		int AF_N=((AF_status&0xff0000)>>16)+1;
		int AF_PLL0=2*AF_osc*AF_M/AF_N;
		int AF_CClLSEL=LPC_SC->CCLKCFG+1;
		int AF_CPUCLK=(AF_PLL0/AF_CClLSEL)*1000000;
		return AF_CPUCLK;
	}

