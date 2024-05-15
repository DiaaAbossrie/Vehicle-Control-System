#include "functions.h"

// Declare and initialize global variables for the system.
unsigned char engineState = 0; // Current state of the engine (0 = OFF, 1 = ON).
unsigned char acState = 0; // Current state of the AC (0 = OFF, 1 = ON).
unsigned char vehicleSpeed = 0; // Current vehicle speed in km/hr.
unsigned char roomTemperature = 25; // Current room temperature in Celsius.
unsigned char Back = 0; // Variable to indicate whether to go back to the previous menu.
#if WITH_ENGINE_TEMP_CONTROL
unsigned char engineTemperature = 100; // Current engine temperature in Celsius (if enabled).
unsigned char engineTemperatureControlState = 0; // Engine temperature control state (0 = OFF, 1 = ON).
#endif

// Function to print the main menu options.
void printMenu(void) {
    printf("Choose an option\n");
    fflush(stdout);
    printf("a. Turn on the vehicle.\n");
    fflush(stdout);
    printf("b. Turn off the vehicle.\n");
    fflush(stdout);
    printf("c. Quit the system.\n");
    fflush(stdout);
}

// Function to print the menu for setting sensor states.
void printSensorsMenu(void) {
    printf("\nSensors set menu\n");
    fflush(stdout);
    printf("a. Turn off the engine.\n");
    fflush(stdout);
    printf("b. Set the traffic light.\n");
    fflush(stdout);
    printf("c. Set the room temperature. (Temperature sensor)\n");
    fflush(stdout);
#if WITH_ENGINE_TEMP_CONTROL
    printf("d. Set the engine temperature. (Engine temperature sensor)\n");
    fflush(stdout);
#endif
}

// Function to process the traffic light data and update vehicle states accordingly.
void processTrafficLights(unsigned char trafficLight) {
    // Switch-case statement to handle different traffic light colors.
    switch (trafficLight) {
        case 'G':
        case 'g':
            vehicleSpeed = 100; // Set vehicle speed to 100 km/hr for green traffic light.
            break;
        case 'O':
        case 'o':
            vehicleSpeed = 30; // Set vehicle speed to 30 km/hr for orange traffic light.
            if (acState == 0)
                acState = 1; // Turn on the AC if it's currently off.
            // Increase room temperature by 25% and optionally increase engine temperature.
            roomTemperature = roomTemperature * (5 / 4) + 1;
#if WITH_ENGINE_TEMP_CONTROL
            if (engineTemperatureControlState == 0)
                engineTemperatureControlState = 1; // Turn on engine temperature control if it's currently off.
            engineTemperature = engineTemperature * (5 / 4) + 1; // Increase engine temperature.
#endif
            break;
        case 'r':
        case 'R':
            vehicleSpeed = 0; // Set vehicle speed to 0 km/hr for red traffic light.
            break;
        default:
            // Display an error message for invalid traffic light colors.
            printf("Invalid traffic light color. Speed set to 0 km/hr.\n");
            fflush(stdout);
            vehicleSpeed = 0;
    }
    // Display the updated vehicle states after processing the traffic light data.
    printf("\n\nVehicle state after applying traffic light data:\n");
    fflush(stdout);
    printf("Engine state: %s\n", engineState ? "ON" : "OFF");
    fflush(stdout);
    printf("AC: %s\n", acState ? "ON" : "OFF");
    fflush(stdout);
    printf("Vehicle Speed: %d km/hr\n", vehicleSpeed);
    fflush(stdout);
    printf("Room Temperature: %d C\n", roomTemperature);
    fflush(stdout);
#if WITH_ENGINE_TEMP_CONTROL
    printf("Engine Temperature Controller State: %s\n", engineTemperatureControlState ? "ON" : "OFF");
    fflush(stdout);
    printf("Engine Temperature: %d C\n\n", engineTemperature);
    fflush(stdout);
#endif
    // Display the sensor menu after processing the traffic light data.
    printSensorsMenu();
}

// Function to process the room temperature data and update vehicle states accordingly.
void processRoomTemperature(unsigned char roomTemp) {
    if (roomTemp < 10 || roomTemp > 30) {
        if (acState == 0)
            acState = 1; // Turn on the AC if it's currently off.
        roomTemperature = 20; // Set room temperature to 20 degrees Celsius for extreme values.
    } else {
        acState = 0; // Turn off the AC if the room temperature is within a comfortable range.
        roomTemperature = roomTemp;
    }
    // Display the updated vehicle states after processing the room temperature data.
    printf("\n\nVehicle state after applying traffic light data:\n");
    fflush(stdout);
    printf("Engine state: %s\n", engineState ? "ON" : "OFF");
    fflush(stdout);
    printf("AC: %s\n", acState ? "ON" : "OFF");
    fflush(stdout);
    printf("Vehicle Speed: %d km/hr\n", vehicleSpeed);
    fflush(stdout);
    printf("Room Temperature: %d C\n", roomTemperature);
    fflush(stdout);
#if WITH_ENGINE_TEMP_CONTROL
    printf("Engine Temperature Controller State: %s\n", engineTemperatureControlState ? "ON" : "OFF");
    fflush(stdout);
    printf("Engine Temperature: %d C\n\n", engineTemperature);
    fflush(stdout);
#endif
    // Display the sensor menu after processing the room temperature data.
    printSensorsMenu();
}

#if WITH_ENGINE_TEMP_CONTROL
// Function to process the engine temperature data and update vehicle states accordingly.
void processEngineTemperature(unsigned char engineTemp) {
    if (engineTemp < 100 || engineTemp > 150) {
        if (engineTemperatureControlState == 0)
            engineTemperatureControlState = 1; // Turn on engine temperature control if it's currently off.
        engineTemperature = 125; // Set engine temperature to 125 degrees Celsius for extreme values.
    } else {
        engineTemperatureControlState = 0; // Turn off engine temperature control if the temperature is within a safe range.
        engineTemperature = engineTemp;
    }
    // Display the updated vehicle states after processing the engine temperature data.
    printf("\n\nVehicle state after applying traffic light data:\n");
    fflush(stdout);
    printf("Engine state: %s\n", engineState ? "ON" : "OFF");
    fflush(stdout);
    printf("AC: %s\n", acState ? "ON" : "OFF");
    fflush(stdout);
    printf("Vehicle Speed: %d km/hr\n", vehicleSpeed);
    fflush(stdout);
    printf("Room Temperature: %d C\n", roomTemperature);
    fflush(stdout);
    printf("Engine Temperature Controller State: %s\n", engineTemperatureControlState ? "ON" : "OFF");
    fflush(stdout);
    printf("Engine Temperature: %d C\n\n", engineTemperature);
    fflush(stdout);
    // Display the sensor menu after processing the engine temperature data.
    printSensorsMenu();
}
#endif

// Function to set the states of various sensors based on user input.
void setSensorsStates(unsigned char choice) {
    switch (choice) {
        case 'A':
        case 'a':
            engineState = 0; // Turn off the engine.
            printf("The engine turned off.\n\n");
            fflush(stdout);
            Back = 1; // Set the Back variable to 1 to indicate going back to the previous menu.
            break;
        case 'B':
        case 'b':
            unsigned char trafficLight;
            printf("Enter the traffic light color (G, O, R): ");
            fflush(stdout);
            scanf(" %c", &trafficLight);
            processTrafficLights(trafficLight);
            break;
        case 'C':
        case 'c':
            unsigned int roomTemp;
            printf("Enter the room temperature: ");
            fflush(stdout);
            scanf(" %u", &roomTemp);
            processRoomTemperature(roomTemp);
            break;
#if WITH_ENGINE_TEMP_CONTROL
        case 'D':
        case 'd':
            unsigned int engineTemp;
            printf("Enter the engine temperature: ");
            fflush(stdout);
            scanf(" %u", &engineTemp);
            processEngineTemperature(engineTemp);
            break;
#endif
        default:
            // Display an error message for invalid choices.
            printf("Invalid choice. Please try again.\n");
            fflush(stdout);
    }
}

// Function to set the vehicle states based on user input.
void setVehicleStates(unsigned char choice) {
    Back = 0; // Reset the Back variable to 0 before processing new input.
    switch (choice) {
        case 'o':
            engineState = 1; // Turn on the engine.
            printSensorsMenu(); // Display the sensor menu.
            char input;
            // Infinite loop to keep the sensor menu running until the user chooses to go back.
            do {
                scanf(" %c", &input);
                setSensorsStates(input);
                if (Back == 1)
                    break; // Break the loop if the Back variable is set to 1.
            } while (1);
            break;
        case 'f':
            engineState = 0; // Turn off the engine.
            printf("The engine turned off.\n");
            fflush(stdout);
            break;
    }
}
