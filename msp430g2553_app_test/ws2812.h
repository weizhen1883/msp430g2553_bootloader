/*************************************************************************
	> File Name: ws2812.h
	> Author: 
	> Mail: 
	> Created Time: Fri Jun  2 01:30:26 2017
 ************************************************************************/

#ifndef _WS2812_H
#define _WS2812_H

typedef struct {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} rgb_color_t;

typedef struct {
    uint8_t pin_num;
    uint16_t num_leds;
    rgb_color_t *led_colors;
} rgb_leds_t;

uint8_t init_ws2812(rgb_leds_t *led_array, uint8_t pin_num, uint16_t num_leds);
uint8_t ws2812_set(rgb_leds_t *led_array);
uint8_t ws2812_clear(rgb_leds_t *led_array);
uint8_t ws2812_disable(rgb_leds_t *led_array);
uint8_t ws2812_color_set(rgb_leds_t *led_array, uint16_t index, rgb_color_t led_color);

#endif
