#ifndef SHOP_H
#define SHOP_H
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include "player.h"
#include "items.h"
#include "main.h"
using namespace std;

// Choosing to view and buy of an item
// To be improved:
// > If there is more than 9 items, have a next page
// > Filtering of data
int item_choose()
{
    string rarity, name, category, sub_category, effect;
    int effect_nums, cost, lvl_req, item_id=1, _x = 1, eff_amount, idk, idk_2;
    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> items = getItems();

    system(systemOS);
    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>>::iterator iter;

    for (iter = items.begin(); iter != items.end(); iter++)
    {
        if (iter->first != 1)
        {
            name = iter->second.first.at(1);
            cout << _x << ". " << name << endl;
            _x++;
        }
    }
    cout << "0. Exit Shop\n";

    cout << "\nView Item: ";
    cin >> item_id;
    if (item_id == 0)
    {
        cin.clear();
        return 0;
    }
    else if (item_id == 23)
    {
        item_id = 1;
        system(systemOS);
        cout << "YOU!\nWHO ARE YOU!?!?\n";
        return item_id;
    }
    item_id += 100;
  
    system(systemOS);
    for (iter = items.begin(); iter != items.end(); iter++)
    {
        if (item_id == iter->first)
        {
            rarity = iter->second.first.at(0);
            name = iter->second.first.at(1);
            category = iter->second.first.at(2);
            sub_category = iter->second.first.at(3);
            cost = iter->second.second.first.at(0);
            lvl_req = iter->second.second.first.at(1);
            system(systemOS);
            cout << "Name: " << name << endl;
            cout << "Category: " << category << " - ";
            cout << sub_category << endl;
            cout << "Rarity: " << rarity << endl;

            effect_nums = iter->second.second.second.size();
            eff_amount = effect_nums / 2;
            cout << "Effects:\n";
            for (int _ea = 1; _ea <= eff_amount; _ea++)
            {
                idk = iter->second.second.second.at(0 + 2 * (_ea - 1));
                idk_2 = iter->second.second.second.at(1 + 2 * (_ea - 1));
                switch (idk)
                {
                case 1:
                    cout << "Base Attack + " << idk_2 << endl;
                    break;
                case 2:
                    cout << "Speed + " << idk_2 << endl;
                    break;
                case 3:
                    cout << "Defence + " << idk_2 << endl;
                    break;
                case 4:
                    cout << "HP + " << idk_2 << endl;
                    break;
                case 5:
                    cout << "Bonus EXP + " << idk_2 << endl;
                    break;
                case 6:
                    cout << "Bonus Moula + " << idk_2 << endl;
                    break;
                }
            }

            cout << "Level Requirement: " << lvl_req << endl;
            cout << "Cost: " << cost << endl << endl;
            cout << "Buy this item? (1 for yes)\n";
            cout << "Type 0 to go back.\n";
            return item_id;
        }
    }
    return 0;
}

// Purchasing function
// If purchase is successful, add item to inventory
auto shop(Game::Inventory player) {
    int item_id, _back;
    string name;
    float cost, bal = player.getBalance();
    float hp = player.getPStats()[0];
    float spd = player.getPStats()[1];
    float def = player.getPStats()[2];
    float base_attack = player.getPStats()[3];

    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> items = getItems();
    item_id = item_choose();
    while (item_id != 0)
    {
        cin >> _back;
        if (_back == 1)
        {
            system(systemOS);
            map<int, pair<vector<string>, pair<vector<int>, vector<int>>>>::iterator iter;
            iter = items.find(item_id);
            name = iter->second.first.at(1);
            cost = iter->second.second.first.at(0);
            if (cost > bal)
            {
                cout << "Transaction failed!\nNot Enough Balance!" << endl;
                cin.clear();
                cin.ignore();
                cin.ignore();
            }
            else
            {
                bal -= cost;
                cout << name << " successfully bought and is transferred to inventory!\n";
                cout << "New balance is: " << bal << endl;
                player.bal = bal;
                cin.clear();
                cin.ignore();

                int effect_nums, eff_amount, idk, idk_2;

                effect_nums = iter->second.second.second.size();
                eff_amount = effect_nums / 2;
                player.addItem(item_id, 1);
                cout << "Press ENTER to continue.\n";
                cin.clear();
                cin.ignore();
            }
        }
        item_id = item_choose();
    }
    return player;
}

#endif