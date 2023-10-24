#ifndef SAVE_H
#define SAVE_H
#include <iostream>
#include <fstream>
#include<iomanip>
#include "json.hpp"
#include "player.h"
#include "items.h"
#include "main.h"
using json = nlohmann::json;
using namespace std;

// If players.json is not empty
// Display the character names saved in players.json
// Returns player data from players.json
json players()
{
    ifstream f; f.open("/Users/hornley/Documents/VSCode/Personal/players.json", ios::in);
    json data{json::parse(f)};
    
    if (data["Character"].size() >= 1){
        for (auto _x = data["Character"].begin(); _x != data["Character"].end(); _x++)
        {
            cout << _x.key() << endl;
        }
        cout << endl;
    }
    f.close();

    return data;
}

// Choose or creating a new character
// To be improved:
// > Confirmation to use character or create new character
// > Deletion of character
Inventory loginPlayer()
{
    string _name;
    
    system(systemOS);
    json data = players();
    cout << "Character Name: ";
    cin >> _name;
    Inventory character(_name, 100, 25, 0, 1, 1000, 0, 15, 1, 0, 20, 0, 0, 0, 0, 0);

    if (data["Character"].size() >= 1){
        for (auto _x = data["Character"].begin(); _x != data["Character"].end(); _x++)
        {
            if (_x.key() == _name)
            {
                float hp = _x.value()["Stats"][0][0];
                float spd = _x.value()["Stats"][0][1];
                float def = _x.value()["Stats"][0][2];
                float ba = _x.value()["Stats"][0][3];
                float bal = _x.value()["Stats"][0][4];
                float exp = _x.value()["Stats"][0][5];
                float exp_r = _x.value()["Stats"][0][6];
                int lvl = _x.value()["Stats"][1][0];
                int sp = _x.value()["Stats"][1][1];
                int tax = _x.value()["Stats"][1][2];
                int w = _x.value()["Stats"][1][3];
                int h = _x.value()["Stats"][1][4];
                int cp = _x.value()["Stats"][1][5];
                int l = _x.value()["Stats"][1][6];
                int b = _x.value()["Stats"][1][7];
                check_stats(_name, lvl, hp, spd, def, ba, bal, sp, exp, exp_r);
                // Add an option if they want to use this account/character
                Inventory character(_name, hp, spd, def, ba, bal, exp, exp_r, lvl, sp, tax, w, h, cp, l, b);

                if (_x.value()["Inventory"].size() >= 1)
                {
                    map<string, int> oms = _x.value()["Inventory"];
                    map<string, int>::iterator iter;
                    for (auto iter = oms.begin(); iter != oms.end(); iter++)
                    {
                        character.addItem(stoi(iter->first), iter->second);
                    }
                }

                cin.clear();
                cin.ignore();
                cin.ignore();
                return character;
            };
        }
        cout << endl;
    }
    return character;
}

// Saves the player data into players.json
// Will not save the data if console/terminal is terminated and not exited properly
void save(Game::Inventory player)
{
    using namespace nlohmann::literals;
    ifstream in("/Users/hornley/Documents/VSCode/Personal/players.json");
    json file = json::parse(in);

    file["Character"][player.getName()]["Stats"] = player.getData();
    map<int, int> _x = player.getInventory();
    map<int, int>::iterator iter;
    for (auto iter = _x.begin(); iter != _x.end(); iter++)
    {
        file["Character"][player.getName()]["Inventory"][to_string(iter->first)] = iter->second;
    }

    ofstream out("/Users/hornley/Documents/VSCode/Personal/players.json");
    out << setw(4) << file << endl;
    in.close();
    out.close();
}

// Saves the items within the items function
void saveItems()
{
    using namespace nlohmann::literals;
    ifstream in("/Users/hornley/Documents/VSCode/Personal/items.json");
    json file = json::parse(in);

    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> _x = getItems();
    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>>::iterator iter;

    for (auto iter = _x.begin(); iter != _x.end(); iter++)
    {
        string category = iter->second.first[2];
        string sub_category = iter->second.first[3];

        int id = iter->first;
        string rarity = iter->second.first[0];
        string name = iter->second.first[1];
        int cost = iter->second.second.first[0];
        int lvl_req = iter->second.second.first[1];
        vector<int> effects = iter->second.second.second;

        file[category][sub_category][to_string(id)] = make_pair(vector<string>{rarity, name}, make_pair(vector<int>{cost, lvl_req}, vector<int>{effects}));
    }

    ofstream out("/Users/hornley/Documents/VSCode/Personal/items.json");
    out << setw(4) << file << endl;
    in.close();
    out.close();
}

#endif