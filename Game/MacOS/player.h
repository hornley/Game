#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<string>
#include<algorithm>
#include "items.h"
using namespace std;

// Stats protected/private implementation
// > Use vector to return stats
namespace Game {
    class Player {
    protected:
        string name;
        string Class;
    public:
        float vitality;
        float strength;
        float intelligence;
        float agility;
        float dexterity;
        float wisdom;
        float luck;
        float charisma;
        float pDef;
        float mDef;
        float constitution;
        float phyPenetration;  // unimplemented - but added to stats
        float magPenetration;  // unimplemented - but added to stats
        float critChance; // unimplemented
        float critDamage; // unimplemented
        float bal;
        float exp;
        float exp_required;
        float expMultiplier; // unimplemented
        float moneyMultiplier; // unimplemented
        int level;
        int stat_point;
        int tax;
        int weapon;
        int helm;
        int chestplate;
        int leggings;
        int boots;
        
        string getClass () { return Class; }

        // Remvoe getBalance and getExp
        // Combine getLevel and get SP
        float getBalance() { return bal; }
        int getLevel () { return level;  }
        vector<float> getExp()
        {
            std::vector<float> expa = {exp, exp_required};
            return expa;
        }
        int getSP() { return stat_point; }
        string getName() { return name; }
        auto getData()
        {
            // vit, str, int, agi, dex, wis, luck, pdef, mdef, pPene, mPene, critC, critD, expMulti, moneyMulti, cons, bal, exp, expr
            auto Data = make_pair(Class, make_pair(vector<float>{vitality, strength, intelligence, agility, dexterity, wisdom, luck, pDef, mDef, phyPenetration, magPenetration, critChance, critDamage, expMultiplier, moneyMultiplier,constitution, bal, exp, exp_required}, vector<int>{level, stat_point, tax, weapon, helm, chestplate, leggings, boots}));
            return Data;
        }
    };

    class Inventory : public Player {
    private:
        static map<int, int> inventory;
        static vector<int> skills;
    public:
        // name, class, vit, str, int, agi, dex, wis, luck, pDef, mDef, pPene*, mPene*, critC*, critD*, expMulti*, moneyMulti*,cons, bal, exp, expr, lvl, sp, tax, w, h, cp, l, b
        // Simplify arguments to STATS
        // Simplify stats to vector instead of individually adding them
        Inventory (string _name, string _class, vector<float> _stats, int lvl, int sp, int _tax, int w, int h, int cp, int l, int b)
        {
            name = _name;
            Class = _class;
            vitality = _stats[0];
            strength = _stats[1];
            intelligence = _stats[2];
            agility = _stats[3];
            dexterity = _stats[4];
            wisdom = _stats[5];
            luck = _stats[6];
            pDef = _stats[7];
            mDef = _stats[8];
            phyPenetration = _stats[9];
            magPenetration =  _stats[10];
            critChance = _stats[11];
            critDamage = _stats[12];
            expMultiplier = _stats[13];
            moneyMultiplier = _stats[14];
            constitution = _stats[15];
            bal = _stats[16];
            exp = _stats[17];
            exp_required = _stats[18];
            level = lvl;
            stat_point = sp;
            tax = _tax;
            weapon = w;
            helm = h;
            chestplate = cp;
            leggings = l;
            boots = b;
        }

        void addSkill(int id)
        {
            if (id != 0)
            {
                int _a = 0;
                for (int x = 0; x < skills.size(); x++)
                {
                    if (id == skills[x])
                    {
                        _a++;
                    }
                }
                if (_a == 0) { skills.push_back(id); }
            }
        }

        // Category and Sub-category addition
        void addItem(int _id, int _amount)
        {
            if (inventory.find(_id) != inventory.end()) { inventory[_id] += 1; }
            else { inventory.insert({_id, _amount}); }
        }

        auto getInventory() { return inventory; }
        auto getSkills() { return skills; }

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
                case 1: vitality -= effect; break;
                case 2: strength -= effect; break;
                case 3: intelligence -= effect; break;
                case 4: agility -= effect; break;
                case 5: dexterity -= effect; break;
                case 6: wisdom -= effect; break;
                case 7: luck -= effect; break;
                case 8: pDef -= effect; break;
                case 9: mDef -= effect; break;
                case 10: phyPenetration -= effect; break;
                case 11: magPenetration -= effect; break;
                case 12: critChance -= effect; break;
                case 13: critDamage -= effect; break;
                case 14: expMultiplier -= effect; break;
                case 15: moneyMultiplier -= effect; break;
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
                case 1: vitality += effect; break;
                case 2: strength += effect; break;
                case 3: intelligence += effect; break;
                case 4: agility += effect; break;
                case 5: dexterity += effect; break;
                case 6: wisdom += effect; break;
                case 7: luck += effect; break;
                case 8: pDef += effect; break;
                case 9: mDef += effect; break;
                case 10: phyPenetration += effect; break;
                case 11: magPenetration += effect; break;
                case 12: critChance += effect; break;
                case 13: critDamage += effect; break;
                case 14: expMultiplier += effect; break;
                case 15: moneyMultiplier += effect; break;
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
                            cout << "VIT + " << effect << endl;
                            break;
                        case 2:
                            cout << "STR + " << effect << endl;
                            break;
                        case 3:
                            cout << "INT + " << effect << endl;
                            break;
                        case 4:
                            cout << "AGI + " << effect << endl;
                            break;
                        case 5:
                            cout << "DEX + " << effect << endl;
                            break;
                        case 6:
                            cout << "WIS + " << effect << endl;
                            break;
                        case 7:
                            cout << "LUCK + " << effect << endl;
                            break;
                        case 8:
                            cout << "Physical Def + " << effect << endl;
                            break;
                        case 9:
                            cout << "Magical Def + " << effect << endl;
                            break;
                        case 10:
                            cout << "Physical Penetration + " << effect << endl;
                            break;
                        case 11:
                            cout << "Magical Penetration + " << effect << endl;
                            break;
                        case 12:
                            cout << "Critical Chance + " << effect << endl;
                            break;
                        case 13:
                            cout << "Critical Damage + " << effect << endl;
                            break;
                        case 14:
                            cout << "EXP Multiplier + " << effect << endl;
                            break;
                        case 15:
                            cout << "Money Multiplier + " << effect << endl;
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
vector<int> Game::Inventory::skills;
#endif