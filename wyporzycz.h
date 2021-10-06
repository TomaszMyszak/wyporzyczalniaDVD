#ifndef WYPORZYCZ_H_INCLUDED
#define WYPORZYCZ_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <limits>
#include <windows.h>
#include <winbase.h>
#include "time.h"
#include "customer.h"

using namespace std;


class rental {
public:
    rental() {}
    rental(const unsigned& klientID, const string& tilte, string& dataOUT, string& dataIN, string& realData)
        : klientID(klientID), tilte(tilte), dataOUT(dataOUT), dataIN(dataIN), realData(realData) {}

    friend ostream& operator<<(ostream& os, const rental& pr) {
        os << "Numer Klienta = '" << pr.klientID << "'\tTytul= '" << pr.tilte << "\tdata wypozyczenia: " << pr.dataOUT << "'\tdata oddania = '" << pr.dataIN << "'\topis = '" << pr.realData << '\'';
        return os;
    }

    void veryfi(unsigned klientID)
    {


    }


  void getFilm() {
        ifstream file("wyporzycz.csv", ios::in);
        string line;
        ostringstream sout;
        int count = 0;
        int IDC;
        cout << "Podaj nr klienta do wyszukania:";
        cin >> IDC;
        for (int row = 1; getline(file, line); ++row)
        {
            if (line.size() <= 0) continue;
            istringstream sin(line);
            int id;
            sin >> id;
            if (id == IDC)
            {
                sout << row << ' ';
                ++count;
            }
        }
        if (count >= 3)
        {
            cout << "klient wyporzyczyl " << count << "razy, pozycje w bazie nr: " << sout.str() << endl;
            file.close();
        }
        else {
        cout << "id 1 znaleziono " << count << " razy w pozycjach: " << sout.str() << endl;
        cout << "mozesz wyporzyczyc klientowi film" << endl;
        fstream plik;
        plik.open("wyporzycz.csv", ios::out | ios::app);
        cout << "Wpisz kolejno:\n " << "Numer Klienta: ";
        cin >> klientID;
        if (!(cin.good() && klientID > 0))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Jeszcze raz: ";
            cin >> klientID;
        }

        cout << "Tytul filmu: ";
        cin >> tilte;

        SYSTEMTIME st;
        GetSystemTime(&st);
        cout << "wypozycza dzis: ";
        Date *dt = new Date();
        dt-> date();
        cout << " ;Oddaje: ";
        Date *t = new Date();
        t->date2();

        cout << "Opis [opisz krotko transakcje: ";
        cin >> realData;

        plik << klientID << "," << tilte << "," << dt << "," << t << "," <<realData << endl;

        }

   }


private:
    unsigned klientID;           //nr klienta
    string tilte;                //tytu³
    string dataOUT;            //czas trwania
    string dataIN;             //czas oddania obliczany
    string realData;             //krótki opis
};

class rentalBuilder {
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
        auto rentalData = readCSVFile(fileName);
        if (rentalData.size() % 5) {
            throw runtime_error("Blad danych...");
        }
        vector<rental> rental;
        for (auto i = 0U; i < rentalData.size(); i += 5) {
            auto klientID = rentalData[i];
            auto tilte = rentalData[i + 1];
            auto dataOUT = rentalData[i + 2];
            auto dataIN = rentalData[i + 3];
            auto realData = rentalData[i + 4];
            auto klientID_num = strtoul(klientID.c_str(), nullptr, 10);
            rental.emplace_back(klientID_num, tilte, dataOUT, dataIN, realData);
        }

        return rental;
    }


    static auto size(const string& fileName) {
        auto rentalData = readCSVFile(fileName);
        if (rentalData.size() % 5) {
            throw runtime_error("Blad danych...");
        }
        vector<rental> rental;

        return rentalData.size() / 5;
    }





};

#endif // WYPORZYCZ_H_INCLUDED
