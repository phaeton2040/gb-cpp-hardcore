#include <fstream>
#include "PhoneBook.h"
#include "tuple"
#include "iostream"
#include <sstream>
#include <algorithm>

bool operator<(const PhoneNumber &p1, const PhoneNumber &p2) {
    return tie(p1.CountryCode, p1.CityCode, p1.Number) < tie(p2.CountryCode, p2.CityCode, p2.Number);
}

bool operator==(const PhoneNumber &p1, const PhoneNumber &p2) {
    return tie(p1.CountryCode, p1.CityCode, p1.Number) == tie(p2.CountryCode, p2.CityCode, p2.Number);
}

ostream &operator<<(ostream &out, const PhoneNumber &p) {
    out << "+" << p.CountryCode << " (" << p.CityCode << ") " << p.Number;

    if (p.AdditionalNumber.has_value()) {
        out << " " << p.AdditionalNumber.value();
    }

    return out;
}

bool operator<(const Person &p1, const Person &p2) {
    return tie(p1.LastName, p1.FirstName, p1.MiddleName) < tie(p2.LastName, p2.FirstName, p2.MiddleName);
}

bool operator==(const Person &p1, const Person &p2) {
    return tie(p1.LastName, p1.FirstName, p1.MiddleName) == tie(p2.LastName, p2.FirstName, p2.MiddleName);
}

ostream &operator<<(ostream &out, const Person &p) {
    out << p.LastName << " " << p.FirstName;

    if (p.MiddleName.has_value()) {
        out << " " << p.MiddleName.value();
    }

    return out;
}

tuple<string, optional<PhoneNumber>> PhoneBook::GetPhoneNumber(const string& lastName) {
    int resultCount = 0;
    tuple<string, optional<PhoneNumber>> result;

    for (auto& c : contacts) {
        if (c.first.LastName == lastName) {
            result = make_tuple("", c.second);
            resultCount++;
        }
    }

    if (resultCount > 1) {
        return tie("found more than 1", nullopt);
    } else if (resultCount == 1) {
        return result;
    }

    return tie("not found", nullopt);
}

enum INDEX {
    LNAME,
    FNAME,
    MNAME,
    COUNTRY_CODE,
    CITY_CODE,
    NUMBER,
    ADDITIONAL_NUMBER
};

PhoneBook::PhoneBook(ifstream& file) {
    if (!file.is_open()) throw invalid_argument("File not found!");

    string line;
    stringstream stream;

    while (getline(file, line)) {
        stream << line;
        Person person;
        PhoneNumber number;
        string word;
        int index = 0;

        while (getline(stream, word, ' ')) {
            switch (index) {
                case LNAME:
                    person.LastName = word;
                    break;
                case FNAME:
                    person.FirstName = word;
                    break;
                case MNAME:
                    word.empty() ? person.MiddleName = nullopt : person.MiddleName = word;
                    break;
                case COUNTRY_CODE:
                    number.CountryCode = stoi(word);
                    break;
                case CITY_CODE:
                    number.CityCode = stoi(word);
                    break;
                case NUMBER:
                    number.Number = word;
                    break;
                case ADDITIONAL_NUMBER:
                    word.empty() ? number.AdditionalNumber = nullopt : number.AdditionalNumber = stoi(word);
                    break;
            }
            index++;
        }

        contacts.emplace_back( person, number );
        stream.clear();
    }

    file.close();
}

void PhoneBook::SortByName() {
    sort(contacts.begin(), contacts.end(), [](const pair<Person, PhoneNumber>& c1, const pair<Person, PhoneNumber>& c2) -> bool {
        return c1.first < c2.first;
    });
}

void PhoneBook::SortByPhone() {
    sort(contacts.begin(), contacts.end(), [](const pair<Person, PhoneNumber>& c1, const pair<Person, PhoneNumber>& c2) -> bool {
        return c1.second < c2.second;
    });
}

ostream &operator<<(ostream &out, const PhoneBook& phoneBook) {
    for (auto& c : phoneBook.contacts) {
        cout << c.first << " : " << c.second << endl;
    }

    cout << endl;

    return out;
}

void PhoneBook::ChangePhoneNumber(Person person, PhoneNumber phoneNumber) {
    for (auto& c : contacts) {
        if (c.first == person) {
            c.second = phoneNumber;
        }
    }
}
