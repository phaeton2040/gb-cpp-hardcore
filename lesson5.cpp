#include <regex>
#include "vector"
#include "set"
#include "string"
#include "iostream"

using namespace std;

// Задание 1
template<class Iterator>
void PrintUniqueWords(Iterator start, Iterator end) {
    set<string> setOfStrings(start, end);

    for (auto &el : setOfStrings) {
        cout << el << ", ";
    }

    cout << endl;
}

// Задание 2
void Ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void Rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Trim(std::string &s) {
    Ltrim(s);
    Rtrim(s);
}

void ClearSpaces(string &s) {
    auto it = adjacent_find(s.begin(), s.end());

    while (it != s.end()) {
        if (*it != ' ') {
            it += 1;
            continue;
        }

        s.erase(it, it + 1);
        it = adjacent_find(it, s.end());
    }
}

unsigned int CountWordsInString(string const& str)
{
    stringstream stream(str);
    return distance(istream_iterator<string>(stream), istream_iterator<string>());
}

// Алгоритм не обрабатывает случаи, когда у нас есть знаки .?! в середине предложения,
// Например предложение "Для разделения текста на предложения используются знак препинания '.', также может использоваться восклицательный знак '!'."
// не будет корректно обработано
multimap<unsigned int, string> Split(string text, const regex& basicRegex)
{
    vector<string> splits;
    multimap<unsigned int, string> splitsMap;
    smatch match;

    while (regex_search(text, match, basicRegex))
    {
        int splitOn = match.position();
        auto sentence = text.substr(0, splitOn);

        Trim(sentence);
        ClearSpaces(sentence);

        if (!sentence.empty()) {
            splits.push_back(sentence);
            auto wordCount = CountWordsInString(sentence);

            splitsMap.insert({wordCount, sentence});
        }

        text = text.substr(splitOn + match.length());
    }

    if(!text.empty()) {
        Trim(text);
        splits.push_back(text);
    }

    return splitsMap;
}

void PrintTextStats() {
    string text;

    cout << "Enter some text: ";
    getline(cin, text);

    auto sentences = Split(text, regex("[.!?\\...]"));

    for_each(sentences.begin(), sentences.end(),
             [](const pair<int, string>& item) {
                 cout << item.first << ": " << item.second << endl;
     });
}

int main() {

    // Задание 1
    vector<string> vs{
        "hello", "world", "to", " the", "to", "world", "foo",
        "world", "hello", "the", "if", "else", "for", "while",
        "if", "while"
    };

    PrintUniqueWords(vs.begin(), vs.end());

    // Задание 2
    // The function 'erase()' erases a part of the string content, shortening     the length of the string.The second parameter        in the erase function is the count, it means how many characters you want it to remove! If you want 'ca' as expected output you                                      should mention 2 as count of characters to be removed... In the first case it becomes 2 so bb is removed but for 'aa' the count becomes as 1 so 'aca' is the output.
    PrintTextStats();
    /*
     * Output:
        16: The function 'erase()' erases a part of the string content, shortening the length of the string
        18: If you want 'ca' as expected output you should mention 2 as count of characters to be removed
        20: The second parameter in the erase function is the count, it means how many characters you want it to remove
        22: In the first case it becomes 2 so bb is removed but for 'aa' the count becomes as 1 so 'aca' is the output
     */
}