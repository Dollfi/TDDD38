#include <iostream>

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::chrono_literals;

void physics(double& temp, bool& boiler_on, bool& simulation_done,
             unique_lock<mutex>& temp_mutex, condition_variable& temp_change)
{
  while ( ! simulation_done )
  {
    temp_mutex.lock();
    if ( boiler_on )
      temp += 4;
    else
      temp -= 1;
    temp_mutex.unlock();
    temp_change.notify_one();
    
    this_thread::sleep_for(1s);
  }
}

void boiler(double& temp, bool& boiler_on, bool& simulation_done,
            unique_lock<mutex>& temp_mutex, condition_variable& temp_change)
{
  while ( ! simulation_done )
  {
    double decision_temp{};
    
    temp_mutex.lock();
    
    while ( temp >= 80 && temp <= 100 )
      temp_change.wait(temp_mutex);

    decision_temp = temp;
    
    if ( temp < 80 )
      boiler_on = true;
    else if ( temp > 100 )
      boiler_on = false;

    temp_mutex.unlock();
    
    cout << decision_temp
         << (boiler_on ? " boiler on" : " boiler off")
         << endl;
  }
}

int main()
{
  double temperature{};
  bool bolier_on{false};
  bool simulation_done{false};
  
  mutex base_mutex{};
  unique_lock<mutex> temp_mutex{base_mutex, std::defer_lock};
  condition_variable temp_change{};
  
  thread p(physics,
           ref(temperature),
           ref(bolier_on),
           ref(simulation_done),
           ref(temp_mutex),
           ref(temp_change)
    );
  thread b(boiler,
           ref(temperature),
           ref(bolier_on),
           ref(simulation_done),
           ref(temp_mutex),
           ref(temp_change)
    );
  
  this_thread::sleep_for(10s);
  
  cout << "Main done" << endl;
  
  p.join();
  b.join();

  return 0;
}
