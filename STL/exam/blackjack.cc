#include <random>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    vector<int> v (52); // parentesis important here
    iota(begin(v), end(v), 1);
    shuffle(begin(v), end(v), random_device{}); // random_shuffle is depricated
    vector<int> card_values;
    transform(begin(v), end(v), back_inserter(card_values),
              [](int card)
              {
                return (card-1) % 13 + 1;
              });
   replace_if(begin(card_values), end(card_values),
              [](int c){return c>10;},
              10);
    vector<int> sums (v.size());
    partial_sum(begin(card_values), end(card_values), begin(sums));
    auto it = lower_bound(begin(sums), end(sums), 17);
    auto N { it - begin(sums) };
    copy_n(begin(v), N+1, ostream_iterator<int>{cout, " "});
}
