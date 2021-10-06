#ifndef FILM_H_INCLUDED
#define FILM_H_INCLUDED


#pragma once
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

class film {
public:
    film() {}
    film(const string& tilte, const string& director, string& time, string& rating, string& description, string& actors, string& dateAdd, unsigned id_)
        : tilte( tilte ), director( director ), time(time), description( description ), actors( actors ), dateAdd( dateAdd ),  id( id_ ) {}

    friend ostream& operator<<(ostream& os, const film& pr) {
        os << "tytul = '" << pr.tilte << "'\trezyser = '" << pr.director << "\tczas trwania: " << pr.time << "'\tocena = '" << pr.rating << "'\topis = '"  << pr.description << "'\taktorzy = '" << pr.actors << "'\tdata dodania = '"  << pr.dateAdd << "'\tnumer filmu = '" << pr.id << '\'';
        return os;
    }

    void addFilm() {
        cout << "Dodaj klienta do bazy...." << endl;
        string const nazwaPliku("customer.csv");
        ofstream mojStrumien(nazwaPliku.c_str(), ios::app);

        cout << "Podaj dane: [ENTER - zatwierdza zapis]" << endl;
        cout << "Tytul: ";
        cin >> tilte;
        cout << "Rezyser: ";
        cin >> director;
        cout << "Czas trwania [min]: ";
        cin >> time;
        cout << "Punktacja: ";
        cin >> rating;
        cout << "Opis [ spacja - _ ]: ";
        cin >> description;
        cout << "Aktorzy [ spacja - _, rozdzielone ; ]:";
        cin >> actors;
        cout << "Data zakupu: ";
        cin >> dateAdd;
        cout << "Numer filmu: ";
        cin >> id;


        if (mojStrumien)
        {
            mojStrumien << tilte << "," << director << "," << time << "min," << rating << "," << description << "," << actors << "," << dateAdd << "," << id << endl;
        }
        else
        {
            cout << "B£¥D: nie mo¿na otworzyæ pliku." << endl;
        }
    }




private:
    string tilte;           //tytu³ filmu
    string director;        //re¿yser
    string time;            //czas trwania
    string rating;          //ocena 1-10
    string description;     //krótki opis filmu
    string actors;          //aktorzy
    string dateAdd;         //data dodania do kolekcji
    unsigned id;            //numer kolejny
};

class filmBuilder {
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
        auto filmData = readCSVFile(fileName);
        if (filmData.size() % 8) {
            throw runtime_error("Blad danych...");
        }
        vector<film> film;
        for (auto i = 0U; i < filmData.size(); i += 8) {
            auto tilte = filmData[i];
            auto director = filmData[i + 1];
            auto time = filmData[i + 2];
            auto rating = filmData[i + 3];
            auto description = filmData[i + 4];
            auto actors = filmData[i + 5];
            auto dateAdd = filmData[i + 6];
            auto id = filmData[i + 7];
            auto id_num = strtoul(id.c_str(), nullptr, 10);
            film.emplace_back(tilte, director, time, rating, description, actors, dateAdd, id_num);
        }

        return film;
    }













};
#endif // FILM_H_INCLUDED
