
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream> 
#include <string>
using namespace std;

class Entity {
public:
    string name;
    int health;
    int damage;

    Entity(string n, int h, int d): name(n), health(h), damage(d) {};

    // check if dead
    bool isAlive(){
        return health > 0;
    }

    // Taking Damage logic
    void takeDamage(int dmg){
        health -= dmg;
        if (health < 0) health = 0;
    }
};

class Player : public Entity {
    private: 
        int  maxHealth;
        int potions;
        int level;
        const int HealAmount = 25;
    public:
        Player(string n, int h, int d) : Entity(n, h, d) {
            maxHealth = h;
            level = 1;
            potions = 3;
        }

        void heal() {
            if(potions  > 0) { // if you still have potions 
                health += HealAmount;
                if(health > maxHealth) health = maxHealth;
                potions--;
            }
        }   
};

class Enemy : public Entity {
    public:
        Enemy(string n, int h, int d) : Entity(n, h, d) {}
};

#endif