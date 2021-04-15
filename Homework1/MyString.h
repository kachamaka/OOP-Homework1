#pragma once
#include <cstddef>

class MyString {
    char* str = nullptr;
    std::size_t len = 0;

    void copy(const MyString&);
    void destroy();
public:
    MyString();
    //rule of 3
    MyString(const MyString&);
    MyString& operator=(const MyString&);
    ~MyString();

    MyString(const char*);

    bool operator==(const MyString&) const;
    bool operator!=(const MyString&) const;

    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;

    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;

    char& front();
    const char& front() const;
    char& back();
    const char& back() const;

    void push_back(char c);
    void pop_back();

    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;

    const char* c_str() const;

    bool operator<(const MyString& rhs) const;

    void clear();
    std::size_t size() const;
    bool empty() const;
    void print();
};