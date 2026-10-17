
#include <iostream>
using namespace std;


class Vehicle {
protected:
    int vehicleID;
    string manufacturer, model;
    int year;

public:
    static int totalVehicles;

    Vehicle() {
        vehicleID = 0;
        manufacturer = "";
        model = "";
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, string m, string mo, int y) {
        vehicleID = id;
        manufacturer = m;
        model = mo;
        year = y;
        totalVehicles++;
    }

    virtual void display() {
        cout << "\nVehicle ID: " << vehicleID;
        cout << "\nManufacturer: " << manufacturer;
        cout << "\nModel: " << model;
        cout << "\nYear: " << year << endl;
    }

    int getID() {
        return vehicleID;
    }

    void setModel(string m) {
        model = m;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    string fuelType;

public:
    Car(int id, string m, string mo, int y, string f)
        : Vehicle(id, m, mo, y) {
        fuelType = f;
    }

    void display() override {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar(int id, string m, string mo, int y,
                string f, int b)
        : Car(id, m, mo, y, f) {
        batteryCapacity = b;
    }

    void display() override {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity
             << " kWh" << endl;
    }
};

class SportsCar : public ElectricCar {
    int topSpeed;

public:
    SportsCar(int id, string m, string mo, int y,
              string f, int b, int s)
        : ElectricCar(id, m, mo, y, f, b) {
        topSpeed = s;
    }

    void display() override {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car {
public:
    Sedan(int id, string m, string mo, int y, string f)
        : Car(id, m, mo, y, f) {}

    void display() override {
        cout << "\nSedan Details:";
        Car::display();
    }
};

class SUV : public Car {
public:
    SUV(int id, string m, string mo, int y, string f)
        : Car(id, m, mo, y, f) {}

    void display() override {
        cout << "\nSUV Details:";
        Car::display();
    }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft(int r) {
        flightRange = r;
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int id, string m, string mo, int y,
              string f, int r)
        : Car(id, m, mo, y, f), Aircraft(r) {}

    void display() override {
        Car::display();
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

int main() {
    Vehicle *v[50];
    int count = 0, choice, id, year;
    string manufacturer, model, fuel;
    int battery, speed, range;

    do {
        cout << "\n--- Vehicle Registry ---";
        cout << "\n1. Add Car";
        cout << "\n2. Add Electric Car";
        cout << "\n3. Add Sports Car";
        cout << "\n4. Add Sedan";
        cout << "\n5. Add SUV";
        cout << "\n6. Add Flying Car";
        cout << "\n7. View All Vehicles";
        cout << "\n8. Search by ID";
        cout << "\n9. Total Vehicles";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6) {
            if (count >= 50) {
                cout << "Registry is full!\n";
                continue;
            }

            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter manufacturer: ";
            cin >> manufacturer;
            cout << "Enter model: ";
            cin >> model;
            cout << "Enter year: ";
            cin >> year;

            if (choice == 1) {
                cout << "Enter fuel type: ";
                cin >> fuel;
                v[count] = new Car(id, manufacturer, model, year, fuel);
            }
            else if (choice == 2) {
                cout << "Enter fuel type: ";
                cin >> fuel;
                cout << "Enter battery capacity: ";
                cin >> battery;
                v[count] = new ElectricCar(id, manufacturer, model,
                                           year, fuel, battery);
            }
            else if (choice == 3) {
                cout << "Enter fuel type: ";
                cin >> fuel;
                cout << "Enter battery capacity: ";
                cin >> battery;
                cout << "Enter top speed: ";
                cin >> speed;
                v[count] = new SportsCar(id, manufacturer, model,
                                         year, fuel, battery, speed);
            }
            else if (choice == 4) {
                cout << "Enter fuel type: ";
                cin >> fuel;
                v[count] = new Sedan(id, manufacturer, model, year, fuel);
            }
            else if (choice == 5) {
                cout << "Enter fuel type: ";
                cin >> fuel;
                v[count] = new SUV(id, manufacturer, model, year, fuel);
            }
            else {
                cout << "Enter fuel type: ";
                cin >> fuel;
                cout << "Enter flight range: ";
                cin >> range;
                v[count] = new FlyingCar(id, manufacturer, model,
                                         year, fuel, range);
            }

            count++;
            cout << "Vehicle added successfully!\n";
        }
        else if (choice == 7) {
            if (count == 0)
                cout << "No vehicles found.\n";

            for (int i = 0; i < count; i++)
                v[i]->display();
        }
        else if (choice == 8) {
            cout << "Enter ID to search: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < count; i++) {
                if (v[i]->getID() == id) {
                    v[i]->display();
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Vehicle not found.\n";
        }
        else if (choice == 9) {
            cout << "Total Vehicles: " << count << endl;
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    for (int i = 0; i < count; i++)
        delete v[i];

    cout << "Program ended.\n";
    return 0;
}
