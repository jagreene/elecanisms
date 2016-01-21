#include <p24FJ128GB206.h>
#include "config.h"
#include "common.h"
#include "ui.h"
#include "timer.h"

int16_t main(void) {
    int led2_on;
    int led3_on;

    led2_on = 0;
    led3_on = 1;
    init_clock();
    init_ui();
    init_timer();

    led_on(&led1);
    timer_setPeriod(&timer2, 0.1);
    timer_start(&timer2);

    while (1) {
        if (timer_flag(&timer2)) {
            timer_lower(&timer2);
            led_toggle(&led1);
        }

        if(!sw_read(&sw2)){
            timer_setPeriod(&timer2, 0.5);
            timer_start(&timer2);
            led2_on = 1;
            led3_on = 0;
        } else if(!sw_read(&sw3)){
            timer_setPeriod(&timer2, 0.1);
            timer_start(&timer2);
            led2_on = 0;
            led3_on = 1;
        }
        led_write(&led2, led2_on);
        led_write(&led3, led3_on);
    }
}

