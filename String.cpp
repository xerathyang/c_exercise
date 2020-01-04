#include <iostream>

using namespace std;

class String {
public:
    String();
    String(const char* init);
    ~String();
    friend istream& operator>>(istream& is, String& string);
    friend ostream& operator<<(ostream& os, String& string);
    friend bool operator==(const String& ls, const String& rs);
    int Length() {
        return this->length;
    }
    int find(const String& str);
    ostream& freq(ostream& os);
    void del(const int& start, const int& length);
    void chardel(const char& c);

private:
    char* str;
    int length;
};

String::String() {
    str = nullptr;
    length = 0;
}

String::String(const char* init) {
    for (this->length = 0; init[this->length] != '\0'; this->length++);
    this->str = new char[this->length];
    for (int i = 0; i < this->length; i++) {
        this->str[i] = init[i];
    }
}

String::~String() {
    if (this->str != nullptr) {
        delete[] this->str;
        this->str = nullptr;
        this->length = 0;
    }
}

istream& operator>>(istream& is, String& string) {
    char input[255];
    is >> input;

    int leng = 0;
    for (leng = 0; input[leng] != '\0'; leng++);
    string.~String();
    string.str = new char[leng];
    string.length = leng;
    for (int i = 0; i < leng; i++) {
        string.str[i] = input[i];
    }
    return is;
}

ostream& operator<<(ostream& os, String& string) {
    for (int i = 0; i < string.length; i++) {
        os << string.str[i];
    }
    return os;
}

bool operator==(const String& ls, const String& rs) {
    if (ls.length != rs.length) {
        return false;
    }
    for (int i = 0; i < ls.length; i++) {
        if (ls.str[i] != rs.str[i]) {
            return false;
        }
    }
    return true;
}

int String::find(const String& str) {
    for (int i = 0; i < this->length; i++) {
        bool check = true;
        for (int p = 0; p < str.length; p++) {
            if (i + p >= this->length || this->str[i + p] != str.str[p]) {
                check = false;
                break;
            }
        }
        if (check)
            return i;
    }
    return -1;
}

ostream& String::freq(ostream& os) {
    int ct[26] = { 0 };
    for (int i = 0; i < this->length; i++) {
        ct[str[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (ct[i]) {
            os << (char)(i + 'a') << " " << ct[i] << endl;
        }
    }
    return os;
}

void String::del(const int& start, const int& length) {
    if (this->length - start - length < 0)
        return;
    int j = 0;
    for (int i = 0, l = length; i < this->length; i++) {
        //get start point
        if (i < start) {
            j++;
            continue;
        }
        //get end point
        if (i >= start && l) {
            l--;
            continue;
        }
        this->str[j++] = this->str[i];
    }

    char* dst = new char[j];
    for (int i = 0; i < j; i++) {
        dst[i] = this->str[i];
    }
    delete[] this->str;
    this->str = dst;
    this->length = j;
}

void String::chardel(const char& c) {
    for (int i = this->length; i >= 0; i--) {
        if (this->str[i] == c)
            this->del(i, 1);
    }
}

int main()
{
    String input, cmd;
    String freq("freq"), find("find"), del("del"), chdel("chdel");
    cin >> input;
    while (cin>>cmd) {
        if (cmd == freq)
            input.freq(cout);
        else if (cmd == find) {
            String cache;
            cin >> cache;
            cout << input.find(cache) << endl;
        }
        else if (cmd == del) {
            int start, length;
            cin >> start >> length;
            input.del(start, length);
            cout << input << endl;
        }
        else if (cmd == chdel) {
            char c;
            cin >> c;
            input.chardel(c);
            cout << input << endl;
        }
    }
}
