#ifndef SAVE_H
#define SAVE_H
#include <iostream>
#include <fstream>
#include<iomanip>
#include "json.hpp"
#include "player.h"
#include "items.h"
#include "main.h"
#include "skills.h"
using json = nlohmann::json;
using namespace nlohmann::literals;
using namespace std;

// If players.json is not empty
// Display the character names saved in players.json
// Returns player data from players.json
json players()
{
    system(systemOS);
    ifstream f; f.open(playersPath, ios::in);
    json data{json::parse(f)};
    
    if (data["Character"].size() >= 1){
        cout << "Saved Characters:\n";
        for (auto _x = data["Character"].begin(); _x != data["Character"].end(); _x++)
        {
            cout << _x.key() << " - (level " << _x.value()["Stats"][1][1][0] << ")" << endl;
        }
        cout << endl;
    }
    f.close();

    return data;
}

auto classing(string _, string _name)
{
    // 19
    // vit, str, int, agi, dex, wis, luck, pDef, mDef, pPene*, mPene*, critC*, critD*, expMulti*, moneyMulti*,cons, bal, exp, expr
    if (_ == "Warrior") { Inventory character(_name, "Warrior", {125, 3, 0, 20, 1, 0, 0, 3, 0, 0, 0, 0, 150, 0, 0, 1, 1000, 0, 15, 1000, 0, 15}, 1, 0, 20, 0, 0, 0, 0, 0); character.addSkill(101); return character; }
    else if (_ == "Archer") { Inventory character(_name, "Archer", {75, 2, 0, 35, 2, 1, 0, 1, 0, 0, 0, 5, 150, 0, 0, 1, 1000, 0, 15}, 1, 0, 20, 0, 0, 0, 0, 0); character.addSkill(102); return character; }
    else if (_ == "Assassin") { Inventory character(_name, "Assassin", {100, 1, 0, 25, 3, 1, 0, 1, 1, 2, 0, 10, 150, 0, 0, 1, 1000, 0, 15}, 1, 0, 20, 0, 0, 0, 0, 0); character.addSkill(103); return character; }
    else { Inventory character(_name, "Mage", {90, 1, 3, 25, 0, 2, 0, 0, 0, 0, 0, 0, 150, 0, 0, 1, 1000, 0, 15}, 1, 0, 20, 0, 0, 0, 0, 0); character.addSkill(104); return character; }
}

// Login Menu Features
// > Choose a currently existing character
// > Create a new character
// > Delete a character
Inventory loginPlayer()
{
    adding();
    adders();
    string _name, _class;
    bool _new;
    int _choice, _chosenClass;
    Inventory character(_name, _class, {125, 3, 0, 20, 1, 0, 0, 3, 0, 0, 0, 0, 150, 0, 0, 1, 1000, 0, 15, 1000, 0, 15}, 1, 0, 20, 0, 0, 0, 0, 0);
    
    do {
        _new = true;
        json data = players();
        cout << "Character Name: ";
        cin >> _name;

        if (data["Character"].size() >= 1)
        {
            for (auto _x = data["Character"].begin(); _x != data["Character"].end(); _x++)
            {
                if (_x.key() == _name)
                {   
                    _new = false;
                    string _class = _x.value()["Stats"][0];
                    float vit = _x.value()["Stats"][1][0][0];
                    float str = _x.value()["Stats"][1][0][1];
                    float Int = _x.value()["Stats"][1][0][2];
                    float agi = _x.value()["Stats"][1][0][3];
                    float dex = _x.value()["Stats"][1][0][4];
                    float wis = _x.value()["Stats"][1][0][5];
                    float luck = _x.value()["Stats"][1][0][6];
                    float pDef = _x.value()["Stats"][1][0][7];
                    float mDef = _x.value()["Stats"][1][0][8];
                    float pPene = _x.value()["Stats"][1][0][9];
                    float mPene = _x.value()["Stats"][1][0][10];
                    float critC = _x.value()["Stats"][1][0][11];
                    float critD = _x.value()["Stats"][1][0][12];
                    float expMulti = _x.value()["Stats"][1][0][13];
                    float moneyMulti = _x.value()["Stats"][1][0][14];
                    float cons = _x.value()["Stats"][1][0][15];
                    float bal = _x.value()["Stats"][1][0][16];
                    float exp = _x.value()["Stats"][1][0][17];
                    float exp_r = _x.value()["Stats"][1][0][18];
                    int lvl = _x.value()["Stats"][1][1][0];
                    int sp = _x.value()["Stats"][1][1][1];
                    int tax = _x.value()["Stats"][1][1][2];
                    int w = _x.value()["Stats"][1][1][3];
                    int h = _x.value()["Stats"][1][1][4];
                    int cp = _x.value()["Stats"][1][1][5];
                    int l = _x.value()["Stats"][1][1][6];
                    int b = _x.value()["Stats"][1][1][7];

                    system(systemOS);
                    check_stats(_class, _x.key(), lvl, vit, str, Int, agi, dex, wis, luck, pDef, mDef, cons, bal, exp, exp_r, sp);

                    // Add an option if they want to use this account/character
                    cout << endl;
                    cout << "1. Use this character\n";
                    cout << "2. Delete this character\n";
                    cout << "3. Select again\n";
                    cin >> _choice;
                    if (_choice == 1)
                    {
                        system(systemOS);
                        cout << "Using " << _name << " to login\nLogging in...\nDone!\nPress ENTER to continue...\n";
                        Inventory character(_name, _class, {vit, str, Int, agi, dex, wis, luck, pDef, mDef, pPene, mPene, critC, critD, expMulti, moneyMulti, cons, bal, exp, exp_r}, lvl, sp, tax, w, h, cp, l, b);
                        if (_x.value()["Inventory"].size() >= 1)
                        {
                            map<string, int> oms = _x.value()["Inventory"];
                            map<string, int>::iterator iter;
                            for (auto iter = oms.begin(); iter != oms.end(); iter++)
                            {
                                character.addItem(stoi(iter->first), iter->second);
                            }
                        }
                        if (_x.value()["Skills"].size() >= 1)
                        {
                            vector<int> oms = _x.value()["Skills"];
                            for (int i = 0; i <= oms.size(); i++)
                            {
                                character.addSkill(oms[i]);
                            }
                        }
                        return character;
                    }
                    else if (_choice == 2)
                    {
                        data["Character"].erase(_x.key());
                        cout << "Successfully deleted " << _name << " from the database.\n";
                        ofstream out(playersPath); out << setw(4) << data << endl; out.close();
                        cin.clear(); cin.ignore(); cin.ignore();
                    }
                    else if (_choice == 3) { }
                    else {cout << "Invalid choice!\n"; cin.clear(); cin.ignore(); cin.ignore();}
                    break;
                }
            }
        }
        if (_new)
        {
            do
            {
                cout << "Choose a class:\n";
                cout << "1. Warrior\n2. Archer\n3. Assassin\n4. Mage";
                cin >> _chosenClass;
                switch (_chosenClass)
                {
                case 1: _class = "Warrior";
                break;
                case 2: _class = "Archer";
                break;
                case 3: _class = "Assassin";
                break;
                case 4: _class = "Mage";
                break; 
                default: cout << "Invalid option!\n"; break;
                }
            } while (_class == ""); 
            character = classing(_class, _name);
            return character;
        }
    } while (_choice != 1);
    return character;
}

// Saves the player data into players.json
// Will not save the data if console/terminal is terminated and not exited properly
void save(Game::Inventory player)
{
    ifstream in(playersPath); json file = json::parse(in);
    file["Character"][player.getName()]["Stats"] = player.getData();
    map<int, int> _x = player.getInventory(); map<int, int>::iterator iter;
    for (auto iter = _x.begin(); iter != _x.end(); iter++) { file["Character"][player.getName()]["Inventory"][to_string(iter->first)] = iter->second; }
    vector<int> _y = player.getSkills();
    file["Character"][player.getName()]["Skills"].clear();
    for (int i = 0; i < _y.size(); i++)
    {
        file["Character"][player.getName()]["Skills"].push_back(_y[i]);
    }
    ofstream out(playersPath); out << setw(4) << file << endl; in.close(); out.close();
}

// Saves the items within the items function
void saveItems()
{
    ifstream in(itemsPath); json file = json::parse(in);

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
        int type = iter->second.second.first[2];
        vector<int> effects = iter->second.second.second;

        file[category][sub_category][to_string(id)] = make_pair(vector<string>{rarity, name}, make_pair(vector<int>{cost, lvl_req, type}, vector<int>{effects}));
    }
    ofstream out(itemsPath); out << setw(4) << file << endl; in.close(); out.close();
}

// Saves the skilsl within h
void saveSkills()
{
    ifstream in(skillsPath); json file = json::parse(in);

    Game::Skill Dummy(0, 0, "Dummy", "Dummy", 0, 0, 1, {0, 0});
    map<int, pair<vector<string>, pair<vector<int>, vector<float>>>> all = Dummy.getAllSkills();
    map<int, pair<vector<string>, pair<vector<int>, vector<float>>>>::iterator iter;

    for (auto iter = all.begin(); iter != all.end(); iter++)
    {
        if (iter->first != 0)
        {
            string sc = iter->second.first[1];
            string id = to_string(iter->first);
            string sn = iter->second.first[0];
            int slq = iter->second.second.first[0];
            int mcf = iter->second.second.first[1];
            int mcp = iter->second.second.first[2];
            int type = iter->second.second.first[3];

            file[sc][id] = make_pair(sn, make_pair(vector<int>{slq, mcf, mcp, type}, vector<float>{iter->second.second.second}));
        }
    }
    ofstream out(skillsPath); out << setw(4) << file << endl; in.close(); out.close();
}

// Save enemies
void saveEnemies()
{
    ifstream in(enemiesPath); json file = json::parse(in);

// id - (name, ( (vit, str, int, agi, dex, wis, pdef, mdef, pp, mp, cc, cd, exp, rewards), (lvl, type) ))
    Game::Enemy Dummy(1, "Dummy", {75, 2, 0, 35, 0, 0, 3, 1, 0, 0, 0, 0, 10, 400}, 1, 1);
    map<int, pair<string, pair<vector<float>, vector<int>>>> all = Dummy.getAllEnemy();
    map<int, pair<vector<string>, pair<vector<int>, vector<float>>>>::iterator iter;

    for (auto iter = all.begin(); iter != all.end(); iter++)
    {
        if (iter->first != 1)
        {
            string name = iter->second.first;
            vector<float> stats = iter->second.second.first;
            string type;
            switch (iter->second.second.second[1])
            {
            case 0: type = "Created"; break;
            case 1: type = "Normal"; break;
            case 2: type = "Uniqe"; break;
            case 404: type = "Boss"; break;
            }

            file[type][to_string(iter->first)] = make_pair(name, make_pair(vector<float>{stats}, vector<int>{iter->second.second.second}));
        }
    }
    ofstream out(enemiesPath); out << setw(4) << file << endl; in.close(); out.close();
}

// SAVES ALL DATA FOR "SAVE AND EXIT" OPTION
void saveData(Inventory player) { saveItems(); saveSkills(); saveEnemies(); save(player); }

#endif