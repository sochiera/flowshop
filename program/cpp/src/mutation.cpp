#include <mutation.h>
#include <random.h>

using namespace genetic;

void genetic::mutate_transpose(int n, Permutation & p){
  for(int i = 0; i < n; i++){
    std::pair<int, int> ab = randpair(p.size());
    p.swap(ab.first, ab.second);
  }
}
