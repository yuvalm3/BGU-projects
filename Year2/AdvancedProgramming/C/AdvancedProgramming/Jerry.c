/**
.c file:
 - Implementations of all declared .h functions
*/


#include <stdio.h>
#include <stdlib.h>
#include "Jerry.h"
#include "Defs.h"
#include <string.h>

// Create new object of PhysicalCharacteristic
pPhysicalCharacteristic create_PC(char *Name, float Value) {
    // Allocate memory for all object
    pPhysicalCharacteristic new_PC = (pPhysicalCharacteristic)malloc(sizeof(PhysicalCharacteristic));
    if (new_PC == NULL) { //check if allocated properly
        return NULL;
    }

    // Allocate memory for the  PC's name
    new_PC->Name = (char *)malloc(strlen(Name) + 1);  // +1 for the null terminator
    if (new_PC->Name == NULL) {
        free(new_PC);  // Free object if not allocated
        return NULL;
    }

    strcpy(new_PC->Name, Name); // Value placement
    new_PC->Value = Value; // Value placement

    return new_PC; // Return a pointer to the new object if it was successfully created
}



// Create new object of Origin
pOrigin create_Origin(char* Dim_Name, pPlanet ptr_to_planet) {
    if (ptr_to_planet == NULL) {
        return NULL;
    }
    // Allocate memory for all object
    pOrigin new_origin = (pOrigin)malloc(sizeof(Origin));
    if (new_origin == NULL) { // Check if allocated properly
        return NULL;
    }

    // Allocate memory for the dimension name
    new_origin->Dim_Name = (char *)malloc(strlen(Dim_Name)+1);
    if (Dim_Name == NULL) { // Check if allocated properly
        free(new_origin); // Free the object I've created
        return NULL;
    }

    strcpy(new_origin->Dim_Name, Dim_Name); // Value placement
    new_origin->ptr_to_planet = ptr_to_planet; // Pointer placement

    return new_origin; // Return a pointer to the new object if it was successfully created
}


// Create new object of Planet
pPlanet create_Planet(char *Name, float x, float y, float z) {
    // Allocate memory for all object
    pPlanet new_planet = (pPlanet)malloc(sizeof(Planet));
    if(new_planet == NULL) { // Check if allocated properly
        return NULL;
    }

    // Allocate memory for the planet name
    new_planet->Name = (char *)malloc( strlen(Name)+1);
    if(new_planet->Name == NULL) {
        free(new_planet); // Free the object I've created
        return NULL;
    }

    strcpy(new_planet->Name, Name); // Value placement
    new_planet->x = x; // Value placement
    new_planet->y = y; // Value placement
    new_planet->z = z; // Value placement

    return new_planet; // Return a pointer to the new object if it was successfully created
}

// Create new object of Jerry
pJerry create_Jerry(char* id, int Happy_Level, pOrigin ptr_to_origin,int number_of_physical_characteristics) {
    // Allocate memory for all object
    pJerry new_jerry = (pJerry)malloc(sizeof(Jerry));
    if (new_jerry == NULL) { // Check if allocated properly
        return NULL;
    }

    // Allocate memory for the planet name
    new_jerry->id = (char *)malloc( strlen(id)+1);
    if(new_jerry->id == NULL) {
        free(new_jerry); // Free the Jerry object I've created
        return NULL;
    }

    strcpy(new_jerry->id, id);  // Value placement
    new_jerry->Happy_Level = Happy_Level; // Value placement
    new_jerry->ptr_to_origin = ptr_to_origin; // Pointer placement
    new_jerry->ptr_to_physical_characteristic = NULL; // Initial an array of PCs to NULL
    new_jerry->number_of_physical_characteristics = number_of_physical_characteristics; // Value placement

    return new_jerry; // Return a pointer to the new object if it was successfully created
}


// Create a function to check if Jerry has a PC by its name
bool check_PC_in_Jerry (pJerry ptr_to_jerry, char* Name_of_pc) {
    if (ptr_to_jerry == NULL) { // If argument pointer of Jerry points to NULL
        return false;
    }

    if (ptr_to_jerry->number_of_physical_characteristics == 0) { // If Jerry has no PCs
        return false;
    }


    // Loop over all characteristics and return true/false
    for (int i = 0; i < ptr_to_jerry->number_of_physical_characteristics; i++) {
        if (strcmp(ptr_to_jerry->ptr_to_physical_characteristic[i]->Name,
                   Name_of_pc) == 0) {
            return true;
        }
    }

    return false;
}

// Add a PC to Jerry by reallocating memory and return status of success/failure
status add_PC_to_Jerry(pJerry ptr_to_jerry, pPhysicalCharacteristic PC) {
    if (ptr_to_jerry == NULL) { // If argument pointer of Jerry points to NULL
        return failure;
    }
    if (PC == NULL) { // If argument pointer of PC points to NULL
        return failure;
    }

    pPhysicalCharacteristic* temp_mem; // Create a dynamic array of pointers to PCs objects

    if (ptr_to_jerry->ptr_to_physical_characteristic == NULL) { // Check if Jerry doesn't have PCs
        temp_mem = (pPhysicalCharacteristic*)malloc(sizeof(pPhysicalCharacteristic)); // Allocating memory
        if (temp_mem == NULL) { // Check if allocated properly
            return failure;
        }
    }
    else {
        // Use a temporary pointer to store the result of realloc
        temp_mem = (pPhysicalCharacteristic*)realloc(ptr_to_jerry->ptr_to_physical_characteristic,sizeof(pPhysicalCharacteristic) * (ptr_to_jerry->number_of_physical_characteristics + 1));
        if (temp_mem == NULL) { // Check if allocated properly
            return failure;
        }
    }

    ptr_to_jerry->ptr_to_physical_characteristic = temp_mem; // If realloc succeeded, assign the new array to ptr_to_jerry
    ptr_to_jerry->ptr_to_physical_characteristic[ptr_to_jerry->number_of_physical_characteristics] = PC; // Assign new PC to the array
    ptr_to_jerry->number_of_physical_characteristics += 1; // Update the number of physical characteristics

    return success; // Return success if it was successfully made
}

// Delete a Jerry's PC by reallocating memory and return status of success/failure
status delete_PC_in_Jerry(pJerry ptr_to_jerry, char* Name_of_pc) {
    if (ptr_to_jerry == NULL) { // If argument pointer of Jerry points to NULL
        return failure;
    }
    if (ptr_to_jerry->number_of_physical_characteristics == 0) { // If Jerry has no PCs
        return failure;
    }
    if (Name_of_pc == NULL) { // If argument Pc's name is NULL
        return failure;
    }

    int index_to_delete = -1;
    // If jerry has this PC
    for (int i = 0; i < ptr_to_jerry->number_of_physical_characteristics; i++) {
        if (strcmp(ptr_to_jerry->ptr_to_physical_characteristic[i]->Name, Name_of_pc) == 0) {
            index_to_delete = i; // Holds the PC's index
            break;
        }
    }
    if (index_to_delete == -1) { // If not found
        return failure;
    }
    ptr_to_jerry->number_of_physical_characteristics -= 1; // Update the number of physical characteristics

    destroy_PC(ptr_to_jerry->ptr_to_physical_characteristic[index_to_delete]); // Free the PC we want to delete

    // If there are no more physical characteristics, free all dynamic array
    if(ptr_to_jerry->number_of_physical_characteristics == 0) {
        free(ptr_to_jerry->ptr_to_physical_characteristic);
        ptr_to_jerry->ptr_to_physical_characteristic = NULL;  // Set to NULL - prevent problems with realloc might occur later
    }

    else {

        // Move all pointers one step to the left in the array and keep the order as it was
        for (int j = index_to_delete; j < ptr_to_jerry->number_of_physical_characteristics; j++) {
            ptr_to_jerry->ptr_to_physical_characteristic[j] = ptr_to_jerry->ptr_to_physical_characteristic[j + 1];
        }

        // Resize the new array to the updated size with a temporary variable
        pPhysicalCharacteristic* temp_mem = (pPhysicalCharacteristic*)realloc(
            ptr_to_jerry->ptr_to_physical_characteristic,sizeof(pPhysicalCharacteristic) *
            ptr_to_jerry->number_of_physical_characteristics
        );

        if (temp_mem == NULL) { // Check if allocates properly
            return failure;
        }

        ptr_to_jerry->ptr_to_physical_characteristic = temp_mem; // Assign updated array
        return success; // Return success if it was successfully made
    }
}

// Print Jerry by format
status print_Jerry(pJerry ptr_to_jerry) {
    if (ptr_to_jerry == NULL) {
        return failure;
    }

    printf("Jerry , ID - %s : \n", ptr_to_jerry->id);
    printf("Happiness level : %d \n", ptr_to_jerry->Happy_Level);
    printf("Origin : %s \n", ptr_to_jerry->ptr_to_origin->Dim_Name);
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",ptr_to_jerry->ptr_to_origin->ptr_to_planet->Name,
        ptr_to_jerry->ptr_to_origin->ptr_to_planet->x,
        ptr_to_jerry->ptr_to_origin->ptr_to_planet->y,
        ptr_to_jerry->ptr_to_origin->ptr_to_planet->z);
    if (ptr_to_jerry->number_of_physical_characteristics == 0) {
        return success;
    }
    else {
        printf("Jerry's physical Characteristics available : \n");
        printf("\t");
        // Loop over PCs dynamic array
        for(int i = 0; i < ptr_to_jerry->number_of_physical_characteristics; i++) {
            printf("%s : %.2f ", ptr_to_jerry->ptr_to_physical_characteristic[i]->Name, ptr_to_jerry->ptr_to_physical_characteristic[i]->Value);
            if (i != ptr_to_jerry->number_of_physical_characteristics - 1) {
                printf(", ");
            }
        }
        printf("\n");
        return success; // Return success if it was successfully made
    }
}

// Print planet by format
status print_Planet(pPlanet ptr_to_planet) {
    if (ptr_to_planet == NULL) { // Check if allocated properly
        return failure;
    }

    printf("Planet : %s (%.2f,%.2f,%.2f) \n",ptr_to_planet->Name,
        ptr_to_planet->x,
        ptr_to_planet->y,
        ptr_to_planet->z);
    return success; // Return success if it was successfully made
}


// Destroy function for Planet
status destroy_planet(pPlanet planet_to_dest) {
    if (!planet_to_dest) return failure; // Check if allocated properly
    free(planet_to_dest->Name);  // Free the dynamically allocated string
    free(planet_to_dest); // Free the struct itself
    return success; // Return success if it was successfully made
}

// Destroy function for PC
status destroy_PC(pPhysicalCharacteristic ptr_to_PC) {
    if (!ptr_to_PC) return failure; // Check if allocated properly
    free(ptr_to_PC->Name);  // Free the dynamically allocated string
    free(ptr_to_PC); // Free the struct itself
    return success; // Return success if it was successfully made
}

// Destroy function for Origin
status destroy_Origin(pOrigin ptr_to_origin) {
    if (!ptr_to_origin) return failure; // Check if allocated properly
    free(ptr_to_origin->Dim_Name); // Free the dynamically allocated string
    ptr_to_origin->ptr_to_planet = NULL; // Update the ptr to the Planet
    free(ptr_to_origin); // Free the struct itself
    return success; // Return success if it was successfully made
}

// Destroy function for Jerry
status destroy_Jerry(pJerry ptr_to_jerry) {
    if (!ptr_to_jerry) return failure; // Check if allocated properly
    free(ptr_to_jerry->id); // Free the dynamically allocated string
    if (ptr_to_jerry->number_of_physical_characteristics != 0) {
        clean_pc_array(ptr_to_jerry->ptr_to_physical_characteristic, ptr_to_jerry->number_of_physical_characteristics);
    }
    ptr_to_jerry->ptr_to_physical_characteristic = NULL; // Update the ptr to the PC
    destroy_Origin(ptr_to_jerry->ptr_to_origin); // Update the ptr to the Origin
    free(ptr_to_jerry); // Free the struct itself
    return success; // Return success if it was successfully made
}






