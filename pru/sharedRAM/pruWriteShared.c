////////////////////////////////////////
// pruWriteToHost.pru1.c
//
// Trying to use the constants table to access DDR.
////////////////////////////////////////
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include "resource_table_empty.h"
#include "prugpio.h"

#define PRU_SHAREDMEM 0x10000

void main(void) {
	// Variable 
	volatile int* share_mem = (volatile int *) PRU_SHAREDMEM;
	uint32_t data = 0xdeadbeef;
	
	
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	
	// Write to DDR from PRU1
	share_mem[0] = data;
	
	// Halt the PRU
	__halt();
}
