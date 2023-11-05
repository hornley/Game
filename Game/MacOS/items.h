#ifndef ITEMS_H
#define ITEMS_H

#include<map>
#include<fstream>
#include<string>
#include<vector>
#include "json.hpp"
#include "main.h"
using json = nlohmann::json;
using namespace std;

// Adds a new item in the items.json
// Types
// 1 -> Default
// 2 -> Player Created
// 3 -> Player Modified
// unconfirmed: Might need a restart to see changes...
// When publish change 1 to 2
void addItem()
{
    ifstream in(itemsPath);
    json file = json::parse(in);
    string r, n, c, sc;
    int id, cost, lvl_req, xa, ca;
    vector<int> effects;

    cout << "Item ID: ";
    cin >> id;
    cout << "Item Name: ";
    cin.ignore();
    getline(cin, n);
    cout << "Item Rarity: ";
    cin >> r;
    cout << "Item Category: ";
    cin >> c;
    cout << "Item Sub-category: ";
    cin >> sc;
    cout << "Item Cost: ";
    cin >> cost;
    cout << "Item Level Requirement: ";
    cin >> lvl_req;
    do{
        cout << "Item Effect: ";
        cin >> xa;
        if (xa == 0) { break; }
        effects.push_back(xa);
        cout << "Item Effect Add: ";
        cin >> ca;
        effects.push_back(ca);
    } while (true);

    file[c][sc][to_string(id)] = make_pair(vector<string>{r, n}, make_pair(vector<int>{cost, lvl_req, 1}, vector<int>{effects}));

    ofstream out(itemsPath);
    out << setw(4) << file << endl;
    in.close();
    out.close();
}

// Get all items function from items.json
// And returns a map of the items
auto getItems()
{
    ifstream in(itemsPath);
    json file = json::parse(in);

    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> items;

    for (auto _i = file.begin(); _i != file.end(); _i++)
    {
        auto sc = _i.value();
        for (auto _sc = sc.begin(); _sc != sc.end(); _sc++)
        {
            for (auto _id = _sc.value().begin(); _id != _sc.value().end(); _id++)
            {
                int id = stoi(_id.key());
                string r = _id.value()[0][0];
                string n = _id.value()[0][1];
                string c = _i.key();
                string sc = _sc.key();
                int cost = _id.value()[1][0][0];
                int lvl_req = _id.value()[1][0][1];
                int type = _id.value()[1][0][2];
                vector<int> effects = _id.value()[1][1];

                items[id] = make_pair(vector<string>{r, n, c, sc}, make_pair(vector<int>{cost, lvl_req, type}, vector<int>{effects}));
            }
        }
    }

    in.close();
    return items;
}

auto getItem(int id)
{
    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> _items = getItems();
    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>>::iterator iter;

    map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> _x;
    for (auto iter = _items.begin(); iter != _items.end(); iter++)
    {
        if (iter->first == id)
        {
            string c = iter->second.first[2];
            string sc = iter->second.first[3];

            int id = iter->first;
            string r = iter->second.first[0];
            string n = iter->second.first[1];
            int cost = iter->second.second.first[0];
            int lvl_req = iter->second.second.first[1];
            int type = iter->second.second.first[2];
            vector<int> effects = iter->second.second.second;

            _x[id] = make_pair(vector<string>{r, n, c, sc}, make_pair(vector<int>{cost, lvl_req, type}, vector<int>{effects}));
        }
    }

    return _x;
}

#endif