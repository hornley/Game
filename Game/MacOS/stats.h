#ifndef STATS_H
#define STATS_H
#include<iostream>
#include<string>
#include "player.h"
#include "main.h"
using namespace std;
using namespace Game;

// Displays player stats
void check_stats(string Class, string char_name, int level, float vit, float str, float Int, float agi, float dex, float wis, float luck, float pDef, float mDef, float cons, float bal, float exp, float exp_r, int stat_point)
{
    float _;
    _ = 200;
    cout << "Character: " << char_name << "'s stats ( " << Class << " - Level " << level << " - xp: " << exp << "/" << exp_r << ")"<< endl;
    cout << "Vitality/HP:        " << vit << endl;
    cout << "Strength:           " << str << endl;
    cout << "Intelligence:       " << Int << endl;
    cout << "Agility:            " << agi << endl;
    cout << "Dexterity:          " << dex << endl;
    cout << "Wisdom:             " << wis << endl;
    cout << "Luck:               " << luck << endl;
    cout << "Physical Defense:   " << pDef << " (" << (1 - _/(_+pDef)) * 100 << "%)" <<  endl;
    cout << "Magical Defense:    " << mDef << endl;
    cout << "Your current balance is: " << bal << endl;
    cout << "Constitution:            " << cons << endl;
    // Constitution status: normal, feed, rest, so on....
    if (stat_point >= 1)
    {
        cout << "Stat points available: " << stat_point << endl;
    }
}

// Stats Menu
// Check Stats input be the player itself...
auto stats(Inventory player) {
    int get_sp, use_sp, stat_point, to_add_tot, vit_ta, agi_ta, str_ta, int_ta, dex_ta, wis_ta, luck_ta;
    int ba_add, apply, balance_alloted;
    bool stat_x;
    do {
        // vit, str, int, agi, dex, wis, luck, pdef, mdef, cons, bal, exp, expr -> 13 (0-12)
        system(systemOS);
        string Class = player.getClass();
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
        float exp_r = player.getData().second.first[18];
        string name = player.getName();
        int lvl = player.getLevel();
        int sp = player.getSP();
        check_stats(Class, name, lvl, vit, str, Int, agi, dex, wis, luck, pDef, mDef, cons, bal, exp, exp_r, sp);
        cout << "\n1. Use stat points\n";
        cout << "2. Buy more stat points\n";
        cout << "0. Back\n";
        cin >> get_sp;

        if (get_sp == 1 && sp >= 1) {
            system(systemOS);
            cout << "You have currently have " << sp << " stat points.\n";
            cout << "Do you want to use your stat points? (1 for yes and 0 for no)\n";
            cin >> use_sp;

            if (use_sp == 1) 
            {
                do 
                {
                    stat_x = false;
                    to_add_tot = 0;
                    system(systemOS);
                    cout << "Input amount to add\n";
                    cout << "Stat points available: " << sp << endl;
                    cout << "Vitality/HP: ";
                    cin >> vit_ta;
                    to_add_tot += vit_ta;
                    cout << "Strength: ";
                    cin >> str_ta;
                    to_add_tot += str_ta;
                    cout << "Intelligence; ";
                    cin >> int_ta;
                    to_add_tot += int_ta;
                    cout << "Agility: ";
                    cin >> agi_ta;
                    to_add_tot += agi_ta;
                    cout << "Dexterity: ";
                    cin >> dex_ta;
                    to_add_tot += dex_ta;
                    cout << "Wisdom: ";
                    cin >> wis_ta;
                    to_add_tot += wis_ta;
                    cout << "Luck: ";
                    cin >> luck_ta;
                    to_add_tot += luck_ta;
                    if (to_add_tot > sp) 
                    {
                        cout << "You exceeded the amount of stat_point available!\n";
                        cout << "You only have " << sp << " stat points!\n"; // not yet done
                        cin.clear();
                        cin.ignore();
                    }

                    else 
                    {
                        system(systemOS);
                        ba_add = str_ta * 0.25;
                        cout << "Vitality/HP = " << vit << " -> " << vit + vit_ta * 3 << endl;
                        cout << "Strength = " << str << " -> " << str + str_ta * 0.5 << endl;
                        cout << "Intelligence = " << Int << " -> " << Int + int_ta * 0.5 << endl;
                        cout << "Agility = " << agi << " -> " << agi + agi_ta * 2 << endl;
                        cout << "Dexterity = " << dex << " -> " << dex + dex_ta * 0.5 << endl;
                        cout << "Wisdom = " << wis << " -> " << wis + wis_ta * 0.5 << endl;
                        cout << "Luck = " << luck << " -> " << luck + luck_ta * 0.5 << endl;
                        cout << "Do you want to apply this changes? (1 for yes---0 for no)\n";
                        cin >> apply;
                        if (apply == 1)
                        {
                            player.vitality += vit_ta * 3;
                            player.strength += str_ta * 0.5;
                            player.intelligence += int_ta * 0.5;
                            player.agility += agi_ta * 2;
                            player.dexterity += dex_ta * 0.5;
                            player.wisdom += wis_ta * 0.5;
                            player.luck += luck_ta * 0.5;
                            player.stat_point -= to_add_tot;
                            stat_x = true;
                        }
                    }
                    if (stat_x) { break; }
                    cin.clear();
                    cin.ignore();
                } while (true);
            }
        }
        else if (get_sp == 1 && sp == 0)
        {
            system(systemOS);
            cout << "You have no stats points to use!\n";
            cout << "Press ENTER to continue.\n";
            cin.clear();
            cin.ignore();
            cin.ignore();
        }
        else if (get_sp == 2) {
            system(systemOS);
            cout << "Available balance: " << bal << endl;
            cout << "How much do you want to use? (10 moula: 1 stat point)\n"; // 8 + 2 tax so 10
            cin >> balance_alloted;
            if (balance_alloted > bal) {
                system(systemOS);
                cout << "You are not that rich! PEASANT!\n";
                cin.clear();
                cin.ignore();
                cin.ignore();
            }
            else {
                player.bal -= balance_alloted;
                player.bal += balance_alloted % 10;
                player.stat_point += balance_alloted / 10;
            }
        }
        else { break; }
    } while (true);
    cin.clear();
    return player;
}  

#endif