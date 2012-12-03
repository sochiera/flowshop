#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <local_search.h>

typedef Individual P;

P LocalSearch::insert(const P * Ind, const int elemIdx, const int i){
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


P transpose(const P * Ind, int a, int b){

  	if(a > b){
    	std::swap(a,b);
	}
	Individual J(*Ind);
  	std::swap(J[a],J[b]);
  	return J;
}  


LocalSearch::Result SimulatedAnnealing::operator () (const P * Ind){
	Result r;
	r.first = *Ind;
	r.second = *Ind;
	return r;
}


GradualSinglePointOperator::GradualSinglePointOperator (double effectiveness){
	Effectiveness = effectiveness;
}

LocalSearch::Result GradualSinglePointOperator::operator () (const P * Ind){
	P min(*Ind);
	std::vector<P> Betters;
	const int n = min.size();
	Betters.push_back(min);
	for(int e = 0; e < n; e++){
		for(int j = 0; j < n; j++){
			P temp = insert(Ind, e, j);
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
      std::vector<Individual *> & children){

	GradualSinglePointOperator ls(0.87);
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = ls(children[i]);
		*(children[i]) = r.first;
		if(state.isBestSet() && r.second < state.Best()) state.SetBest(r.second);
	}


}