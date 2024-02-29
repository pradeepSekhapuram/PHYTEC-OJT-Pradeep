#include <stdio.h>
#include <stdlib.h>
#include <mraa.h>

#define SWITCH1_PIN 12
#define SWITCH2_PIN 13
#define LED_PIN 62

int main() {
    // Initialize MRAA
    mraa_init();

    // Initialize GPIO pins
    mraa_gpio_context switch1_pin = mraa_gpio_init(SWITCH1_PIN);
    mraa_gpio_context switch2_pin = mraa_gpio_init(SWITCH2_PIN);
    mraa_gpio_context led_pin = mraa_gpio_init(LED_PIN);

    // Set the direction of the pins
    mraa_gpio_dir(switch1_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(switch2_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(led_pin, MRAA_GPIO_OUT);

    int switch1_state = 0;
    int switch2_state = 0;

    while (1) {
        // Read the state of the switches
        int current_switch1_state = mraa_gpio_read(switch1_pin);
        int current_switch2_state = mraa_gpio_read(switch2_pin);

        // Check for a rising edge (button press) on switch1
        if (current_switch1_state == 1 && switch1_state == 0) {
            // Turn on the LED
            mraa_gpio_write(led_pin, 1);
            printf("LED turned ON\n");
        }

        // Check for a rising edge (button press) on switch2
        if (current_switch2_state == 1 && switch2_state == 0) {
            // Turn off the LED
            mraa_gpio_write(led_pin, 0);
            printf("LED turned OFF\n");
        }

        // Update the switch states
        switch1_state = current_switch1_state;
        switch2_state = current_switch2_state;

        usleep(100000);  // Sleep for 100ms to avoid high CPU usage
    }

    // Cleanup and close GPIO pins
    mraa_gpio_close(switch1_pin);
    mraa_gpio_close(switch2_pin);
    mraa_gpio_close(led_pin);

    // Deinitialize MRAA
    mraa_deinit();

    return 0;
}

