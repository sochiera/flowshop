#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <local_search.h>
#include <iostream>
#include <bitset>
#include <queue>

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


LocalSearch::Result TabooSearch::operator () 
  (const P * Ind) const
{


	Individual x(*Ind);
	int bestVal = instance_.evaluate(&x);

	const int n = x.size();
	std::bitset<maxCost> * taboo = new std::bitset<maxCost>;
	std::vector<int> * _M = new std::vector<int>;
	std::vector<std::pair<int, std::pair<int, int> > > * M = new std::vector<std::pair<int, std::pair<int, int> > >;
	std::queue<int> * q = new std::queue<int>;

	Result r;
	r.second = x;

	for (int i = 0; i < NumIterations; ++i)
	{
		M->clear();
		for(int j = 0; j < n; j++){
			Individual temp(x);
			temp.insert(j, n-1);
			_M->clear();
			*_M = instance_.evaluate_all_insertions(&temp);
		
			for (unsigned int k = 0; k < _M->size(); ++k){
				std::pair<int, int> change(j, k);
				std::pair<int, std::pair<int, int> >  p((*_M)[k], change);
				M->push_back(p);
			}
		}
		std::sort(M->begin(), M->end());

		if(bestVal > (*M)[0].first){
			r.second = x;
			r.second.insert(((*M)[0]).second.first, ((*M)[0]).second.second);
			bestVal = (*M)[0].first;
		}

		bool flague = false;
		for (unsigned int i = 0; i < M->size(); ++i){
			if(!flague && !(*taboo)[(*M)[i].first]){
				x.insert(((*M)[i]).second.first, ((*M)[i]).second.second);
				flague = true;
			}
			if(!(*taboo)[(*M)[i].first]){
				q->push(i);
				(*taboo)[i] = 1;
				if(q->size() > TabooSize){
					(*taboo)[q->front()] = 0;
					q->pop();
				}
			}
		}
	}
	delete q;
	delete taboo;
	delete M;
	delete _M;
	r.first = x;
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


void SimpleStrategy::operator () (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = local_search_(children[i]);
		*(children[i]) = r.first;
    state.set_best_if_better(r.second);
	}
}
