/**
 * @file distort.c
 * @author Ali Nasrolahi (a.nasrolahi01@gmail.com)
 * @brief Generates distortion using FS1000A module.
 * @version 1.0
 * @date 2023-05-19
 */

#include "common.h"
#include "driver/gpio.h"
#include "driver/hw_timer.h"

/**
 * @brief Set GPIO pin.
 * @note D15/SCL/D3 for WeMos D1 R1.
 */
#define GPIO_OUTPUT_IO_0 5

/**
 * @brief Mask of requested pins.
 */
#define PINS (1ULL << GPIO_OUTPUT_IO_0)

/* Pulses */
#define PULSE_CNT 1

/* starts from 10khz */
#define BASE_FREQ 10

/* Sequences */
#define SEQ 50

#define WAVE_LENGTH (1000 * 1000 / BASE_FREQ * 2)

void hw_timer_pulse_ctl(void *arg)
{
    static int state;

    gpio_set_level(GPIO_OUTPUT_IO_0, state ^ 1);
}

void app_main(void)
{
    gpio_config_t io_conf;

    /**
     * @brief Here we settings up GPIO which connected to our
     * FS1000A module.
     */
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = PINS;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;

    gpio_config(&io_conf);

    INFO("Initialize hw_timer for hw_timer_pulse_ctl");
    hw_timer_init(hw_timer_pulse_ctl, NULL);

    for (int pulses = PULSE_CNT, seq = 1; seq <= SEQ; seq++) {
        INFO("Sequences %d", seq);
        while (pulses--) {
            hw_timer_alarm_us(WAVE_LENGTH * seq, 1);
        }
    }

    INFO("Deinitialize hw_timer for callback1");
    hw_timer_deinit();
}
