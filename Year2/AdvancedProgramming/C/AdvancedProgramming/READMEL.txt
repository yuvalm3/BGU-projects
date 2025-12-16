README File

Data Storage

The data is stored in two arrays, one for Jerries and one for Planets.
These arrays are allocated on the stack, as their size is known at runtime and their memory is automatically released when the program terminates.
All dynamically allocated memory referenced by these arrays, including Jerries, Origins, Physical Characteristics and strings,
is explicitly released during runtime when no longer needed.

Memory Management

Dynamic memory allocation is handled carefully throughout the program.
In case of a memory allocation failure, dedicated cleanup functions are invoked to ensure that all dynamically allocated memory is properly released, preventing memory leaks.

Configuration File

The read_config_file function is responsible for loading all the data from the configuration file.
The file is parsed in two stages. First, all Planet objects are created. Second, all Jerry objects are created along with their Origins and Physical Characteristics.
If memory allocation fails at any point during this process, the function cleans up any previously allocated memory and returns a failure status.
In such a case, the program terminates gracefully and prints an appropriate message to the user.

User Interaction

A menu driven interface is presented to the user, allowing interaction with the Jerry management system.
The user can view existing Jerries and Planets, add or remove physical characteristics, and query Jerries by planet or by physical characteristic.
The user may perform multiple operations until choosing to exit the program.

Program Termination

When the user chooses to exit the program, all dynamically allocated memory is released in an orderly manner.
This ensures that the program terminates in a clean state with no memory leaks.


Documentation 

Detailed documentation is provided in the header files, which define the public interface of each module.
Each exposed function is documented with its purpose, parameters, and return value, allowing the implementation to function as a clear and well defined black box.

Modularity

The program was designed with modularity in mind. All logic related to Jerry manipulation is encapsulated within the Jerry module, allowing the main program to change without affecting the underlying functionality. This is especially important as future assignments may require replacing or modifying the main function. The menu logic is implemented directly within each case of the switch statement. Since each case is relatively short and self contained, this approach improves readability without introducing unnecessary helper functions that could obscure the program flow.
In my opinion, this approach is preferable since the codes in cases are relatively short, and an excess of functions might lead to difficulty in tracking what is happening in the program.
