#include <msp430.h> 


/**
 * Name: CCDSensorDataRetrival
 * This code takes 9 inputs (DATA[7:0], DCLK) and 1 output (SHUTTER) from the epc635 sensor.
 * It outputs a HW shutter signal (toggling SHUTTER) to start image acquisition.
 *
 * From MSP430 to BBB:
 * P1.6 (SDO)  ---  P9_18 (SDI)
 * P1.4 (SCL)  ---  P9_22 (SCLK)
 *
 * From MSP430 to epc635:
 * P2.7 (in)   ---  D0
 * P2.6 (in)   ---  D1
 * P3.3 (in)   ---  D2
 * P3.6 (in)   ---  D3
 * P3.7 (in)   ---  D4
 * P2.2 (in)   ---  D5
 * P1.3 (in)   ---  D6
 * P3.0 (in)   ---  D7
 *
 * P3.1 (in)   ---  DCLK
 * P2.3 (out)  ---  SHUTTER
 */
void init(void) {
    // Set up inputs and output from epc635
    P2DIR &= BIT7   // Direct pin as input (D0)
    P2DIR &= BIT6   // Direct pin as input (D1)
    P3DIR &= BIT3   // Direct pin as input (D2)
    P3DIR &= BIT6   // Direct pin as input (D3)
    P3DIR &= BIT7   // Direct pin as input (D4)
    P2DIR &= BIT2   // Direct pin as input (D5)
    P1DIR &= BIT3   // Direct pin as input (D6)
    P3DIR &= BIT0   // Direct pin as input (D7)

    P3DIR &= BIT1   // Direct pin as input (DCLK)
    P2DIR |= BIT3   // Direct pin as output (SHUTTER)

    // Set up SPI for BBB

}

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop the Watchdog timer
	PM5CTL0 &= ~LOCKPM5;        // Disable GPIO power-on default high-impedance mode
}
