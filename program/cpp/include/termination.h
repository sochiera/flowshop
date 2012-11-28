#ifndef TERMINATION_CONDITION_H_
#define TERMINATION_CONDITION_H_

#include <algorithm_state.h>

class TerminationCondition{
  public:
    virtual ~TerminationCondition(){};
    virtual bool operator() (const AlgorithmState & state) const = 0;
};


class NumIterationsCondition{
  public:
    NumIterationsCondition(int max_iterations);
    virtual bool operator() (const AlgorithmState & state) const;

  private:
    int max_iterations_;
};

#endif
