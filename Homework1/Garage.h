#pragma once
#include <cstddef>

#include "Vehicle.h"

class Garage {
	Vehicle** vehicles = nullptr;

	//number of parking spaces
	std::size_t capacity;
	//number of parking spaces used
	std::size_t usedSpace = 0;
	std::size_t numOfVehicles = 0;
	//capacity for num of vehicles
	std::size_t vehiclesCapacity = 2;

	void copy(const Garage&);
	bool existsInGarage(const char*) const;
	bool existsInGarage(const Vehicle&) const;
	bool canInsert(const Vehicle&) const;
	void incrementSpace(std::size_t);
	void decrementSpace(std::size_t);
	void expand();
public:
	Garage(const Garage&);
	Garage& operator=(const Garage&);
	~Garage();

	Garage(std::size_t capacity);

	void insert(Vehicle&);

	void erase(const char*);

	const Vehicle& at(std::size_t pos) const;
	const Vehicle& operator[](std::size_t pos) const;


	bool empty() const;
	std::size_t size() const;
	void clear();

	const Vehicle* find(const char* registration) const;
};