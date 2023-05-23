/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE 	DT_ALIAS(led0) // or "DT_NODELABEL(led0)"
#define SW0_NODE	DT_ALIAS(sw0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

void main(void)
{
	int ret;

	if (!device_is_ready(led.port)) return;
	if (!device_is_ready(button.port)) return;

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) return;

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) return;

	while (1) {
		gpio_pin_set_dt(&led, gpio_pin_get_dt(&button));
		k_msleep(SLEEP_TIME_MS);
	}
}
