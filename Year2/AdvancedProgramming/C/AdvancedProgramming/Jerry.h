/**
.h file:
    - Creating the structs
    - Declare all .c functions
*/
#ifndef JERRY_H
#define JERRY_H

#include "Defs.h"


/**
    Struct Planet:
    - All Jerries are coming from a Planet. Each Planet is unique and there are no two Planets with the same Name.
    - Each Planet has coordinates in space - x, y, z

    * Creating a pointer to the object
*/
typedef struct Planet_t {
    char* Name;
    float x;
    float y;
    float z;
} Planet;

typedef Planet *pPlanet;

/**
    Struct Origin:
    - Every creature in space comes from a certain origin.
    - The origin object contains the planet from which it comes
      and the name of the dimension which the creature came.

    * Creating a pointer to the object
*/
typedef struct Origin_t {
    char* Dim_Name;
    pPlanet ptr_to_planet;
} Origin;

typedef Origin *pOrigin;

/**
    Struct : PhysicalCharacteristic  *In short version - PC
    - Each creature has physical characteristics that represent it.
    - The object contains a unique name for
    the attribute, and a value for the attribute.
    - The physical characteristics are attributes with an actual numerical value

    * Creating a pointer to the object
*/
typedef struct PhysicalCharacteristic_t {
    char* Name;
    float Value;
} PhysicalCharacteristic;

typedef PhysicalCharacteristic *pPhysicalCharacteristic;

/**
    Struct : Jerry
    - Each object represents a specific Jerry of a certain origin.
    - Each jerry has:
    A unique ID (string of characters)
    An integer representing Jerry's level of happiness (a number between 0 and 100)
    Its origin
    A dynamic set of physical properties known about the particular Jerry
    A number representing current amount of PC's

    * Creating a pointer to the object
*/
typedef struct Jerry_t {
    char* id;
    int Happy_Level;
    pOrigin ptr_to_origin;
    pPhysicalCharacteristic* ptr_to_physical_characteristic; ;
    int number_of_physical_characteristics;
}Jerry;

typedef Jerry *pJerry;





/**
    Declarations of all functions in .c file
*/

/**
create_PC function:
    input: char* *Name - name of PC
        float Value - value of PC
    output: pointer to the new created PC
*/
pPhysicalCharacteristic create_PC(char *Name, float Value);

/**
create_Planet function:
    input: char* Name - name of the planet
        float x - coordinate
        float y - coordinate
        float z - coordinate
    output: pointer to the new created Planet
*/
pPlanet create_Planet(char *Name, float x, float y, float z);

/**
create_Origin function:
    input: char* Dim_Name - name of dimension the planet came from
        pPlanet ptr_to_planet - a pointer to the planet
    output: pointer to the new created Origin
*/
pOrigin create_Origin(char* Dim_Name, pPlanet ptr_to_planet);

/**
create_Jerry function:
    input: char* id - unique ID of the new Jerry to create
        pOrigin ptr_to_origin - a pointer to the Origin the Jerry came from
        int Happy_Level
        int number_of_physical_characteristics
    output: pointer to the new created Jerry
*/
pJerry create_Jerry(char* id, int Happy_Level, pOrigin ptr_to_origin,int number_of_physical_characteristics);



/**
check_PC_in_Jerry function:
    input: char* Name_of_pc
           pJerry ptr_to_jerry
    output: Tru/False if the Jerry has this specific PC
*/
bool check_PC_in_Jerry (pJerry ptr_to_jerry, char* Name_of_pc);

/**
add_PC_to_Jerry function:
    input: pJerry ptr_to_jerry
           pPhysicalCharacteristic PC
    output: Success/Failure if the process was successful
    purpose: Add a PC into the dynamic PCs array of a specific Jerry
*/
status add_PC_to_Jerry(pJerry ptr_to_jerry, pPhysicalCharacteristic PC);

/**
delete_PC_to_Jerry function:
    input: pJerry ptr_to_jerry
        char* Name_of_pc
    output: Success/Failure if the process was successful
    purpose: Delete a PC in a specific Jerry by sending the name of the PC
*/
status delete_PC_in_Jerry(pJerry ptr_to_jerry, char* Name_of_pc);

/**
print_Jerry function:
    input: pJerry ptr_to_jerry
    output: Success/Failure if the process was successful
    purpose: Print the information about a specific Jerry by format
*/
status print_Jerry(pJerry ptr_to_jerry);

/**
print_Planet function:
    input: pPlanet ptr_to_planet
    output: Success/Failure if the process was successful
    purpose: Print the information about a specific Planet by format
*/
status print_Planet(pPlanet ptr_to_planet);

/**
destroy_Planet function:
    input: pPlanet ptr_to_planet we want to destroy
    output: Success/Failure if the process was successful
    purpose: Take out a specific Planet from the Planets array and clean all memory we've allocated
*/
status destroy_planet(pPlanet planet_to_dest);

/**
destroy_PC function:
    input: pPhysicalCharacteristic ptr_to_PC we want to destroy
    output: Success/Failure if the process was successful
    purpose: Clean all memory allocated for a specific PC
*/
status destroy_PC(pPhysicalCharacteristic ptr_to_PC);

/**
destroy_Origin function:
    input: pOrigin ptr_to_origin we want to destroy
    output: Success/Failure if the process was successful
    purpose: Clean all memory allocated for a specific Origin
*/
status destroy_Origin(pOrigin ptr_to_origin);

/**
destroy_Jerry function:
    input: pJerry ptr_to_jerry we want to destroy
    output: Success/Failure if the process was successful
    purpose: Take out a specific Jerry from the Jerries array and clean all memory we've allocated
*/
status destroy_Jerry(pJerry ptr_to_jerry);

/**
clean_pc_array function:
    input: pPhysicalCharacteristic* array
           int size - size of the PCs array
    output: Success/Failure if the process was successful
    purpose: Clean all memory allocated for an array of PCs each Jerry has

    ** In use when a Jerry is destroyed we want to clean its PCs array
*/
void clean_pc_array(pPhysicalCharacteristic* array, int size);



#endif //JERRY_H
