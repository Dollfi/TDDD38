/* Program that calculate total sum of each column in a csv file. 
   The input file can have rows with different number of columns */

#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

// Type alias
using row = vector<double>;

vector<row> read_csv_file(istream &);
row calculate_sums(vector<row> const &);
void print(row const &, ostream & = cout);

int main(int argc, char const * argv[])
{
  if ( argc != 2 )
  {
    cerr << "Usage: " << argv[0] << " \"input file\"\n";
    return 1;
  }

  ifstream input_file { argv[1] };
  if ( !input_file )
  {
    cerr << "File \"" << argv[1] << "\" couldn't be opened\n";
    return 2;
  }
  auto numbers = read_csv_file(input_file);
  auto sums = calculate_sums(numbers);
  print(sums);

  return 0;
}

row parse_row(string const & r)
{
  row res;
  istringstream iss{r};
  string word;
  
  while ( getline(iss, word, ',') )
  {
    try
    {
      // stod throws invalid_argument if word can't be parsed as double
      res.push_back(stod(word));
    }
    catch (std::invalid_argument)
    {}
  }
  return res;
}

// Alternative to parse_row without stod
row parse_row_double(string const & r)
{
  row res;
  istringstream iss{r};
  double val;
  while (true)
  {
    while ( iss >> val )
    {
      res.push_back(val);
      iss.ignore();
    }
    
    if ( iss.fail() )
    {
      iss.clear();
      iss.ignore();
    }
    else
      break;
  }
  return res;
}

vector<row> read_csv_file(istream & is)
{
  string line;
  vector<row> rows;
  while ( getline(is, line) )
  {
    rows.push_back( parse_row(line) );
  }
  return rows;
}

int columns(vector<row> const & rows)
{
  size_t cols {};
  for ( auto const & r : rows )
  {
    cols = std::max(r.size(), cols);
  }
  return cols;
}
row calculate_sums(vector<row> const & rows)
{
  row sums (columns(rows));
  for ( auto const & r : rows )
  {
    for ( size_t i {}; i < r.size(); ++i )
    {
      sums.at(i) += r.at(i);
    }
  }
  return sums;
}
void print(row const & sums, ostream & os)
{
  // store the old flags of the stream to
  // reset the state after our operations
  auto flags = os.flags();
  os << fixed << setprecision(2);
  for ( auto i : sums )
  {
    os << setw(10) << i;
  }
  os << endl;
  os.flags(flags);
}
