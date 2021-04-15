#include <iostream>
#include <cstring>
#include <new>
#include <stdexcept>

#include "../Homework1/MyString.h"

typedef void(*TestFunction)();

bool hasError = false;

bool runTest(TestFunction pfn, const char* name) {
	std::cout << "Running test \"" << name << "\"... ";

	hasError = false;
	pfn();

	std::cout << (hasError ? " ERROR\n" : " OK\n");

	return hasError;
}

int main()
{

}

#define TEST_CASE(name) \
void name(); \
bool testvar_##name = runTest(name, #name); \
void name()

//--------------------------------------------------
//test functions

TEST_CASE(test_MyStringDefaultConstructor) {
	try {
		MyString s;
		if (!(s.empty() && s.size() == 0)) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}

void checkConstCharArrayConstructor(const char* str) {
	try {
		MyString s(str);
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringCheckConstCharArrayConstructorWithEmptyString) {
	const char* str = "";
	checkConstCharArrayConstructor(str);
}
TEST_CASE(test_MyStringCheckConstCharArrayConstructorWithString) {
	const char* str = "test";
	checkConstCharArrayConstructor(str);
}
TEST_CASE(test_MyStringCheckConstCharArrayConstructorWithUninitializedString) {
	char str[100];
	checkConstCharArrayConstructor(str);
}

void checkMyStringIfEmpty(const char* str) {
	std::size_t l = std::strlen(str);
	try {
		MyString s(str);
		if (l == 0) {
			if (s.empty() == false) {
				hasError = true;
			}
		}
		else {
			if (s.empty() == true) {
				hasError = true;
			}
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringCheckIfEmptyWithEmptyString) {
	const char* str = "";
	checkMyStringIfEmpty(str);
}
TEST_CASE(test_MyStringCheckIfEmptyWithString) {
	const char* str = "test";
	checkMyStringIfEmpty(str);
}
TEST_CASE(test_MyStringCheckIfEmptyWithUninitializedCharArray) {
	char str[100];
	checkMyStringIfEmpty(str);
}

void checkIsEqual(const char* str1, const char* str2) {
	try {
		MyString a(str1), b(str2);
		if (std::strcmp(str1, str2) == 0) {
			if (a != b) {
				hasError = true;
			}
		}
		else {
			if (a == b) {
				hasError = true;
			}
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}

}
TEST_CASE(test_MyStringIsEqualOperatorWithEqualStrings) {
	const char* str1 = "test";
	const char* str2 = "test";
	checkIsEqual(str1, str2);
}
TEST_CASE(test_MyStringIsEqualOperatorWithStrings) {
	const char* str1 = "testing";
	const char* str2 = "testing1";
	checkIsEqual(str1, str2);
}
TEST_CASE(test_MyStringIsEqualOperatorWithEmptyStrings) {
	const char* str1 = "";
	const char* str2 = "";
	checkIsEqual(str1, str2);
}
TEST_CASE(test_MyStringIsEqualOperatorWithOneEmptyString) {
	const char* str1 = "";
	const char* str2 = "test";
	checkIsEqual(str1, str2);
}
TEST_CASE(test_MyStringIsEqualOperatorWithUninitializedString) {
	char str1[4];
	const char* str2 = "test";
	checkIsEqual(str1, str2);
}
TEST_CASE(test_MyStringIsEqualOperatorWithUninitializedStrings) {
	char str1[4];
	char str2[5];
	checkIsEqual(str1, str2);
}

TEST_CASE(test_MyStringCopyConstructor) {
	const char* str = "testing";
	try {
		MyString a(str);
		MyString b = a;
		if (a != b) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}

void checkMyStringCopyAssignmentOperator(const char* str) {
	try {
		MyString a(str);
		MyString b;
		b = a;
		if (a != b) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringCopyAssignmentOperator) {
	const char* str = "testing";
	checkMyStringCopyAssignmentOperator(str);
}
TEST_CASE(test_MyStringCopyAssignmentOperatorWithUninitializedString) {
	char str[4];
	checkMyStringCopyAssignmentOperator(str);
}

void checkMyStringSizeFunction(const char* str) {
	size_t l = std::strlen(str);
	try {
		MyString s(str);
		if (s.size() != l) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringSizeWithString) {
	const char* str = "test";
	checkMyStringSizeFunction(str);
}
TEST_CASE(test_MyStringSizeWithEmptyString) {
	const char* str = "";
	checkMyStringSizeFunction(str);
}
TEST_CASE(test_MyStringSizeWithUninitializedString) {
	char str[10];
	checkMyStringSizeFunction(str);
}


void checkMyStringAt(std::size_t pos, char testChar = 't') {
	try {
		MyString s("testing");
		char myChar = s.at(pos);
		if (myChar != testChar) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e){
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringAtWithInvalidPos) {
	checkMyStringAt(-3);
}
TEST_CASE(test_MyStringAtWithValidCharAndPos) {
	checkMyStringAt(0, 't');
}
TEST_CASE(test_MyStringAtWithValidCharAndInvalidPos) {
	checkMyStringAt(10, 't');
}


void checkMyStringAtConst(std::size_t pos, char testChar = 't') {
	try {
		const MyString s("testing");
		char myChar = s.at(pos);
		if (myChar != testChar) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringAtConstWithInvalidPos) {
	checkMyStringAtConst(-3);
}
TEST_CASE(test_MyStringAtConstWithValidCharAndPos) {
	checkMyStringAtConst(0, 't');
}
TEST_CASE(test_MyStringAtConstWithValidCharAndInvalidPos) {
	checkMyStringAtConst(10, 't');
}

void checkMyStringAtOperator(std::size_t pos) {
	const char* str = "testing";
	try {
		MyString s(str);
		char myChar = s[pos];
		char strChar = str[pos];
		if (myChar != strChar) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringAtOperatorWithValidPos) {
	checkMyStringAtOperator(0);
}


void checkMyStringAtOperatorConst(std::size_t pos) {
	const char* str = "testing";
	try {
		const MyString s(str);
		char myChar = s[pos];
		char strChar = str[pos];
		if (myChar != strChar) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringAtOperatorConstWithValidPos) {
	checkMyStringAtOperatorConst(2);
}

void checkMyStringFront(const char* str) {
	try {
		MyString s(str);
		char firstC = str[0];
		if (s.front() != firstC) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringFront) {
	checkMyStringFront("testing");
}

void checkMyStringFrontConst(const char* str) {
	try {
		const MyString s(str);
		char firstC = str[0];
		if (s.front() != firstC) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringFrontConst) {
	checkMyStringFrontConst("testing");
}

void checkMyStringBack(const char* str) {
	try {
		MyString s(str);
		char lastC = str[std::strlen(str) - 1];
		if (s.back() != lastC) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringBackWithCorrectData) {
	checkMyStringBack("testing");
}

void checkMyStringBackConst(const char* str) {
	try {
		const MyString s(str);
		char lastC = str[std::strlen(str) - 1];
		if (s.back() != lastC) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringBackConst) {
	checkMyStringBackConst("testing");
}

void checkMyStringClear(const char* str) {
	try {
		MyString a(str);
		a.clear();
		if (a.size() != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringClear) {
	const char* str = "testing";
	checkMyStringClear(str);
}
TEST_CASE(test_MyStringClearWithEmpty) {
	const char* str = "";
	checkMyStringClear(str);
}

void checkMyStringPushBack(char c) {
	const char* str = "testing";
	try {
		MyString a(str);
		a.push_back(c);
		if (c != '\0') {
			if (a.back() != c) {
				hasError = true;
			}
		}
		else {
			if (a.back() != str[std::strlen(str) - 1]) {
				hasError = true;
			}
		}

	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringPushBackWithChar) {
	char c = 'a';
	checkMyStringPushBack(c);
}
TEST_CASE(test_MyStringPushBackWithEmptyChar) {
	char c = '\0';
	checkMyStringPushBack(c);
}

void checkMyStringPushBackOperator(char c) {
	const char* str = "testing";
	try {
		MyString a(str);
		a += c;
		if (c != '\0') {
			if (a.back() != c) {
				hasError = true;
			}
		}
		else {
			if (a.back() != str[std::strlen(str) - 1]) {
				hasError = true;
			}
		}

	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringPushBackOperator) {
	char c = 'a';
	checkMyStringPushBackOperator(c);
}
TEST_CASE(test_MyStringPushBackOperatorWithEmptyChar) {
	char c = '\0';
	checkMyStringPushBackOperator(c);
}

TEST_CASE(test_MyStringPopBack) {
	try {
		MyString a("testing");
		a.pop_back();
		if (a.back() != 'n') {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}

char* concatenate(const char* str1, const char* str2) {
	std::size_t len1 = std::strlen(str1);
	std::size_t len2 = std::strlen(str2);

	std::size_t newLen = len1 + len2;
	char* concat = new char[newLen + 1];
	for (std::size_t i = 0; i < len1; i++) {
		concat[i] = str1[i];
	}
	for (std::size_t j = len1; j < newLen; j++) {
		concat[j] = str2[j - len1];
	}
	concat[newLen] = '\0';
	return concat;
}
void checkMyStringConcatOperator(const char* str1, const char* str2) {
	try {
		MyString a(str1);
		MyString b(str2);
		std::size_t len = a.size() + b.size();

		char* concat = concatenate(str1, str2);

		a += b;
		MyString c(concat);

		if (a.size() != c.size() || a != c) {
			hasError = true;
		}
		delete[] concat;

	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringConcatOperator) {
	checkMyStringConcatOperator("testing", " the concat");
}
TEST_CASE(test_MyStringConcatOperatorWithEmptyStringOn1) {
	checkMyStringConcatOperator("", "testing");
}
TEST_CASE(test_MyStringConcatOperatorWithEmptyStringOn2) {
	checkMyStringConcatOperator("testing", "");
}
TEST_CASE(test_MyStringConcatOperatorWithEmptyStrings) {
	checkMyStringConcatOperator("", "");
}

void checkMyStringOperatorPlusChar(char c) {
	try {
		MyString a("testing");
		a = a + c;
		if (c != '\0') {
			if (a[a.size() - 1] != c) {
				hasError = true;
			}
		}
		else {
			if (a[a.size() - 1] != 'g') {
				hasError = true;
			}
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringConcatOperatorPlusWithChar) {
	checkMyStringOperatorPlusChar('A');
}
TEST_CASE(test_MyStringConcatOperatorPlusWithEmptyChar) {
	checkMyStringOperatorPlusChar('\0');
}

void checkMyStringOperatorPlusOther(const char* str) {
	const char* testStr = "testing";
	try {
		MyString a(testStr);
		MyString b(str);
		MyString c = a + b;

		std::size_t newLen = std::strlen(testStr) + std::strlen(str);
		char* newStr = concatenate(testStr, str);

		MyString newS(newStr);
		if (c != newS) {
			hasError = true;
		}

		delete[] newStr;
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringConcatOperatorPlusWithString) {
	checkMyStringOperatorPlusOther(" something");
}
TEST_CASE(test_MyStringConcatOperatorPlusWithEmpty) {
	checkMyStringOperatorPlusOther("");
}

void checkMyString_c_str(const char* str) {
	try {
		MyString a(str);

		const char* s = a.c_str();
		if (str[0] == '\0') {
			if (s[0] != '\0') {
				hasError = true;
				return;
			}
		}
		if (std::strcmp(str, s) != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyString_c_str) {
	checkMyString_c_str("testing");
}
TEST_CASE(test_MyString_c_strWithEmpty) {
	checkMyString_c_str("");
}

void checkMyStringLesserThanOperator(const char* str1, const char* str2) {
	try {
		MyString a(str1);
		MyString b(str2);

		if (str1[0] == '\0') {
			if (str2[0] == '\0') {
				if (a < b) {
					hasError = true;
					return;
				}
			}
			else {
				if (!(a < b)) {
					hasError = true;
					return;
				}
			}
		}
		if (str2[0] == '\0') {
			if (str1[0] == '\0') {
				if (a < b) {
					hasError = true;
					return;
				}
			}
			else {
				if (a < b) {
					hasError = true;
					return;
				}
			}
		}

		int diff = std::strcmp(str1, str2);
		if (diff > 0) {
			//1 > 2
			if (a < b) {
				hasError = true;
			}
		}
		else if (diff == 0) {
			//1 = 2
			if (a < b) {
				hasError = true;
			}
		}
		else {
			//1 < 2
			if (!(a < b)) {
				hasError = true;
			}
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_MyStringLesserThanOperatorWithSame) {
	checkMyStringLesserThanOperator("testing", "testing");
}
TEST_CASE(test_MyStringLesserThanOperatorWithGreater1) {
	checkMyStringLesserThanOperator("testing1", "testing");
}
TEST_CASE(test_MyStringLesserThanOperatorWithGreater2) {
	checkMyStringLesserThanOperator("testing", "testing1");
}
TEST_CASE(test_MyStringLesserThanOperatorWithSameLengthButGreater1) {
	checkMyStringLesserThanOperator("testing2", "testing1");
}
TEST_CASE(test_MyStringLesserThanOperatorWithSameLengthButGreater2) {
	checkMyStringLesserThanOperator("testing1", "testing2");
}
TEST_CASE(test_MyStringLesserThanOperatorWithEmptyString1) {
	checkMyStringLesserThanOperator("", "testing");
}
TEST_CASE(test_MyStringLesserThanOperatorWithEmptyString2) {
	checkMyStringLesserThanOperator("testing", "");
}
TEST_CASE(test_MyStringLesserThanOperatorWithEmptyStrings) {
	checkMyStringLesserThanOperator("", "");
}
