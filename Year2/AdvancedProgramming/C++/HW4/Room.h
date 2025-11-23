#ifndef ROOM_H
#define ROOM_H
#include "Entity.h"
#include <iostream>

class Room
{
    std::string m_ID;
    int m_Camp_Fire_Amount;
    Entity Monster;
    Room** m_Array_Of_Rooms;
    int m_Num_Of_Rooms;

public:
    // Constructors
    Room();
    // Regular constructor
    Room(int campFire, int monsterLife, int monsterDamage,std::string ID);
    // Copy constructor
    Room(const Room& other);

    // Setters
    void Set_Camp_Fire_Amount(const int campFire) { m_Camp_Fire_Amount = campFire;}
    void Set_Monster_Life(const int monsterLife) { Monster.Set_Curr_Life(monsterLife);}
    void Set_Monster_Damage(const int monsterDamage) { Monster.Set_Damage(monsterDamage);}
    void Set_ID(const std::string& ID) { m_ID = ID; }
    void Increase_Num_Of_Rooms() {m_Num_Of_Rooms++;}

    // Getters
    Entity& Get_Monster() {return Monster;}
    std::string Get_ID()const {return m_ID;}
    int Get_Campfire()const {return m_Camp_Fire_Amount;}
    int Get_Num_Of_Rooms()const {return m_Num_Of_Rooms;}
    Room** Get_Rooms_Array() {return m_Array_Of_Rooms;}

    // Operators
    // Operator [] for access
    const Room* operator[](int index) const;

    // Operator [] for placement
    Room*& operator[](int index);

    void ResizeArray(int newSize);

    // Destructor
   ~Room();
};

#endif //ROOM_H
