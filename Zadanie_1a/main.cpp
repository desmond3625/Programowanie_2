#include <iostream>
#include <string>

using namespace std;
//Program in C++, with strings implemented using string library, accepting some constant number of names,
// and putting them into an array.

int main() {

    int n = 10; //constant number of input names

    string allNames[n]; //array of strings

    for (int t = 0; t < n; t++) {
        string str = "";
        getline(cin, str);   //reads input line
        allNames[t] = str;  //saves name in the names array
    }

    //names display loop
    for (int t = 0; t < n; t++) {
        cout << allNames[t]<<endl;
    }

    return 0;
}
