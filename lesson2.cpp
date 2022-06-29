#include "iostream"
#include "vector"
#include "algorithm"
#include <fstream>
#include <sstream>
#include "Timer.cpp"

using namespace std;

template<typename T>
void Swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

int CountVowels1() {
    // the actual file is ignored due to its size;
    // the original file is here - https://github.com/mmcky/nyu-econ-370/raw/master/notebooks/data/book-war-and-peace.txt
    ifstream file("book-war-and-peace.txt");

    if (!file.is_open()) throw invalid_argument("File not found!");

    string line;
    stringstream stringstr;
    int count = 0;

    while (getline(file, line)) {
        count += count_if(line.begin(), line.end(), [](auto c) {
            bool isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
            bool isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');

            return isLowercaseVowel || isUppercaseVowel;
        });
    }

    return count;
}

int CountVowels2() {
    // the actual file is ignored due to its size;
    // the original file is here - https://github.com/mmcky/nyu-econ-370/raw/master/notebooks/data/book-war-and-peace.txt
    ifstream file("book-war-and-peace.txt");

    if (!file.is_open()) throw invalid_argument("File not found!");

    string line;
    stringstream stringstr;
    int count = 0;

    while(getline(file, line)) {
        for (char c : line)
        {
            bool isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
            bool isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
            if (isLowercaseVowel || isUppercaseVowel) {
                ++count;
            }
        }
    }

    return count;
}

template<typename T>
void SortPointers(vector<T*> &data) {
    sort(data.begin(), data.end(), [](T* a, T* b) {
        return *a < *b;
    });
}

int main() {
    // Задание 1
    int x = 5, y = 7;

    Swap<int>(&x, &y);
    cout << "x = " << x << ", y = " << y << endl;

    string str1 = "Hello", str2 = "World";

    Swap<string>(&str1, &str2);
    cout << "str1 = " << str1 << ", str2 = " << str2 << endl;

    // Задание 2
    int* a = new int(4);
    int* b = new int(3);
    int* c = new int(7);
    int* d = new int(2);
    int* e = new int(9);
    int* f = new int(1);
    vector<int*> vec = {a, b, c, d, e, f};

    SortPointers<int>(vec);

    for (auto &i : vec) {
        cout << *i;
    }

    cout << endl;

    // Задание 3
    Timer timer("count_if and while loop");
    cout << "Vowels in War and Peace: " << CountVowels1() << endl;
    timer.print();

    cout << endl;

    Timer timer2("2 loops");
    cout << "Vowels in War and Peace: " << CountVowels2() << endl;
    timer2.print();

    cout << endl;

    // Увы, я не придумал, как посчитать символы с помощью std::find :(
}