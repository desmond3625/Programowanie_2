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

//Calculates subnet adress on the basis of IP adress and mask
void getSubnetAdress(int ip[4], int mask[4], int subnet[4]){

    for (int i=0;i<4;i++){
        subnet[i]= (ip[i] & mask[i]);
    }
}
//Prints IP adress, mask and subnet adress in decimal, hex and binary format
void print(int ip[4], int mask[4], int subnet[4]){

    cout<<"IPv4 adress:"<<endl;
    for (int i=0;i<4;i++){
       cout<<ip[i];
        if(i<3){cout<<".";}
    }
    cout<<endl;
    for (int i=0;i<4;i++){
        printf("%x",ip[i]);
        if(i<3){cout<<".";}
    }
    cout<<endl;
    for (int i=0;i<4;i++){
        bitset<8> b=ip[i];
        cout<<b;
        if(i<3){cout<<".";}
    }
    cout<<endl<<endl;
    cout<<"Mask:"<<endl;
    for (int i=0;i<4;i++){
        cout<<mask[i];
        if(i<3){cout<<".";}
    }
    cout<<endl;
    for (int i=0;i<4;i++){
        printf("%x",mask[i]);
        if(i<3){cout<<".";}
    }
    cout<<endl;
    for (int i=0;i<4;i++){
        bitset<8> b=mask[i];
        cout<<b;
        if(i<3){cout<<".";}
    }
    cout<<endl<<endl;
    cout<<"Subnet:"<<endl;
    for (int i=0;i<4;i++){
        cout<<subnet[i];
        if(i<3){cout<<".";}
    }
    cout<<endl;
    for (int i=0;i<4;i++){
        printf("%x",subnet[i]);
        if(i<3){cout<<".";}
    }
    cout<<endl;
    for (int i=0;i<4;i++){
        bitset<8> b=subnet[i];
        cout<<b;
        if(i<3){cout<<".";}
    }
    cout<<endl;
}


int main() {

    int ipOctets[4];
    int maskOctets[4];
    int subnetOctets[4];

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

    getSubnetAdress(ipOctets,maskOctets,subnetOctets);
    print(ipOctets,maskOctets,subnetOctets);

    return 0;
}
