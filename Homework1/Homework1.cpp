#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

#include "Garage.h"
#include "VehicleList.h"

MyString inputString() {
	try {
		MyString input;
		char c = '\0';
		while (c != '\n') {
			input.push_back(c);
			std::cin.get(c);
		}
		return input;
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't input string...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
		return nullptr;
	}
}

void cls() {
	std::system("cls");
}
void print(const char* str) {
	size_t len = std::strlen(str);
	for (size_t i = 0; i < len; i++) {
		std::cout << str[i];
	}
	std::cout << std::endl;
}
void printOptions() {
	std::cout << "[1] Create Vehicle \n";
	std::cout << "[2] Garage Settings \n";
	std::cout << "[3] Show Vehicles \n";
	std::cout << "[4] Show Garage Contents \n";
	std::cout << "[5] Clear Screen \n";
	std::cout << "[6] Exit \n";
}
void printVehicles() {
	std::size_t numOfVehicles = VehicleList::Get().size();
	if (numOfVehicles == 0) {
		std::cout << "There are currently no vehicles... \n\n";
		return;
	}
	try {
		for (std::size_t i = 0; i < numOfVehicles; i++) {
			if (VehicleList::Get()[i] != nullptr) {
				std::cout << "[" << (i + 1) << "] ";
				std::cout << VehicleList::Get()[i]->registration() << " -- ";
				std::cout << VehicleList::Get()[i]->description() << " -- ";
				std::cout << VehicleList::Get()[i]->space() << "\n";
			}
		}
		std::cout << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't print vehicles...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
	}
}
void printGarageOptions() {
	std::cout << "[1] Insert Vehicle \n";
	std::cout << "[2] Erase Vehicle \n";
	std::cout << "[3] Clear Garage \n";
}
void printGarageContents(const Garage& garage) {
	std::size_t vehiclesInGarage = garage.size();
	if (vehiclesInGarage == 0) {
		std::cout << "Garage is currently empty... \n\n";
		return;
	}
	try {
		for (std::size_t i = 0; i < vehiclesInGarage; i++) {
			if (&garage[i] != nullptr) {
				std::cout << "[" << i + 1 << "] ";
				std::cout << garage[i].registration() << " -- ";
				std::cout << garage[i].description() << " -- ";
				std::cout << garage[i].space() << "\n";
			}
		}
		std::cout << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't print garage contents...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
	}
}

void createGarage(Garage& garage) {
	int capacity;
	while (true) {
		std::cout << std::endl;
		std::cout << "Enter garage capacity: ";
		while (!(std::cin >> capacity)) {
			std::cin.clear();
			std::cin.ignore();
		}

		if (capacity <= 0) {
			std::cout << "Please enter valid garage capacity... ";
			continue;
		}
		break;
	}
	try {
		Garage myGarage(capacity);
		garage = myGarage;
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't create garage...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
	}
	std::cout << std::endl;
}

void inputVehicle() {
	try {
		std::cout << "Enter vehicle registration: ";
		MyString registration = inputString();
		std::cout << std::endl;
		std::cout << "Enter vehicle description: ";
		MyString description = inputString();
		int space;
		while (true) {
			std::cout << std::endl;
			std::cout << "Enter vehicle space: ";
			while (!(std::cin >> space)) {
				std::cin.clear();
				std::cin.ignore();
			}
			if (space <= 0) {
				std::cout << "Please enter valid vehicle space... ";
				continue;
			}
			break;
		}

		std::cout << std::endl;

		Vehicle* v = new Vehicle(registration.c_str(), description.c_str(), space);
		VehicleList::Get().insert(*v);
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't input vehicle...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
	}
}

void insertVehicle(Garage& garage) {
	bool insertingVehicle = 1;
	while (insertingVehicle) {
		printVehicles();

		std::size_t vehiclePos;
		std::cout << "Select vehicle to insert (0 to abort): ";
		std::cin >> vehiclePos;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore();
			while (std::cin.get() != '\n') continue;
			continue;
		}

		std::cout << std::endl;

		if (vehiclePos == 0) {
			//abort action
			return;
		}

		if (vehiclePos > VehicleList::Get().size()) {
			std::cout << "Please enter valid vehicle position... \n";
			continue;
		}

		try {
			garage.insert(*(VehicleList::Get()[vehiclePos - 1]));
		}
		catch (const std::exception& e) {
			std::cerr << "Couldn't insert vehicle...\n";
			std::cerr << "Reason: " << e.what() << "\n\n";
		}

		insertingVehicle = 0;
	}
}

void eraseVehicle(Garage& garage) {
	bool erasingVehicle = 1;
	while (erasingVehicle) {
		printGarageContents(garage);

		std::size_t vehiclePos;
		std::cout << "Select vehicle to erase (0 to abort): ";
		std::cin >> vehiclePos;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore();
			while (std::cin.get() != '\n') continue;
			continue;
		}

		std::cout << std::endl;

		if (vehiclePos == 0) {
			return;
		}

		if (vehiclePos > garage.size()) {
			std::cout << "Please enter valid vehicle position... \n";
			continue;
		}

		try {
			garage.erase(garage[vehiclePos - 1].registration());
		}
		catch (const std::exception& e) {
			std::cerr << "Couldn't erase vehicle...\n";
			std::cerr << "Reason: " << e.what() << "\n\n";
		}

		erasingVehicle = 0;
	}
}

void clearGarage(Garage& garage) {
	try {
		garage.clear();
	}
	catch (const std::exception& e) {
		std::cerr << "Couldn't clear garage...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
	}
}

void garageSettings(Garage& garage) {
	if (VehicleList::Get().size() == 0) {
		std::cout << "There are currently no vehicles to interact with... \n\n";
		return;
	}

	while (true) {
		printGarageOptions();

		int option;
		std::cout << "Please select an option (0 to abort): ";
		std::cin >> option;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore();
			while (std::cin.get() != '\n') continue;
			continue;
		}

		std::cout << std::endl;
		if (option == 0) {
			return;
		}

		switch (option) {
		case 1:
			insertVehicle(garage);
			return;
		case 2:
			if (garage.size() == 0) {
				std::cout << "There are currently no vehicles in the garage... \n\n";
				return;
			}
			eraseVehicle(garage);
			return;
		case 3:
			clearGarage(garage);
			return;
		default:
			break;
		}
	}
}

void garageManager(Garage& garage) {
	bool isInUse = 1;

	while (isInUse) {
		printOptions();

		int opt;
		std::cout << "Please select an option: ";
		std::cin >> opt;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore();
			while (std::cin.get() != '\n') continue;
			continue;
		}
		std::cin.clear();
		std::cin.ignore();

		std::cout << std::endl;

		switch (opt) {
		case 1:
			inputVehicle();
			break;
		case 2:
			garageSettings(garage);
			break;
		case 3:
			printVehicles();
			break;
		case 4:
			printGarageContents(garage);
			break;
		case 5:
			cls();
			break;
		case 6:
			return;
		default:
			break;
		}
	}
}

int main()
{
	std::cout << "Creating garage... \n";

	try {
		Garage garage(0);
		createGarage(garage);

		garageManager(garage);
	}
	catch (const std::exception& e) {
		std::cerr << "Error running the program...\n";
		std::cerr << "Reason: " << e.what() << "\n\n";
	}

	return 0;
}
