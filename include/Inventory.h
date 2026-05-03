#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>


class Item {
    public:
    //data
    std::string name;
    int DamageBonus;
    
    //chaining pointer
    Item *next;

    Item (std::string n, int DMG_BNS) : name(n), DamageBonus(DMG_BNS) {
        next = nullptr;
    }
};


class InventoryList {
public:

    Item *head;
    Item *tail;

    InventoryList() {
        head = nullptr;
        tail = nullptr;
    }

    ~InventoryList();
    //methods
    void AddItem(std::string n, int dmg);
    void display();

};




#endif INVENTORY_H