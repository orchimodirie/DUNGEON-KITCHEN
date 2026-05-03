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


void InventoryList::dropItem(std::string targetName) {
    if (head == nullptr) { //if lis is empty
        std::cout<<"The list is empty"<<std::endl;
        return;
    }

    if(head->name == targetName) {
        Item *nextNode = head->next; //store the next pointer

        delete head; //delete the current head;
        head = nextNode;

        return;
    }


    //if the target is at the middle or at the tail
    Item *previous;
    Item *current = head;

    while (current != nullptr){ //traverse tp the node
        if(current->name != targetName){
            previous = current;
            current = current->next;
        }
        else if (current->name == targetName && current->next != nullptr) { //in between node
            // the current is node is the target
            previous->next = current->next;
            delete current;
        }
        else if (current->name == targetName && current->next == nullptr) { //the last node
            previous->next = nullptr;
            delete current;
        }
    }

}

