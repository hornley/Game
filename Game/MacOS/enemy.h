#ifndef ENEMY_H
#define ENEMY_H
using namespace std;
#include<vector>
#include<map>

// Stats protected/private implementation
// > Use vector to return stats
namespace Game {
    class Enemy {
    protected:
        int id;
        static map<int, pair<string, pair<vector<float>, vector<int>>>> allEnemy;
    public:
        float vitality;
        float strength;
        float intelligence;
        float agility;
        float dexterity;
        float wisdom;
        float pDef;
        float mDef;
        float phyPenetration;  // unimplemented - but added to stats
        float magPenetration;  // unimplemented - but added to stats
        float critChance; // unimplemented
        float critDamage; // unimplemented
        float exp_gain;
        float rewards;
        int level;  // exp and stat
        int type;
        string name;
        Enemy (int _id, string _name, vector<float> _stats, int lvl, int _type)
        {
            id = _id;
            name = _name;
            vitality = _stats[0];
            strength = _stats[1];
            intelligence = _stats[2];
            agility = _stats[3];
            dexterity = _stats[4];
            wisdom = _stats[5];
            pDef = _stats[6];
            mDef = _stats[7];
            phyPenetration = _stats[8];
            magPenetration = _stats[9];
            critChance = _stats[10];
            critDamage = _stats[11];
            exp_gain = _stats[12];
            rewards = _stats[13];

            level = lvl;
            type = _type;
            allEnemy.insert({_id, make_pair(_name, make_pair(vector<float>{vitality, strength, intelligence, agility, dexterity, wisdom, pDef, mDef, phyPenetration, magPenetration, critChance, critDamage, exp_gain, rewards}, vector<int>{lvl, _type}))});
        }
        static auto getAllEnemy() { return allEnemy; }
        int getID() { return id; }
        // auto getEnemy(int id)
        // {
        //     map<int, pair<string, pair<vector<float>, vector<int>>>> oms = allEnemy;
        //     map<int, pair<string, pair<vector<float>, vector<int>>>>::iterator iter;
        //     map<int, pair<string, pair<vector<float>, vector<int>>>> x;
        //     for (auto iter = oms.begin(); iter != oms.end(); iter++)
        //     {
        //         int id = iter->first;
        //         string name = iter->second.first[0];
        //         vector<float> stats = iter->second.second.first;
        //         int lvl = iter->second.second.second[0];
        //         int type = iter->second.second.second[1];
        //         x.insert({ id, make_pair(name, make_pair(vector<float>{stats}, vector<float>{lvl, type} )) });
        //     }
        //     return x;
        // }
    };
}

map<int, pair<string, pair<vector<float>, vector<int>>>> Game::Enemy::allEnemy;

void addEnemy()
{
    ifstream in(enemiesPath);
    json file = json::parse(in);
    int id;
    string name;
    vector<float> stats;
    float oms;
    int lvl;
    int type;
    string ty;

    cout << "Enemy ID: ";
    cin >> id;
    cout << "Enemy Name: ";
    getline(cin, name);
    cout << "Enemy Stats\n";
    cout << "VIT/STR/INT/AGI/DEX/WIS/pDEF/mDEF/pPene/mPene/critChance/critDamage/exp_gain/rewards\n";
    for (int i = 1; i <= 14; i++)
    {
        cin >> oms;
        stats.push_back(oms);
    }
    cout << "Enemey Level: ";
    cin >> lvl;
    cout << "Enemy Type: ";
    cin >> type;
    
    switch (type)
    {
    case 0: ty = "Created"; break;
    case 1: ty = "Normal"; break;
    case 2: ty = "Uniqe"; break;
    case 3: ty = "Boss"; break;
    }

    file[ty][to_string(id)] = make_pair(name, make_pair(vector<float>{stats}, vector<int>{lvl, type}));
    ofstream out(enemiesPath); out << setw(4) << file << endl; in.close(); out.close();
}

void adders()
{
    ifstream in (enemiesPath);
    json file = json::parse(in);

    for (auto i = file.begin(); i != file.end(); i++)
    {
        auto x = i.value();
        for (auto j = x.begin(); j != x.end(); j++)
        {
            int id = stoi(j.key());
            string name = j.value()[0];
            vector<float> stats = j.value()[1][0];
            int lvl = j.value()[1][1][0];
            int type = j.value()[1][1][1];
            Enemy oms(id, name, stats, lvl, type);
        }
    }
}

#endif