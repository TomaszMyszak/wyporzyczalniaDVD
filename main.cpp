// DVD.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <winbase.h>
#include "customer.h"
#include "film.h"
#include "wyporzycz.h"
#include "time.h"



using namespace std;

void searchCustomer();
void addcustomer();
void addfilm();
void getFilm();
void comeBack();
void passwrd();




int main()
{


    cout << "==========================================================================================" << endl;
    cout << " ******************              *******            ********         ******************  " << endl;
    cout << " *****        ******              *******          *******           *****         *****  " << endl;
    cout << " *****        *******              *******        ******             *****         ******  " << endl;
    cout << " *****        *******               *******     ******               *****         ******  " << endl;
    cout << " *****        *******                 *******  ******                *****         ******  " << endl;
    cout << " *****        ******                    ***********                  *****         *****  " << endl;
    cout << " ******************                       *******                    ****************     " << endl;
    cout << "=========================================================================================== " << endl;

    cout << endl << endl;

    cout << "Witamy w programie do rejestracji wypozyczonych filmow. Program wysiwtala aktualn¹ liste klientow, oraz \n";
    cout << "liste filmwo jaka posiadasz. Mozesz dodac nowy film oraz klienta, pod warunkiem posiadania uprawnien admina \n";
    cout << "Program nie jest doskonaly, dodajac do bazy dane nie uzywamh w pozycjach spacji, zamiast tego _ - jest za spacja \n";
    cout << "Mielej pracy.......\n";
    cout << "Aby zakonczyc program nacisnij 0 [zero]";

    cout << endl << endl;

    //utorzenie objektów

    customer* c = new customer();
    film* f = new film();
    rental* w = new rental();
    Date *td = new Date();

    cout << "Przed rozpoczeciem musisz podac haslo" << endl;

    passwrd();

    cout << endl;

    /// Menu ///
    int wybor;
    do {

        cout <<"Dzis jest: ";
        td -> date();
        cout <<  endl;
        cout << "MENU PROGRAMU" << endl;

        cout << "1. Dodaj klienta do bazy" << endl;
        cout << "2. Dodaj film do bazy" << endl;
        cout << "3. Wyporzycz film" << endl;
        cout << "4. Zmien opis filmu" << endl;
        cout << "5. Wysietl liste klientow" << endl;
        cout << "6. Wyswietl liste filmow" << endl;
        cout << "7. Wyswietll liste filmow wyporzycozych" << endl;

        cout << "TWOJ WYBOR: ";

        cin >> wybor;
        cout << endl;





        switch (wybor)
        {
        case 1: {
            cout << "Zanim dodasz klienta sprawdz czy nie ma go w bazie." << endl;
            //searchCustomer();
            c->searchCustomer();
            cout << endl;
            comeBack();
        } break;
        case 2: {
          // addfilm();
            f->addFilm();
            comeBack();
         }break;
        case 3: {
            cout << endl << "LISTA KLIENTOW" << endl;
            auto customer = customerBuilder::buildFromCSVFile("customer.csv");
            for (const auto& customer : customer) {
                cout.width(20);
                cout << customer << '\n';
                cout.width(20);

            }
            cout << endl << endl;
            cout << "======================================================================================================" << endl;
            w->getFilm();
            cout << "======================================================================================================" << endl;
          comeBack();

        }break;

        case 4: {
            cout << "Zmiana opisu filmu:" << endl;
        }break;

        case 5: {
            cout << endl << "LISTA KLIENTOW" << endl;
            auto customer = customerBuilder::buildFromCSVFile("customer.csv");
            for (const auto& customer : customer) {
                cout.width(20);
                cout << customer << '\n';
                cout.width(20);

            }


            cout << endl << "Liczba klietow w bazie: ";
            auto size = customerBuilder::size("customer.csv");
            cout << size;
            cout << endl << endl;
            comeBack();
        }break;

        case 6: {
            cout << endl << "LISTA FILMOW" << endl;
            auto film = filmBuilder::buildFromCSVFile("film.csv");
            for (const auto& film : film) {
                cout.width(5);
                cout << film << '\n';
                cout.width(5);
                cout << endl;
            }
            comeBack();

        }break;
        case 7: {
            cout << endl << "LISTA FILMOW WYPOZYCZONYCH" << endl;
            auto rental = rentalBuilder::buildFromCSVFile("wyporzycz.csv");
            for (const auto& rental : rental) {
                cout.width(5);
                cout << rental << '\n';
                cout.width(5);
                cout << endl;
            }

            cout << endl << "Liczba wypozyczonych filmow: ";
            auto sizer = rentalBuilder::size("wyporzycz.csv");
            cout << sizer;
            cout << endl << endl;
            comeBack();
        }break;

        }
    }while (wybor != 0);

    delete c;
    delete f;
    delete w;
    delete td;

    return 0;
};


void comeBack() {
    char powrot;

    cout << "q: powrot do menu ";

    cin >> powrot;

    if ((powrot == 'q') || (powrot == 'Q'))
    {
        system("CLS");
        main(); //main zamiast menu
    }
    else
        cout << "\nDo widzenia...\n";
}

void passwrd() {
    string password = "";
    string correctPassword = "admin";

    unsigned tries = 3;
    char character = ' ';

    do {
        cout << "Enter password: ";
        while ((character = _getch()) != '\r') {
            cout << "*";
            password += character;
        }

        if (password != correctPassword) {
            password = "";
            tries -= 1;
            cout << "\nTries remaining: " << tries << endl;

        }
    } while (tries > 0 && password != correctPassword);

    if (tries == 0) {
            cout << "\nZostałes zablokowany!\n";

    }
    else cout << "\nPassword correct!\n";


}
