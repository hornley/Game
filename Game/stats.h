#ifndef STATS_H
#define STATS_H
#include<iostream>
#include<string>
#include "player.h"
#include "main.h"
using namespace std;
using namespace Game;

// Displays player stats
void check_stats(string char_name, int level, float hp, float spd, float def, float base_attack, float bal, int stat_point, float exp, float exp_r)
{
    float _;
    _ = 200;
    cout << "Character " << char_name << "'s stats (Level " << level << " - xp: " << exp << "/" << exp_r << ")"<< endl;
    cout << "HP: " << hp << endl;
    cout << "Speed: " << spd << endl;
    cout << "Defense: " << def << " (" << (1 - _/(_+def)) * 100 << "%)" <<  endl;
    cout << "Base Attack: " << base_attack << endl;
    cout << "Your current balance is: " << bal << endl;
    if (stat_point >= 1)
    {
        cout << "Stat points available: " << stat_point << endl;
    }
}

// Stats Menu
auto stats(Inventory player) {
    int get_sp, use_sp, stat_point, to_add_tot, hp_ta, spd_ta, def_ta, ba_ta;
    int ba_add, apply, balance_alloted;
    bool stat_x;
    do {
        system(systemOS);
        float hp = player.getPStats()[0];
        float spd = player.getPStats()[1];
        float def = player.getPStats()[2];
        float base_attack = player.getPStats()[3];
        float bal = player.getBalance();
        string name = player.getName();
        int lvl = player.getLevel();
        int sp = player.getSP();
        float exp = player.getExp()[0];
        float exp_r = player.getExp()[1];
        check_stats(name, lvl, hp, spd, def, base_attack, bal, sp, exp, exp_r);
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
                    cout << "HP: ";
                    cin >> hp_ta;
                    to_add_tot += hp_ta;
                    cout << "Speed: ";
                    cin >> spd_ta;
                    to_add_tot += spd_ta;
                    cout << "Defense: ";
                    cin >> def_ta;
                    to_add_tot += def_ta;
                    cout << "Attack: ";
                    cin >> ba_ta;
                    to_add_tot += ba_ta;
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
                        ba_add = ba_ta * 0.25;
                        cout << "HP = " << hp << " -> " << hp + hp_ta * 3 << endl;
                        cout << "Speed = " << spd << " -> " << spd + spd_ta * 2 << endl;
                        cout << "Defense = " << def << " -> " << def + def_ta << endl;
                        cout << "Attack = " << base_attack << " -> " << base_attack + ba_ta * 0.5 << endl;
                        cout << "Do you want to apply this changes? (1 for yes---0 for no)\n";
                        cin >> apply;
                        if (apply == 1)
                        {
                            player.hp += hp_ta * 3;
                            player.speed += spd_ta * 2;
                            player.def += def_ta;
                            player.base_attack += ba_ta * 0.5;
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