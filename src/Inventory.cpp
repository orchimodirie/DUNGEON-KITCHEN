#include "Inventory.h"
#include <string>
#include <iostream>

//destructor
InventoryList::~InventoryList() {
    Item* current = head;
    while (current != nullptr) {
        Item* NextNode = current->next;
        delete current;
        current = NextNode;
    }
    head = nullptr;
}

void InventoryList::AddItem(std::string n, int dmg) {
    Item *newItem = new Item(n, dmg);

    if(head == nullptr) { // if list is empty
        head = newItem;
        tail = head;
    } else { // if list has node already
        tail->next = newItem;
        tail = newItem;
    }
}

void InventoryList::display() {
    Item *walker = head;

    if (head == nullptr) 
    {
        std::cout<<"The List is empty!"<<std::endl;
        return;
    }

    
    while (walker != nullptr) {
        std::cout<<"Item 1: "<<walker->name<<" Damage Bonus = "<<walker->DamageBonus<<std::endl;
        walker = walker->next;
    }
}
