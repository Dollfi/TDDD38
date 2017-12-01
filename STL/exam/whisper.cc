#include <cctype>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>
#include <functional>
#include <random>
using namespace std;

int main()
{
    // Step 1
    vector<string> words { istream_iterator<string>{cin},
                           istream_iterator<string>{} };
    // Step 2:
    //   a: create a vector of indices to words using iota
    //   b: shuffle the vector
    //   c: sort the first seventh of the vector in descending order
    //      so that the indeces are correct after removing
    //   d: remove the indices in words according to the first
    //      seventh in our index vector
    vector<size_t> indices (words.size());
    // Different ways of using generate to fill indices with values
    /*    int val {};
     // Using global variable
    generate(begin(indices), end(indices), [&val]{return val++;});
     // Using data member in closure object
    generate(begin(indices), end(indices), [val=0]()mutable{return val++;});
    // using a static variable inside function call operator
    generate(begin(indices), end(indices), 
            []{
            static int val {};
            return val++;});
  */
    iota(begin(indices), end(indices), 0);
    shuffle(begin(indices), end(indices), random_device{});
    size_t seventh { words.size() / 7};
    sort(begin(indices), begin(indices)+seventh, greater<>{});
    for_each(begin(indices), begin(indices)+seventh,
            [&words](size_t idx) { words.erase(words.begin()+idx); });
    
    // Step 3:
    transform(begin(words), end(words), begin(words),
            [](string s)
            {
                //transform(begin(s), end(s), begin(s), [](char c){return tolower(c);});
                // C has no namespaces, that tolower is in the global
                // namespace
                transform(begin(s), end(s), begin(s), ::tolower);
                if ( s.size() > 7 )
                {
                    // find_last_of gives index of last character in s
                    // that matches any in the given string
                    size_t last_vowel { s.find_last_of("aeiouy") };
                    if ( last_vowel != string::npos )
                    {
                        // removes all elements from last_vowel to end
                        s.erase(last_vowel);
                    }
                }
                return s;
            });
    // step 4
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
}
