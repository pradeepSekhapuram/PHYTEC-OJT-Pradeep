#include <stdio.h>
#include <mraa.h>

#define INPUT_PIN 35
#define LED1_PIN 61
#define LED2_PIN 62
#define LED3_PIN 63

int main() {
    // Initialize MRAA
    mraa_init();

    // Initialize GPIO pins
    mraa_gpio_context input_pin = mraa_gpio_init(INPUT_PIN);
    mraa_gpio_context led1_pin = mraa_gpio_init(LED1_PIN);
    mraa_gpio_context led2_pin = mraa_gpio_init(LED2_PIN);
    mraa_gpio_context led3_pin = mraa_gpio_init(LED3_PIN);

    // Set the direction of the pins
    mraa_gpio_dir(input_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(led1_pin, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2_pin, MRAA_GPIO_OUT);
    mraa_gpio_dir(led3_pin, MRAA_GPIO_OUT);

    int switch_state = 0;
    int switch_press_count = 0;

    while (1) {
        int current_switch_state = mraa_gpio_read(input_pin);

        // Check for a rising edge (button press)
        if (current_switch_state == 1 && switch_state == 0) {
            switch_press_count++;

            // Turn off all LEDs
            mraa_gpio_write(led1_pin, 0);
            mraa_gpio_write(led2_pin, 0);
            mraa_gpio_write(led3_pin, 0);

            // Determine which LED to turn on based on the press count
            if (switch_press_count == 1) {
                mraa_gpio_write(led1_pin, 1);
            } else if (switch_press_count == 2) {
                mraa_gpio_write(led2_pin, 1);
            } else if (switch_press_count == 3) {
                mraa_gpio_write(led3_pin, 1);
            }

            printf("Switch pressed %d times\n", switch_press_count);
        }

        switch_state = current_switch_state;
        usleep(100000);  // Sleep for 100ms to avoid high CPU usage
    }

    // Cleanup and close GPIO pins
    mraa_gpio_close(input_pin);
    mraa_gpio_close(led1_pin);
    mraa_gpio_close(led2_pin);
    mraa_gpio_close(led3_pin);

    // Deinitialize MRAA
    mraa_deinit();

    return 0;
}

