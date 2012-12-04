#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <local_search.h>
#include <iostream>

typedef Individual P;

P LocalSearch::insert(const P * Ind, int elemIdx, int i) const{
  P t(*Ind);
  int x = t[elemIdx];
  if(elemIdx > i){
    for(int j = elemIdx; j > i; j--){
      t[j] = t[j-1];
    }
    t[i] = x;
  }
  if(elemIdx < i){
    for(int j = elemIdx; j < i; j++){
      t[j] = t[j+1];
    }
    t[i] = x;
  }
  return t;
}


LocalSearch::Result SimulatedAnnealing::operator () 
  (const P * Ind) const
{
	Result r;
	r.first = *Ind;
	r.second = *Ind;
	return r;
}


LocalSearch::Result GradualSinglePointOperator::operator () 
  (const P * Ind) const
{
	P min(*Ind);
	std::vector<P> Betters;
	const int n = min.size();
	Betters.push_back(min);
	for(int e = 0; e < n; e++){
		for(int j = 0; j < n; j++){
			P temp = insert(Ind, e, j);
			std::cout << temp << std::endl;
			if(temp < min){
				Betters.push_back(temp);
			}
		}
	}
	std::sort(Betters.begin(), Betters.end());
	Result r;
	int s = (int)(((float)(Betters.size()))*Effectiveness);
	r.first = Betters[s];
	r.second = Betters[0];
	return r;
}


void SimpleStrategy::operator () (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = local_search_(children[i]);
		*(children[i]) = r.first;
    state.set_best_if_better(r.second);
	}
}
