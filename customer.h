#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>


using namespace std;

class customer {
public:
    customer() {}
    customer(const string& name_, const string& surname_, string& city, unsigned ID_)
        : surname{ surname_ }, name{ name_ }, city{ city }, ID{ ID_ } {}

    friend ostream& operator<<(ostream& os, const customer& pr) {
        os << "Nazwisko = '" << pr.surname << "'\tImie = '" << pr.name << "'\tMiasto: " << pr.city << "'\tID = '" << pr.ID << '\'';
        return os;
    }


    void addcustomer() {
        cout << "Dodaj klienta do bazy...." << endl;
        fstream plik;
        plik.open("customer.csv", ios::out | ios::app);;
        cout << "======================================================================================================" << endl;
        cout << "Podaj dane: (imie,nazwisko,miasto,nr) [ENTER - zatwierdza zapis]" << endl;
        cin >> name;
        cin >> surname;
        cin >> city;
        cin >> ID;
        cout << "======================================================================================================" << endl;

        plik << name << "," << surname << "," << city << "," << ID << endl;

        if (!plik)
        {
            cout << "BLAD: nie mozna otworzyc pliku." << endl;
        }
    }


    void searchCustomer() {

        ifstream plik("customer.csv");
        string tekst;
        string szukana;
        cout << "Podaj Imie i Nazwisko: ";
        cin >> szukana;
        while (!plik.eof())
        {
            getline(plik, tekst);
            if (!(string::npos == tekst.find(szukana))) {
                cout << "ZNALEZIONO TAKIEGO KLIENTA";
                break;
            }
            else {
                cout << "Mozesz go dodac do bazy, nie ma takiego klienta" << endl;
                addcustomer();
                plik.close();
            }
            addcustomer();
        };


    }

private:
    string name;
    string surname;
    string city;
    unsigned ID;
};

class customerBuilder {
private:
    static auto readCSVFile(const string& fileName) {
        vector<string> values;
        ifstream file(fileName);

        if (!file) {
            throw runtime_error("Niestey baza sie nie wczytala... ");
        }

        string lineInFile;
        string field;

        while (file) {
            getline(file, lineInFile);
            istringstream ss(lineInFile);
            while (getline(ss, field, ',')) {
                values.emplace_back(field);
            }
        }

        return values;
    }
public:
    static auto buildFromCSVFile(const string& fileName) {
        auto customerData = readCSVFile(fileName);
        if (customerData.size() % 4) {
            throw runtime_error("Blad danych...");
        }
        vector<customer> customer;
        for (auto i = 0U; i < customerData.size(); i += 4) {
            auto surname = customerData[i];
            auto name = customerData[i + 1];
            auto city = customerData[i + 2];
            auto age = customerData[i + 3];
            auto ID_num = strtoul(age.c_str(), nullptr, 10);
            customer.emplace_back(name, surname, city, ID_num);
        }

        return customer;
    }

    static auto size(const string& fileName) {
        auto customerData = readCSVFile(fileName);
        if (customerData.size() % 4) {
            throw runtime_error("Blad danych...");
        }
        vector<customer> customer;

        return customerData.size() / 4;
    }







};

#endif // CUSTOMER_H_INCLUDED
