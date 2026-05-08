
#ifndef ENTITY_H
#define ENTITY_H

#include "Inventory.h"
#include <iostream> 
#include <string>
using namespace std;

class Entity {
public:
    string name;
    int health;
    int damage; // base damage of an enitity

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
    public:
    int  maxHealth;
    int totalDMG; // given by the equipped weapon and base damage;
    int potions;
    int level;
    int exp;
    int expToNextLevel;
    InventoryList inventory;
    Item *equipedWeapon;

    const int HealAmount = 15;

        Player(string n, int h, int d) : Entity(n, h, d) {
            maxHealth = h;
            level = 1; // level intialized as one
            potions = 3; // default number of potions
            exp = 0;    // default baseline of exp
            expToNextLevel = 100;   //intial threshold of level 1
            equipedWeapon = nullptr; // no current equipped weapon
            totalDMG = damage;
        }

        void heal() {
            if(potions  > 0) { // if you still have potions 
                health += HealAmount;
                if(health > maxHealth) health = maxHealth;
                potions--;
            }
        }

        void levelUp(){
            level += 1;
            maxHealth += 20;
            health = maxHealth;
            potions = 3;
            damage += 5; // Increase base damage
            
            // Recalculate total damage to include the new base damage
            totalDMG = damage;
            if (equipedWeapon != nullptr) {
                totalDMG += equipedWeapon->DamageBonus;
            }

            exp -= expToNextLevel; // this will retain the extra exp
            expToNextLevel *= 1.5;
        }
        
};

class Enemy : public Entity {
    public:
         int expDrop;
        Enemy(string n, int h, int d, int exp) : Entity(n, h, d) {
            expDrop = exp;
        }
};

#endif