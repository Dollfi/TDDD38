#include <string>
#include <vector>
#include <iostream>
#include <set>
#include "print.h"

using namespace std;

int main()
{
    std::vector<int> a {3,5,7};
    print(a);
    cout << endl;
    print(2, std::vector<int>{2,3,5,6}, "anna", 3.4, "james"s, 'd', std::vector<std::string>{"C++", "Java"}, std::set<float>{4.4, 2.3});
    a.push_back(5);
    cout << endl;
    print(a);
}
