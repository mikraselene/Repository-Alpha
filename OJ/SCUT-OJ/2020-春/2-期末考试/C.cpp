// C (WA)

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Monster
{
public:
    Monster()
    {
        this->attack = 0;
        this->hp = 0;
    }
    int GetAttack()
    {
        return attack;
    }
    int GetHP()
    {
        return hp;
    }
    void SetAs(int as)
    {
        this->as = as;
    }
    void SetAttack(int attack)
    {
        this->attack = attack;
    }
    void SetHP(int hp)
    {
        this->hp = hp;
    }
    double GetThreaten()
    {
        double th = attack * ceil(hp * 1.0 / as);
        return th;
    }
    friend bool operator>(Monster A, Monster B)
    {
        return A.GetThreaten() > B.GetThreaten();
    }

private:
    int as;
    int attack;
    int hp;
};

bool cmp(Monster A, Monster B)
{
    return A > B;
}

class Scuter
{
public:
    Scuter(int hp, int attack)
    {
        this->attack = attack;
        this->hp = hp;
    }
    bool IsDeath()
    {
        return hp <= 0;
    }
    int LeastLossOfHP(Monster *monster, int num)
    {
        int lossHP = 0;
        sort(monster, monster + num, cmp);
        for (int i = 0; i < num; i++)
        {
            int sum = 0;
            int time = ceil(monster[i].GetHP() * 1.0 / this->attack);
            for (int j = i; j < num; j++)
            {
                sum += monster[j].GetAttack() * time;
            }
            lossHP += sum;
        }
        this->hp -= lossHP;
        return lossHP;
    }

private:
    int attack;
    int hp;
};

int main()
{
    Monster *monster;
    int attack, hp, num;
    while (cin >> hp >> attack)
    {
        int as = attack;
        Scuter scuter(hp, attack);
        cin >> num;
        monster = new Monster[num];
        for (int i = 0; i < num; ++i)
        {
            cin >> hp >> attack;
            monster[i].SetHP(hp);
            monster[i].SetAttack(attack);
            monster[i].SetAs(as);
        }
        cout << scuter.LeastLossOfHP(monster, num) << " ";
        if (scuter.IsDeath())
        {
            cout << "Dead" << endl;
        }
        else
        {
            cout << "Alive" << endl;
        }
        delete[] monster;
        monster = nullptr;
    }
}
