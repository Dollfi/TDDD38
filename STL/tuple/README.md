# Tuple
A seminar on ```std::tuple``` and some new features in C++17 (mostly structured binding and constexpr-if). 

[test_tuple.cc](test_tuple.cc) shows some of the interface of tuple. [my_tuple.h](my_tuple.h) is a variant of gcc's implementation of tuple used to show some of the template techniques available in the language.

[exam_results.cc](exam_results.cc) is a possible solution to an old exam question where a file ([STUDENT_RESULTS.TXT](STUDENT_RESULTS.TXT)) with some results for students from some exam. The tast was to read, sort and print the results with a given format, only using the stl (in main).
Here we use ```std::tuple``` to implement ```operator<``` for our own class type. We then expandend the problem to also add support for structured binding to our class so that the user can get access to data in a nice way. This is implemented in both C++17, C++14 and C++98 (even though structured binding of course only works for 17).
