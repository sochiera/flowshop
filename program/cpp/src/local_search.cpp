#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <local_search.h>

typedef Individual P;


P SimulatedAnnealing::operator () (const P * Ind){
	return *Ind;
}


P SinglePointOperator::operator () (const P * Ind){
	P min(*Ind);
	const int n = min.size();
	for(int e = 0; e < n; e++){
		for(int j = 0; j < n; j++){
			P temp = insert(Ind, e, j);
			if(p < min){
				min = p;
			}
		}
	}
	return min;
}


