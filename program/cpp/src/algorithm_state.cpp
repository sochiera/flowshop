#include <algorithm_state.h>
#include <individual.h>

AlgorithmState::AlgorithmState(){
  iteration_ = 0;  
  best_found_ = "";
}

int AlgorithmState::isBestSet() const{
  return (best_found_ == "") ? 0 : 1;
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


const Individual AlgorithmState::Best() const{
	return best_found_;
}


void AlgorithmState::SetBest(Individual Ind){
	best_found_ = Ind;
}