#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <individual.h>
#include <algorithm_state.h>
#include <cstdlib>

typedef Individual P;


class LocalSearch{
	virtual operator() 
      (P * Ind) = 0;

  public:
    P transpose(const P * Ind, int a, int b){
      const int n = Ind->size();
      if(a > b){
        std::swap(a,b);
      }

      Individual J(*Ind);
      std::swap(J[a],J[b]);
      return J;
    }  

    P insert(const P * Ind, const int elemIdx, const int i){
      P t(*Ind);
      int x = t[elemIdx];
      if(elemIdx > i){
        for(int j = e; j > i; j--){
          t[j] = t[j-1];
        }
        t[i] = x;
      }
      if(elemIdx < i){
        for(int j = e; j < i; j++){
          t[j] = t[j+1];
        }
        t[i] = x;
      }

      return t;
    }
};


class SimulatedAnnealing : public LocalSearch{

  public:  
    P operator() 
      (P * a);

};


class SinglePointOperator : public LocalSearch{

  public:  
    P operator() 
      (P * a);

};


class LocalSearchStrategy{
  public:
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
};


#endif
  

