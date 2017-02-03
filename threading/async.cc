#include <thread>
#include <iostream>
#include <future>
#include <chrono>
using namespace std;

int foo(int a, int b)
{
    cout << "Foo\n";
    this_thread::sleep_for(2s);
    return a+b;
}

int main()
{
    // will wait for the first thread that calls f.get and then
    // run foo in that thread
    future<int> f = async(std::launch::deferred, foo, 2, 3);
    // runs foo in it's own thread
    // future<int> f = async(std::launch::async, foo, 2, 3);
    cout << "main\n";
    this_thread::sleep_for(1.5s);
    cout << f.get() << endl;
}
