#include <iostream>
#include <fstream>
#include <string>
#include<chrono>

using namespace std;

class Log {

private:
    string levels[7] = {"FINEST", "FINER", "FINE", "CONFIG", "INFO", "WARNING", "SEVERE"};
    int currentLevel;

public:
    Log() {
        currentLevel = 0;
    }

    Log(int x) {
        if (x >= 0 && x < 7) {
            currentLevel = x;
        } else {
            currentLevel = 0;
            cout << "Input level not valid. Default level FINE set." << endl;
        }
    }

    void increaseLevel() {
        if (currentLevel + 1 < 7) {
            currentLevel += 1;
            cout << "Log level set to " << levels[currentLevel] << endl;
        } else {
            cout << "SEVERE level already set. Log level unchanged." << endl;
        }
    }

    void decreaseLevel() {
        if (currentLevel - 1 >= 0) {
            currentLevel -= 1;
            cout << "Log level set to " << levels[currentLevel] << endl;
        } else {
            cout << "FINE level already set. Log level unchanged." << endl;
        }
    }

    void setLevel(int x) {

        if (x >= 0 && x < 7) {
            currentLevel = x;
            cout << "Log level set to " << levels[x] << endl;
        }
    }

private:
    string severe() { return "This is the message for SEVERE level\n"; }

    string warning() { return "This is the message for WARNING level\n"; }

    string info() { return "This is the message for INFO level\n"; }

    string config() { return "This is the message for CONFIG level\n"; }

    string fine() { return "This is the message for FINE level\n"; }

    string finer() { return "This is the message for FINER level\n"; }

    string finest() { return "This is the message for FINEST level\n"; }

public:
    void printLogMessages() {

        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << ctime(&timenow);

        cout << "Current log state: " << levels[currentLevel] << endl << endl;
        if (currentLevel < 1) { cout << finest(); }
        if (currentLevel < 2) { cout << finer(); }
        if (currentLevel < 3) { cout << fine(); }
        if (currentLevel < 4) { cout << config(); }
        if (currentLevel < 5) { cout << info(); }
        if (currentLevel < 6) { cout << warning(); }
        if (currentLevel < 7) { cout << severe(); }
        cout << endl;
    }

    void printLogMessagesFile(string filename) {

        ofstream output;
        output.open(filename);

        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        output << ctime(&timenow);

        output << "Current log state: " << levels[currentLevel] << endl << endl;
        if (currentLevel < 1) { output << finest(); }
        if (currentLevel < 2) { output << finer(); }
        if (currentLevel < 3) { output << fine(); }
        if (currentLevel < 4) { output << config(); }
        if (currentLevel < 5) { output << info(); }
        if (currentLevel < 6) { output << warning(); }
        if (currentLevel < 7) { output << severe(); }
        output << endl;
        output.close();
    }
};

int main() {

    string cmd;
    int logLevel;
    string outputType;
    string fileName;

    cout << "Choose log messages output type(CONSOLE/FILE)";
    cin >> outputType;

    if (outputType == "FILE") {
        cout << "Input file name" << endl;
        cin >> fileName;
    }

    cout << "Input log level";
    cin >> logLevel;
    Log l = Log(logLevel);

    while (true) {
        cin >> cmd;
        if (cmd == "ChangeLevel") {
            cout << "Input log level";
            cin >> logLevel;
            l.setLevel(logLevel);
        }
        if (cmd == "IncreaseLevel") {
            l.increaseLevel();
        }
        if (cmd == "DecreaseLevel") {
            l.decreaseLevel();
        }
        if (cmd == "PrintLog") {
            if (outputType == "CONSOLE") { l.printLogMessages(); }
            else {
                l.printLogMessagesFile(fileName);
            }
        }
        if (cmd == "End") {
            return 0;
        }
    }
    return 0;
}
