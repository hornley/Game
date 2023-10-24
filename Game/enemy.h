#ifndef ENEMY_H
#define ENEMY_H
using namespace std;

namespace Game {
    #include<vector>
    #include<map>
    class Enemy {
    protected:
        int id;
        static map<int, pair<string, pair<vector<float>, vector<int>>>> allEnemy;
    public:
        float hp;  // stat
        float speed;  // stat
        float def;  // stat
        float base_attack;  // stat
        float exp_gain;
        float rewards;
        int level;  // exp and stat
        int type;
        string name;
        Enemy (int _id, string _name, float _hp, float spd, float _def, float ba, float eg, float rw, int lvl, int _type)
        {
            id = _id;
            hp = _hp;
            speed = spd;
            def = _def;
            base_attack = ba;
            level = lvl;
            exp_gain = eg;
            rewards = rw;
            name = _name;
            type = _type;
            allEnemy.insert({_id, make_pair(_name, make_pair(vector<float>{_hp, spd, _def, ba, eg, rw}, vector<int>{lvl, _type}))});
        }
        static auto getAllEnemy() { return allEnemy; }
        int getID() { return id; }
    };
}

map<int, pair<string, pair<vector<float>, vector<int>>>> Game::Enemy::allEnemy;

void addEnemy() 
{
    // ID - Name - HP - Speed - Def - BA - Exp - Rewards - Level - Type
    Enemy E_101(101, "Thief", 75, 35, 3, 2, 10, 400, 1, 1);
    Enemy E_102(102, "Bandit", 120, 42, 7, 4, 25, 700, 3, 1);
    Enemy E_103(103, "Gang Member", 150, 50, 12, 8, 24, 1050, 5, 1);
}

#endif