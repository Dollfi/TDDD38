// Shows some usages of std::map and std::set from
// the seminar on apr 19

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <string>
using namespace std;

// a function that reads all values in cin and stores them in a vector
// the values are then sorted and all duplicates are removed. The
// values are then printed separated by spaces
void print_unique_sorted_vector()
{
	// read using istream_iterator
	vector<int> vals{ istream_iterator<int>{cin}, istream_iterator<int>{} };
	sort(begin(vals), end(vals));
	// unique will not alter the size of the vector. All found duplicates
	// are moved to the end and the returned iterator refers to the first
	// duplicate found.
	auto it = unique(begin(vals), end(vals));
	// vector::erase knows how to decrease the size
	vals.erase(it, end(vals));
	copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "});
}

// The implementation can be improved by using a better container.
// std::set will store unique values in sorted order - perfect!
void print_unique_sorted_set()
{
	set<int> vals{istream_iterator<int>{cin}, istream_iterator<int>{}};
	copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "});
}

// a new task - create a frequency table of characters using a map.
void count_chars()
{
	map<char, int> counter;
	// the index operator will insert a new value if the key isn't found,
	// always returns a reference to the matched value	
	for_each(istream_iterator<char>{cin}, istream_iterator<char>{}, 
			[&counter] (char c) {++counter[c]; }
	);
	// can't use ostream_iterator. It requires that the output operator
	// is found by ADL, which usually requires that it is in namespace std
	// since all arguments to the operator (ostream and pair) is in std.
	for_each(begin(counter), end(counter), 
			[](pair<char, int> const & p)
			{
				cout << p.first << ": " << p.second;
			}
	);
}

// The main program takes a command followed by numerical values. Will print
// a value depending on the command. Examples:
//   a.out sum 1 2 3 4 5.6 => 15.6
//   a.out max 1 2 -5 19   => 19
int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		cerr << "Wrong number of arguments\n";
		return 1;
	}
	// preallocate a vector to store all numeric values
	vector<double> values(argc - 2);

	// use C pointer arithmetics to create a vector of string to store 
	// the numerical values (not program name or command)
	vector<string> args{ argv + 2, argv + argc };
	
	// use transform to create a vector<double> from the strings
	transform(begin(args), end(args), begin(values),
		[](string const & s) { return stod(s); });

	// using transform without the vector<string>
	//transform(argv + 2, argv + argc, begin(values),
		//[](string const & s) { return stod(s); });

	// storing a lambda (closure object) in a variable. Please note
	// that fun has an unnamed, unique type.
	auto fun = [](vector<double> const & vals)
	{
		return accumulate(begin(vals), end(vals), 0.0);
	};

	// a map to associate a string (command name) to a function.
	// std::function is a generic way of storing a reference to some
	// callable object (closure, function object, function pointer etc)
	// Simple initialization with list initialization
	map<string, function<double(vector<double>const&)>> functions
	{
		{"sum", fun },
		{"max", [](vector<double> const & vals)
		{
			return *max_element(begin(vals), end(vals));
		}}
	};

	// check if the command name is correct
	if (functions.find(argv[1]) == functions.end())
	{
		cerr << "command " << argv[1] << " invalid\n";
		return 2;
	}

	// call the appropriate function
	cout << "Value: " << functions[argv[1]](values) << endl;
}
