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

    const int best() const;
    void set_best_if_better(const Individual & Ind);

  private:
    Population population_;
    int iteration_;
    int best_solution_;
};

#endif
