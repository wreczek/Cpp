#include "Osoba.h"
#include <vector>
#include <set>
#include <map>
#include <random>
#include <algorithm>

int main()
{
    srand(time(nullptr));

    cout << "Vector:\n";
    vector <Osoba> osoby;
    for(int i = 0; i < 30; i++)
    {
        osoby.push_back(Osoba());
    }
    for(vector <Osoba>::iterator it = osoby.begin(); it != osoby.end(); it++)
    {
        (*it).display();
    }

    cout << "Set:\n";
    set <Osoba> zbior(osoby.begin(), osoby.end());
    for(set <Osoba>::iterator it = zbior.begin(); it != zbior.end(); it++)
    {
        (*it).display();
    }

    cout << "Mapa:\n";
    map <string, Osoba> mapa;
    for(int i = 0; i < 30; i++)
    {
        auto a = Osoba();
        mapa[a.getKlucz()] = a;
    }
    for(map <string, Osoba>::iterator it = mapa.begin(); it != mapa.end(); it++)
    {
        it->second.display();
    }

    cout << "Generate:\n";
    vector <Osoba> osoby2(20);
    generate(osoby2.begin(), osoby2.end(), [] ()
             {
                 auto a = Osoba();
                 return a;
             }
             );
    for(vector <Osoba>::iterator it = osoby2.begin(); it != osoby2.end(); it++)
    {
        (*it).display();
    }

    cout << "Find_if:\n";
    auto a = find_if(osoby2.begin(), osoby2.end(), [] (Osoba& os)->bool {return os.getRokUr() == 2000;});
    if(a != osoby2.end()) a->display();
    else cout << "Empty!\n";

    cout << "Count_if:\n";
    int rokUr;
    cin >> rokUr;
    cout << count_if(osoby2.begin(), osoby2.end(), [&rokUr] (Osoba& os)->bool{return os.getRokUr() == rokUr;}) << endl;

    cout << "Sort:\n";
    sort(osoby2.begin(), osoby2.end(), [] (Osoba& os1, Osoba& os2)->bool {if(os1.getRokUr() == os2.getRokUr())
         {return os1.getNazwisko() < os2.getNazwisko();};
         return os1.getRokUr() < os2.getRokUr();});

    for(vector <Osoba>::iterator it = osoby2.begin(); it != osoby2.end(); it++)
    {
        (*it).display();
    }

    cout << "Unique:\n";
    osoby2.erase(unique(osoby2.begin(), osoby2.end(), [] (Osoba& os1, Osoba& os2)->bool{return os1.getNazwisko() == os2.getNazwisko();})
            , osoby2.end());
    for(vector <Osoba>::iterator it = osoby2.begin(); it != osoby2.end(); it++)
    {
        (*it).display();
    }
}

