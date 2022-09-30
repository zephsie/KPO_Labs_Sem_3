#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<string> &v) {
    for (const string &s: v) {
        cout << s + " ";
    }
    cout << endl;
}

vector<vector<string>> task(const string &s) {
    vector<string> words;
    string word;

    for (char c: s) {
        if (c == ' ') {
            words.push_back(word);
            word = "";
        } else {
            word += c;
        }
    }
    words.push_back(word);

    sort(words.begin(), words.end());
    vector<vector<string>> result;

    do {
        result.push_back(words);
    } while (next_permutation(words.begin(), words.end()));

    return result;
}

int main() {
    string s;
    getline(cin, s);

    vector<vector<string>> result = task(s);

    for (const vector<string> &v: result) {
        print(v);
    }

    return 0;
}