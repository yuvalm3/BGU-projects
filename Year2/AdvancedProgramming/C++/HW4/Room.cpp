#include "Room.h"
#include <utility>

Room::Room()
    : m_Num_Of_Rooms(0), m_Camp_Fire_Amount(0), m_Array_Of_Rooms(nullptr) {
    Monster =  Entity(0,0,"Monster");
}

Room::Room(int campFire, int monsterLife, int monsterDamage, std::string ID)
    : m_Num_Of_Rooms(0), m_Camp_Fire_Amount(campFire), m_ID(std::move(ID)), m_Array_Of_Rooms(nullptr) {
    Monster =  Entity(monsterLife,monsterDamage,"Monster");
}

// Copy constructor with shallow copy
Room::Room(const Room& other)
    : m_Camp_Fire_Amount(other.m_Camp_Fire_Amount),
      Monster(other.Monster),
      m_Num_Of_Rooms(other.m_Num_Of_Rooms),
      m_ID(other.m_ID) {

    m_Array_Of_Rooms = new Room*[m_Num_Of_Rooms];  // Allocates the array of Room pointers

    // Copy the room pointers
    for (int i = 0; i < m_Num_Of_Rooms; ++i) {
        if (other.m_Array_Of_Rooms[i] != nullptr) {
            // Copy the pointer
            m_Array_Of_Rooms[i] = other.m_Array_Of_Rooms[i];
        } else {
            m_Array_Of_Rooms[i] = nullptr;  // Preserve null pointers
        }
    }
}

// Operator[] for access - the room object can't be changed
const Room* Room::operator[](const int index) const {
    return m_Array_Of_Rooms[index];
}

// Operator[] for placement
Room*& Room::operator[](const int index) {
    if(index >= m_Num_Of_Rooms) {
        this->ResizeArray(index + 1);
    }
    return m_Array_Of_Rooms[index];
}

// Resize the array when needed
void Room::ResizeArray(const int newSize) {
    if (newSize <= m_Num_Of_Rooms) {
        return;  // No need to resize if new size is not larger than current size
    }
    Room** newArray = new Room*[newSize]; // Allocate a new array
    for (int i = 0; i < newSize; i++) {
        if (i < m_Num_Of_Rooms) {
            newArray[i] = m_Array_Of_Rooms[i]; // Copy the pointer
        } else {
            newArray[i] = nullptr; // Initialize new pointers to nullptr
        }
    }
    delete[] m_Array_Of_Rooms; // Free old array
    m_Array_Of_Rooms = newArray; // Assign the new array
}


// Destructor to clean up allocated memory for Rooms
Room::~Room() {
    if (m_Array_Of_Rooms != nullptr) {
        for (int i = 0; i < m_Num_Of_Rooms; i++) {
            if (m_Array_Of_Rooms[i]) {
                delete m_Array_Of_Rooms[i]; // Delete each Room instance in the array
            }
        }
        // Delete the array itself
        delete[] m_Array_Of_Rooms;
    }
}


