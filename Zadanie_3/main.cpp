#include <iostream>
#include <bitset>
#include <regex>

using namespace std;

//Function validating input
bool validate(string s){

    bool formatCorrect=false;
    regex rule("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");  //regular expression describing IP and mask format
    auto matchResults = std::smatch{};
    formatCorrect=regex_search(s, matchResults, rule);

    return formatCorrect;
}


int main() {

    //Input data entered by user
    std::cout << "Enter IPv4 adress:" << std::endl;
    string ip;
    getline(cin, ip);

    while(validate(ip)==false){
        cout<< "Entered data not correct."<<endl;
        getline(cin, ip);
    }

    cout << "Enter mask:" << endl;
    string mask;
    getline(cin,mask);

    while(validate(mask)==false){
        cout<< "Entered data not correct."<<endl;
        getline(cin, mask);
    }


    return 0;
}
