#include <cstring>
#include <stdexcept>
#include <cassert>

#include "Garage.h"

void Garage::copy(const Garage& g) {
	Vehicle** tempVehicleAddresses = new Vehicle * [g.vehiclesCapacity]();
	for (std::size_t i = 0; i < g.vehiclesCapacity; i++) {
		tempVehicleAddresses[i] = g.vehicles[i];
	}
	delete[] vehicles;

	vehicles = tempVehicleAddresses;
	capacity = g.capacity;
	usedSpace = g.usedSpace;
	numOfVehicles = g.numOfVehicles;
	vehiclesCapacity = g.vehiclesCapacity;
}
bool Garage::existsInGarage(const char* registration) const {
	for (std::size_t i = 0; i < vehiclesCapacity; i++) {
		if (vehicles[i] != nullptr) {
			if (std::strcmp(vehicles[i]->registration(), registration) == 0) {
				return true;
			}
		}
	}
	return false;
}
bool Garage::existsInGarage(const Vehicle& v) const {
	return existsInGarage(v.registration());
}
bool Garage::canInsert(const Vehicle& v) const {
	if (usedSpace + v.space() > capacity) {
		return false;
	}
	return true;
}
void Garage::incrementSpace(std::size_t addSpace) {
	usedSpace += addSpace;
	numOfVehicles++;
}
void Garage::decrementSpace(std::size_t removeSpace) {
	usedSpace -= removeSpace;
	numOfVehicles--;
}
void Garage::expand() {
	Vehicle** newVehicles = new Vehicle * [vehiclesCapacity * 2]();
	for (std::size_t i = 0; i < vehiclesCapacity; i++) {
		newVehicles[i] = vehicles[i];
	}

	delete[] vehicles;
	vehicles = newVehicles;
	vehiclesCapacity *= 2;
}

Garage::Garage(const Garage& g) {
	copy(g);
}
Garage& Garage::operator=(const Garage& g) {
	if (this != &g) {
		copy(g);
	}
	return *this;
}
Garage::~Garage() {
	delete[] vehicles;
	capacity = 0;
	usedSpace = 0;
	numOfVehicles = 0;
	vehiclesCapacity = 0;
}

Garage::Garage(std::size_t size) {
	vehicles = new Vehicle * [vehiclesCapacity]();
	capacity = size;
}

void Garage::insert(Vehicle& v) {
	if (!canInsert(v)) {
		throw std::runtime_error("Capacity overflow");
	}
	if (existsInGarage(v)) {
		throw std::runtime_error("Vehicle already in garage");
	}
	if (numOfVehicles == vehiclesCapacity) {
		expand();
	}

	vehicles[numOfVehicles] = &v;
	incrementSpace(v.space());
}
void Garage::erase(const char* registration) {
	if (registration == nullptr || !existsInGarage(registration)) {
		return;
	}

	for (std::size_t i = 0; i < vehiclesCapacity; i++) {
		if (std::strcmp(vehicles[i]->registration(), registration) == 0) {
			std::size_t removedSpace = vehicles[i]->space();
			vehicles[i] = nullptr;
			vehicles[i] = vehicles[numOfVehicles - 1];
			decrementSpace(removedSpace);
			break;
		}
	}
	return;
}

const Vehicle& Garage::at(std::size_t pos) const {
	if (pos >= numOfVehicles) {
		throw std::out_of_range("Out of range");
	}
	return *vehicles[pos];
}
const Vehicle& Garage::operator[](std::size_t pos) const {
	assert(pos >= 0 && pos < capacity);

	return *vehicles[pos];
}

bool Garage::empty() const {
	if (usedSpace == 0) {
		return true;
	}
	return false;
}
std::size_t Garage::size() const {
	return numOfVehicles;
}

void Garage::clear() {
	Vehicle** clearVehicles = new Vehicle * [2]();

	delete[] vehicles;

	vehicles = clearVehicles;
	usedSpace = 0;
	numOfVehicles = 0;
	vehiclesCapacity = 2;
}

const Vehicle* Garage::find(const char* registration) const {
	for (std::size_t i = 0; i < vehiclesCapacity; i++) {
		if (vehicles[i] != nullptr) {
			if (std::strcmp(vehicles[i]->registration(), registration) == 0) {
				return vehicles[i];
			}
		}
	}

	return nullptr;
}