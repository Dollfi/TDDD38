// some stream manipulators

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  cout << fixed << setprecision(2);
  for ( int i {10}; i < 20; ++i )
  {
    cout << left << setw(4) << i
	 << setw(6) << i/10.0 << endl;
  }

  return 0;
}
