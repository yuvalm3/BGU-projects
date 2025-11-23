#include "Game.h"


Game::Game(const std::string& ConfigFilePath, int Player_Life, int Player_Damage)
: Player(Player_Life, Player_Damage, "Player") {
    Empty_Room_For_Start = new Room(); // Create a Room and activate the field for the first Room
    Current_Room = Empty_Room_For_Start; // Initialize the Current Room to the starting empty Room

    std::ifstream configFile(ConfigFilePath); // Open the file
    std::string line; // Declare a line
    // While file is not over:
    while (std::getline(configFile, line)) {

        int X = 0, Y = 0, Z = 0; // Initialize the tokens
        std::string W;

        // Parsing the line
        size_t start = 0, end;

        // First token
        end = line.find(' ', start);
        W = line.substr(start, end - start);
        start = end + 1;

        // Second token
        end = line.find(' ', start);
        X = std::stoi(line.substr(start, end - start));
        start = end + 1;

        // Third token
        end = line.find(' ', start);
        Y = std::stoi(line.substr(start, end - start));
        start = end + 1;

        // Fourth token
        Z = std::stoi(line.substr(start));

        Room* New_Room = new Room(X, Y, Z,W); // Create the Room
        Place_A_Room(Empty_Room_For_Start, New_Room); // Place the new room in its proper place
    }

    // Close the file after reading and parsing
    configFile.close();
}

void Game::Run_Game() {
    std::cout << Player; // Print the Player
    std::cout << "I see you like challenges, by how much do you want to reduce your damage?" << std::endl;
    int Damage_To_Subtract;
    std::cin >> Damage_To_Subtract;
    int temp = Player.Get_Damage();
    Get_Player().Set_Damage(temp - Damage_To_Subtract); // Set the updated Damage
    Current_Room = Empty_Room_For_Start; // Initialize the Current Room before the loop

    while (true) { // Always process the room before checking exit conditions
        std::cout << Player;

        // Process the current room
        int temp3 = Check_If_Empty_Room();
        if (temp3 == true) {
            Move_Room(); // Move next Room if current is empty
            continue;
        }

        bool fight = true; // For fight's return
        int maxLife = Current_Room->Get_Monster().Get_Max_Life(); // To check Monster existence
        if (maxLife != 0) {
            fight = this->Fight(); // Start a fight
        }
        if (fight == false) {
            return; // Exit game if fight is lost
        }

        // Check if the room has more rooms
        if ((*Current_Room).Get_Num_Of_Rooms() == 0) {
            std::cout << "The room continues and opens up to the outside. You won against the dungeon" << std::endl;
            return; // Exit game when all rooms are done
        }

        Move_Room(); // Move only if more rooms exist
    }
}

// Fight against the Monster
bool Game::Fight() {
    if (Get_Player() > (*Get_Current_Room()).Get_Monster()){
        std::cout << "You encounter a smaller monster" << std::endl;
    }
    else {
        if (Get_Player() == (*Get_Current_Room()).Get_Monster()) {
            std::cout << "You encounter a equally sized monster" << std::endl;
        }
        else {
            std::cout << "You encounter a larger monster" << std::endl;
        }
    }

    std::cout << (*Get_Current_Room()).Get_Monster(); // Print the Monster

    while (true) {
        (*Get_Current_Room()).Get_Monster() -= Get_Player();
        int monsterLife = (*Get_Current_Room()).Get_Monster().Get_Curr_Life(); // Get the current life of the Monster
        if (monsterLife <= 0) { // Attack the Monster
            std::cout << "You deal " << Get_Player().Get_Damage() << " damage to the monster and leave it with 0 health" << std::endl;
            std::cout << "You defeat the monster and go on with your journey" << std::endl;
            return true;
        }
        else {
            std::cout << "You deal " << Get_Player().Get_Damage() << " damage to the monster and leave it with " <<
                monsterLife << " health" << std::endl;
        }
        Get_Player() -= (*Get_Current_Room()).Get_Monster();
        if (Get_Player().Get_Curr_Life() <= 0) { // Monster attacks the Player
            std::cout << "The monster deals " << (*Get_Current_Room()).Get_Monster().Get_Damage() <<
                " damage to you and leaves you with 0 health" << std::endl;
            std::cout << "You lost to the dungeon" << std::endl;
            return false;
        }
        else {
            std::cout << "The monster deals " << (*Get_Current_Room()).Get_Monster().Get_Damage() <<
                " damage to you and leaves you with " << Get_Player().Get_Curr_Life() << " health" << std::endl;
        }
    }
}

// Place a Room in its proper place
void Game::Place_A_Room(Room* startingRoom, Room* roomToAdd) {
    std::string id_to_add = roomToAdd->Get_ID();
    if (id_to_add.size() == 1) {
        int id_integer = std::stoi(id_to_add);  // Convert string to int
        if (id_integer == 0) { // Deal first placement when Room's array is empty
            (*startingRoom)[0] = roomToAdd; // Place the Room
            (*startingRoom).Increase_Num_Of_Rooms(); // +1 Number of current room's rooms
            return;
        }
        if (startingRoom->Get_Num_Of_Rooms() <= id_integer) { // The Room doesn't have place
            startingRoom->ResizeArray(id_integer + 1);  // Resize the array
            (*startingRoom)[id_integer] = roomToAdd; // Place the Room
            (*startingRoom).Increase_Num_Of_Rooms(); // +1 Number of current room's rooms
            return;
        }
        (*startingRoom)[id_integer] = roomToAdd; // The Room has place
        (*startingRoom).Increase_Num_Of_Rooms(); // +1 Number of current room's rooms
    }
    else {
        // Loop through each character in the string (each digit in the ID) except the last one
        for (char digitChar : id_to_add.substr(0, id_to_add.length() - 1)) {
            int digit = digitChar - '0'; // Convert the character back to an integer by ASCII value
            startingRoom = (*startingRoom)[digit]; // // Move to the next level in the hierarchy
        }
        int lastDigit = id_to_add[id_to_add.size() - 1] - '0';
        if(startingRoom->Get_Num_Of_Rooms() <= lastDigit) { // The Room doesn't have place
            startingRoom->ResizeArray(lastDigit + 1);  // Resize the array
            (*startingRoom)[lastDigit] = roomToAdd; // Place the Room
            (*startingRoom).Increase_Num_Of_Rooms(); // +1 Number of current room's rooms
            return;
        }
        (*startingRoom)[lastDigit] = roomToAdd; // The Room has place
        (*startingRoom).Increase_Num_Of_Rooms(); // +1 Number of current room's rooms
    }
}


Game::~Game() {
        delete Empty_Room_For_Start;
}


bool Game::Check_If_Empty_Room() {
    if (Current_Room->Get_Campfire() == 0) { // If there is a Campfire in the Room
        // Get the max life of the monster to check if it exists
        int maxLife = Current_Room->Get_Monster().Get_Max_Life();
        if(maxLife == 0){
            std::cout << "You arrive to an empty room" << std::endl;
            return true;
        }
    }
    else {
        std::cout << "You sit by the campfire and heal " << Current_Room->Get_Campfire() << " health" << std::endl;
        if ((Player.Get_Curr_Life() + Current_Room->Get_Campfire()) < Player.Get_Max_Life()) {
            Player += Current_Room->Get_Campfire();
            return false;
        }
    }
    return false;
}

// Move through Rooms
int Game::Move_Room() {
    int Chosen_Room = -1;
    if (Current_Room->Get_Num_Of_Rooms() == 1) {
        std::cout << "You see a single corridor ahead of you labeled 0" << std::endl;
        std::cin >> Chosen_Room;
        Current_Room = (*Current_Room)[0];
        return Chosen_Room;
    }
    std::cout << "You see corridors labeled from 0 to " << (Current_Room->Get_Num_Of_Rooms() - 1) <<
        ". Which one will you choose?" << std::endl;
    std::cin >> Chosen_Room;
    Current_Room = (*Current_Room)[Chosen_Room];
    return Chosen_Room;
}


