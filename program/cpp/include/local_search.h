#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <individual.h>
#include <algorithm_state.h>
#include <cstdlib>

typedef Individual P;


class LocalSearch{
  public:

    typedef std::pair<Individual, Individual> Result;	

    P transpose(const P * Ind, int a, int b);

    P insert(const P * Ind, const int elemIdx, const int i);

    virtual Result operator() 
      (const P * Ind) = 0;
};


class SimulatedAnnealing : public LocalSearch{

  public:  
    Result operator() 
      (const P * a);

};




class GradualSinglePointOperator : public LocalSearch{

  public:  
    GradualSinglePointOperator(double effectiveness = 1.0);
    virtual Result operator() 
      (const P * a);


  private:
    double Effectiveness;
};


class LocalSearchStrategy{
  public:
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) = 0;
};

class SimpleStrategy : public LocalSearchStrategy{
  public:
    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children);
};

#endif
  

