////////////////////////////////////////
// imageAcquisition.pru1.c
// After sequencer and configuration codes have been run on the CCD
// sensor, run this code to collect the data
////////////////////////////////////////
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "prugpio.h"


#define CYCLES_PER_SECOND 200000000 /* PRU has 200 MHz clock */

// #define P9_31 (1 << 0) /* R30 at 0x1 = pru1_pru0_pru_r30_0 = ball A13 = P9_31 */

/* Pin definitions for PRU1 */
#define D0 (1 << 0)         // P8_45: 0x0 at R31
#define D1 (1 << 1)         // P8_46: 0x1 at R31
#define D2 (1 << 2)         // P8_43: 0x2 at R31
#define D3 (1 << 3)         // P8_44: 0x3 at R31
#define D4 (1 << 4)         // P8_41: 0x4 at R31
#define D5 (1 << 5)         // P8_42: 0x5 at R31
#define D6 (1 << 6)         // P8_39: 0x6 at R31    
#define D7 (1 << 7)         // P8_40: 0x7 at R31

#define DCLK (1 << 9)       // P8_29: 0x9 at R31
#define SHUTTER (1 << 11)   // P8_30: 0xB at R30

#define PRU_SHAREDMEM 0x10000

volatile register uint32_t __R31; /* input register for PRU */
volatile register uint32_t __R30; /* output register for PRU */

// 8-bit integer to hold pixel data
uint8_t pixel = 0;

void main(void) {
    // Variable declarations
    uint32_t *gpio1 = (uint32_t *)GPIO1;
    volatile int* shared_mem = (volatile int *) PRU_SHAREDMEM;
    
    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
	
	// Make sure that SHUTTER is LOW before shuttering
	__R30 &= ~SHUTTER;
    __delay_cycles(1000);
	
	int pCount = 0;
    
    // Start image acquisition using HW shutter
    __R30 |= SHUTTER;
    __delay_cycles(50); // Hold for 250ns
    __R30 &= ~SHUTTER;

    // While loop to gather data from CCD sensor
    while ( pCount < 12228) {
        
        while( (__R31 & DCLK) == 0 ) {}

        // Wait for data read
        while ( __R31 & DCLK ) {}

        // Wait until we're at the mid-point
        while ( (__R31 & DCLK) == 0 ) {}
        
        // Increment the counter
        pCount++;

        // Take the 8 samples; if signal is high
        // flip the corresponding bit on "pixel"
        
        
        if ( __R31 & D0 )
            pixel |= D0;

        if ( __R31 & D1 )
            pixel |= D1;
        
        if ( __R31 & D2 )
            pixel |= D2;

        if ( __R31 & D3 )
            pixel |= D3;

        if ( __R31 & D4 )
            pixel |= D4;

        if ( __R31 & D5 )
            pixel |= D5;

        if ( __R31 & D6 )
            pixel |= D6;

        if ( __R31 & D6 )
            pixel |= D6;

        if ( __R31 & D7 )
            pixel |= D7;
        
        // Save pixel into Shared RAM (12kB)
        shared_mem[pCount] = pixel;

        // Reset pixel for next data
        pixel = 0;
        
        // Wait out the high level
        while ( __R31 & DCLK ) {}
    }
    
    // Turn on USR 2 LED
    gpio1[GPIO_SETDATAOUT]   = USR2;	// On
    
    // Halt the PRU
    __halt();
}

// Sets pinmux
#pragma DATA_SECTION(init_pins, ".init_pins")
#pragma RETAIN(init_pins)
const char init_pins[] =  
	"/sys/devices/platform/ocp/ocp:P8_30pinmux/state\0pruout\0" \
	"/sys/devices/platform/ocp/ocp:P8_29pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_45pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_46pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_43pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_44pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_41pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_42pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_39pinmux/state\0pruin\0" \
    "/sys/devices/platform/ocp/ocp:P8_40pinmux/state\0pruin\0" \
    "/sys/class/leds/beaglebone:green:usr2/trigger\0none\0" \
    "\0\0";
