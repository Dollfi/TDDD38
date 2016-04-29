#include "Timer.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <functional>
#include <string>
#include <deque>
#include <list>
using namespace std;


namespace seminar_3
{
    // a constant seed value to get the same data for each test
    // constexpr can be calculated at compile-time. Can be used on
    // functions that are simple enough as well
    constexpr const size_t random_seed{ 42 };
	
    // Inserts a value in a given container in sorted order. Uses a standard
    // linear search unless passed the optimized flag.
	template <typename Container>
	void insert_sorted(Container & c,
		typename Container::value_type const & val,
		bool optimized)
	{
		typename Container::iterator it;
		if (optimized)
		{
            // binary search (not efficient for non-random access iterators)
			it = lower_bound(begin(c), end(c), val);
		}
		else
		{
			it = find_if(begin(c), end(c),
				[val](auto const & v) {return v >= val; });
		}
		c.insert(it, val);
	}
    // a separate namespace to make sure that we won't get any name clashes
	namespace detail
	{
        // uses expression SFINAE to remove the function from overload resolution
        // if c doesn't have a push_back member function
/*		template <typename Container>
		auto insert_first(Container & c,
			typename Container::value_type const & val, int)
		-> decltype(c.push_back(val), void())
		{
			c.push_front(val);
		}
		*/
        // using enable_if to get the same (or at least similar) behavior.
		// enable_if_t<...> is shorthand for "typename enable_if<...>::type"
        template <typename Container>
		enable_if_t<
			is_member_function_pointer<decltype(&Container::push_front) >::value>
		insert_first(Container & c,
			typename Container::value_type const & val, int)
		{
			c.push_front(val);
		}

		template <typename Container>
		void insert_first(Container & c,
			typename Container::value_type const & val, long)
		{
			c.insert(begin(c), val);
		}
	}
	template <typename Container>
	void insert_first(Container & c, typename Container::value_type const & val)
	{
        // calling a helper function in the detail namespace. The extra zero is passed
        // to guard against ambigous overloads. If both overloads exists, the push_front
        // variant is called since 0 is an int literal. If only the insert variant is left
        // after overload resolution, the 0 is promoted to long.
		detail::insert_first(c, val, 0);
	}

	namespace detail
	{
		template <typename Container>
		enable_if_t<is_member_function_pointer<decltype(&Container::push_back)>::value>
		insert_last(Container & c,
			typename Container::value_type const & val, int)
		{
			c.push_back(val);
		}

		template <typename Container>
		void insert_last(Container & c,
			typename Container::value_type const & val,
			long)
		{
			c.insert(end(c), val);
		}
	}
	template <typename Container>
	void insert_last(Container & c, typename Container::value_type const & val)
	{
		detail::insert_last(c, val, 0);
	}

	namespace detail
	{
		template <typename Container>
		auto remove_first(Container & c, int)
        -> decltype(c.pop_front(), void())
		{
			c.pop_front();
		}
		template <typename Container>
		void remove_first(Container & c, long)
		{
			c.erase(begin(c));
		}

	}
	template <typename Container>
	void remove_first(Container & c)
	{
		detail::remove_first(c, 0);
	}

	template <typename Container>
	void remove_last(Container & c)
	{
		c.pop_back();
	}


	template <typename Container>
	void remove_index(Container & c, size_t s)
	{
		c.erase(next(begin(c), s));
	}

	// anonymous namespace, the declarations are only seen in this file
	namespace
	{
		// seed a Mersenne-twister engine from a random number
		// std::mt19937 random_engine{ std::random_device{}() };

		// magic number seed (to get the same test sequence)
		std::mt19937 random_engine{ random_seed };
	}

	size_t random_value(size_t min, size_t max)
	{
		uniform_int_distribution<size_t> dist{ min, max };
        // passing a generator to a distribution generates a random number according
        // to the given distribution. In this case we'll get an int (size_t) in the
        // range [min, max] (inclusive)
		return dist(random_engine);
	}

	template <typename Container>
	size_t random_index(Container const & c)
	{
		return random_value(0, c.size()-1);
	}
}

namespace
{
    // test functions.
		template <typename Container>
	void insert_sorted_remove_random(vector<int> const & test_data, bool b)
		{
		using namespace seminar_3;
		Container vals;
		for (auto i : test_data)
		{
			insert_sorted(vals, i, b);
		}
		while (!vals.empty())
		{
			remove_index(vals, random_index(vals));
		}
	}
	template <typename Container>
	void insert_sorted_remove_random(vector<int> const & test_data)
	{
		insert_sorted_remove_random<Container>(test_data, false);

	}

	template <typename Container>
	void insert_start_remove_start(size_t n)
	{
		Container c;
		for (; n; --n)
		{
			seminar_3::insert_first(c, 1);
		}
		while ( !c.empty() )
		{
			seminar_3::remove_first(c);
		}
	}
	template <typename Container>
	void insert_start_remove_last(size_t n)
	{
		Container c;
		for (; n; --n)
		{
			seminar_3::insert_first(c, 1);
		}
		while ( !c.empty() )
		{
			seminar_3::remove_last(c);
		}
	}
	template <typename Container>
	void insert_last_remove_start(size_t n)
	{
		Container c;
		for (; n; --n)
		{
			seminar_3::insert_last(c, 1);
		}
		while ( !c.empty() )
		{
			seminar_3::remove_first(c);
		}
	}
	template <typename Container>
	void insert_last_remove_last(size_t n)
	{
		Container c;
		for (; n; --n)
		{
			seminar_3::insert_last(c, 1);
		}
		while ( !c.empty() )
		{
			seminar_3::remove_last(c);
		}
	}
}


namespace
{
    // a simple function to test the mean runtime of a given function f.
	template <typename Fun>
	void run_test(Fun f, string const & desc, int iterations=5)
	{
		Timer t; // see Timer.h/cc
		chrono::microseconds tot{};
		cout << desc;
		clog << " [" << iterations << " iterations]\n";
		for (int i {}; i < iterations; ++i)
		{
			clog << "\t" << i+1 << ": ";
			t.tick(); // reset the clock

			f(); // call the function
			
			auto time = t.tock(); // count number of microseconds since reset
			tot += time;
			clog << time.count() << "us\n";
		}
		clog << "\n\tTotal: " << tot.count()
			<< "\n\tMean:  ";
        // using the new digit separator ' to get more readable code. It can be placed
        // between numbers in a numerical literal (see §2.9 in the standard for full grammar)
		cout << tot.count() / iterations / 1'000'000.0 << 's' << endl;
	}
	
}

int main(int argc, char* argv[])
{
    using namespace seminar_3;
	// use either the first command-line argument or 10000 as number of values.
    size_t values{ argc>1 ? stoul(argv[1]) : 10000 };

	cout << "Running tests with N=" << values;

	// declarations for the randomized tests
    auto repeat_frequency{ argc > 2 ? stod(argv[2]) : 0.1 };
	auto max_val = static_cast<size_t>(values*repeat_frequency);
	vector<int> test_data(values);
    // generate will call a function (without arguments) for each element in a given range 
    // and assign the current element the return value from the function. 
    // bind sets fixed values for a given function. In this case, we create a new function
    // that takes zero arguments and passes 0 as first and max_val as second argument to
    // random_value. 
    // bind can also be used with placeholders to just bind some arguments:
    //   auto fun = bind(random_value, 3, placeholders::_1); 
    //   fun(14) => gives a random value in range [3,14]
    //   the first argument to the generated function is passed as second argument to 
    //   random_value (and the first is fixed as 3)
    generate(begin(test_data), end(test_data), bind(random_value, 0, max_val));

    cout << "Insert random numbers in order. Remove randomly.\n\n";
    // re-seed the engine for each test case to get the same sequence
    random_engine.seed(random_seed);
	run_test([test_data] {insert_sorted_remove_random<vector<int>>(test_data); }, "vector");
	random_engine.seed(random_seed);
	run_test([test_data] {insert_sorted_remove_random<deque<int>>(test_data); }, "deque");
	random_engine.seed(random_seed);
	run_test([test_data] {insert_sorted_remove_random<list<int>>(test_data); }, "list");


	cout << "Insert random numbers in order with lower_bound. Remove randomly.\n\n";
	random_engine.seed(random_seed);
	run_test([test_data] {insert_sorted_remove_random<vector<int>>(test_data, true); }, "vector");
	random_engine.seed(random_seed);
	run_test([test_data] {insert_sorted_remove_random<deque<int>>(test_data, true); }, "deque");
	random_engine.seed(random_seed);
	run_test([test_data] {insert_sorted_remove_random<list<int>>(test_data, true); }, "list");

	cout << "Insert numbers in beginning, remove from beginning.\n\n";
	run_test([values] {insert_start_remove_start<vector<int>>(values); }, "vector");
	run_test([values] {insert_start_remove_start<deque<int>>(values); }, "deque");
	run_test([values] {insert_start_remove_start<list<int>>(values); }, "list");

	cout << "Insert numbers in beginning, remove from end.\n\n";
	run_test([values] {insert_start_remove_last<vector<int>>(values); }, "vector");
	run_test([values] {insert_start_remove_last<deque<int>>(values); }, "deque");
	run_test([values] {insert_start_remove_last<list<int>>(values); }, "list");

	cout << "Insert numbers at end, remove from end.\n\n";
	run_test([values] {insert_last_remove_last<vector<int>>(values); }, "vector");
	run_test([values] {insert_last_remove_last<deque<int>>(values); }, "deque");
	run_test([values] {insert_last_remove_last<list<int>>(values); }, "list");

	cout << "Insert numbers at end, remove from beginning.\n\n";
	run_test([values] {insert_last_remove_start<vector<int>>(values); }, "vector");
	run_test([values] {insert_last_remove_start<deque<int>>(values); }, "deque");
	run_test([values] {insert_last_remove_start<list<int>>(values); }, "list");


	return 0;
}

