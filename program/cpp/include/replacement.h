#ifndef REPLACEMENT_H_
#define REPLACEMENT_H_

#include <algorithm_state.h>

class ReplacementStrategy{
  public:
    virtual ~ReplacementStrategy(){}

    // it should delete children that go into population 
    // from children list
    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const; 
};

#endif
