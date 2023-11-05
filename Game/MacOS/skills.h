#ifndef ABILITIES_H
#define ABILITIES_H
#include<map>
#include<vector>
#include<string>
using namespace std;

namespace Game {
    // Considering:
    // > Base Damage (will lower ratio)
    class Skill {
        private:
            static map<int, pair<vector<string>, pair<vector<int>, vector<float>>>> allSkills;
        public:
            int skill_id;
            int skill_level_req;
            int dmg_type;
            string skill_name;
            string skill_class;
            vector<float> stat_ratio;
            int mana_consumption;  // fixed consumption
            int mana_consumption_percentage;  // percentage based consumption
            Skill (int si, int slq, string sn, string sc, int mcf, int mcp, int type, vector<float> sr)
            {
                skill_id = si;
                skill_level_req = slq;
                skill_name = sn;
                skill_class = sc;
                mana_consumption = mcf;
                mana_consumption_percentage = mcp;
                dmg_type = type;
                vector<float> stat_ratio = sr;
                allSkills.insert({si, make_pair(vector<string>{sn, sc}, make_pair(vector<int>{slq, mcf, mcp, type}, vector<float>{sr}))});
            }
            auto getAllSkills()
            {
                return allSkills;
            }
            auto getSkill (int id)
            {
                map<int, pair<vector<string>, pair<vector<int>, vector<float>>>> oms = allSkills;
                map<int, pair<vector<string>, pair<vector<int>, vector<float>>>>::iterator iter;

                map<int, pair<vector<string>, pair<vector<int>, vector<float>>>> _y;
                for (auto iter = allSkills.begin(); iter != allSkills.end(); iter++)
                {
                    if (iter->first == id)
                    {
                        string _sn = iter->second.first[0];
                        int _slq = iter->second.second.first[0];
                        int _mcf = iter->second.second.first[1];
                        int _mcp = iter->second.second.first[2];
                        int type = iter->second.second.first[3];

                        _y.insert({id, make_pair(vector<string>{_sn}, make_pair(vector<int>{_slq, _mcf, _mcp, type}, vector<float>{iter->second.second.second}))});
                    }
                }
                return _y;
            }
    };
}
map<int, pair<vector<string>, pair<vector<int>, vector<float>>>> Game::Skill::allSkills;

void addSkill()
{
    ifstream in(skillsPath);
    json file = json::parse(in);
    string sc, id, sn;
    int slq, mcf, mcp, type;
    float xa, ca;
    vector<float> sr;

    cout << "Skill Class: ";
    cin >> sc;
    cout << "Skill ID: ";
    cin >> id;
    cout << "Skill Name: ";
    cin.ignore();
    getline(cin, sn);
    cout << "Skill level requirement: ";
    cin >> slq;
    cout << "Skill Fixed consumption: ";
    cin >> mcf;
    cout << "Skill Percentage consumption: ";
    cin >> mcp;
    cout << "Skill Damage Type: ";
    cin >> type;
    do{
        cout << "Skill Stat: ";
        cin >> xa;
        if (xa == 0) { break; }
        sr.push_back(xa);
        cout << "Stat ratio: ";
        cin >> ca;
        sr.push_back(ca);
    } while (true);

    file[sc][id] = make_pair(sn, make_pair(vector<int>{slq, mcf, mcp, type}, vector<float>{sr}));
    ofstream out(skillsPath); out << setw(4) << file << endl; in.close(); out.close();
}

void adding()
{
    // 1 - str
    // 2 - int
    // 3 - agi
    // 4 - dex
    ifstream in(skillsPath);
    json file = json::parse(in);

    for (auto i = file.begin(); i != file.end(); i++)
    {
        auto x = i.value();
        for (auto j = x.begin(); j != x.end(); j++)
        {
            int id = stoi(j.key());
            int slq = j.value()[1][0][0];
            string name = j.value()[0];
            string skillClass = i.key();
            int mcf = j.value()[1][0][1];
            int mcp = j.value()[1][0][2];
            int type = j.value()[1][0][3];
            vector<float> sr = j.value()[1][1];
            Skill oms(id, slq, name, skillClass, mcf, mcp, type, sr);
        }
    }
    in.close();
}

#endif