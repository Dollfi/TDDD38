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
    transform(begin(card_values), end(card_values), begin(card_values), 
            [](int card){
             if ( card > 10 )
             {
                return 10;
             }
             return card;});
    vector<int> sums (v.size());
    partial_sum(begin(card_values), end(card_values), begin(sums));
    auto it = lower_bound(begin(sums), end(sums), 17);
    // auto it = find_if(begin(sums), end(sums), [](int v){return v > 16;});
    auto N { it - begin(sums) };
    copy(begin(v), begin(v)+N+1, ostream_iterator<int>{cout, " "});
}
