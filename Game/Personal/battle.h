#ifndef BATTLE_H
#define BATTLE_H
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include "enemy.h"
#include "player.h"
#include "main.h"
using namespace Game;

int _aa;

auto enemies()
{
    addEnemy();
    Enemy enemy(1, "Dum", 0, 0, 0, 0, 0, 0, 0, 0);
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
                    float hp = iter->second.second.first.at(0);
                    float spd = iter->second.second.first.at(1);
                    float def = iter->second.second.first.at(2);
                    float ba = iter->second.second.first.at(3);
                    float eg = iter->second.second.first.at(4);
                    float rw = iter->second.second.first.at(5);
                    int lvl = iter->second.second.second.at(0);
                    int type = iter->second.second.second.at(1);

                    // Show Enemy Stats and who is first turn

                    system(systemOS);
                    cout << name;
                    cout << " | Level: " << lvl << endl;
                    cout << "Hit Points:   " << hp << endl;
                    cout << "Speed:\t      " << spd << endl;
                    cout << "Def:\t      " << def << endl;
                    cout << "Base Attack:  " << ba << endl;

                    _aa = 0;
                    cout << "\nDo you want to fight " << name << "?\n";
                    cout << "Type [1] if yes\n";
                    cin >> _aa;

                    if (_aa == 1) 
                    {
                        Enemy enemys(id, name, hp, spd, def, ba, eg, rw, lvl, type);
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

// Only for normal types! (without heal and other things)
auto normal_fight(Inventory player, Enemy enemy)
{
    if (enemy.getID() == 1) { return player; }
    // Player
    string name = player.getName();
    float hp = player.getPStats()[0];
    float spd = player.getPStats()[1];
    float def = player.getPStats()[2];
    float base_attack = player.getPStats()[3];
    float bal = player.getBalance();
    float exp = player.getExp()[0];
    float exp_required = player.getExp()[1];
    int level = player.getLevel();
    int stat_point = player.getSP();

    // Enemy
    string enemy_name = enemy.name;
    float enemy_hp = enemy.hp;
    float enemy_spd = enemy.speed;
    int enemy_ba = enemy.base_attack;
    float enemy_def = enemy.def;
    float exp_gain = enemy.exp_gain;
    float enemy_reward = enemy.rewards;

    bool player_turn, enemy_turn, success, wl=false;
    int healing_done, _XL, chp, echp, enhancement, action, heal=1, heal_option, forfeit, damage, attack;

    healing_done = 0;
    system(systemOS);
    cout << "First Turn: ";
    if (spd > enemy_spd) {
        player_turn = true;
        enemy_turn = false;
        cout << name;
    }

    // enemy first turn
    else {
        player_turn = false;
        enemy_turn = true;
        cout << enemy_name;
    }
    cout << "\nPress ENTER to continue...\n";
    cin.clear();
    cin.ignore();
    cin.ignore();

    chp = hp;        // Player HP to use for Battling
    echp = enemy_hp; // Enemy max HP
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
                cout << "1. Money enhanced attack\n";
                cout << "2. Normal attack\n";
                cin >> attack;
                system("clear;");
                // Attack Option
                if (attack == 1) {
                    cout << "You currently have: " << bal << " in your balance.\n";
                    cout << "How much do you want to use to enhance you attack?\n";
                    cin >> enhancement;
                    if (enhancement > bal) {
                        cout << "You don't have enough balance for that!\n";
                    }
                    else {
                        player.bal -= enhancement;
                        damage = base_attack * 0.30 * enhancement;
                        success = true;
                    }
                }
                else if (attack == 2) {
                    damage = base_attack;
                    success = true;
                }
                else {
                    cin.clear();
                }
                // Successful Action
                if (success) {
                    system(systemOS);
                    cout << "You dealt " << damage << endl;
                    damage *= (200/(200+enemy_def));
                    enemy_hp -= damage;
                    cout << "Enemy's HP: " << enemy_hp << endl;
                    // WINNING
                    if (enemy_hp <= 0) {
                        float bal = player.getBalance();
                        _XL = 0;
                        cout << "\nYOU WON THE FIGHT!\n";
                        cout << "Moula: " << bal << " -> " << bal + enemy_reward << endl;
                        cout << "Exp: " << exp << " -> " << exp + exp_gain << " (" << exp_required << ") " << endl;
                        exp = player.getExp()[0];
                        player.exp += exp_gain;
                        player.bal += enemy_reward;
                        // LEVEL UP
                        while (exp > exp_required) {
                            player.level += 1;
                            player.exp -= exp_required;
                            player.exp_required *= 1.35;
                            player.stat_point += 4;
                            player.hp *= 1.1;  // += 5 or 10
                            player.speed *= 1.1;  // += 3 or 5
                            player.def += 1;
                            player.base_attack *= 1.1; // += 1 or 2
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

                if (chp > hp * 0.8) {
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
                        if (chp > hp) {
                            chp -= (chp - hp);
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
                        if (chp > hp) {
                            chp -= (chp - hp);
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
                        if (chp > hp) {
                            chp -= (chp - hp);
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
                        if (chp > hp) {
                            chp -= (chp - hp);
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
                        if (chp > hp) {
                            chp -= (chp - hp);
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
                enemy_turn = true;
                player_turn = false;
            }
            cin.clear();
            cin.ignore();
        }

        // Enemy Turn na to
        else {
            system(systemOS);
            damage = (rand() % enemy_ba + 1) * 12.5;
            damage *= (200/(200+def));
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
            player_turn = true;
            enemy_turn = false;
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