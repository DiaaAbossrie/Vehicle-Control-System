#include "functions.h"

int main(void) {
    // Infinite loop to keep the program running until the user decides to quit.
    do {
        // Display the main menu.
        printMenu();
        char input;
        // Get user input for menu choice.
        scanf(" %c", &input);

        // Process user input with a switch-case statement.
        switch (input) {
            case 'A':
            case 'a':
                // Call the function to turn on the vehicle.
                setVehicleStates('o');
                break;
            case 'B':
            case 'b':
                // Call the function to turn off the vehicle.
                setVehicleStates('f');
                break;
            case 'C':
            case 'c':
                // Print a message and exit the program when the user chooses to quit.
                printf("Quitting the system.\n");
                return 0;
            default:
                // Display an error message for invalid choices.
                printf("Invalid choice. Please try again.\n");
        }
    } while (1); // Infinite loop condition to keep the program running.
    return 0; // Return 0 to indicate successful program execution.
}
