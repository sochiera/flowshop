#ifndef REPLACEMENT_H_
#define REPLACEMENT_H_

#include <algorithm_state.h>

class ReplacementStrategy{
  public:
    virtual ~ReplacementStrategy(){}

    virtual void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const = 0; 
};



class BestOfReplacement : public ReplacementStrategy{
  public:
    void operator() (AlgorithmState & state, 
      std::vector<Individual *> & children) const;
};

#endif
