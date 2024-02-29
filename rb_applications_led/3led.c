#include <stdio.h>
#include <stdlib.h>
#include <mraa.h>

#define SWITCH1_PIN 12
#define SWITCH2_PIN 13
#define SWITCH3_PIN 14
#define LED1_PIN 61
#define LED2_PIN 62
#define LED3_PIN 63

int main() {
    // Initialize MRAA
    mraa_init();

    // Initialize GPIO pins
    mraa_gpio_context switch1_pin = mraa_gpio_init(SWITCH1_PIN);
    mraa_gpio_context switch2_pin = mraa_gpio_init(SWITCH2_PIN);
    mraa_gpio_context switch3_pin = mraa_gpio_init(SWITCH3_PIN);
    mraa_gpio_context led1_pin = mraa_gpio_init(LED1_PIN);
    mraa_gpio_context led2_pin = mraa_gpio_init(LED2_PIN);
    mraa_gpio_context led3_pin = mraa_gpio_init(LED3_PIN);

    // Set the direction of the pins
    mraa_gpio_dir(switch1_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(switch2_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(switch3_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(led1_pin, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2_pin, MRAA_GPIO_OUT);
    mraa_gpio_dir(led3_pin, MRAA_GPIO_OUT);

    int switch1_state = 0;
    int switch2_state = 0;
    int switch3_state = 0;

    while (1) {
        // Read the state of the switches
        int current_switch1_state = mraa_gpio_read(switch1_pin);
        int current_switch2_state = mraa_gpio_read(switch2_pin);
        int current_switch3_state = mraa_gpio_read(switch3_pin);

        // Check for a rising edge (button press) on switch1
        if (current_switch1_state == 1 && switch1_state == 0) {
            mraa_gpio_write(led1_pin, 1);
            printf("LED1 turned ON\n");
            usleep(500000);  // Sleep for 500ms
            mraa_gpio_write(led1_pin, 0);
            printf("LED1 turned OFF\n");
        }

        // Check for a rising edge (button press) on switch2
        if (current_switch2_state == 1 && switch2_state == 0) {
            mraa_gpio_write(led2_pin, 1);
            printf("LED2 turned ON\n");
            usleep(500000);  // Sleep for 500ms
            mraa_gpio_write(led2_pin, 0);
            printf("LED2 turned OFF\n");
        }

        // Check for a rising edge (button press) on switch3
        if (current_switch3_state == 1 && switch3_state == 0) {
            mraa_gpio_write(led3_pin, 1);
            printf("LED3 turned ON\n");
            usleep(500000);  // Sleep for 500ms
            mraa_gpio_write(led3_pin, 0);
            printf("LED3 turned OFF\n");
        }

        // Update the switch states
        switch1_state = current_switch1_state;
        switch2_state = current_switch2_state;
        switch3_state = current_switch3_state;

        usleep(100000);  // Sleep for 100ms to avoid high CPU usage
    }

    // Cleanup and close GPIO pins
    mraa_gpio_close(switch1_pin);
    mraa_gpio_close(switch2_pin);
    mraa_gpio_close(switch3_pin);
    mraa_gpio_close(led1_pin);
    mraa_gpio_close(led2_pin);
    mraa_gpio_close(led3_pin);

    // Deinitialize MRAA
    mraa_deinit();

    return 0;
}

