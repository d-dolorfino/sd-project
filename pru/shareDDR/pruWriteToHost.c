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

// Definition of control register structures
// cd #pragma DATA_SECTION(PRU1_CTRL, ".PRU1_CTRL")
// pruCtrl PRU1_CTRL;

// Mapping Constant table registers to variables
volatile far uint32_t CT_DDR __attribute__( (cregister( "DDR", near), peripheral));

void main(void) {
	// Variable declaration
	uint32_t *ddrPtr = (uint32_t *)&CT_DDR;
	uint32_t data = 0xdeadbeef;
	
	
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	// Allow PRU to write to Host (AM335x) Memory
	CT_CFG.PMAO_bit.PMAO_PRU1 = 1;
	
	// Pointer to Host DDR memory address
	PRU1_CTRL.CTPPR1_bit.C31_BLK_POINTER = 0;
	
	// Write to DDR from PRU1
	*ddrPtr = data;
	
	// Halt the PRU
	__halt();
}
