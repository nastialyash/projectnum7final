

#include <iostream>

using namespace std;

class Service {
protected:
    string type; 
    string name;  
    double price; 

public:
    Service() : type(type), name(name), price(0.0) {}

    Service(string t, string n, double p) : type(t), name(n), price(p) {}

    virtual void display() const {
        cout << type << ": " << name << ", " << price << " grn" << endl;
    }

    string getType() const { return type; }
    string getName() const { return name; }
    double getPrice() const { return price; }

    virtual ~Service() {}
};


class Haircut : public Service {
public:
    Haircut(string n, double p) : Service("Haircut", n, p) {}
    Haircut() : Service() {}
};

class Coloring : public Service {
public:
    Coloring(string n, double p) : Service("Coloring", n, p) {}
    Coloring() : Service() {}
};

class Manicure : public Service {
    string additional;

public:
    Manicure(string n, double p, string add = "")
        : Service("Manicure", n, p), additional(add) {}
    Manicure() : Service(), additional("") {}

    void display() const override {
        Service::display();
        if (!additional.empty())
            cout << " Additional : " << additional << endl;
    }
};

class CosmeticProcedure : public Service {
    int duration;

public:
    CosmeticProcedure(string n, double p, int d)
        : Service("Cosmetic procedure", n, p), duration(d) {}
    CosmeticProcedure() : Service(), duration(0) {}

    void display() const override {
        cout << type << ": " << name << ", " << price
            << " grn,duration" << duration << endl;
    }
};


class Salon {
    static const int maxservice = 100; 
    Service* services[maxservice];
    int serviceCount;

public:
    Salon() : serviceCount(0) {
        for (int i = 0; i < maxservice; i++) {
            services[i] = nullptr;
        }
    }

    ~Salon() {
        for (int i = 0; i < serviceCount; i++) {
            delete services[i];
        }
    }

    void addService(Service* service) {
        if (serviceCount < maxservice) {
            services[serviceCount++] = service;
        }
        else {
            cout << "Service cant addn!\n";
        }
    }

    void removeService(const string& name) {
        for (int i = 0; i < serviceCount; i++) {
            if (services[i] && services[i]->getName() == name) {
                delete services[i];
                services[i] = nullptr;

                
                for (int j = i; j < serviceCount - 1; j++) {
                    services[j] = services[j + 1];
                }

                services[--serviceCount] = nullptr;
                cout << "Service \"" << name << "\" delete\n";
                return;
            }
        }
        cout << "Service\"" << name << "\" not found \n";
    }

    void displayServices() const {
        if (serviceCount == 0) {
            cout << "No  services \n";
            return;
        }

        cout << "List pf services : \n";
        for (int i = 0; i < serviceCount; i++) {
            if (services[i])
                services[i]->display();
        }
    }

    
};


void displayMenu() {
    cout << "\n=== Menu ===\n";
    cout << "1. Add services\n";
    cout << "2. Delete services\n";
    cout << "3. Show all services\n";
    
    cout << "4. Exit\n";
    cout << "Enter an action ";
}

void addServiceMenu(Salon& salon) {
    int choice;
    cout << "1. Haircut\n";
    cout << "2. Coloring\n";
    cout << "3. Manicure\n";
    cout << "4.Cosmetic procedure\n";
    cout << "Enter a type of services :  ";
    cin >> choice;

    string name;
    double price;
    cout << "Enter a name of service : ";
    cin.ignore();
    cin >> name;
    cout << "Enter price of service :  ";
    cin >> price;

    switch (choice) {
    case 1:
        salon.addService(new Haircut(name, price));
        break;
    case 2:
        salon.addService(new Coloring(name, price));
        break;
    case 3: {
        string additional;
        cout << "Enter a add services :  ";
        cin.ignore();
        cin >> additional;
        salon.addService(new Manicure(name, price, additional));
        break;
    }
    case 4: {
        int duration;
        cout << "Enter a duration of procedure ";
        cin >> duration;
        salon.addService(new CosmeticProcedure(name, price, duration));
        break;
    }
    default:
        cout << "Not good choice \n";
    }
}

int main() {
    Salon salon;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addServiceMenu(salon);
            break;
        case 2: {
            string name;
            cout << "Enter a num of procedure :  ";
            cin.ignore();
            cin >> name;
            salon.removeService(name);
            break;
        }
        case 3:
            salon.displayServices();
            break;
        
        case 4:
            cout << "Exit  \n";
            break;
        default:
            cout << "Not good choice .\n";
        }
    } while (choice != 4);
}
