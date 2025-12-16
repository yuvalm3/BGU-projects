/**
Manage.Jerries file:
Building a system to manage existing Jerries by Morty.
This part will focus on writing the different Jerries and performing actions on them
*/



#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jerry.h"


// Function to free each planet in Planets array
void clean_planets_array(pPlanet* array, int size) {
    int i = 0;
    for (i=0; i < size; i++) {
        destroy_planet(array[i]);
        array[i] = NULL;
    }
}

// Function to free each Jerry in Jerries array
void clean_jerries_array(pJerry* array, int size) {
    int i = 0;
    for (i=0; i < size; i++) {
        destroy_Jerry(array[i]);
        array[i] = NULL;
    }
}

// Function to free each Jerry array
void clean_pc_array(pPhysicalCharacteristic* array, int size) {
    int i = 0;
    for(i=0; i < size; i++) {
        destroy_PC(array[i]);
        array[i] = NULL;
    }
    free(array);
}

/**
read_config_file function:
input: a path to a configuration file, array of all planets, array of all Jerries, number of planets in array, number of Jerries in array
output: status success/failure about the reading and storing of data
purpose: reading all file in once
*/
status read_config_file(char* file,pPlanet* Planets_Array,pJerry* Jerries_Array, int num_of_planets,int num_of_jerries) {
    // Open the configuration file
    FILE* config_file = fopen(file, "r");
    if (config_file == NULL) { // Check if NULL
        return failure;
    }

    char line[256]; // A buffer to hold the lines from configuration file

    fgets(line, sizeof(line), config_file); // Read the first row of the file
    line[strcspn(line, "\n")] = '\0'; // Remove the '/n' to compare to the word 'Planets'
    if (strcmp(line, "Planets")==0) { // check if the first line is the word "Planets"
        // create the planets
        for (int i = 0; i < num_of_planets; i++) {
            fgets(line, sizeof(line), config_file); //read a line for a planet
            char* name = strtok(line, ","); //store planet's name
            float x = atof(strtok(NULL,",")); //store planet's x
            float y = atof(strtok(NULL,",")); //store planet's y
            float z = atof(strtok(NULL,"/n")); //store planet's z

            pPlanet temp = create_Planet(name, x, y, z); // Create a single planet
            if (temp == NULL) { // If failed - clean all memory
                clean_planets_array(Planets_Array, num_of_planets);
                return failure;
            }

            // Create and store the planet if success
            Planets_Array[i] = temp;
        }
    }
    else {
        fclose(config_file); // Close the file if first word in file isn't 'Planets'
        return failure;
    }

    fgets(line, sizeof(line), config_file); // Read next row and check if the word 'Jerries' appear
    line[strcspn(line, "\n")] = '\0'; // Remove the '/n' to compare to the word 'Jerries'
    if(strcmp(line, "Jerries") == 0) {
        // Create all Jerries
        for (int i = 0; i < num_of_jerries; i++) {
            if (i == 0) {
                fgets(line, sizeof(line), config_file); //read a line for a Jerry
            }

            // Store the values to Jerrie's fields
            char* id = strtok(line, ",");
            char* dim_name = strtok(NULL, ",");
            char* planet_name = strtok(NULL, ",");
            int happy_level = atoi(strtok(NULL, "/n"));

            int index = -1; // Represent the index of current Jerry's planet in planets array

            // A 'for' loop to find the Jerry's planet
            for (int j = 0; j < num_of_planets; j++) {
                if (strcmp(Planets_Array[j]->Name, planet_name) == 0) {
                    index = j;
                    break;
                }
            }

            // Create Jerry's origin object
            pOrigin curr_origin = create_Origin(dim_name, Planets_Array[index]);
            if (curr_origin == NULL) {
                clean_planets_array(Planets_Array, num_of_planets);
                clean_jerries_array(Jerries_Array, num_of_jerries);
                return failure;
            }

            // Create Jerry's object
            pJerry new_jerry = create_Jerry(id, happy_level, curr_origin, 0);
            if (new_jerry == NULL) {
                clean_planets_array(Planets_Array, num_of_planets);
                clean_jerries_array(Jerries_Array, num_of_jerries);
                return failure;
            }

            fgets(line, sizeof(line), config_file); // Read next row and check if the Jerry has PC's

            // For each Jerry:
            while (line[0] == '\t')  { // Until no more PC's or current Jerry doesn't have PC's at all
                char* PC_name = strtok(line + 1, ":"); // Store PC's name
                float value = atof(strtok(NULL, "/n")); // Store PC's value
                pPhysicalCharacteristic new_pc = create_PC(PC_name, value); // Create PC object
                if (new_pc == NULL) { // If failed - clean all memory
                    clean_planets_array(Planets_Array, num_of_planets);
                    clean_jerries_array(Jerries_Array, num_of_jerries);
                    return failure;
                }
                status temp_check = add_PC_to_Jerry(new_jerry,new_pc); // Add PC to Jerry
                if (temp_check == failure) {
                    free(new_pc); // Failure check
                    clean_planets_array(Planets_Array, num_of_planets);
                    clean_jerries_array(Jerries_Array, num_of_jerries);
                    return failure;
                }
                char* check_if_file_end = fgets(line, sizeof(line), config_file); // Read the next row
                if (check_if_file_end == NULL) { // If the file end (next row is NULL)
                    break; // Get out from 'While' loop
                }
            }
            Jerries_Array[i] = new_jerry; // Add current Jerry to Jerries array
        }
    }
    fclose(config_file); // Close the file
    return success; // We succeeded!
}

// A Function that prints the menu to the screen
void Menu() {
    printf("AW JEEZ RICK, what do you want to do now ? \n");
    printf("1 : Print all Jerries \n");
    printf("2 : Print all Planets \n");
    printf("3 : Add physical characteristic to Jerry \n");
    printf("4 : Remove physical characteristic from Jerry \n");
    printf("5 : Print Jerries by a planet \n");
    printf("6 : Print Jerries by a physical characteristic \n");
    printf("7 : Go home \n");
}

/**
    Main function:
    input: int argc: number of arguments sent by the caller of the program
           char* argv[]: store the arguments in an array by order
    output: void (no return)
    Function description: Helps Morty manage all the Jerries they collected to enable the safe return of each of them to his home.
                          During runtime the main display a menu of different choices, Each has different purpose.
*/
void main(int argc, char* argv[]) {
    // Extract arguments from configuration file
    int num_of_Planets = atoi(argv[1]); // Number of planets
    int num_of_Jerries = atoi(argv[2]); // Number of Jerries
    char* Configuration_File = argv[3]; // Configuration file path

    pPlanet planets_array[num_of_Planets]; // Create Planets array in Stack
    pJerry jerries_array[num_of_Jerries]; // Create Jerries array in Stack


    // Call the function that reads the configuration file
    status temp = read_config_file(Configuration_File, planets_array, jerries_array, num_of_Planets, num_of_Jerries);
    if (temp == failure) { // Check if failed
        printf("Memory Problem \n");
        exit(1);
    }


    int choice = 0 ; // Initialize a variable to hold the input
    char input[300]; // Buffer for user input
    char *ptr_to_input; // Pointer for strtol to detect invalid input


    // I use do while loop to display the menu to user in any case
    // If he chose option 7 - get out of program with cleaning memory
    do {
        Menu();  // Display menu to user

        fgets(input, sizeof(input), stdin); // Reads choice of user
        choice = strtol(input, &ptr_to_input, 10); // Convert input to an integer

        // Check if the conversion failed or input is out of range
        if (*ptr_to_input != '\n' || choice < 1 || choice > 7) {
            choice = -1; // Make sure it will go to default case
        }

        switch (choice) {
            case 1: // Print all Jerries
                for (int i = 0; i < num_of_Jerries; i++) {
                    print_Jerry(jerries_array[i]);
                }
            break;
            case 2: // Print all Planets
                for (int i = 0; i < num_of_Planets; i++) {
                    print_Planet(planets_array[i]);
                }
            break;
            case 3: // Add physical characteristic to Jerry
                printf("What is your Jerry's ID ? \n");
            char jerry_id_to_change[300]; // Buffer to hold Jerry's ID
            char pc_name_to_add[300]; // Buffer to hold PC's name
            fgets(jerry_id_to_change, sizeof(jerry_id_to_change), stdin); // Reads PC's name
            jerry_id_to_change[strlen(jerry_id_to_change)-1] = '\0'; // Replace /n in /0
            int index_of_jerry_to_change = -1;
            // Find Jerry
            for (int i = 0; i < num_of_Jerries; i++) {
                if (strcmp(jerry_id_to_change, jerries_array[i]->id) == 0) {
                    index_of_jerry_to_change = i;
                }
            }

            if (index_of_jerry_to_change == -1) { // If there is no Jerry with this ID
                printf("OH NO! I CAN'T FIND HIM RICK ! \n");
                break;
            }
            else {
                printf("What physical characteristic can you add to Jerry - %s ? \n",jerries_array[index_of_jerry_to_change]->id);
                fgets(pc_name_to_add, sizeof(pc_name_to_add), stdin); // Reads a PC name
                pc_name_to_add[strlen(pc_name_to_add)-1] = '\0'; // Replace /n in /0
                int index_of_pc = -1;
                // Find PC
                for (int i = 0; i < jerries_array[index_of_jerry_to_change]->number_of_physical_characteristics; i++) {
                    if (strcmp(pc_name_to_add, jerries_array[index_of_jerry_to_change]->ptr_to_physical_characteristic[i]->Name) == 0) {
                        index_of_pc = i;
                    }
                }
                if (index_of_pc == -1) { // If the Jerry doesn't have the PC that the user wants to add
                    printf("What is the value of his %s ? \n", pc_name_to_add);
                    char value_input_as_string[300]; // Buffer to hold the value input
                    fgets(value_input_as_string, sizeof(value_input_as_string), stdin); // Reads a PC's value
                    value_input_as_string[strlen(value_input_as_string)-1] = '\0'; // Replace /n in /0
                    float value_input = atof(value_input_as_string); // Casting from string to float
                    pPhysicalCharacteristic temp_pc = create_PC(pc_name_to_add, value_input); // Create new PC
                    if (temp_pc == NULL) { // If failure - clean all memory
                        clean_planets_array(planets_array, num_of_Planets);
                        clean_jerries_array(jerries_array, num_of_Jerries);
                        printf("Memory Problem \n");
                        exit(1); // Exit because failure or abnormal termination of the program
                    }
                    status temp_if_add = add_PC_to_Jerry(jerries_array[index_of_jerry_to_change], temp_pc); // Add PC to chosen Jerry
                    if (temp_if_add == failure) {
                        clean_planets_array(planets_array, num_of_Planets);
                        clean_jerries_array(jerries_array, num_of_Jerries);
                        printf("Memory Problem \n");
                        exit(1);
                    }
                    print_Jerry(jerries_array[index_of_jerry_to_change]);
                    break;
                }
                printf("RICK I ALREADY KNOW HIS "); // If the chosen Jerry has this PC already
                for (int i = 0; pc_name_to_add[i] != '\0'; i++) { // Print in uppercase
                    putchar(toupper(pc_name_to_add[i]));
                }
                printf(" ! \n");
                break;
            }

            case 4: // Remove physical characteristic from Jerry
                printf("What is your Jerry's ID ? \n");
            char jerry_id_to_remove_from[300]; // Buffer to hold Jerry's ID
            char pc_name_to_remove[300]; // Buffer to hold PC's name
            fgets(jerry_id_to_remove_from, sizeof(jerry_id_to_remove_from), stdin); // Reads Jerry's ID
            jerry_id_to_remove_from[strlen(jerry_id_to_remove_from)-1] = '\0'; // Replace /n in /0
            int index_of_jerry_to_remove_from = -1;
            // Find Jerry
            for (int i = 0; i < num_of_Jerries; i++) {
                if (strcmp(jerry_id_to_remove_from, jerries_array[i]->id) == 0) {
                    index_of_jerry_to_remove_from = i;
                }
            }

            if (index_of_jerry_to_remove_from == -1) { // If there is no Jerry with this ID
                printf("OH NO! I CAN'T FIND HIM RICK ! \n");
                break;
            }
            else {
                printf("What physical characteristic do you want to remove from Jerry - %s ? \n",jerries_array[index_of_jerry_to_remove_from]->id);
                fgets(pc_name_to_remove, sizeof(pc_name_to_remove), stdin); // Reads PC's name
                pc_name_to_remove[strlen(pc_name_to_remove)-1] = '\0'; // Replace /n in /0
                int index_of_pc_to_remove = -1;
                // Find PC
                for (int i = 0; i < jerries_array[index_of_jerry_to_remove_from]->number_of_physical_characteristics; i++) {
                    if (strcmp(pc_name_to_remove, jerries_array[index_of_jerry_to_remove_from]->ptr_to_physical_characteristic[i]->Name) == 0) {
                        index_of_pc_to_remove = i;
                    }
                }
                if (index_of_pc_to_remove == -1) {
                    printf("RICK I DON'T KNOW HIS "); // If the chosen Jerry doesn't have this PC
                    for (int i = 0; pc_name_to_remove[i] != '\0'; i++) { // Print in uppercase
                        putchar(toupper(pc_name_to_remove[i]));
                    }
                    printf(" ! \n");
                    break;
                }
                status check_if_deleted = delete_PC_in_Jerry(jerries_array[index_of_jerry_to_remove_from], pc_name_to_remove); // Remove PC from Jerry
                if (check_if_deleted == failure) {
                    clean_planets_array(planets_array, num_of_Planets);
                    clean_jerries_array(jerries_array, num_of_Jerries);
                    printf("Memory Problem \n");
                    exit(1);
                }
                else {
                    print_Jerry(jerries_array[index_of_jerry_to_remove_from]); // Print Jerry
                    break;
                }

            }

            case 5: // Print Jerries by a planet
                printf("What planet is your Jerry from ? \n");
            char planet_name_check[300]; // Buffer to hold the planet name
            int count_jerries = 0;
            int count_planets = 0;
            fgets(planet_name_check, sizeof(planet_name_check), stdin); // Reads planet name from user
            planet_name_check[strlen(planet_name_check)-1] = '\0'; // Replace /n in /0
            // A 'For' loop to check if there is a planet with the input name
            for (int i = 0; i < num_of_Planets; i++) {
                if (strcmp(planet_name_check, planets_array[i]->Name) == 0) {
                    count_planets++;
                }
            }
            if (count_planets == 0) {
                printf("RICK I NEVER HEARD ABOUT "); // There are no planets with this input planet's name
                for (int i = 0; planet_name_check[i] != '\0'; i++) { // Print in uppercase
                    putchar(toupper(planet_name_check[i]));
                }
                printf(" ! \n");
                break;
            }

            else {
                // A 'for' loop to check which Jerries are from the input planet
                for (int i = 0; i < num_of_Jerries; i++) {
                    if (strcmp(planet_name_check, jerries_array[i]->ptr_to_origin->ptr_to_planet->Name) == 0) {
                        count_jerries++;
                        print_Jerry(jerries_array[i]);
                    }
                }

                if (count_jerries == 0) { // There are no Jerries from the input planet
                    printf("OH NO! I DON'T KNOW ANY JERRIES FROM ");
                    for (int i = 0; planet_name_check[i] != '\0'; i++) { // Print in uppercase
                        putchar(toupper(planet_name_check[i]));
                    }
                    printf(" ! \n");
                    break;
                }
                else {
                    break;
                }
            }

            case 6: // Print Jerries by physical characteristic
            printf("What do you know about your Jerry ? \n");
            char pc_name_check[300]; // Buffer to hold PC's name
            int count_pc = 0;
            fgets(pc_name_check, sizeof(pc_name_check), stdin); // Reads a PC's name
            pc_name_check[strlen(pc_name_check)-1] = '\0'; // Replace /n in /0

            // A 'for' loop to check if there is a Jerry with the input pc
            for (int i = 0; i < num_of_Jerries; i++) {
                // An inner loop to check the PCs in each Jerry
                for (int j = 0; j < jerries_array[i]->number_of_physical_characteristics; j++) {
                    if (strcmp(pc_name_check, jerries_array[i]->ptr_to_physical_characteristic[j]->Name) == 0) {
                        count_pc++;
                        print_Jerry(jerries_array[i]);
                    }
                }
            }

            if (count_pc == 0) {
                printf("OH NO! I DON'T KNOW ANY JERRY'S "); // There is no Jerry with this PC
                for (int i = 0; pc_name_check[i] != '\0'; i++) { // Print in uppercase
                    putchar(toupper(pc_name_check[i]));
                }
                printf(" ! \n");
                break;
            }
            else {
                break;
            }

            case 7: // Go home - clean all allocated memory and leave the program with a message to user

            clean_planets_array(planets_array, num_of_Planets);
            clean_jerries_array(jerries_array, num_of_Jerries);
            printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
            break;

                default: // Default case - In case user didn't pick a valid number (1-7)
                        printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");
                break;
            }

        } while (choice != 7);
}


