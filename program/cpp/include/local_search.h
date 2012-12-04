#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <individual.h>
#include <algorithm_state.h>
#include <cstdlib>
#include <instance.h>


class LocalSearch{
  public:
    LocalSearch(const FlowshopInstance & instance)
      : instance_(instance) {};

    typedef std::pair<Individual, Individual> Result;	
    Individual insert(const Individual * Ind, int elemIdx, int i) const;
    virtual Result operator() (const Individual * Ind) const = 0;
  
  protected:
    const FlowshopInstance & instance_;
};



class SimulatedAnnealing : public LocalSearch{
  public:  
    SimulatedAnnealing(const FlowshopInstance & instance)
      : LocalSearch(instance) {}

    Result operator() (const Individual * a) const;
};



class GradualSinglePointOperator : public LocalSearch{
  public:  
    GradualSinglePointOperator(const FlowshopInstance & instance, double effectiveness = 1.0)
      : LocalSearch(instance), Effectiveness(effectiveness) {} 
      
    virtual Result operator() (const Individual * a) const;

  private:
    double Effectiveness;
};



class LocalSearchStrategy{
  public:
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
};


class LaziestStrategy : public LocalSearchStrategy{
  public:
    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const {}
};


class SimpleStrategy : public LocalSearchStrategy{
  public:
    SimpleStrategy(const LocalSearch & local) :
      local_search_(local) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;

  private:
    const LocalSearch & local_search_;
};

#endif
  

