#include <iostream>
#include <cstring>
#include <new>
#include <stdexcept>

#include "../Homework1/Vehicle.h"

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

void check_VehicleConstructor(const char* reg, const char* desc, std::size_t space) {
	try {
		Vehicle a(reg, desc, space);
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_VehicleConstructor) {
	const char* reg = "TX9999XH";
	const char* desc = "Audi A3";
	std::size_t space = 1;
	check_VehicleConstructor(reg, desc, space);
}
TEST_CASE(test_VehicleConstructorWithEmptyReg) {
	const char* reg = "";
	const char* desc = "Audi A3";
	std::size_t space = 1;
	check_VehicleConstructor(reg, desc, space);
}
TEST_CASE(test_VehicleConstructorWithEmptyDesc) {
	const char* reg = "TX9999XH";
	const char* desc = "";
	std::size_t space = 1;
	check_VehicleConstructor(reg, desc, space);
}
TEST_CASE(test_VehicleConstructorWithZeroSpace) {
	const char* reg = "TX9999XH";
	const char* desc = "Audi A3";
	std::size_t space = 0;
	check_VehicleConstructor(reg, desc, space);
}

void check_VehicleRegistration(const char* reg, const char* desc, std::size_t space) {
	try {
		Vehicle a(reg, desc, space);
		const char* r = a.registration();
		if (std::strcmp(reg, r) != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_VehicleRegistration) {
	const char* reg = "TX9999XH";
	const char* desc = "AUDI A3";
	std::size_t space = 1;
	check_VehicleRegistration(reg, desc, space);
}
TEST_CASE(test_VehicleRegistrationWithEmptyDesc) {
	const char* reg = "";
	const char* desc = "AUDI A3";
	std::size_t space = 1;
	check_VehicleRegistration(reg, desc, space);
}


void check_VehicleDescription(const char* reg, const char* desc, std::size_t space) {
	try {
		Vehicle a(reg, desc, space);
		const char* d = a.description();
		if (std::strcmp(desc, d) != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_VehicleDescription) {
	const char* reg = "TX9999XH";
	const char* desc = "AUDI A3";
	std::size_t space = 1;
	check_VehicleDescription(reg, desc, space);
}
TEST_CASE(test_VehicleDescriptionWithEmptyDesc) {
	const char* reg = "";
	const char* desc = "AUDI A3";
	std::size_t space = 1;
	check_VehicleDescription(reg, desc, space);
}

void check_VehicleSpace(const char* reg, const char* desc, std::size_t space) {
	try {
		Vehicle a(reg, desc, space);
		std::size_t vehSpace = a.space();
		if (space != vehSpace) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_VehicleSpace) {
	const char* reg = "TX9999XH";
	const char* desc = "AUDI A3";
	std::size_t space = 1;
	check_VehicleSpace(reg, desc, space);
}
TEST_CASE(test_VehicleSpaceWithZeroSpace) {
	const char* reg = "TX1111XT";
	const char* desc = "AUDI A3";
	std::size_t space = 0;
	check_VehicleSpace(reg, desc, space);
}
