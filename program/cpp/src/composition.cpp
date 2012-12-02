#include <crossover.h>
#include <algorithm>
#include <random.h>
#include <cassert>


typedef Individual P;



Crossover::Result Composition::operator () (const P & mom, const P & dad){
  Crossover::Result r;
  r.first = cross(mom, dad);
  r.second = cross(dad, mom);
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