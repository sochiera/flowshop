#ifndef MUTATION_H_
#define MUTATION_H_

#include <individual.h>
#include <algorithm_state.h>

class Mutation{

};


class MutationStrategy{
  public:
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
};


#endif
  
