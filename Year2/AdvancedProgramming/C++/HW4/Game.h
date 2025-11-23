#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <string>
#include <fstream>
#include "Entity.h"
#include "Room.h"

class Game
{
    Entity Player;
    Room* Empty_Room_For_Start;
    Room* Current_Room;

public:

    // Regular Constructor
    Game(const std::string& ConfigFilePath, int Player_Life, int Player_Damage);

    // Getters
    Entity& Get_Player() {return Player;}
    Room* Get_Start_Room()const {return Empty_Room_For_Start;}
    Room* Get_Current_Room()const {return Current_Room;}

    void Place_A_Room(Room* startingRoom, Room* roomToAdd);
    void Run_Game();
    bool Fight();
    bool Check_If_Empty_Room();
    int Move_Room();

    // Destructor
    ~Game();

};

#endif //GAME_H

