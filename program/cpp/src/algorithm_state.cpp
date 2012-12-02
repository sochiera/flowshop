#include <algorithm_state.h>

AlgorithmState::AlgorithmState(){
  iteration_ = 0;  
}

int AlgorithmState::iteration() const{
  return iteration_;
}

void AlgorithmState::inc_iteration() {
  iteration_++;
}

Population & AlgorithmState::population(){
  return population_;
}


const Population & AlgorithmState::population() const{
  return population_;
}
