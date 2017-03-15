#include <msp430g2553.h>
#include <stdint.h>

// Vector table handlers
typedef void interrupt_vector_handler(void);
interrupt_vector_handler *PORT1_VECTOR_HANDLER = (interrupt_vector_handler *)0x0202;
interrupt_vector_handler *PORT2_VECTOR_HANDLER = (interrupt_vector_handler *)0x0203;
interrupt_vector_handler *ADC10_VECTOR_HANDLER = (interrupt_vector_handler *)0x0205;
interrupt_vector_handler *USCIAB0TX_VECTOR_HANDLER = (interrupt_vector_handler *)0x0206;
interrupt_vector_handler *USCIAB0RX_VECTOR_HANDLER = (interrupt_vector_handler *)0x0207;
interrupt_vector_handler *TIMER0_A1_VECTOR_HANDLER = (interrupt_vector_handler *)0x0208;
interrupt_vector_handler *TIMER0_A0_VECTOR_HANDLER = (interrupt_vector_handler *)0x0209;
interrupt_vector_handler *WDT_VECTOR_HANDLER = (interrupt_vector_handler *)0x020A;
interrupt_vector_handler *COMPARATORA_VECTOR_HANDLER = (interrupt_vector_handler *)0x020B;
interrupt_vector_handler *TIMER1_A1_VECTOR_HANDLER = (interrupt_vector_handler *)0x020C;
interrupt_vector_handler *TIMER1_A0_VECTOR_HANDLER = (interrupt_vector_handler *)0x020D;
interrupt_vector_handler *NMI_VECTOR_HANDLER = (interrupt_vector_handler *)0x020E;

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
        uart_write_char(rx_char);
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

    P1OUT |= BIT0;

	__bis_SR_register(GIE + LPM4_bits);
	return 0;
}
