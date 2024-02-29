#include <stdio.h>
#include <stdlib.h>
#include <mraa.h>

#define INPUT_PIN 35
#define OUTPUT_PIN 61

int main() {
    // Initialize MRAA
    mraa_init();

    // Initialize GPIO pins
    mraa_gpio_context switch_pin = mraa_gpio_init(INPUT_PIN);
    mraa_gpio_context led_pin = mraa_gpio_init(OUTPUT_PIN);

    // Set the direction of the pins
    mraa_gpio_dir(switch_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(led_pin, MRAA_GPIO_OUT);

    int switch_state = 0;

    while (1) {
        int current_switch_state = mraa_gpio_read(switch_pin);

        // Check for a rising edge (button press)
        if (current_switch_state == 1 && switch_state == 0) {
            // Toggle the LED
            mraa_gpio_write(led_pin, 1);
        } else if (current_switch_state == 0 && switch_state == 1) {
            // Turn off the LED when the button is released
            mraa_gpio_write(led_pin, 0);
        }

        switch_state = current_switch_state;
        usleep(100000);  // Sleep for 100ms to avoid high CPU usage
    }

    // Cleanup and close GPIO pins
    mraa_gpio_close(switch_pin);
    mraa_gpio_close(led_pin);

    // Deinitialize MRAA
    mraa_deinit();

    return 0;
}

