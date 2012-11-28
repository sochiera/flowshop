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

  private:
    Population population_;
    int iteration_;
};

#endif
