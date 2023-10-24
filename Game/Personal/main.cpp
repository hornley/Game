#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "json.hpp"
#include "player.h"
#include "items.h"
#include "shop.h"
#include "stats.h"
#include "enemy.h"
#include "battle.h"
#include "save.h"
#include "main.h"
using namespace Game;
using json = nlohmann::json;
char systemOS[5] = {'c', 'l', 'e', 'a', 'r'};

/*
To be finished
- Shop
> Shop limited items
> Prompt for buying another copy of item

> Globally define "clear" for other os
> Battle Menu
*> Normal fight (Enemy only attacks)
*> Unique fight (Enemy can heal)
*> Boss Fight
*> Dungeon
> Enemies and Items in a file
> Add a function to give others the ability to create their own enemy or item

To fix
> Input bugs
*/ 

void saveData(Inventory player)
{
    saveItems();
    save(player);
}

auto login()
{
    auto player = loginPlayer();
    return player;
}

auto character(Inventory player)
{
    int option;
    do {
        system(systemOS);
        cout << "Character Menu\n";
        cout << "1. Check stats\n";
        cout << "2. Inventory\n";
        cout << "0. Back\n";
        cin >> option;
        if (option == 1)
        {
            player = stats(player);
        }
        else if (option == 2)
        {
            player.showInventory();
        }
        else if (option > 2 or option < 0)
        {
            cout << "Invalid option!\n";
            cin.clear();
            cin.ignore();
            cin.ignore();
        }
    } while (option != 0);

    return player;
}

auto loop()
{
    int option;
    auto player = login();
    do {
        system(systemOS);
        cout << "Choose an Option!\n";
        cout << "1. Character Menu\n";
        cout << "2. Shop\n";
        cout << "3. Battle\n";
        cout << "0. Save and Exit\n";
        cin >> option;
        if (option == 1)
        {
            player = character(player);
        }
        else if (option == 2)
        {
            player = shop(player);
        }
        else if (option == 3)
        {
            player = menu(player);
        }
        else if (option > 3 or option < 0)
        {
            cout << "Invalid option!\n";
            cin.clear();
            cin.ignore();
            cin.ignore();
        }
    } while (option != 0);
    return player;
}

int main()
{
    auto player = loop();

    // addItem(109, "Common", "Omsim", "Weapon", "Sword", 150, 1, {1, 2, 3, 76});
    // items();
    
    saveData(player);
}