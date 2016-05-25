/*
 * A program to solve a exam-grade problem.
 * The problem in short:
 *  A subway system has two levels of prices, pay for each trip or pay for one day
 *  The cost of a single trip is based on the number of zones travelled (zone 2 to zone 0 costs 3 zones)
 *  There is a file with all travels made by a single person during one day called TRIPS.TXT. Each line 
 *   in that file consists of two integers; the station where the trip started and the ending station. 
 *   A station is represented by a three digit number where the first digit is the zone.
 *
 *  The task is to find whether it is cheapest to buy single tickets or a day card.
 */
#include <iterator>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
using namespace std;

// Has to create an own type, since the input operator won't be found
// by ADL for reading a std::pair<int,int> from an istream. ADL (argument-dependant lookup)
// will only look for candidates in the std namespace since both arguments to the functions
// are declared there. 
struct trip : public pair<int,int> {};

// another solution is to create a simple type to represent a station with instead of int,
/*struct station
{
    int id;
    int zone() const {return id/100;}
};
using trip = pair<station,station>;
*/

istream & operator>>(istream & is, trip & t)
{
    return is >> t.first >> t.second;
}

const int ZONE_PRICE = 12;
const int DAY_PRICE = 120;

int main()
{
    ifstream ifs {"TRIPS.TXT"};
    vector<trip> trips {istream_iterator<trip>{ifs}, istream_iterator<trip>{}};
    vector<int> zones (trips.size());
    transform(begin(trips), end(trips), begin(zones),
            [](trip const & t)
            {
                return 1+abs(t.first/100 - t.second/100);
            });
    auto total = ZONE_PRICE * accumulate(begin(zones), end(zones), 0);
    if (total < DAY_PRICE)
    {
        cout << "You bought single tickets for a total of " << total << "kr" << endl;
    }
    else
    {
        cout << "You bought a day card for a total of " << DAY_PRICE << "kr\n";
    }
}
