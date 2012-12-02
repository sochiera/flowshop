#include <crossover.h>
#include <random.h>
#include <algorithm>


std::vector<Individual *> RandomCrossoverStrategy::operator() (
  const AlgorithmState & state, 
  std::vector<const Individual *> & parents) const
{
  std::vector<Individual *> children;
  const Population & P = state.population();

  for(int i = 0; i < P.size(); i++){
    std::pair<int, int> ab = randpair(P.size());
    if(randbool(0.5))
      std::swap(ab.first, ab.second);

    Crossover::Result r = cross_(P[ab.first], P[ab.second]); 
    Individual * a = new Individual(r.first);
    Individual * b = new Individual(r.second);
    children.push_back(a);
    children.push_back(b);
  }

  return children;
}

