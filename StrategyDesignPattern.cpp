#include <iostream>
#include <memory>

using namespace std;

class Vehicle;

class VehicleStrategy
{
    public:
    virtual void drive() = 0;

    virtual ~VehicleStrategy() = default;
};

class SportVehicleStategy : public VehicleStrategy
{
private:
    /* data */
public:
    SportVehicleStategy(/* args */) = default;
    ~SportVehicleStategy() = default;


    void drive() override
    {
        cout<<"Driving Sport Vehicle \n";
    }
};

class SportNormalStategy : public VehicleStrategy
{
private:
    /* data */
public:
    SportNormalStategy(/* args */) = default;
    ~SportNormalStategy() = default;


    void drive() override
    {
        cout<<"Driving Normal Vehicle \n";
    }
};




class Vehicle
{
    unique_ptr<VehicleStrategy> pVehicleStrategy;

public: 
    Vehicle(unique_ptr<VehicleStrategy> ptr) : pVehicleStrategy(std::move(ptr)){}

    virtual void typeVehicle() = 0;

    void driveVehicle()
    {
        pVehicleStrategy->drive();
    }
};

// child classes
class NormalVehicle : public Vehicle
{
private:
    /* data */
public:
    NormalVehicle(unique_ptr<VehicleStrategy> ptr): Vehicle(std::move(ptr)){}

    void typeVehicle() override
    {
        cout<<"Vehicle Type: Normal Vehicle \n";
    }
};

class SportVehicle : public Vehicle
{
private:
    /* data */
public:
    SportVehicle(unique_ptr<VehicleStrategy> ptr): Vehicle(std::move(ptr)){}

    void typeVehicle() override
    {
        cout<<"Vehicle Type: Sport Vehicle \n";
    }
};



int main()
{
    unique_ptr<VehicleStrategy> ptrStgy = make_unique<SportNormalStategy>();
    unique_ptr<Vehicle> ptr = make_unique<SportVehicle>(std::Move(ptrStgy));
}