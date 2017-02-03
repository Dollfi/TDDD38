#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
using namespace std;

struct Negator
{

    void operator()(int & val)
    {
        if ( val < 0 )
        {
            val = abs(val);
            count++;
        }
    }

int count {};
};


int main(int argc, char * argv[])
{
    // standard command-line argument handling...
    // Step 1
    if ( argc != 2 )
    {
        cerr << "Call as \"" << argv[0] << "\" Filename\n";
        return 1;
    }
    // step 2
    ifstream ifs { argv[1] };
    if  ( ! ifs ) // are any error flags set?
    {
        cerr << "Faulty file\n";
        return 2;
    }
    // step 3
    vector<int> vals { istream_iterator<int>{ifs}, istream_iterator<int>{} };
    /*
      vector<int> vals;
      copy(istream_iterator<int>{ifs}, istream_iterator<int>{},
           back_inserter(v));
    */
    // Step 4
    cout << "Numbers read:\n";
    copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "} );
    cout << '\n' << endl;

    // step 5
    //   With function object
    auto fun = for_each(begin(vals), end(vals), Negator{});
    int count { fun.count };
    // with lambda
    /*  int count {};
        for_each(begin(vals), end(vals), [&count](int & val){
        if ( val < 0 )
        {
            count++;
            val = abs(val);
        }});
    */
    // separate the two tasks
    //auto count { count_if(begin(vals), end(vals), [](int v){return v<0;}) };
    //auto count { count_if(begin(vals), end(vals), signbit<int>) };
    //transform(begin(vals), end(vals), begin(vals), ::abs);
    cout << count << " negative values where found\n"
         << "\nAfter making all the numbers positive:\n";
    // step 6
    copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "} );
    cout << '\n' << endl;
    
    // step 7
    partial_sort(begin(vals), begin(vals)+5, end(vals));
    cout << "Five smallest numbers:\n";
    copy(begin(vals), next(begin(vals),5), ostream_iterator<int>{cout, " "});
    cout << '\n' << endl;
    
    // step 8
    vals.erase(begin(vals), begin(vals)+5);
    cout << "Five smallest numbers removed:\n";
     copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "} );
    cout << '\n' << endl;
 }
