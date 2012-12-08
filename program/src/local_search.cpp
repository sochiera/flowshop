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
  t.insert(elemIdx, i);
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
			temp.set_cost(instance_.evaluate(&temp));
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



LocalSearch::Result SinglePointOperator::operator ()
  (const P * ind) const
{
  const int n = ind->size();
  int best_k = 0;
  int best_j = 0;
  int best_val = 1000000000;
  
  for(int k = 0; k < n; k++){
    P father(*ind);
    father.insert(k, n-1);
    std::vector<int> costs = instance_.evaluate_all_insertions(&father);
    
    int bi = 0;
    for(unsigned int i = 1; i < costs.size(); i++)
      bi = (costs[bi] < costs[i]) ? bi : i;

    if(costs[bi] < best_val){
      best_val = costs[bi];
      best_k = k;
      best_j = bi;
    }
  }

  P res(*ind);
  res.insert(best_k, n-1);
  res.insert(n-1, best_j);
  res.set_cost(best_val);
  return std::make_pair(res, res);
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
