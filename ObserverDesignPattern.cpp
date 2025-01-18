 #include <iostream>
 #include <memory>
 #include <vector>
 #include <algorithm>

 using namespace std;


 class Observer
 {
    public:
    virtual void update() = 0;
 };

 class EmailAlertObserver : public Observer
 {
    public:
    void update() 
    {
        cout<<"Email sent to observer \n";
    }
 };

 class MobileSmsObserver : public Observer
 {
 public:
    void update()
    {
        cout<<"Mobile SMS Sent to observer \n";
    }
 };
 
 class Observable
 {
    protected:
        vector<shared_ptr<Observer>> observers;

    public:
        virtual void add(shared_ptr<Observer> ptrObsr) = 0;
        virtual void remove(shared_ptr<Observer> ptrObsr) = 0;

        virtual void notify() = 0;

        virtual void updateData() = 0;
 };

 class ObservalbeConcerete : public Observable
 {
 public:
    void add(shared_ptr<Observer> ptrOb)
    {
        observers.push_back(ptrOb);
    }

    void remove(shared_ptr<Observer> ptrOb)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), ptrOb), observers.end());
    }

    void notify() override
    {
        for(auto & ptr: observers)
            ptr->update();
    }

    void updateData() override
    {
        cout<<"Data updated \n";
        notify();
    }
 };
 
 