#pragma once
#include <cstddef>

#include "Vehicle.h"

//custom class for vehicles to insert in garage

class VehicleList {
	Vehicle** vehicleList = nullptr;
	
	std::size_t capacity = 2;
	std::size_t numOfVehicles = 0;

	VehicleList();
	~VehicleList();

	bool existsInVehicleList(const char*) const;
	bool existsInVehicleList(const Vehicle&) const;
	void expand();
public:
	static VehicleList& Get() {
		static VehicleList vL_instance;
		return vL_instance;
	}

	VehicleList(const VehicleList&) = delete;
	VehicleList& operator=(const VehicleList&) = delete;

	void insert(Vehicle&);

	void erase(const char*);

	Vehicle* at(std::size_t pos) const;
	Vehicle* operator[](std::size_t pos) const;

	std::size_t size();
};

