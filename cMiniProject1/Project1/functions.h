#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>

#define WITH_ENGINE_TEMP_CONTROL 1 // Define a macro for engine temperature control (currently disabled).

// Function declarations with brief descriptions.
void printMenu(void); // Print the main menu options.
void printSensorsMenu(void); // Print the menu for setting sensor states.
void processTrafficLights(unsigned char trafficLight); // Process traffic light data.
void processRoomTemperature(unsigned char roomTemp); // Process room temperature data.
void processEngineTemperature(unsigned char engineTemp); // Process engine temperature data (if enabled).
void setSensorsStates(unsigned char choice); // Set sensor states based on user input.
void setVehicleStates(unsigned char choice); // Set vehicle states based on user input.

#endif // FUNCTIONS_H_
