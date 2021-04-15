#include <iostream>
#include <cstring>
#include <stdexcept>

#include "../Homework1/VehicleList.h"

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

TEST_CASE(test_VehicleListInsertAndAtOperator) {
	try {
		VehicleList& vL = VehicleList::Get();
		Vehicle* v1 = new Vehicle("TX1111XT", "Audi A3", 1);
		Vehicle* v2 = new Vehicle("TX2222XT", "Audi A4", 1);
		Vehicle* v3 = new Vehicle("TX3333XT", "Audi A6", 1);

		vL.insert(*v1);
		vL.insert(*v2);
		vL.insert(*v3);
		if (strcmp(vL[2]->registration(), v3->registration()) != 0) {
			hasError = true;
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}

TEST_CASE(test_VehicleListInsertAndErase) {
	try {
		VehicleList& vL = VehicleList::Get();

		Vehicle* v1 = new Vehicle("TX1112XT", "Audi A3", 1);

		vL.insert(*v1);

		vL.erase(v1->registration());
		//note: keeping in mind previous test was executed and static initial state is not empty
		if (vL.size() != 3) {
			hasError = true;
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}