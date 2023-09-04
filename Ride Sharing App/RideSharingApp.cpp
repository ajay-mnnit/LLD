#include <iostream>]
#include <unordered_map>

/*
This is a low level design of an ride sharing application with having the below mentioned functionalities:
	Rider:
		name of the rider
		book a ride with a origin and destination point
		update a ride
		withdraw a ride
		book no of seats for the ride
		close the ride and display fare amount

	Driver:
		
*/


enum RideStatus
{
	IDLE,
	CREATED,
	WITHDRAWN,
	COMPLETED
};

class Ride
{
public:

	static const int FARE_PER_KM = 20;

	Ride();
	int calculateFare();

	//setter
	void setId(int);
	void setOrigin(int);
	void setDest(int);
	void setSeats(int);
	void setRideStatus(RideStatus);

	//getter
	int getId();
	int getRideStatus();

private:
	int id;
	int origin, dest;
	int seats;
	RideStatus rideStatus;
};

Ride::Ride()
{
	id = origin = dest = seats = 0;
	rideStatus = RideStatus::IDLE;
}

int Ride::calculateFare()
{
	int diff = dest - origin;

	if (seats < 2)
	{
		return diff * FARE_PER_KM;
	}
	
	return diff * seats * FARE_PER_KM;
}

void Ride::setId(int id)
{
	this->id = id;
}

void Ride::setOrigin(int origin)
{
	this->origin = origin;
}

void Ride::setDest(int dest)
{
	this->dest = dest;
}

void Ride::setSeats(int seats)
{
	this->seats = seats;
}

void Ride::setRideStatus(RideStatus rideStatus)
{
	this->rideStatus = rideStatus;
}

int Ride::getId()
{
	return this->id;
}

int Ride::getRideStatus()
{
	return this->rideStatus;
}


class Person
{
public:
	std::string _name;
};

class Rider : private Person
{
private:
	std::unordered_map<int, Ride> ridesCompleted;
	Ride currentRide;

public:
	Rider(std:: string);
	void createRide(int, int, int, int);
	void updateRide(int, int, int, int);
	void withdrawRide(int);
	int closeRide();
};

Rider::Rider(std::string name)
{
	this->_name = name;
}

void Rider::createRide(int id, int origin, int dest, int seats)
{
	if (origin > dest)
	{
		std::cout << "Enter Valid origin and destination" << std::endl;
		return;
	}
	this->currentRide.setId(id);
	this->currentRide.setOrigin(origin);
	this->currentRide.setDest(dest);
	this->currentRide.setSeats(seats);

	this->currentRide.setRideStatus(RideStatus::CREATED);

}
void Rider::updateRide(int id, int origin, int dest, int seats)
{
	if (this->currentRide.getRideStatus() == RideStatus::WITHDRAWN)
	{
		std::cout << "A Withdrew ride cannot be modified" << std::endl;
		return;
	}

	if (this->currentRide.getRideStatus() == RideStatus::COMPLETED)
	{
		std::cout << "A Completed ride cannot be modified" << std::endl;
		return;
	}
	
	this->createRide(id, origin, dest, seats);
}

void Rider :: withdrawRide(int id)
{
	if (this->currentRide.getId() != id)
	{
		std::cout << "Enter a valid ride id" << std::endl;
		return;
	}

	if (this->currentRide.getRideStatus() != RideStatus::CREATED)
	{
		std::cout << "A non-existing ride cannot be withdrawn" << std::endl;
		return;
	}
	 
	this->currentRide.setRideStatus(RideStatus::WITHDRAWN);
}

int Rider::closeRide()
{
	if (this->currentRide.getRideStatus() != RideStatus::CREATED)
	{
		std::cout << "A non-existing ride cannot be closed" << std::endl;
		return 0;
	}

	this->currentRide.setRideStatus(RideStatus::COMPLETED);
	this->ridesCompleted.insert({ currentRide.getId(), currentRide });

	return currentRide.calculateFare();
}

class Driver : private Person
{
public:
	Driver(std::string);
};

Driver::Driver(std::string name)
{
	_name = name;
}

int main()
{
	std::cout << "Ride Sharing Application Starts....\n\n";

	Rider rider("Ajay Kumar");
	Driver driver("Sumit");

	rider.createRide(0, 100, 20, 1);
	std::cout << rider.closeRide() << std::endl;
	rider.updateRide(0, 100, 20, 3);
	std::cout << rider.closeRide() << std::endl;

	std::cout << "----------------------------------------------------\n\n";

	rider.createRide(0, 10, 200, 1);
	rider.withdrawRide(0);
	rider.updateRide(0, 200, 20, 2);
	std::cout << rider.closeRide() << std::endl;

	std::cout << "----------------------------------------------------\n\n";

	rider.createRide(0, 10, 200, 1);
	rider.updateRide(0, 200, 20, 2);
	std::cout << rider.closeRide() << std::endl;

	return 0;
}