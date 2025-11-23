#include "Entity.h"

// Copy constructor
Entity::Entity(const Entity &other) {
    this->m_Entity_Name = other.m_Entity_Name;
    this->m_Curr_Life = other.m_Curr_Life;
    this->m_Max_Life = other.m_Max_Life;
    this->m_Damage = other.m_Damage;
}

// Helper function for print
std::ostream &Entity::show(std::ostream &output) const {
    output << m_Entity_Name << " (" << m_Max_Life << "/" << m_Curr_Life << ") - " << m_Damage << std::endl;
    return output;
}

// Operators implementation
void Entity::operator+=(int const Life_To_Add) {
    m_Curr_Life+=Life_To_Add;
}
void Entity::operator-=(int const Life_To_Subtract) {
    m_Damage-=Life_To_Subtract;
}
void Entity::operator-=(const Entity& other) {
    m_Curr_Life = m_Curr_Life - other.m_Damage;
}
bool Entity::operator>(const Entity& other)const {
    return (this->m_Damage*this->m_Curr_Life > other.m_Damage*other.m_Curr_Life);
}
bool Entity::operator==(const Entity& other)const {
    return (this->m_Damage*this->m_Curr_Life == other.m_Damage*other.m_Curr_Life);
}
std::ostream& operator<<(std::ostream& out, const Entity& entity) {
    return entity.show(out);
}

