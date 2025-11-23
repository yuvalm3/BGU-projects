#include "Game.h"

int main(int argc, char* argv[]) {

    // Parse the arguments
    int playerLife = std::stoi(argv[1]);  // Convert Player_Life (first argument) to int
    int playerDamage = std::stoi(argv[2]);  // Convert Player_Damage (second argument) to int
    std::string configFilePath = argv[3];  // Get the configuration file path (third argument) by string

    // Create the Game instance
    Game myGame(configFilePath, playerLife, playerDamage);

    // Run the game
    myGame.Run_Game();

    return 0;
}
