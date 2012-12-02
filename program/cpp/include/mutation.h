#ifndef MUTATION_H_
#define MUTATION_H_

#include <individual.h>
#include <algorithm_state.h>
#include <crossover.h>

class Mutation{
	virtual void operator() 
      (Individual * a) = 0;

};


class RandomPermutationCrossover : public Mutation{

  public:  
  	static const double Constancy = 0.75;
    virtual void operator() 
      (Individual * a);


};


class PermutationShift : public Mutation{

  public:  
  	static const double Shift = 0.15;
    virtual void operator() 
      (Individual * a);


};



class MutationStrategy{
  public:
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0;
};


#endif
  

