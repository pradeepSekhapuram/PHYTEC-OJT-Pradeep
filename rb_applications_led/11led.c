#include <stdio.h>
#include <mraa.h>
#include <unistd.h>

// Define pin numbers for LEDs and the switch
#define LED1_PIN 62
#define LED2_PIN 61
#define SWITCH_PIN 35

int main() {
    // Initialize GPIO pins
    mraa_gpio_context led1 = mraa_gpio_init(LED1_PIN);
    mraa_gpio_context led2 = mraa_gpio_init(LED2_PIN);
    mraa_gpio_context switch_pin = mraa_gpio_init(SWITCH_PIN);

    // Set the pins as OUTPUT for LEDs and INPUT for the switch
    mraa_gpio_dir(led1, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2, MRAA_GPIO_OUT);
    mraa_gpio_dir(switch_pin, MRAA_GPIO_IN);

    // Initialize variables
    int switch_state = 0;
    int press_count = 0;

    while (1) {
        // Check the switch state
        int current_switch_state = mraa_gpio_read(switch_pin);

        // Check if the switch is pressed
        if (current_switch_state == 1 && switch_state == 0) {
            // Increment press count
            press_count++;

            // Toggle LEDs based on press count
            if (press_count % 2 == 1) {
                mraa_gpio_write(led1, 1);
                mraa_gpio_write(led2, 0);
            } else {
                mraa_gpio_write(led1, 0);
                mraa_gpio_write(led2, 1);
            }

            // Update switch state
            switch_state = 1;

            // Print the current state
            printf("Switch pressed %d times - LED1: %d, LED2: %d\n", press_count,
                   mraa_gpio_read(led1), mraa_gpio_read(led2));
        }

        // Check if the switch is released
        else if (current_switch_state == 0 && switch_state == 1) {
            // Update switch state
            switch_state = 0;
        }

        // Sleep to avoid rapid checking
        usleep(100000);
    }

    // Cleanup GPIO on program exit
    mraa_gpio_write(led1, 0);
    mraa_gpio_write(led2, 0);

    // Close GPIO contexts
    mraa_gpio_close(led1);
    mraa_gpio_close(led2);
    mraa_gpio_close(switch_pin);

    return 0;
}
