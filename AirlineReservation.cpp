#include "AirlineReservation.h"

Passenger::Passenger(const string& name) : name(name), next(nullptr) {}

Flight::Flight(const string& flightName) : flightName(flightName), passengerHead(nullptr), next(nullptr) {}

AirlineReservationSystem::AirlineReservationSystem() : flightHead(nullptr) {}

void Flight::addPassenger(const string& name) {
    Passenger* newPassenger = new Passenger(name);
    if (!passengerHead || passengerHead->name > name) {
        newPassenger->next = passengerHead;
        passengerHead = newPassenger;
        return;
    }

    Passenger* current = passengerHead;
    while (current->next && current->next->name < name) {
        current = current->next;
    }
    newPassenger->next = current->next;
    current->next = newPassenger;
}

bool Flight::removePassenger(const string& name) {
    if (!passengerHead) return false;

    if (passengerHead->name == name) {
        Passenger* temp = passengerHead;
        passengerHead = passengerHead->next;
        delete temp;
        return true;
    }

    Passenger* current = passengerHead;
    while (current->next && current->next->name != name) {
        current = current->next;
    }

    if (!current->next) return false;

    Passenger* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

bool Flight::isPassengerPresent(const string& name) {
    Passenger* current = passengerHead;
    while (current) {
        if (current->name == name) return true;
        current = current->next;
    }
    return false;
}

void Flight::displayPassengers() {
    Passenger* current = passengerHead;
    if (!current) {
        cout << "No passengers in this flight.\n";
        return;
    }
    while (current) {
        cout << current->name << "\n";
        current = current->next;
    }
}

void AirlineReservationSystem::addFlight(const string& flightName) {
    Flight* newFlight = new Flight(flightName);
    if (!flightHead || flightHead->flightName > flightName) {
        newFlight->next = flightHead;
        flightHead = newFlight;
        return;
    }

    Flight* current = flightHead;
    while (current->next && current->next->flightName < flightName) {
        current = current->next;
    }
    newFlight->next = current->next;
    current->next = newFlight;
}

void AirlineReservationSystem::removeFlight(const string& flightName) {
    if (!flightHead) return;

    if (flightHead->flightName == flightName) {
        Flight* temp = flightHead;
        flightHead = flightHead->next;
        delete temp;
        return;
    }

    Flight* current = flightHead;
    while (current->next && current->next->flightName != flightName) {
        current = current->next;
    }

    if (!current->next) return;

    Flight* temp = current->next;
    current->next = current->next->next;
    delete temp;
}

Flight* AirlineReservationSystem::findFlight(const string& flightName) {
    Flight* current = flightHead;
    while (current) {
        if (current->flightName == flightName) return current;
        current = current->next;
    }
    return nullptr;
}

void AirlineReservationSystem::reserveTicket(const string& flightName, const string& passengerName) {
    Flight* flight = findFlight(flightName);
    if (!flight) {
        cout << "Flight not found!\n";
        return;
    }
    flight->addPassenger(passengerName);
    cout << "Ticket reserved for " << passengerName << " flight: " << flightName << ".\n";
}

void AirlineReservationSystem::cancelTicket(const string& flightName, const string& passengerName) {
    Flight* flight = findFlight(flightName);
    if (!flight) {
        cout << "Flight not found!\n";
        return;
    }
    if (flight->removePassenger(passengerName)) {
        cout << "Ticket canceled for " << passengerName << " flight:" << flightName << ".\n";
    } else {
        cout << "Passenger not found!\n";
    }
}

void AirlineReservationSystem::checkReservation(const string& flightName, const string& passengerName) {
    Flight* flight = findFlight(flightName);
    if (!flight) {
        cout << "Flight not found!\n";
        return;
    }
    if (flight->isPassengerPresent(passengerName)) {
        cout << passengerName << " has a reservation on flight " << flightName << ".\n";
    } else {
        cout << passengerName << " does not have a reservation on flight " << flightName << ".\n";
    }
}

void AirlineReservationSystem::displayPassengers(const string& flightName) {
    Flight* flight = findFlight(flightName);
    if (!flight) {
        cout << "Flight not found!\n";
        return;
    }
    cout << "Passengers on flight " << flightName << ":\n";
    flight->displayPassengers();
}

void AirlineReservationSystem::menu() {
    while (true) {
        cout << "\nAirline Reservation System Menu:\n";
        cout << "1. Reserve a Ticket\n";
        cout << "2. Cancel a Reservation\n";
        cout << "3. Check Reservation\n";
        cout << "4. Display Passengers\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 5) break;

        string flightName, passengerName;
        switch (choice) {
            case 1:
                cout << "Enter flight name: ";
                getline(cin, flightName);
                cout << "Enter passenger name: ";
                getline(cin, passengerName);
                reserveTicket(flightName, passengerName);
                break;
            case 2:
                cout << "Enter flight name: ";
                getline(cin, flightName);
                cout << "Enter passenger name: ";
                getline(cin, passengerName);
                cancelTicket(flightName, passengerName);
                break;
            case 3:
                cout << "Enter flight name: ";
                getline(cin, flightName);
                cout << "Enter passenger name: ";
                getline(cin, passengerName);
                checkReservation(flightName, passengerName);
                break;
            case 4:
                cout << "Enter flight name: ";
                getline(cin, flightName);
                displayPassengers(flightName);
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
