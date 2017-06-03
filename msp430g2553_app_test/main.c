#include <msp430g2553.h>
#include <stdint.h>
#include "ozino.h"
#include "ws2812.h"

// uart functions
void uart_write_char(char c) {
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = c;
}

void uart_write_string(char *buf) {
    while (*buf) uart_write_char(*buf++);
}

void USCI0RX_ISR(void) {
    uint8_t rx_char;
    if (IFG2 & UCA0RXIFG) {
        rx_char = UCA0RXBUF;
        if (rx_char == '\r' || rx_char == '\n') {
            uart_write_string("\r\n");
        } else {
            uart_write_char(rx_char);
        }
    }
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	// configure clocks;
	BCSCTL1 = CALBC1_16MHZ; 		// Set oscillator to 16MHz
	DCOCTL = CALDCO_16MHZ;  		// Set oscillator to 16MHz

    // configure pins
    P1DIR = 0xFF;									// Set P1 to output direction
	P2DIR = 0xFF;									// Set P2 to output direction
	P3DIR = 0xFF;									// Set P3 to output direction

	P1OUT = 0x00;									// Set P1  outputs to logic 0
	P2OUT = 0x00;									// Set P2  outputs to logic 0
	P3OUT = 0x00;									// Set P3  outputs to logic 0

	// init uart
	P1SEL |= BIT1 | BIT2;
    P1SEL2 |= BIT1 | BIT2;
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK = 16MHz
	UCA0BR1 = 0;
	UCA0BR0 = 138;
	UCA0MCTL = UCBRS_7 | UCBRF_0;
	UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
    IE2 |= UCA0RXIE; // enable RX interrupt
	uart_write_string((char *)"APP Started!! UART Ready!\r\n");
    USCIAB0RX_VECTOR_HANDLER = USCI0RX_ISR;

    rgb_leds_t rgb_leds;
    rgb_color_t test_color = { .green = 55, .red = 127, .blue = 0 };
    init_ws2812(&rgb_leds, 2, 7);
    ws2812_color_set(&rgb_leds, 0, test_color);
    ws2812_color_set(&rgb_leds, 1, test_color);
    ws2812_color_set(&rgb_leds, 2, test_color);
    ws2812_color_set(&rgb_leds, 3, test_color);
    ws2812_color_set(&rgb_leds, 4, test_color);
    ws2812_color_set(&rgb_leds, 5, test_color);
    ws2812_color_set(&rgb_leds, 6, test_color);
    ws2812_set(&rgb_leds);

	__bis_SR_register(GIE + LPM4_bits);

	return 0;
}
