#include <iostream>
#include <string>

using namespace std;

int main() {

    struct CompetitionClass {
        string level;
        string category;
    };

    struct Skater {
        string name;
        string surname;
        char gender;
        CompetitionClass *compClass; //field with pointer to another structure
    };


    Skater *skater1 = new Skater{"Nathan", "Chen", 'M'};
    cout << skater1->name << endl;
    cout << skater1->surname << endl;
    cout << skater1->gender << endl;

    CompetitionClass *senSingles = new CompetitionClass{"senior", "singles"};
    skater1->compClass = senSingles; //assigning pointer to CompetitionClass object to objects from Skater structure.

    cout << skater1->compClass->category << endl;
    cout << skater1->compClass->level << endl;

    Skater *skater2 = new Skater{"Alexandra", "Trusova", 'F'};
    CompetitionClass *jrDance = new CompetitionClass;
    jrDance->level = "junior";
    jrDance->category = "ice dance";

    cout<<endl;
    skater2->compClass = jrDance;
    cout << skater2->name << endl;
    cout << skater2->surname << endl;
    cout << skater2->gender << endl;
    cout << skater2->compClass->category << endl;
    cout << skater2->compClass->level << endl;

    delete skater1;
    delete skater2;
    delete senSingles;
    delete jrDance;

    return 0;
}
