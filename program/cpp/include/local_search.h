#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <individual.h>
#include <algorithm_state.h>
#include <cstdlib>

class LocalSearch{
	virtual operator() 
      (Individual & a) = 0;

  public:
    Individual transpose(Individual I, int a, int b){
      const int n = I.size();
      if(a > b){
        std::swap(a,b);
      }

      Individual J(I);
      std::swap(J[a],J[b]);
    }  
};


class SimulatedAnnealing : public LocalSearch{

  public:  
    SimulatedAnnealing(int step = 0, );
    Individual operator() 
      (Individual & a);

  private:
    
};



class LocalSearchStrategy{
  public:
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
};


#endif
  

