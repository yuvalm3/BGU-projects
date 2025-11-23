#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <ostream>
#include <utility>

class Entity
{
    int m_Max_Life;
    int m_Curr_Life;
    int m_Damage;
    std::string m_Entity_Name;

    std::ostream& show(std::ostream& output) const;

public:
    // Constructors
    // Default constructor
    Entity() : m_Max_Life(0), m_Curr_Life(0), m_Damage(0), m_Entity_Name("Default Entity Name") {}
    // Regular constructor
    Entity(const int Max_Life, const int Damage, std::string Name) : m_Max_Life(Max_Life), m_Curr_Life(Max_Life), m_Damage(Damage), m_Entity_Name(std::move(Name)) {}
    // Copy constructor
    Entity(const Entity& other);

    // Getters
    int Get_Curr_Life()const {return m_Curr_Life;}
    int Get_Damage()const {return m_Damage;}
    int Get_Max_Life()const {return m_Max_Life;}

    // Setters
    int Set_Curr_Life(const int life) {this->m_Curr_Life = life; return m_Curr_Life;}
    int Set_Max_Life(const int life) {this->m_Max_Life = life;return m_Max_Life;}
    int Set_Damage(const int damage) {this->m_Damage = damage; return m_Damage;}

    // Operators
    void operator+=(int Life_To_Add);
    void operator-=(int Life_To_Subtract);
    void operator-=(const Entity& other);
    bool operator>(const Entity& other)const;
    bool operator==(const Entity& other) const;

    // Print Operator
    friend std::ostream& operator<<(std::ostream& out, const Entity& entity);

    // Default Destructor
    ~Entity() = default;
};

#endif //ENTITY_H
