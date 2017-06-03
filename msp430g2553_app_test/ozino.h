/*************************************************************************
	> File Name: ozino.h
	> Author:  Zhen Wei 
	> Mail: 
	> Created Time: Wed May 10 15:21:38 2017
 ************************************************************************/

#ifndef _OZINO_H
#define _OZINO_H

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

#endif
