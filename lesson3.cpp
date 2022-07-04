#include <iostream>
#include <array>
#include <cmath>
#include "vector"
#include "iterator"

using namespace std;

// Р—Р°РґР°РЅРёРµ 1
template<typename T>
void addMeanToVector(vector<T> &vec) {
    T total = 0;
    for(auto &i : vec) {
        total += i;
    }

    vec.push_back(total / vec.size());
}

// Р—Р°РґР°РЅРёРµ 2
template<int Rows, int Cols>
class Matrix {
private:
    array<array<int, Cols>, Rows> data;
    int _determinant_internal(array<array<int, Cols>, Rows> _data, int size) {
        int det = 0;
        array<array<int, Cols>, Rows> minor{};

        if (size == 2) {
            return ((_data[0][0] * _data[1][1]) - (_data[1][0] * _data[0][1]));
        } else {
            for (int x = 0; x < size; x++) {
                int min_i = 0;

                for (int i = 1; i < size; i++) {
                    int min_j = 0;

                    for (int j = 0; j < size; j++) {
                        if (j == x) {
                            continue;
                        }

                        minor[min_i][min_j] = _data[i][j];
                        min_j++;
                    }
                    min_i++;
                }
                det = det + (pow(-1, x) * _data[0][x] * _determinant_internal(minor, size - 1 ));
            }
        }
        return det;
    }
public:
    Matrix() {}
    Matrix(array<array<int, Cols>, Rows> d) {
        data = d;
    }

    int determinant() {
        if (Cols != Rows) {
            throw invalid_argument("Determinant can be calculated for square matrix only!");
        }

        return _determinant_internal(data, Cols);
    }
};

// Р—Р°РґР°РЅРёРµ 3
class IntRange
{
public:
    IntRange(int start, int end) {
        if (start < end) {
            for(int i = start; i <= end; i++) {
                m_data.push_back(i);
            }
        } else {
            for(int i = start; i >= end; i--) {
                m_data.push_back(i);
            }
        }
    }
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int*;
        using reference         = int&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(&m_data.at(0)); }
    Iterator end()   { return Iterator(&m_data.back()); }

private:
    vector<int> m_data;
};

int main()
{
    // Р—Р°РґР°РЅРёРµ 1
    vector<float> v{1, 2.3f, 3.4f, 5, 4.1f };
    addMeanToVector<float>(v);

    cout << "Mean value is: " << v.back() << endl;
    // 3.16

    // Р—Р°РґР°РЅРёРµ 2
    array<array<int, 3>, 3> data = {{{5, 8, 2}, {8, 3, 1}, {5, 3, 9}}};
    auto *m1 = new Matrix<3, 3>(move(data));

    cout << "Matrix 3x3 determinant: " << m1->determinant() << endl;
    // -398

    array<array<int, 4>, 4> data2 = {{
                                             {2,2,3,4},
                                             {2,3,4,5},
                                             {6,7,12,15},
                                             {10,11,12,13}
                                     }};
    auto *m2 = new Matrix<4, 4>(move(data2));

    cout << "Matrix 4x4 determinant: " << m2->determinant() << endl;
    // -16


    // Р—Р°РґР°РЅРёРµ 3
    IntRange range(20, 50);

    for (auto &i : range) {
        cout << "Iterator value: " << i << endl;
    }
    /*
        Iterator value: 20
        Iterator value: 21
        Iterator value: 22
        Iterator value: 23
        Iterator value: 24
        Iterator value: 25
        Iterator value: 26
        Iterator value: 27
        Iterator value: 28
        Iterator value: 29
        Iterator value: 30
        Iterator value: 31
        Iterator value: 32
        Iterator value: 33
        Iterator value: 34
        Iterator value: 35
        Iterator value: 36
        Iterator value: 37
        Iterator value: 38
        Iterator value: 39
        Iterator value: 40
        Iterator value: 41
        Iterator value: 42
        Iterator value: 43
        Iterator value: 44
        Iterator value: 45
        Iterator value: 46
        Iterator value: 47
        Iterator value: 48
        Iterator value: 49
     */

    cout << "-------------" << endl;

    IntRange range2(20, 10);

    for (auto &i : range2) {
        cout << "Iterator value: " << i << endl;
    }
    /*
        Iterator value: 20
        Iterator value: 19
        Iterator value: 18
        Iterator value: 17
        Iterator value: 16
        Iterator value: 15
        Iterator value: 14
        Iterator value: 13
        Iterator value: 12
        Iterator value: 11
     */

    return 0;
}