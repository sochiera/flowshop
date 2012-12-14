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

    struct Result{
      Individual first;
      Individual second;
      int num_processed;

      Result(const Individual & f, const Individual & s, int n) 
        : first(f), second(s), num_processed(n) {}

      Result() : num_processed(0) {}
    };


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


class TabooSearch : public LocalSearch{
  public:  
    TabooSearch(const FlowshopInstance & instance, int numIterations, unsigned int tabooSize)
      : LocalSearch(instance), NumIterations(numIterations), TabooSize(tabooSize) {}

    Result operator() (const Individual * a) const;

  private:

    int NumIterations;
    unsigned int TabooSize;
    static const int maxCost = 100000;
};


class GradualSinglePointOperator : public LocalSearch{
  public:  
    GradualSinglePointOperator(const FlowshopInstance & instance, double effectiveness = 1.0)
      : LocalSearch(instance), Effectiveness(effectiveness) {} 
      
    Result operator() (const Individual * a) const;

  private:
    double Effectiveness;
};



class SinglePointOperator : public LocalSearch{
  public:
    SinglePointOperator(const FlowshopInstance & instance)
      : LocalSearch(instance) {}

    Result operator() (const Individual * a) const;
};









class LocalSearchStrategy{
  public:
    LocalSearchStrategy(const LocalSearch & ls)
      : local_search_(ls) {}
    
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
 
  protected:
    const LocalSearch & local_search_;
};


class LaziestStrategy : public LocalSearchStrategy{
  public:
    LaziestStrategy(const LocalSearch & ls)
      : LocalSearchStrategy(ls) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const {}
};


class SimpleStrategy : public LocalSearchStrategy{
  public:
    SimpleStrategy(const LocalSearch & local) :
      LocalSearchStrategy(local) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
};


class ParallelSearchStrategy : public LocalSearchStrategy{
  public: 
    ParallelSearchStrategy(const LocalSearch & local) 
      : LocalSearchStrategy(local) {}

    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
};

#endif
