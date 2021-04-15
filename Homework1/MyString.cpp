#include <iostream>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include "MyString.h"

void MyString::copy(const MyString& other) {
    char* tempStr = new char[other.len + 1];
    strcpy_s(tempStr, other.len + 1, other.str);

    delete[] str;
    str = tempStr;
    len = other.len;
}
void MyString::destroy() {
    delete[] str;
    len = 0;
}

MyString::MyString() {
    str = new char[1];
    len = 0;
    str[0] = '\0';
}
MyString::MyString(const MyString& other) {
    copy(other);
}
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}
MyString::~MyString() {
    destroy();
}

MyString::MyString(const char* initString) {
    if (initString == nullptr) {
        str = new char[1];
        len = 0;
        str[0] = '\0';
    }
    else {
        std::size_t newLen = std::strlen(initString);

        char* tempStr = new char[newLen + 1];
        strcpy_s(tempStr, newLen + 1, initString);

        str = tempStr;
        len = newLen;
    }
}

bool MyString::operator==(const MyString& rhs) const {
    if (len == rhs.len && std::strcmp(str, rhs.str) == 0) {
        return true;
    }
    return false;
}
bool MyString::operator!=(const MyString& rhs) const {
    return !operator==(rhs);
}

char& MyString::at(std::size_t pos) {
    if (pos >= len || pos < 0) {
        throw std::out_of_range("pos out of range");
    }

    return str[pos];
}
const char& MyString::at(std::size_t pos) const {
    if (pos >= len || pos < 0) {
        throw std::out_of_range("pos out of range");
    }

    return str[pos];
}
char& MyString::operator[](std::size_t pos) {
    assert(pos >= 0 && pos < len);
    return str[pos];
}
const char& MyString::operator[](std::size_t pos) const {
    assert(pos >= 0 && pos < len);
    return str[pos];
}

char& MyString::front() {
    assert(len > 0);
    return str[0];
}
const char& MyString::front() const {
    assert(len > 0);
    return str[0];
}

char& MyString::back() {
    assert(len > 0);
    return str[len - 1];
}
const char& MyString::back() const {
    assert(len > 0);
    return str[len - 1];
}

void MyString::push_back(char c) {
    if (c != '\0') {
        std::size_t newLen = len + 1;
        char* newString = new char[newLen + 1];
        for (std::size_t i = 0; i < len; i++) {
            newString[i] = str[i];
        }
        newString[newLen - 1] = c;
        newString[newLen] = '\0';
        
        delete[] str;
        str = newString;
        len = newLen;
    }
}
void MyString::pop_back() {
    assert(len > 0);

    str[len - 1] = '\0';
    --len;
}

MyString& MyString::operator+=(char c) {
    this->push_back(c);
    return *this;
}
MyString& MyString::operator+=(const MyString& rhs) {
    if (rhs.empty()) {
        return *this;
    }
    if (this->empty()) {
        copy(rhs);
        return *this;
    }

    std::size_t newLen = len + rhs.len;
    char* concatString = new char[newLen + 1];
    for (std::size_t i = 0; i < len; i++) {
        concatString[i] = str[i];
    }
    for (std::size_t j = len; j < newLen; j++) {
        concatString[j] = rhs[j - len];
    }
    concatString[newLen] = '\0';

    delete[] str;
    str = concatString;
    len = newLen;
    
    return *this;
}

MyString MyString::operator+(char c) const {
    if (c != '\0') {
        MyString newS = *this;
        newS.push_back(c);
        return newS;
    }
    return *this;
}
MyString MyString::operator+(const MyString& rhs) const {
    MyString newS = *this;
    newS += rhs;
    return newS;
}

const char* MyString::c_str() const {
    return str;
}

bool MyString::operator<(const MyString& rhs) const {
    int thisBeforeOther = std::strcmp(str, rhs.str);
    if (thisBeforeOther < 0) {
        return true;
    }
    return false;
}

void MyString::clear() {
    str[0] = '\0';
    len = 0;
}
std::size_t MyString::size() const {
    return len;
}
bool MyString::empty() const {
    if (str == nullptr || len == 0 ) {
        return true;
    }
    return false;
}
void MyString::print() {
    for (size_t i = 0; i < len; i++) {
        std::cout << str[i];
    }
    std::cout << std::endl;
}

