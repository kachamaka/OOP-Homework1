#include <stdexcept>

#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) {
	if (space == 0) {
		throw std::runtime_error("Space cannot be 0");
	}

	this->registrationNumber = registration;
	this->desc = description;
	this->vehSpace = space;
}

const char* Vehicle::registration() const {
	return registrationNumber.c_str();
}
const char* Vehicle::description() const {
	return desc.c_str();
}
std::size_t Vehicle::space() const {
	return vehSpace;
}