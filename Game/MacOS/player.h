#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<string>
#include "items.h"
using namespace std;

namespace Game {
    class Player {
    protected:
        string id;
    public:
        float hp;  // stat
        float speed;  // stat
        float def;  // stat
        float base_attack;  // stat
        float bal;  // bal
        float exp;  // exp
        float exp_required;  // exp
        int level;  // exp and stat
        int stat_point;  // stat
        int tax;  // stat
        int weapon;
        int helm;
        int chestplate;
        int leggings;
        int boots;
        vector<float> getPStats ()
        {
            std::vector<float> stats = {hp, speed, def, base_attack};
            return stats;
        }
        float getBalance()
        {
            return bal;
        }
        int getLevel ()
        {
            return level;
        }
        vector<float> getExp()
        {
            std::vector<float> expa = {exp, exp_required};
            return expa;
        }
        int getSP()
        {
            return stat_point;
        }
        string getName()
        {
            return id;
        }
        auto getData()
        {
            auto Data = make_pair(vector<float>{hp, speed, def, base_attack, bal, exp, exp_required}, vector<int>{level, stat_point, tax, weapon, helm, chestplate, leggings, boots});
            return Data;
        }
    };

    class Inventory : public Player {
    private:
        static map<int, int> inventory;
    public:
        Inventory (string _id, float _hp, float spd, float _def, float ba, float _bal, float _exp, float expr, int lvl, int sp, int _tax, int w, int h, int cp, int l, int b)
        {
            id = _id;
            hp = _hp;
            speed = spd;
            def = _def;
            base_attack = ba;
            bal = _bal;
            exp = _exp;
            exp_required = expr;
            level = lvl;
            stat_point = sp;
            tax = _tax;
            weapon = w;
            helm = h;
            chestplate = cp;
            leggings = l;
            boots = b;
        }
        
        // Category and Sub-category addition
        void addItem(int _id, int _amount)
        {
            if (inventory.find(_id) != inventory.end()) { inventory[_id] += 1; }
            else { inventory.insert({_id, _amount}); }
        }

        auto getInventory() { return inventory; }

        void unequipItem(int toUnequip)
        {
            int effect_nums, eff_amount, idk, effect;

            auto _x = getItem(toUnequip);
            auto iter = _x.begin();
            vector<int> effects = iter->second.second.second;
            effect_nums = effects.size();
            eff_amount = effect_nums / 2;
            
            for (int _ea = 1; _ea <= eff_amount; _ea++)
            {
                idk = effects.at(0 + 2 * (_ea - 1));
                effect = effects.at(1 + 2 * (_ea - 1));
                switch (idk)
                {
                case 1: base_attack -= effect; break;
                case 2: speed -= effect; break;
                case 3: def -= effect; break;
                case 4:  hp -= effect; break;
                }
            }
        }

        void equipItem(string name, string c, string sc, int id, vector<int> effects)
        {
            int effect_nums, eff_amount, idk, effect;

            if (c == "Weapon") { if (weapon != 0) { unequipItem(weapon); } weapon = id; }
            else
            {
                if (sc == "Helm") { if (helm != 0) { unequipItem(weapon); } helm = id; }
                else if (sc == "Chestplate") { if (chestplate != 0) { unequipItem(weapon); }  chestplate = id; }
                else if (sc == "Leggings") { if (leggings != 0) { unequipItem(weapon); }  leggings = id; }
                else { if (boots != 0) { unequipItem(weapon); }  boots = id; }
            }
            effect_nums = effects.size();
            eff_amount = effect_nums / 2;
            for (int _ea = 1; _ea <= eff_amount; _ea++)
            {
                idk = effects.at(0 + 2 * (_ea - 1));
                effect = effects.at(1 + 2 * (_ea - 1));
                switch (idk)
                {
                case 1: base_attack += effect; break;
                case 2: speed += effect; break;
                case 3: def += effect; break;
                case 4: hp += effect; break;
                }
            }
            cout << name << "Successfully equipped";
            cin.clear();
            cin.ignore();
            cin.ignore();
        }

        void showInventory()
        {
            int _xa = 1, choice, effect_nums, eff_amount, idk, effect;
            char _a;
            map<int, int> inv = getInventory();
            map<int, int>::iterator iter;
            system("clear");
            for (auto iter = inv.begin(); iter != inv.end(); iter++)
            {
                auto _item = getItem(iter->first);
                map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> oms = _item;
                map<int, pair<vector<string>, pair<vector<int>, vector<int>>>>::iterator _;
                for (auto _ = oms.begin(); _ != oms.end(); _++) { cout << _xa << ". " << _->second.first[1] << " - " << iter->second << endl; } _xa++;
            }
            cout << "0. Cancel\n";
            cout << "Choose an item to view: ";
            cin >> choice;
            choice += 100;
            for (auto iter = inv.begin(); iter != inv.end(); iter++)
            {
                auto _item = getItem(choice);
                map<int, pair<vector<string>, pair<vector<int>, vector<int>>>> oms = _item;
                map<int, pair<vector<string>, pair<vector<int>, vector<int>>>>::iterator _;
                for (auto _ = oms.begin(); _ != oms.end(); _++)
                {
                    string c = _->second.first[2];
                    string sc = _->second.first[3];

                    int id = _->first;
                    string r = _->second.first[0];
                    string n = _->second.first[1];
                    int cost = _->second.second.first[0];
                    int lvl_req = _->second.second.first[1];
                    vector<int> effects = _->second.second.second;
                    
                    cout << endl;
                    cout << n << endl;
                    effect_nums = effects.size();
                    eff_amount = effect_nums / 2;
                    cout << "Effects:\n";
                    for (int _ea = 1; _ea <= eff_amount; _ea++)
                    {
                        idk = effects.at(0 + 2 * (_ea - 1));
                        effect = effects.at(1 + 2 * (_ea - 1));
                        switch (idk)
                        {
                        case 1:
                            cout << "Base Attack + " << effect << endl;
                            break;
                        case 2:
                            cout << "Speed + " << effect << endl;
                            break;
                        case 3:
                            cout << "Defence + " << effect << endl;
                            break;
                        case 4:
                            cout << "HP + " << effect << endl;
                            break;
                        case 5:
                            cout << "Bonus EXP + " << effect << endl;
                            break;
                        case 6:
                            cout << "Bonus Moula + " << effect << endl;
                            break;
                        }
                    }

                    cout << "\nEquip? [Y/N]\n";
                    cin >> _a;
                    if (_a == 'Y' or _a == 'y')
                    {
                        equipItem(n, c, sc, id, effects);
                    }
                }
                if (_a != 'Y' or _a != 'y') { break; }
            }
        }
    };
}

map<int, int> Game::Inventory::inventory;

#endif