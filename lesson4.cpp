#include "iostream"
#include "algorithm"
#include "string"
#include "set"
#include "numeric"

#define FLOAT_GEN_MAX 200

using namespace std;

template<template<typename ... > class Container, typename Value>
void PrintContainer(const Container<Value> &data) {
    for (auto &el : data) {
        cout << el << ", ";
    }

    cout << endl;
}

// Задание 1
// Данная функция должна работать со всеми последовательными контейнерами (но это не точно)
template<template<typename ... > class Container, typename Value>
void InsertSorted(Container<Value> &data, const Value &value, bool reverseSorted = false)
{
    if (!reverseSorted) {
        data.insert(lower_bound(data.begin(), data.end(), value), value);
    } else {
        data.insert(lower_bound(data.rbegin(), data.rend(), value).base(), value);
    }
}

int main() {
    // Задание 1
    vector<int> v1 = {1,2,4,5};
    InsertSorted(v1, 3);
    PrintContainer(v1);

    set<string> s1 = {"ab", "fg", "we", "za"};
    InsertSorted(s1, string("cd"));
    PrintContainer(s1);

    // Задание 2
    vector<float> vec_f(10);

    generate(vec_f.begin(), vec_f.end(), []() {
        return static_cast <float> (rand()) / static_cast <float> (RAND_MAX/FLOAT_GEN_MAX);
    });

    PrintContainer(vec_f);

    vector<int> vec_i;

    copy(vec_f.begin(), vec_f.end(), back_insert_iterator<vector<int>>(vec_i));
    PrintContainer(vec_i);

    float mse = inner_product(vec_f.begin(), vec_f.end(), vec_i.begin(), 0.f, plus<>(), [](float x, int y) {
        auto err = x - y;

        return err * err;
    });

    cout << mse << endl;

    // Проверяем
    float mse2 = 0;
    for (int i = 0; i < vec_f.size(); i++) {
        auto err = vec_f.at(i) - vec_i.at(i);

        mse2 += err * err;
    }

    cout << mse2 << endl;
}