#include <iostream>
#include <cstring>

class MyString {
private:
    char* str;
    int size;
    static int count;

public:
    MyString() : str(new char[80]), size(80) {
        count++;
    }

    MyString(int length) : str(new char[length]), size(length) {
        count++;
    }

    MyString(const char* s) : str(new char[strlen(s) + 1]), size(strlen(s)) {
        strcpy(str, s);
        count++;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            str = new char[size + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    void inputString() {
        std::cout << "Enter a string: ";
        std::cin.getline(str, size);
    }

    void displayString() const {
        std::cout << "String: " << str << std::endl;
    }

    MyString operator++(int) {
        MyString temp(*this);
        char* newStr = new char[size + 2];
        strcpy(newStr, str);
        newStr[size] = 'x';
        newStr[size + 1] = '\0';
        delete[] str;
        str = newStr;
        return temp;
    }

    MyString operator--(int) {
        MyString temp(*this);
        if (size > 0) {
            char* newStr = new char[size];
            strncpy(newStr, str, size - 1);
            newStr[size - 1] = '\0';
            delete[] str;
            str = newStr;
            size--;
        }
        return temp;
    }

    friend MyString operator+(int n, const MyString& myStr) {
        MyString result(n + myStr.size);
        for (int i = 0; i < n; ++i) {
            result.str[i] = 'x';
        }
        strcpy(result.str + n, myStr.str);
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& myStr) {
        os << myStr.str;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, MyString& myStr) {
        is.getline(myStr.str, myStr.size);
        return is;
    }

    ~MyString() {
        delete[] str;
        count--;
    }

    static int getCount() {
        return count;
    }
};

int MyString::count = 0;

int main() {
    MyString defaultString("Hello");
    defaultString.displayString();

    MyString sum = 4 + defaultString;
    std::cout << sum << std::endl;

    MyString userInput;
    std::cout << "Enter a string: ";
    std::cin >> userInput;
    std::cout << "You entered: " << userInput << std::endl;

    std::cout << "Number of MyString objects created: " << MyString::getCount() << std::endl;

    return 0;
}
