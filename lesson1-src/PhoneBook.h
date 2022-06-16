//
// Created by User on 16.06.2022.
//

#ifndef CPP_HARDCORE_PHONEBOOK_H
#define CPP_HARDCORE_PHONEBOOK_H

#include <vector>
#include "string"
#include "optional"

using namespace std;

struct Person {
    string LastName;
    string FirstName;
    optional<string> MiddleName;

    friend bool operator<(const Person& p1, const Person& p2);
    friend bool operator==(const Person& p1, const Person& p2);
    friend ostream& operator<<(ostream & out, const Person& p);
};

struct PhoneNumber {
    int CountryCode;
    int CityCode;
    string Number;
    optional<int> AdditionalNumber;

    friend bool operator<(const PhoneNumber& p1, const PhoneNumber& p2);
    friend bool operator==(const PhoneNumber& p1, const PhoneNumber& p2);
    friend ostream& operator<<(ostream& out, const PhoneNumber& p);
};

class PhoneBook {
private:
    vector<pair<Person, PhoneNumber>> contacts;
public:
    explicit PhoneBook(ifstream& file);

    void SortByName();
    void SortByPhone();
    tuple<string, optional<PhoneNumber>> GetPhoneNumber(const string& lastName);
    void ChangePhoneNumber(Person person, PhoneNumber phoneNumber);

    friend ostream& operator<<(ostream& out, const PhoneBook& phoneBook);
};


#endif //CPP_HARDCORE_PHONEBOOK_H
