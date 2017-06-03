/*************************************************************************
	> File Name: ws2812.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 12 10:43:24 2017
 ************************************************************************/

#include <msp430g2553.h>
#include <stdlib.h>
#include <stdint.h>
#include "ws2812.h"

#define WS2812_SEND_ONE                 P2OUT |= (1 << (PIN));\
                                        asm("NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                        );\
                                        P2OUT &= ~(1 << (PIN));\
                                        asm("NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                        );

#define WS2812_SEND_ZERO                P2OUT |= (1 << (PIN));\
                                        asm("NOP\n\t"\
                                            "NOP\n\t"\
                                        );\
                                        P2OUT &= ~(1 << (PIN));\
                                        asm("NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                            "NOP\n\t"\
                                        );


uint8_t init_ws2812(rgb_leds_t *led_array, uint8_t pin_num, uint16_t num_leds) {
    uint16_t i;
    led_array->led_colors = (rgb_color_t *) malloc (sizeof(rgb_color_t) * num_leds);
    led_array->pin_num = pin_num;
    led_array->num_leds = num_leds;
    
    P2DIR |= (1 << pin_num);
    P2OUT &= ~(1 << pin_num);

    for (i = 0; i < num_leds; i++) {
        led_array->led_colors[i].green = 0;
        led_array->led_colors[i].red = 0;
        led_array->led_colors[i].blue = 0;
    }
    return 1;
}

uint8_t ws2812_set(rgb_leds_t *led_array) {
    uint16_t i;
    uint8_t j;
    const uint8_t PIN = led_array->pin_num;
    P2OUT &= ~(1 << PIN);
    __delay_cycles(1000);

    for (i = 0; i < led_array->num_leds; i++) {
        for (j = 8; j > 0; j--) {
            if (((led_array->led_colors[i].green >> (j - 1)) && 0x01) == 1) {
                WS2812_SEND_ONE;
            } else {
                WS2812_SEND_ZERO;
            }
        }
        for (j = 8; j > 0; j--) {
            if (((led_array->led_colors[i].red >> (j - 1)) && 0x01) == 1) {
                WS2812_SEND_ONE;
            } else {
                WS2812_SEND_ZERO;
            }
        }
        for (j = 8; j > 0; j--) {
            if (((led_array->led_colors[i].blue >> (j - 1)) && 0x01) == 1) {
                WS2812_SEND_ONE;
            } else {
                WS2812_SEND_ZERO;
            }
        }
    }
    return 1;
}

uint8_t ws2812_clear(rgb_leds_t *led_array) {
    uint16_t i = 0;
    for (i = 0; i < led_array->num_leds; i++) {
        led_array->led_colors[i].green = 0;
        led_array->led_colors[i].red = 0;
        led_array->led_colors[i].blue = 0;
    }
    ws2812_set(led_array);
    return 1;    
}

uint8_t ws2812_disable(rgb_leds_t *led_array) {
    free(led_array->led_colors);
    led_array->num_leds = 0;
    return 1;
}

uint8_t ws2812_color_set(rgb_leds_t *led_array, uint16_t index, rgb_color_t led_color) {
    if (index >= led_array->num_leds) return 0;

    led_array->led_colors[index].green = led_color.green;
    led_array->led_colors[index].red = led_color.red;
    led_array->led_colors[index].blue = led_color.blue;
    return 1;
}
