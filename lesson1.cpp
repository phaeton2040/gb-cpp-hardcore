#include <iostream>
#include <fstream>
#include <tuple>
#include "lesson1-src/PhoneBook.h"
#include "string"

using namespace std;

int main() {
    ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt PhoneBook book(file);

    PhoneBook book(file);

    cout << book;
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;
    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;
    cout << "-----GetPhoneNumber-----" << endl;

    // лямбда функция, которая принимает фамилию и выводит номер телефона
    // человека, либо строку с ошибкой

    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer).value();
        else
            cout << get<0>(answer);
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
                           PhoneNumber{7, 123, "15344458", nullopt});
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                           PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
}
