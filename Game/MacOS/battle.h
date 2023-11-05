#ifndef BATTLE_H
#define BATTLE_H
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include "enemy.h"
#include "player.h"
#include "main.h"
#include "skills.h"
using namespace Game;

int _aa;
auto enemies()
{
    Enemy enemy(1, "Dummy", {75, 2, 0, 35, 0, 0, 3, 1, 0, 0, 0, 0, 10, 400}, 1, 1);
    int _xa, eChosen;

    map<int, pair<string, pair<vector<float>, vector<int>>>> _x = enemy.getAllEnemy();
    map<int, pair<string, pair<vector<float>, vector<int>>>>::iterator iter;
    do
    {
        _xa = 0;
        system(systemOS);

        cout << "Choose an Enemy to view!\n";
        for (iter = _x.begin(); iter != _x.end(); iter++)
        {
            if (iter->first != 1)
            {
                _xa++;
                cout << _xa << ". ";
                cout << iter->second.first << endl;
            }
        }
        cout << "0. Back\n";
        cin >> eChosen;
        if (eChosen <= _xa && eChosen != 0) {
            for (iter = _x.begin(); iter != _x.end(); iter++)
            {
                if (iter->first == eChosen + 100)
                {
                    int id = iter->first;
                    string name = iter->second.first;
                    float vit = iter->second.second.first.at(0);
                    float str = iter->second.second.first.at(1);
                    float Int = iter->second.second.first.at(2);
                    float agi = iter->second.second.first.at(3);
                    float dex = iter->second.second.first.at(4);
                    float wis = iter->second.second.first.at(5);
                    float pDef = iter->second.second.first.at(6);
                    float mDef = iter->second.second.first.at(7);
                    float pp = iter->second.second.first.at(8);
                    float mp = iter->second.second.first.at(9);
                    float cc = iter->second.second.first.at(10);
                    float cd = iter->second.second.first.at(11);
                    float eg = iter->second.second.first.at(12);
                    float rw = iter->second.second.first.at(13);
                    int lvl = iter->second.second.second.at(0);
                    int type = iter->second.second.second.at(1);

                    // Show Enemy Stats and who is first turn

                    system(systemOS);
                    cout << name << " - (Level " << lvl << ")" << endl;
                    cout << "Vitality:          " << vit << endl;
                    cout << "Agility:           " << agi << endl;
                    cout << "Strenght:          " << str << endl;
                    cout << "Intelligence:      " << Int << endl;
                    cout << "Dexterity:         " << dex << endl;
                    cout << "Wisdom:            " << wis << endl;
                    cout << "Physical Def:      " << pDef << endl;
                    cout << "Magical Def:       " << mDef << endl;
                    cout << "\nRewards:\n";
                    cout << "EXP:               " << eg << endl;
                    cout << "Money:             " << rw << endl;

                    _aa = 0;
                    cout << "\nDo you want to fight " << name << "?\n";
                    cout << "Type [1] if yes\n";
                    cin >> _aa;

                    if (_aa == 1) 
                    {
                        Enemy enemys(id, name, {vit, str, Int, agi, dex, wis, pDef, mDef, pp, mp, eg, rw}, lvl, type);
                        return enemys;
                        break;
                    }
                    break;
                }
            }
        }
        else { break; }
    } while (_aa != 1);
    return enemy;
}

// To be Added:
// > Endurance (dmg red)
// > Accuracy (hit chance)
// > Crit Chance and Crit Damage
auto damage_dealt(int dmg_type, float pDef, float mDef, float pPene, float mPene, vector<float> stats, vector<float> ratio)
{
    float damage, totdmg = 1;
    // dmg_type:
    // 1 -> Physical 
    // 2 -> Magical
    // 3 -> Both
        damage = 0;
        for (int i = 0; i < ratio.size(); i += 2)
        {
            float stat = ratio[i];
            float statuse = stats[stat - 1];
            float sRatio = ratio[i + 1];
            damage += statuse * sRatio;
        }

    if (dmg_type == 1) { totdmg = damage * (200/(200+pDef)); }
    else if (dmg_type == 2) { totdmg = damage * (275/(275+mDef)); }
    return totdmg;
}

// Only for normal types! (without heal and other things)
auto normal_fight(Inventory player, Enemy enemy)
{
    if (enemy.getID() == 1) { return player; }
    // Player
    string name = player.getName();
    float vit = player.getData().second.first[0];
    float str = player.getData().second.first[1];
    float Int = player.getData().second.first[2];
    float agi = player.getData().second.first[3];
    float dex = player.getData().second.first[4];
    float wis = player.getData().second.first[5];
    float luck = player.getData().second.first[6];
    float pDef = player.getData().second.first[7];
    float mDef = player.getData().second.first[8];
    float pPene = player.getData().second.first[9];
    float mPene = player.getData().second.first[10];
    float critC = player.getData().second.first[11];
    float critD = player.getData().second.first[12];
    float expMulti = player.getData().second.first[13];
    float moneyMulti = player.getData().second.first[14];
    float cons = player.getData().second.first[15];
    float bal = player.getData().second.first[16];
    float exp = player.getData().second.first[17];
    float exp_required = player.getData().second.first[18];
    int level = player.getLevel();

    // Enemy
    string enemy_name = enemy.name;
    float enemy_vit = enemy.vitality;
    float enemy_agi = enemy.agility;
    float enemy_str = enemy.strength;
    float enemy_int = enemy.intelligence;
    float enemy_dex = enemy.dexterity;
    float enemy_pDef = enemy.pDef;
    float enemy_mDef = enemy.mDef;
    float enemy_cChance = enemy.critChance;
    float enemy_cDamage = enemy.critDamage;
    float exp_gain = enemy.exp_gain;
    float enemy_reward = enemy.rewards;

    bool player_turn, enemy_turn, success, wl=false;
    int healing_done, _XL, chp, echp, enhancement, action, heal=1, heal_option, forfeit, damage, attack, p_turn_amount=1, p_turn=1, e_turn_amount=1, e_turn=1;

    healing_done = 0;
    system(systemOS);
    cout << "First Turn: ";
    if (agi > enemy_agi or agi == enemy_agi) {
        p_turn_amount = agi / enemy_agi;
        player_turn = true;
        enemy_turn = false;
        cout << name;
    }

    // enemy first turn
    else {
        e_turn_amount = enemy_agi / agi;
        player_turn = false;
        enemy_turn = true;
        cout << enemy_name;
    }

    cout << "\nPress ENTER to continue...\n";
    cin.clear();
    cin.ignore();
    cin.ignore();

    chp = vit;        // Player HP to use for Battling
    echp = enemy_vit; // Enemy max HP
    while (chp > 0) {
        float bal = player.getBalance();
        // Battle Action
        if (player_turn) {
            system(systemOS);
            cout << "Choose an action!\n";
            cout << "1. Attack\n";
            cout << "2. Heal\n";
            cout << "3. Use an Item\n";
            cout << "4. Forfeit\n";
            cin >> action;

            // Attack Option
            if (action == 1) {
                system(systemOS);
                cout << "Choose an attack!\n";
                cout << "1. Money attack\n";
                vector<int> playerSkills = player.getSkills();
                map<int, pair<vector<int>, vector<float>>> choices;
                Skill Dummy(0, 0, "asd", "Dummy", 0, 0, 0, {0, 0});
                int _xa = 2;
                for (int i = 0; i < playerSkills.size(); i++)
                {
                    map<int, pair<vector<string>, pair<vector<int>, vector<float>>>> Skills = Dummy.getSkill(playerSkills[i]);
                    map<int, pair<vector<string>, pair<vector<int>, vector<float>>>>::iterator iter;
                    for (auto iter = Skills.begin(); iter != Skills.end(); iter++)
                    {
                        cout << _xa << ". " << iter->second.first[0] << endl;
                        choices.insert({_xa, make_pair(vector<int>{iter->second.second.first}, vector<float>{iter->second.second.second})});
                        _xa++;
                    }
                }
                cin >> attack;
                system("clear;");
                if (attack == 1) {
                    cout << "You currently have: " << bal << " in your balance.\n";
                    cout << "How much do you want to use to enhance you attack?\n";
                    cin >> enhancement;
                    if (enhancement > bal) {
                        cout << "You don't have enough balance for that!\n";
                    }
                    else {
                        player.bal -= enhancement;
                        damage = str * 0.30 * enhancement;
                        success = true;
                    }
                }
                else if (attack <= choices.size() + 1) {
                    map<int, pair<vector<int>, vector<float>>>::iterator iter;
                    for (auto iter = choices.begin(); iter != choices.end(); iter++)
                    {
                        if (attack == iter->first)
                        {
                            damage = damage_dealt(iter->second.first[3], enemy_pDef, enemy_mDef, pPene, mPene, vector<float>{str, Int, agi, dex}, iter->second.second);
                        }
                    }
                    success = true;
                }
                else {
                    cin.clear();
                }
                // Successful Action
                if (success) {
                    system(systemOS);
                    echp -= damage;
                    cout << "You dealt " << damage << endl;
                    cout << "Enemy's HP: " << echp << endl;
                    // WINNING
                    if (echp <= 0) {
                        float bal = player.getBalance();
                        _XL = 0;
                        cout << "\nYOU WON THE FIGHT!\n";
                        cout << "Moula: " << bal << " -> " << bal + enemy_reward << endl;
                        cout << "Exp: " << exp << " -> " << exp + exp_gain << " (" << exp_required << ") " << endl;
                        player.exp += exp_gain;
                        player.bal += enemy_reward;
                        exp = player.getExp()[0];
                        // EXP_REQUIRED NOT UPDATING EVERY LEVEL UP!
                        // LEVEL UP
                        while (exp > exp_required) {
                            player.level += 1;
                            player.exp -= exp_required;
                            player.exp_required *= 1.35;
                            player.stat_point += 4;
                            player.vitality *= 1.1;  // tbc
                            player.agility *= 1.1;  // tbc
                            player.dexterity *= 1.1;  // tbc
                            player.wisdom *= 1.1;  // tbc
                            player.pDef += 1;
                            player.mDef += 1;
                            player.strength *= 1.1;  // tbc
                            exp -= exp_required;
                            exp_required *= 1.35;
                            _XL++;
                        }
                        if (_XL != 0) { cout << "YOU LEVELED UP " << _XL << " TIMES!\n"; }

                        cin.clear();
                        cin.ignore();
                        cin.ignore();
                        wl = true;
                        break;
                    }
                    
                    cout << "Press enter to continue!\n";
                    cin.clear();
                    cin.ignore();
                }
            }

            // Heal Option
            else if (action == 2) {
                if (healing_done == 3) {
                    cout << "You can't use heal anymore!\n";
                }

                if (chp > vit * 0.8) {
                    cout << "You're HP is still above 80%, are you sure?\n";
                    cout << "1 for yes 0 for no\n";
                    cin >> heal;
                }

                if (heal == 1) {
                    cout << "Heal options (current level " << level << ")\n";
                    cout << "Current HP: " << chp << endl;
                    cout << " \tCost\tHP Recovery\tRequired Level\n";
                    cout << "1. \t100\t    15\t\t      1\n";
                    cout << "2. \t200\t    40\t\t      5\n";
                    cout << "3. \t400\t    100\t\t      10\n";
                    cout << "4. \t700\t    250\t\t      15\n";
                    cout << "5. \t1000\t    500\t\t      20\n";
                    cout << "0. Cancel\n";
                    cin >> heal_option;
                    switch (heal_option)
                    {
                    case 1:
                        if (bal < 100) {
                            cout << "Not enough balance!\n";
                            break;
                        }
                        player.bal -= 100;
                        chp += 15;
                        if (chp > vit) {
                            chp -= (chp - vit);
                        }
                        cout << chp << " + 15\n";
                        success = true;
                        healing_done++;
                        break;
                    case 2:
                        if (bal < 200) {
                            cout << "Not enough balance!\n";
                            break;
                        }
                        player.bal -= 200;
                        chp += 40;
                        if (chp > vit) {
                            chp -= (chp - vit);
                        }
                        cout << chp << " + 40\n";
                        success = true;
                        healing_done++;
                        break;
                    case 3:
                        if (bal < 400) {
                            cout << "Not enough balance!\n";
                            break;
                        }
                        player.bal -= 400;
                        chp += 100;
                        if (chp > vit) {
                            chp -= (chp - vit);
                        }
                        cout << chp << " + 100\n";
                        success = true;
                        healing_done++;
                        break;
                    case 4:
                        if (bal < 700) {
                            cout << "Not enough balance!\n";
                            break;
                        }
                        player.bal -= 700;
                        chp += 250;
                        if (chp > vit) {
                            chp -= (chp - vit);
                        }
                        cout << chp << " + 250\n";
                        success = true;
                        healing_done++;
                        break;
                    case 5:
                        if (bal < 1000) {
                            cout << "Not enough balance!\n";
                            break;
                        }
                        player.bal -= 1000;
                        chp += 500;
                        if (chp > vit) {
                            chp -= (chp - vit);
                        }
                        cout << chp << " + 500\n";
                        success = true;
                        healing_done++;
                        break;
                    case 0:
                        break;
                    default:
                        cout << "That is not an option!\n";
                        break;
                    }
                }
            }

            // Use an Item Option
            else if (action == 3) {

            }

            // Forfeit Option
            else if (action == 4) {
                cout << "Are you sure, you will lose 90\% of your balance?\n";
                cin >> forfeit;
                cin.clear();
                cin.ignore();
                if (forfeit == 1) {
                    cout << "You lost " << bal * 0.9 << " moula for forfeiting!!!\n";
                    player.bal *= 0.1;
                    cout << "Press Enter to continue.\n";
                    break;
                }
            }
        

            // If player turn is successful
            if (success) {
                if (p_turn == p_turn_amount)
                {
                    enemy_turn = true;
                    player_turn = false;
                    e_turn = 1;
                }
                else { p_turn++; }
            }
            cin.clear();
            cin.ignore();
        }

        // Enemy Turn na to
        else {
            system(systemOS);
            // damage = damage_dealt(enemy_str, enemy_int, pDef, mDef, 1);
            damage = 15;
            cout << "Enemy dealt " << damage << endl;
            chp -= damage;
            cout << "Your HP: " << chp << endl;
            if (chp <= 0) {
                cout << "YOU LOST THE FIGHT!\n";
                cin.clear();
                cin.ignore();
                break;
            }
            cout << "Press enter to continue!\n";
            cin.clear();
            cin.ignore();
            if (e_turn == e_turn_amount)
            {
                player_turn = true;
                enemy_turn = false;
                p_turn = 1;
            }
            else { e_turn++; }
        }
    }
    return player;
}

auto menu (Inventory player)
{
    int option;
    system(systemOS);
    cout << "Battle Menu\n";
    cout << "1. Fight\n";
    cout << "2. Training\n";
    cout << "3. Boss Fight\n";
    cout << "4. Dungeon\n";
    cout << "0. Back\n";
    cin >> option;

    while (option != 0)
    {
        if (option == 1)
        {
            auto enemy = enemies();
            
            if (enemy.getID() != 1) 
            {
                auto players = normal_fight(player, enemy);
                if (_aa == 1) { return players; }
            }
        }
        else if (option == 2)
        {

        }
        system(systemOS);
        cout << "Battle Menu\n";
        cout << "1. Fight\n";
        cout << "2. Training\n";
        cout << "3. Boss Fight\n";
        cout << "4. Dungeon\n";
        cout << "0. Back\n";
        cin >> option;
    }

    return player;
}

#endif