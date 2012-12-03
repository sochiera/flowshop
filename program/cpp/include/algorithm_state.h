#ifndef ALGORITHM_STATE_H_
#define ALGORITHM_STATE_H_

#include <vector>
#include <population.h>

class AlgorithmState{
  public:
    AlgorithmState();
    int iteration() const; 
    void inc_iteration(); 
    Population & population();   
    const Population & population() const;
    const Individual Best() const;
    void SetBest(Individual Ind);
    int isBestSet() const; 

  private:
    Population population_;
    int iteration_;
    Individual best_found_;
};

#endif
