#include <mutation.h>
#include <random.h>
#include <cassert>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdlib>

typedef Individual P;

void mutate_transpose(int n, Individual & p){
  for(int i = 0; i < n; i++){
    std::pair<int, int> ab = randpair(p.size());
    p.swap(ab.first, ab.second);
  }
}


void RandomPermutationCrossover::operator () (Individual & a, Crossover & c){
	const int n = a.size();
	P randPerm(n);
	std::vector<int> vConst;
	std::vector<int> vDiff;

	for(int i = 0; i < n; i++){

		if(randbool(Constancy)) vConst.push_back(i);
		else vDiff.push_back(i);
	}

	std::random_shuffle ( vDiff.begin(), vDiff.end() );

	unsigned int vc = 0;
	unsigned int vd = 0;
	for(int i = 0; i < n; i++){
		if(vc < vConst.size() && vConst[vc] == i){
			randPerm[i] = vConst[vc];
			vc++;
		}
		else{
			randPerm[i] = vDiff[vd];
			vd++;
		}
	}


	Crossover::Result r = c(a, randPerm);

	if( r.first > r.second ){
		std::copy(r.first.begin(), r.first.end(), a.begin());
	}
	else{
		std::copy(r.second.begin(), r.second.end(), a.begin());
	}


	assert( a.valid() );
}



void PermutationShift::operator () (Individual & a, Crossover & c){
	const int n = a.size();
	
	const int shift = Shift + randint(1, 2*Shift);

	P shiftedPerm(n);

	for(int i = 0; i < n; i++){
		int x = (i + shift >=  n) ? (i+shift - n) : (i+shift)
		shiftedPerm[i] = a[x];
	}

	std::copy(shiftedPerm.begin(), shiftedPerm.end(), a.begin());

	assert( a.valid() );

}


