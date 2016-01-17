#include <iostream>
using namespace std;

int main()
{
  string s;
  while ( cin >> s )
  {
    cout << s << endl;
  }
  /* Do NOT use the error bits as loop condition 
  while ( cin.good() )
  {
    cin >> s;
    cout << s << endl;
  }
  */

}
