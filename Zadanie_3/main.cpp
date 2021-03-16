#include <iostream>
#include <bitset>
#include <regex>

using namespace std;

//Function splitting input string into 4 octets and converting them to integers
void splitOctets(string s, int * octetsInt){

    string octets[4];
    int k = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') { k++; }
        else {
            octets[k]+=s[i];
        }
    }

    for (int i=0;i<4;i++){
        octetsInt[i]=stoi(octets[i]);
    }
}
//Function validating if octets values fit in range 0-255
bool validateValues(int * octetsInt){

    for (int i=0;i<4;i++){
        if(octetsInt[i]>255){return false;}
    }
    return true;
}

//Function validating input - format and values
bool validate(string s, int * octetsInt) {

    bool formatCorrect = false;
    regex rule("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");  //regular expression describing IP and mask format
    auto matchResults = std::smatch{};
    formatCorrect = regex_search(s, matchResults, rule);
    if(!formatCorrect){return false;}
    splitOctets(s,octetsInt);
    return validateValues(octetsInt);
}

string getSubnetAdress(int ip[4], int mask[4]){

    string subnetAdress="";
    int values[4];

    for (int i=0;i<4;i++){
        values[i]= (ip[i] & mask[i]);
    }
    subnetAdress= to_string(values[0])+'.'+to_string(values[1])+'.'+to_string(values[2])+'.'+to_string(values[3]);

    return subnetAdress;
}


int main() {

    int ipOctets[4];
    int maskOctets[4];

    //Input data entered by user
    std::cout << "Enter IPv4 adress:" << std::endl;
    string ip;
    getline(cin, ip);

    while (!validate(ip,ipOctets)) {
        cout << "Entered data not correct." << endl;
        getline(cin, ip);
    }

    cout << "Enter mask:" << endl;
    string mask;
    getline(cin, mask);

    while (!validate(mask, maskOctets)) {
        cout << "Entered data not correct." << endl;
        getline(cin, mask);
    }

    cout<<getSubnetAdress(ipOctets,maskOctets);
    return 0;
}
