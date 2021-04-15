#include <cstring>
#include <stdexcept>
#include <cassert>
#include "VehicleList.h"

bool VehicleList::existsInVehicleList(const char* registration) const {
	for (std::size_t i = 0; i < capacity; i++) {
		if (vehicleList[i] != nullptr) {
			if (std::strcmp(vehicleList[i]->registration(), registration) == 0) {
				return true;
			}
		}
	}
	return false;
}
bool VehicleList::existsInVehicleList(const Vehicle& v) const {
	return existsInVehicleList(v.registration());
}
void VehicleList::expand() {
	Vehicle** newVehicleList = new Vehicle * [capacity * 2]();
	for (std::size_t i = 0; i < capacity; i++) {
		newVehicleList[i] = vehicleList[i];
	}

	delete[] vehicleList;
	vehicleList = newVehicleList;
	capacity *= 2;
}

VehicleList::VehicleList() {
	vehicleList = new Vehicle * [capacity]();
}

VehicleList::~VehicleList() {
	for (std::size_t i = 0; i < capacity; i++) {
		delete vehicleList[i];
	}

	delete[] vehicleList;
	capacity = 0;
	numOfVehicles = 0;
}

void VehicleList::insert(Vehicle& v) {
	if (existsInVehicleList(v)) {
		throw std::runtime_error("Vehicle already in Vehicle List");
	}
	if (numOfVehicles == capacity) {
		expand();
	}
	vehicleList[numOfVehicles] = &v;
	numOfVehicles++;
}
void VehicleList::erase(const char* registration) {
	if (registration == nullptr || !existsInVehicleList(registration)) {
		return;
	}

	for (std::size_t i = 0; i < capacity; i++) {
		if (std::strcmp(vehicleList[i]->registration(), registration) == 0) {
			vehicleList[i] = nullptr;
			vehicleList[i] = vehicleList[numOfVehicles - 1];
			numOfVehicles--;
			break;
		}
	}
}

Vehicle* VehicleList::at(std::size_t pos) const {
	if (pos >= numOfVehicles) {
		throw std::out_of_range("out of range");
	}
	return vehicleList[pos];
}
Vehicle* VehicleList::operator[](std::size_t pos) const {
	assert(pos >= 0 && pos < numOfVehicles);

	return vehicleList[pos];
}

std::size_t VehicleList::size() {
	return numOfVehicles;
}