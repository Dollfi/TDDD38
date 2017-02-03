#include <random>
#include <array>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

int main()
{
    vector<int> vals { 1,2,3,5,6,3,5};

    // Different ways of copying all values from vals into a new vector
    //
    // 1: use copy constructor (obvious)
    {
        vector<int> cpy {vals};
    }
    // 2: use iterator-based constructor
    {
        vector<int> cpy { begin(vals), end(vals) };
    }
    // 3: create a vector with enough elements and use std::copy
    {
        vector<int> cpy (vals.size());
        std::copy(begin(vals), end(vals), begin(cpy));
    }
    // 4: use a back_insert_iterator to insert elements into cpy
    {
        vector<int> cpy;
        std::copy(begin(vals), end(vals), back_inserter(cpy));
    }
    
    // use copy_if with a lambda expression to only copy even numbers
    vector<int> even;

    copy_if(begin(vals), end(vals),
            back_inserter(even),
            [](int val) { return val % 2 == 0; });


    // create an array of 52 ints and give them values 1..52. Shuffle the elements and print to cout using an ostream_iterator

    array<int, 52> deck;
    iota(begin(deck), end(deck), 1);
    shuffle(begin(deck), end(deck), random_device{});
    copy(begin(deck), end(deck), ostream_iterator<int>{cout, "\n"});
}
