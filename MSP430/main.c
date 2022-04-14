#include <msp430fr6989.h>


/**
 * Name: CCDSensorDataRetrival
 * This code takes 9 inputs (DATA[7:0], DCLK) and 1 output (SHUTTER) from the epc635 sensor.
 * It outputs a HW shutter signal (toggling SHUTTER) to start image acquisition. This uses
 * while-loop method implemented by Dr. Abichar to sample the data, polling the DCLK
 *
 * From MSP430 to BBB:
 * P1.6 (SDO)  ---  P9_18 (SDI)
 * P1.4 (SCL)  ---  P9_22 (SCLK)
 * P2.4 (CS)   ---  P9_17 (CS)
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

void initSPI(void) {

    /////////////////////////////////////
    // Configuring the SPI pins
    /////////////////////////////////////
    // Divert UCB0CLK/P1.4 pin to serial clock
    P1SEL1 &= ~BIT4;
    P1SEL0 |= BIT4
    // Divert UCB0SIMO/P1.6 pin to SIMO
    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;
    // OK to ignore UCB0STE/P1.5 since we'll connect the display's enable bit to low (enabled all the time)
    // OK to ignore UCB0SOMI/P1.7 since the display doesn't give back any data
    return;
}

void configSPI(void) {
    //////////////////////////
    // SPI configuration
    //////////////////////////

    // Put eUSCI in reset state while modifying the configuration
    UCB0CTLW0 |= UCSWRST;

    // Set clock phase to "capture on 1st edge, change on following edge"
    UCB0CTLW0 |= UCCKPH;
    // Set clock polarity to "inactive low" (done by default)

    // Set data order to "transmit MSB first"
    UCB0CTLW0 |= UCMSB;
    // Set MCU to "SPI master"
    UCB0CTLW0 |= UCMST;
    // Set SPI to "3 pin SPI" (we won't use eUSCI's chip select) (done by default)

    // Set module to synchronous mode
    UCB0CTLW0 |= UCSYNC;
    // Set clock to SMCLK
    UCB0CTLW0 |= UCSSEL_2;

    // Set clock divider to 1 (SMCLK is from DCO at 8 MHz; we'll run SPI at 8 MHz)
    UCB0BRW = 1;

    // Exit the reset state at the end of the configuration
    UCB0CTLW0 &= ~UCSWRST;

    // Set CS' (chip select) bit to 0 (always enabled)
    P2DIR &= ~BIT5;

    return;
}

// TODO:
void spiWriteByte(uint8_t write) {
    // Wait until BUSY flag clears
    while ( (UCB0IFG & UCTXIFG ) != 0 ) {}
    UCB0TXBUF = write;
}

void init(void) {
    // Set up inputs and output from epc635
    P2DIR &= BIT7;   // Direct pin as input (D0)
    P2DIR &= BIT6;   // Direct pin as input (D1)
    P3DIR &= BIT3;   // Direct pin as input (D2)
    P3DIR &= BIT6;   // Direct pin as input (D3)
    P3DIR &= BIT7;   // Direct pin as input (D4)
    P2DIR &= BIT2;   // Direct pin as input (D5)
    P1DIR &= BIT3;   // Direct pin as input (D6)
    P3DIR &= BIT0;   // Direct pin as input (D7)

    P3DIR &= BIT1   // Direct pin as input (DCLK)
    P2DIR |= BIT3   // Direct pin as output (SHUTTER)

    // Set up SPI for BBB
    initSPI();
    configSPI();
}


void main(void) {
    // Variables
    unsigned char d0, d1, d2, d3, d4, d5, d6, d7;
    char pixel[];

	WDTCTL = WDTPW | WDTHOLD;	// Stop the Watchdog timer
	PM5CTL0 &= ~LOCKPM5;        // Disable GPIO power-on default high-impedance mode

	// Infinite loop
	while(1) {
	    while( (P3IN & BIT1) == 0 ) {}

	    // Wait for data ready
	    while ( (P3IN & BIT1) != 0) {}

	    // Wait until we're at mid-point
	    while( (P3IN & BIT1) == 0) {}

	    // Take the 8 DATA samples
	    d0 = char(P2IN & BIT7);
	    d1 = char(P2IN & BIT6);
	    d2 = char(P3IN & BIT3);
	    d3 = char(P3IN & BIT6);

	    d4 = char(P3IN & BIT7);
	    d5 = char(P2IN & BIT2);
	    d6 = char(P1IN & BIT3);
	    d7 = char(P3IN & BIT0);

	    // TODO: Take data bits and concatenate into a byte

	    // TODO: Transfer using SPI to BBB

	    // Wait until high level
	    while ( (P3IN & BIT1) ) {}
	}
}
