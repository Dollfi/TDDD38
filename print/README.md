# print

A short example on variadic templates and expression SFINAE
Requires a C++14-compliant compiler

There are three different implementations.

 * The basic one has different specializations of `print` for each type.
 * `print-v2.tcc` has an inline namespace with specializations of a template function `print_impl`.
 * `print-fold.tcc` uses *fold expressions* (unary right fold over the comma operator) to get rid of the recursive calls.
