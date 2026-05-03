#include "Inventory.h"
#include <string>
#include "displayUI.h"
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
    system("cls");
    MenuBox invBox(2);
    invBox.setTitle("--- INVENTORY ---");

    if (head == nullptr) 
    {
            invBox.addOption("No item YET");
    } else {
        Item *walker = head;
        int counter = 1;

        while (walker != nullptr) {
            invBox.addOption("[" + to_string(counter) + "] " + walker->name + " (+ " + to_string(walker->DamageBonus) + " DMG)");
            walker = walker->next;
            counter++;
        }
    }

    invBox.addEmptyLine();
    invBox.draw(false);
    invBox.systemPause("Press [Enter] to close inventory...");
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

        if(head == nullptr) {
            tail = nullptr;
        }
        return;
    }


    //if the target is at the middle or at the tail
    Item *previous = nullptr;
    Item *current = head;

    while (current != nullptr){ //traverse tp the node

        if(current->name == targetName){ //found the node;
            previous->next = current->next;

            if(current->next == nullptr) { //its the tail
                tail = previous;
            }

            delete current;
            return;
        }
    
        //if not found, continue traversing
        previous = current;
        current = current->next;
    }

}