#include <stdio.h>
#include <stdlib.h>
#include <mraa.h>

#define SWITCH_PIN 35
#define LED1_PIN 61
#define LED2_PIN 62

int main() {
    // Initialize MRAA
    mraa_init();

    // Initialize GPIO pins
    mraa_gpio_context switch_pin = mraa_gpio_init(SWITCH_PIN);
    mraa_gpio_context led1_pin = mraa_gpio_init(LED1_PIN);
    mraa_gpio_context led2_pin = mraa_gpio_init(LED2_PIN);

    // Set the direction of the pins
    mraa_gpio_dir(switch_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(led1_pin, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2_pin, MRAA_GPIO_OUT);

    int switch_state = 0;
    int switch_press_count = 0;

    while (1) {
        int current_switch_state = mraa_gpio_read(switch_pin);

        // Check for a rising edge (button press)
        if (current_switch_state == 1 && switch_state == 0) {
            switch_press_count++;

            // Toggle LED1 based on the press count
            for (int i = 0; i < switch_press_count; i++) {
                mraa_gpio_write(led1_pin, !mraa_gpio_read(led1_pin));
            }

            // Toggle LED2 based on 3 times the press count
            for (int i = 0; i < 3 * switch_press_count; i++) {
                mraa_gpio_write(led2_pin, !mraa_gpio_read(led2_pin));
            }

            printf("Switch pressed %d times\n", switch_press_count);
        }

        switch_state = current_switch_state;
        usleep(100000);  // Sleep for 100ms to avoid high CPU usage
    }

    // Cleanup and close GPIO pins
    mraa_gpio_close(switch_pin);
    mraa_gpio_close(led1_pin);
    mraa_gpio_close(led2_pin);

    // Deinitialize MRAA
    mraa_deinit();

    return 0;
}

