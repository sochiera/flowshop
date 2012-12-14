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
      r.num_processed += _M->size();
		
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
		for (unsigned int k = 0; k < M->size(); ++k){
			if(!flague && !(*taboo)[(*M)[k].first]){
				x.insert(((*M)[k]).second.first, ((*M)[k]).second.second);
				flague = true;
				q->push(k);
				(*taboo)[k] = 1;
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
	r.first = r.second;
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
  int processed = 0;
  
  for(int k = 0; k < n; k++){
    P father(*ind);
    father.insert(k, n-1);
    std::vector<int> costs = instance_.evaluate_all_insertions(&father);
    processed += costs.size();
    
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
  return Result(res, res, processed);
}






void SimpleStrategy::operator () (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = local_search_(children[i]);
		*(children[i]) = r.first;
    state.set_best_if_better(r.second);
    state.inc_processed(r.num_processed);
	}
}



void ParallelSearchStrategy::operator () (AlgorithmState & state, 
      std::vector<Individual *> & children) const
{
  #pragma omp parallel for
	for(unsigned int i = 0; i < children.size(); i++){
		LocalSearch::Result r = local_search_(children[i]);
		*(children[i]) = r.first;
    
    #pragma omp critical
    {
      state.set_best_if_better(r.second);
	    state.inc_processed(r.num_processed);
    }
  }
}
