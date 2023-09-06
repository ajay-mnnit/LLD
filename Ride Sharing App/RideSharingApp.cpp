#include <iostream>
#include <unordered_map>
#include <queue>

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


enum class DriverStatus
{
	IDLE,
	BOOKED
};

enum class RideStatus
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
	void setDriverId(int);

	//getter
	int getId();
	RideStatus getRideStatus();
	int getDriverId();

private:
	int id;
	int origin, dest;
	int seats;
	RideStatus rideStatus;
	int driverId;
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

RideStatus Ride::getRideStatus()
{
	return this->rideStatus;
}

void Ride::setDriverId(int id)
{
	this->driverId = id;
}

int Ride::getDriverId()
{
	return this->driverId;
}

class Person
{
public:
	std::string name;
};

class Rider : private Person
{
private:
	std::unordered_map<int, Ride> ridesCompleted; 
	Ride currentRide;
public:
	Rider(std:: string);
	int createRide(int, int, int, int, int);
	void updateRide(int, int, int, int);
	void withdrawRide(int);
	int closeRide();
	int getDriverId();
};

Rider::Rider(std::string name)
{
	this->name = name;
}

int Rider::createRide(int id, int origin, int dest, int seats, int driverId)
{
	if (origin > dest)
	{
		std::cout << "Enter Valid origin and destination" << std::endl;
		return 0;
	}
	this->currentRide.setId(id);
	this->currentRide.setOrigin(origin);
	this->currentRide.setDest(dest);
	this->currentRide.setSeats(seats);
	this->currentRide.setDriverId(driverId);
	this->currentRide.setRideStatus(RideStatus::CREATED);

	return 1;
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
	
	this->createRide(id, origin, dest, seats, this->getDriverId());
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

int Rider::getDriverId()
{
	return this->currentRide.getDriverId();
}

class Driver : private Person
{
private:
	DriverStatus driverStatus;
public:
	Driver(std::string);
	std::string getName();
	void setStatus(DriverStatus status);
	DriverStatus getStatus();
};

Driver::Driver(std::string name)
{
	this->name = name;
	driverStatus = DriverStatus::IDLE;
}

std::string Driver::getName()
{
	return this->name;
}

void Driver::setStatus(DriverStatus status)
{
	this->driverStatus = status;
}

DriverStatus Driver::getStatus()
{
	return this->driverStatus;
}


int main()
{
	std::cout << "Ride Sharing Application Starts....\n\n";

	std::unordered_map<int, Driver*> mdriver;
	std::queue<int> waitingQueue;

	Driver sundar = Driver("sundar");
	Driver yuga = Driver("Yuga");

	mdriver.insert({ 1, &sundar });
	mdriver.insert({2, &yuga});

	waitingQueue.push(1);
	waitingQueue.push(2);

	Rider rider("Ajay");
	Rider rider2("Sumit");
	Rider rider3("Manjit");


	if (!waitingQueue.empty())
	{
		int id = waitingQueue.front();

		if (rider.createRide(0, 10, 100, 1,id) == 1)
		{
			mdriver[id]->setStatus(DriverStatus::BOOKED);
			waitingQueue.pop();
			std::cout<<"Ride booked with "<<mdriver[id]->getName()<<std::endl;
		}
	}
	else
	{
		std::cout << "No diver is availalbe, Please wait for sometime\n\n";
	}

	if (!waitingQueue.empty())
	{
		int id = waitingQueue.front();

		if (rider2.createRide(0, 0, 200, 1, id) == 1)
		{
			mdriver[id]->setStatus(DriverStatus::BOOKED);
			waitingQueue.pop();
			std::cout << "Ride booked with " << mdriver[id]->getName() << std::endl;
		}
	}
	else
	{
		std::cout << "No diver is availalbe, Please wait for sometime\n\n";
	}


	if (!waitingQueue.empty())
	{
		int id = waitingQueue.front();

		if (rider3.createRide(0, 20, 100, 1, id) == 1)
		{
			mdriver[id]->setStatus(DriverStatus::BOOKED);
			waitingQueue.pop();
			std::cout << "Ride booked with " << mdriver[id]->getName() << std::endl;
		}
	}
	else
	{
		std::cout << "No diver is availalbe, Please wait for sometime\n\n";
	}

	int amount = rider.closeRide();
	if (amount)
	{
		int driverid = rider.getDriverId();
		mdriver[driverid]->setStatus(DriverStatus::IDLE);
		waitingQueue.push(driverid);
		std::cout << "Ride eneded with:"<< mdriver[driverid]->getName()<<" Amount paid: "<<amount << std::endl;
	}
	rider.updateRide(0, 100, 20, 3); 
	 
	amount = rider2.closeRide();
	if (amount)
	{
		int driverid = rider2.getDriverId();
		mdriver[driverid]->setStatus(DriverStatus::IDLE);
		waitingQueue.push(driverid);
		std::cout << "Ride eneded with:" << mdriver[driverid]->getName() << " Amount paid: " << amount << std::endl;
	}

	std::cout << "----------------------------------------------------\n\n"; 
	 

	return 0;
}