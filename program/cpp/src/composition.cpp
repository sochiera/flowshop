#include <crossover.h>
#include <algorithm>
#include <random.h>


typedef Individual P;



Crossover::Result Composition::operator () (const P & mom, const P & dad){
  Result r;
  std::pair<int, int> ab = randpair(mom.size()); 
  r.first = cross(ab.first, ab.second, mom, dad);
  r.second = cross(ab.first, ab.second, dad, mom);
  return r;
}



P Composition::cross(const P & mom, const P & dad){
  const int n = mom.size();
  P child(n);

  for(int i = 0; i < n; i++){
    child[i] = mom[dad[i]];
  }

  assert(child.valid());

  return child;
}
