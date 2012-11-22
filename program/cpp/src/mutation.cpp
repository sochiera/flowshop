#include <mutation.h>
#include <random.h>


void mutate_transpose(int n, Permutation & p){
  for(int i = 0; i < n; i++){
    std::pair<int, int> ab = randpair(p.size());
    p.swap(ab.first, ab.second);
  }
}
