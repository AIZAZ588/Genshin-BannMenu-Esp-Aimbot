/*
	Keyboard Inputs from User
*/

/* libraries */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <esp_log.h>

/* Global variables */
char c;
char str[100];
int Charindex = 0;  // Index to store characters in the str array

void app_main(void) {
    memset(str, 0, sizeof(str));  // Initialize str to all zeroes

    while (true) {
        c = 0;  // Reset the character before each input

        // Loop to capture characters until we hit 'Enter' (newline character)
        while (c != '\n') {
            c = getchar();  // Get character from user input

            // If a valid character is received
            if (c != 0xff) {
                // Ensure we don't exceed array bounds
                if (Charindex < sizeof(str) - 1) {
					
					printf("%c", c);   // Echo the character back to the user
                    str[Charindex++] = c;  // Store character in the string and increment index
                }
            }
            vTaskDelay(100 / portTICK_PERIOD_MS);  // Delay to allow processing
        }

        // Null-terminate the string
        str[Charindex - 1] = '\0';  // Replace '\n' with a null terminator to end the string

        // Display the entered string
        printf("\nYou Entered: %s\n", str);

        // Reset the index and clear the string for next input
        Charindex = 0;
        memset(str, 0, sizeof(str));

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}