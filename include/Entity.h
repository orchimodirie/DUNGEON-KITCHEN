
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream> 
#include <string>
using namespace std;

class Entity {
public:
    string name;
    int health;
    int maxHealth;
    int damage;
    int level;

    Entity(string n, int h, int d){
        name = n;
        maxHealth = h;
        health = h;
        damage = d;
        level = 1;
    }

    // check if dead
    bool isAlive(){
        return health > 0;
    }

    // Taking Damage logic
    void takeDamage(int dmg){
        health -= dmg;
        if (health < 0)
            health = 0;
    }

    //healing logic
    void heal(int amount){
        health += amount;
        if (health > maxHealth)
            health = maxHealth;
    }
};

#endif