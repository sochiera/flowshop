#ifndef PARENT_SELECTOR_H_
#define PARENT_SELECTOR_H_

#include <vector>
#include <individual.h>
#include <population.h>
#include <algorithm_state.h>

class ParentSelector{
  public:
    virtual ~ParentSelector(){}
    virtual std::vector<const Individual *> 
      operator() (const AlgorithmState & state) const = 0;
};

#endif
