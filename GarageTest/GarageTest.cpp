#include <iostream>
#include <cstring>
#include <new>
#include <stdexcept>

#include "../Homework1/Garage.h"

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

void checkGarageConstructor(std::size_t size){
	try {
		Garage g(size);
	}
	catch(const std::bad_alloc& e){
		std::cerr << e.what();
	}
}
TEST_CASE(test_GarageConstructor) {
	checkGarageConstructor(5);
}
TEST_CASE(test_GarageConstructorWithZero) {
	checkGarageConstructor(0);
}
TEST_CASE(test_GarageConstructorWithNegative) {
	checkGarageConstructor(-1);
}

TEST_CASE(test_GarageCopyConstructor) {
	try {
		Vehicle v1("TX1234XT", "Audi A3", 1);
		Vehicle v2("TX4444XT", "Audi A3", 1);

		Garage g1(10);
		g1.insert(v1);
		g1.insert(v2);
		Garage g2 = g1;
		if (std::strcmp(g2.at(1).registration(), v2.registration()) != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}
TEST_CASE(test_GarageCopyAssignmentOperator) {
	try {
		Vehicle v1("TX1111XT", "Audi A3", 1);
		Vehicle v2("TX2222XT", "Audi A3", 1);
		Vehicle v3("TX3333XT", "Audi A3", 1);
		Vehicle v4("TX4444XT", "Audi A3", 1);
		Garage g1(10);
		Garage g2(5);
		g1.insert(v1);
		g1.insert(v2);
		g2.insert(v3);
		g2.insert(v4);
		g2 = g1;
		if (std::strcmp(g2.at(1).registration(), v2.registration()) != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}

TEST_CASE(test_GarageInsertWithOneVehicleAndAtFunction) {
	try {
		Vehicle v("TX1234XT", "Audi A3", 1);
		{
			Garage g(10);
			g.insert(v);
			if (std::strcmp(g.at(0).registration(), g[0].registration()) != 0) {
				hasError = true;
			}
		}
		if (&v == nullptr) {
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

TEST_CASE(test_GarageInsertSeveralVehicles) {
	try {
		Vehicle v1("TX1111XT", "Audi A3", 1);
		Vehicle v2("TX2222XT", "Audi A3", 1);
		Vehicle v3("TX3333XT", "Audi A3", 1);
		Vehicle v4("TX4444XT", "Audi A3", 8);
		Garage g(10);
		g.insert(v1);
		g.insert(v2);
		g.insert(v3);
		g.insert(v4);
		if (g.size() != 4) {
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

TEST_CASE(test_GarageInsertAndEraseVehicleAndEmptyFunction) {
	try {
		Vehicle v("TX1111XT", "Audi A3", 1);
		Garage g(10);
		if (!g.empty()) {
			hasError = true;
		}
		g.insert(v);
		g.erase("TX1111XT");
		if (!g.empty()) {
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

TEST_CASE(test_GarageInsertAndEraseVehicles) {
	try {
		Vehicle v1("TX1111XT", "Audi A3", 1);
		Vehicle v2("TX2222XT", "Audi A3", 1);
		Vehicle v3("TX3333XT", "Audi A3", 1);
		Vehicle v4("TX4444XT", "Audi A3", 1);
		Vehicle v5("TX5555XT", "Audi A3", 4);
		Vehicle v6("TX6666XT", "Audi A3	", 2);
		Garage g(10);
		g.insert(v1);
		g.insert(v2);
		g.insert(v3);
		g.insert(v4);
		g.insert(v5);
		g.insert(v6);
		if (g.size() != 6) {
			hasError = true;
		}
		g.erase("TX2222XT");
		g.erase("TX4444XT");

		if (std::strcmp(g.at(3).registration(), v5.registration()) != 0) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}

TEST_CASE(test_GarageAt) {
	try {
		Vehicle v1("TX1111XT", "Audi A3", 1);
		Vehicle v2("TX2222XT", "Audi A3", 1);
		Vehicle v3("TX3333XT", "Audi A3", 1);
		Vehicle v4("TX4444XT", "Audi A3", 1);
		Vehicle v5("TX5555XT", "Audi A3", 4);
		Vehicle v6("TX6666XT", "Audi A3	", 2);
		Garage g(10);
		g.insert(v1);
		g.insert(v2);
		g.insert(v3);
		g.insert(v4);
		g.insert(v5);
		g.insert(v6);
		const char* t1 = g.at(0).registration();
		const char* t2 = g.at(99999999).registration();
		const char* t3 = g.at(-1).registration();
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}

TEST_CASE(test_GarageClear) {
	try {
		Vehicle v1("TX1111XT", "Audi A3", 1);
		Vehicle v2("TX2222XT", "Audi A3", 1);
		Vehicle v3("TX3333XT", "Audi A3", 1);
		Garage g(10);
		g.insert(v1);
		g.insert(v2);
		g.insert(v3);
		g.clear();
		if (!g.empty()) {
			hasError = true;
		}
		Vehicle v4("TX3333XT", "Audi A3", 10);
		g.insert(v4);
		if (std::strcmp(g[0].registration(), v4.registration()) != 0) {
			hasError = true;
		}
		 
		//overflow
		g.insert(v1);
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
}

TEST_CASE(test_GarageFind) {
	try {
		Vehicle v1("TX1111XT", "Audi A3", 1);
		Vehicle v2("TX2222XT", "Audi A3", 1);
		Vehicle v3("TX3333XT", "Audi A3", 1);
		Vehicle v4("TX4444XT", "Audi A3", 1);
		Vehicle v5("TX5555XT", "Audi A3", 4);
		Vehicle v6("TX6666XT", "Audi A3	", 2);
		Garage g(10);
		g.insert(v1);
		g.insert(v2);
		g.insert(v3);
		g.insert(v4);
		g.insert(v5);
		g.insert(v6);
		const char* s = v3.registration();
		const Vehicle* v = g.find(s);
		if (std::strcmp(v->registration(), s) != 0) {
			hasError = true;
		}
		v = g.find("test");
		if (v != nullptr) {
			hasError = true;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cerr << e.what();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what();
	}
}
