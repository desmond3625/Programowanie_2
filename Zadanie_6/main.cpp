#include <iostream>

using namespace std;

class Ship;
class Captain;

class Captain {
private:
    string name;
    string surname;
    int age;
    bool isRetired;

public:

    Captain() {
        this->name = "John";
        this->surname = "Doe";
        this->age = 0;
        this->isRetired = false;
    }

    Captain(string name, string surname, int age, bool isRetired) {
        this->name = name;
        this->surname = surname;
        this->age = age;
        this->isRetired = isRetired;
    }

    int getAge() {
        return age;
    }

    void setAge(int age) {
        this->age = age;
    }

    void setName(string name, string surname) {
        this->name = name;
        this->surname = surname;
    }

    void setRetirement(bool isRetired) {
        this->isRetired = isRetired;
    }

    bool checkRetirement() {
        return isRetired;
    }

    friend std::ostream &operator<<(std::ostream &str, const Ship &ship);

    friend std::ostream &operator<<(std::ostream &str, const Captain &captain);

    ~Captain() {};
};


class Ship {

private:
    string name;
    int crew;
    int foodRations;

protected:
    Captain captain;

public:

    Ship() {
        this->name = "";
        this->captain = Captain();
        this->crew = 0;
    }

    Ship(string name, Captain captain, int crew) {
        this->name = name;
        this->captain = captain;
        this->crew = crew;
    }

    int getCrew() const {
        return crew;
    }

    void setCrew(int crew) {
        this->crew = crew;
    }

    void enlistCrew(int newMembers) {
        crew += newMembers;
    }

    Captain getCaptain() {
        return this->captain;
    }

    void setFood(int foodRations) {
        this->foodRations = foodRations;
    }

    int getFood() {
        return foodRations;
    }

    virtual void calculateFood() {
        foodRations = crew * 4;
    }

    virtual void calculateFood(bool dessert) {

        if (dessert) {
            foodRations = crew * 5;
        } else {
            foodRations = crew * 4;
        }
    }

    friend std::ostream &operator<<(std::ostream &str, const Ship &ship);


    virtual ~Ship() {}

};

std::ostream &operator<<(std::ostream &str, const Ship &ship) {
    str << "Ship name:   " << ship.name << "\n"
        << "Captain:     " << ship.captain.name << " " << ship.captain.surname << "\n"
        << "Crew:        " << ship.crew << "\n\n";

    return str;
}

std::ostream &operator<<(std::ostream &str, const Captain &captain) {
    string r;
    if (captain.isRetired) { r = "yes"; }
    else { r = "no"; }

    str << "Captain:     " << captain.name << " " << captain.surname << "\n"
        << "Age:         " << captain.age << "\n"
        << "Retired:     " << r << "\n\n";

    return str;
}

class PassengerShip : public virtual Ship {
private:
    int passengers;

public:
    int getPassengers() const {
        return passengers;
    }

    void setPassengers(int passengers) {
        this->passengers = passengers;
    }

    int getTotalPeople() const {
        return passengers + getCrew();
    }

    void calculateFood() override{
        setFood((passengers + getCrew()) * 4);
    }

    void calculateFood(bool dessert) override {
        if (dessert) {
            setFood((passengers + getCrew()) * 5);
        } else {
            setFood((passengers + getCrew()) * 4);
        }
    }
};

class MilitaryShip : public virtual Ship {
public:
    int towers;
public:

    MilitaryShip() {
        towers = 0;
    }

    int getTowers() {
        return towers;
    }

    void setTowers(int towers) {
        this->towers = towers;
    }
};

class Transporter : public PassengerShip, public MilitaryShip {

};

int main() {

    //Different uses of constructors:

    Captain capt_1 = Captain("William", "Turner", 39, false);
    Ship ship_1 = Ship("Black Pearl", capt_1, 23);

    Ship ship_2 = Ship("Whiskey", Captain("Johnny", "Walker", 72, true), 15);

    Ship ship_3 = {"Kolmogorov", Captain("Don", "Kot", 20, false), 16};

    Captain capt_4 = Captain("Charlie", "Parker", 55, true);
    Ship *ship_4 = new Ship("Wild Bebop", capt_4, 33);

    cout << ship_1;
    cout << ship_2;
    cout << ship_3;
    cout << *ship_4;

    cout << "----------------------------------------------------\n";

    //Copy constructor example
    Ship ship_copy = Ship(ship_3);
    cout<<"Origin ship: \n";
    cout << ship_3;
    cout<<"Copy ship: \n";
    cout << ship_copy;

    ship_3.setCrew(25);
    cout<<"Origin ship: \n";
    cout << ship_3;
    cout<<"Origin ship: \n";
    cout << ship_copy;
    cout << "----------------------------------------------------\n";

    //Function calls for object created with and without dynamic allocation

    cout<<*ship_4;
    ship_4->enlistCrew(13);
    cout << *ship_4;

    cout<<ship_1;
    ship_1.enlistCrew(4);
    cout << ship_1;
    cout << "----------------------------------------------------\n";

    //Inheritance example - constructor and methods

    PassengerShip pShip_1 = PassengerShip();
    cout << "Total people: " << pShip_1.getTotalPeople() << "\n";
    pShip_1.enlistCrew(13);
    cout << "Total people: " << pShip_1.getTotalPeople() << "\n";
    pShip_1.setPassengers(22);
    cout << "Total people: " << pShip_1.getTotalPeople() << "\n";
    cout << pShip_1.getCaptain(); //default captain created

    cout << "----------------------------------------------------\n";

    //Inherited class with modified method of parent class
    PassengerShip pShip_food;
    pShip_food.setPassengers(33);
    pShip_food.setCrew(12);
    cout << "Passenger + crew: " << pShip_food.getTotalPeople() << std::endl;
    pShip_food.calculateFood();
    cout << "Food rations: " << pShip_food.getFood() << std::endl;
    Ship ship_food;
    ship_food.setCrew(15);
    cout << "Crew: " << ship_food.getCrew() << std::endl;
    ship_food.calculateFood();
    cout << "Food rations: " << ship_food.getFood() << std::endl;

    cout << "----------------------------------------------------\n";

    //Two different class methods with the same name but with different arguments
    cout << "Crew: " << ship_food.getCrew() << std::endl;
    ship_food.calculateFood(true);
    cout << "Food rations with desserts: " << ship_food.getFood() << std::endl;
    ship_food.calculateFood();
    cout << "Food rations default: " << ship_food.getFood() << std::endl;

    cout << "Passenger + crew: " << pShip_food.getTotalPeople() << std::endl;
    pShip_food.calculateFood(true);
    cout << "Food rations with desserts: " << pShip_food.getFood() << std::endl;
    pShip_food.calculateFood();
    cout << "Food rations default: " << pShip_food.getFood() << std::endl;

    cout << "----------------------------------------------------\n";

    //Class inheriting after more than one class - virtual inheritance
    Transporter tr;
    tr.setTowers(3);
    cout << "Number of towers: " << tr.getTowers() << endl;

    cout << "----------------------------------------------------\n";

    //Creating array of pointers to different types of ships
    Transporter *trb = new Transporter();
    trb->setCrew(19);
    PassengerShip *passShip = new PassengerShip();
    passShip->setCrew(33);
    passShip->setPassengers(100);
    Ship *shipList[] = {new Ship{}, new PassengerShip{},
                        new Ship("Guardians Of Galaxy", Captain("Peter", "Quill", 30, false), 4), trb, passShip};

    for (Ship* s : shipList)
    {
        cout << *s;
        s->calculateFood(false); //virtual methods
        cout << "Food rations: " << s->getFood()<<"\n\n";
    }

    cout << "----------------------------------------------------\n";

    //Casting methods available only in subclass
    Ship* ship = new PassengerShip{};
    ship->enlistCrew(5);
    (*dynamic_cast<PassengerShip*>(ship)).setPassengers(60);
    cout<<"Total people: "<<(*dynamic_cast<PassengerShip*>(ship)).getTotalPeople()<<endl;

    cout << "----------------------------------------------------\n";

    delete ship_4;
    return 0;
}