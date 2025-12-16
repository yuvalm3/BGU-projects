README File

Data Storage:

The data is stored in two arrays: one for Jerries and one for Planets.
These arrays are allocated on the stack, as the memory allocated for them is automatically cleaned up when the program ends.
Additionally, any dynamically allocated memory associated with these arrays is manually released during runtime if necessary.

Memory Management:

When memory allocation fails, I invoke two dedicated functions, clean_planets_array and clean_jerries_array.
These functions ensure all dynamically allocated memory is released to preventing memory leaks.
*clean_pc_array is in use inside setroy_Jerry - thats why I declared it in Jerry.h file

Configuration File
The read_config_file function is responsible for loading all the data from the configuration file.

If memory allocation fails at any point during this process, the function cleans up any allocated memory and returns a failure status.
In the event of a failure, the program terminates gracefully, accompanied by a message to the user.

User Interaction
A menu is presented to the user, allowing them to choose from various options to modify and interact with the Jerries system as desired.
The user can perform multiple operations until they decide to exit the program.

Program Termination
When the user chooses to exit the program, all allocated memory is cleaned up to ensure no memory leaks. This guarantees that the program terminates in a clean state.


Documentation 
I provided detailed explanations for each function in the .h file, as it is the file exposed to anyone reviewing the code.

Modularity

Throughout the process, I adhered to the principle of modularity, which is crucial, especially since in the next assignment the main function will change.
In such cases, we want the "black box" handling the operations on Jerry to remain unchanged.
**I chose to write the code directly within each case in the menu, rather than creating separate helper functions for each case.
In my opinion, this approach is preferable since the codes in cases are relatively short, and an excess of functions might lead to difficulty in tracking what is happening in the program.
