#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<iomanip>
#include "json.hpp"
#include "player.h"
#include "items.h"
#include "shop.h"
#include "stats.h"
#include "enemy.h"
#include "battle.h"
#include "save.h"
#include "main.h"
#include "skills.h"
using namespace Game;
using json = nlohmann::json;

#if defined(_WIN32) || defined(WIN32)
    char systemOS[3] = {'c', 'l', 's'};
#else
    char systemOS[5] = {'c', 'l', 'e', 'a', 'r'};
#endif

string playersPath;
string itemsPath;
string skillsPath;
string enemiesPath;

void devmode();

void setPath(int numArgs, char args[])
{
    string aux(args);

    #if defined(_WIN32) || defined(WIN32)
        int pos = aux.rfind('\\');
    #else
        int pos = aux.rfind('/');
    #endif

    string path = aux.substr(0, pos+1);
    playersPath = path + "players.json";
    itemsPath = path + "items.json";
    skillsPath = path + "skills.json";
    enemiesPath = path + "enemies.json";
}   

// Better Login Menu
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
        else if (option == 3)
        {
            cout << player.getSkills()[0];
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
        else if (option == 4)
        {
            devmode();
        }
        else if (option > 4 or option < 0)
        {
            cout << "Invalid option!\n";
            cin.clear();
            cin.ignore();
            cin.ignore();
        }
    } while (option != 0);
    return player;
}

int main(int numArgs, char *args[])
{
    cout << setprecision(1);
    cout << fixed;
    setPath(numArgs, args[0]);
    auto player = loop();
    saveData(player);
}

void devmode()
{
    int option;
    do
    {
        system(systemOS);
        cout << "Choose an Option!\n";
        cout << "1. Add Item\n";
        cout << "2. Add Skill\n";
        cout << "3. Add Enemy\n";
        cout << "0. Back\n";
        cin >> option;
        if (option == 1)
        {
            addItem();
        }
        else if (option == 2)
        {
            addSkill();
        }
        else if (option == 3)
        {
            addEnemy();
        }
    } while (option != 0);
}