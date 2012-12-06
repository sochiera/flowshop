#include <solver.h>
#include <vector>
#include <cstdio>
#include <cassert>


void FlowshopSolver::run(
  const FlowshopInstance & instance,
  const TerminationCondition & termination,
  int population_size
)
{
  // generate random population
  for(int i = 0; i < population_size; i++){
    Individual * next = new Individual(instance.num_tasks());
    next->randomize();
    next->set_cost(instance.evaluate(next));
    state.population().add(next);
  }
  
  // evaluate individuals, sort them etc.
  update_population(instance);

  while( !termination(state) ){
    // select parents
    std::vector<const Individual *> parents = 
      parent_selector(state);

    // crossover 
    std::vector<Individual *> children = 
      crossover_strategy(state, parents);

    // mutation
    mutation_strategy(state, children);

    // evaluate children
    for(unsigned int i = 0; i < children.size(); i++){
      double c = instance.evaluate(children[i]); 
      children[i]->set_cost(c);
    }

    local_search(state, children);

    // replacement
    replacement_strategy(state, children);

    // evaluate again
    update_population(instance);

    // one more iteration...
    state.inc_iteration();

    printf("\033[1Gcurrent iteration : %5d best: %d",
      state.iteration(), state.population().best());
    fflush(stdout);

    save_iteration_info();
  }
}


void FlowshopSolver::update_population(const FlowshopInstance & instance){
  state.population().update_stats();
  adaptation.update(state);
}


const std::vector<IterationInfo> & FlowshopSolver::iterations() const{
  return iterations_;
}


void FlowshopSolver::save_iteration_info(){
  IterationInfo info;
  info.cost_mean = state.population().mean();
  info.cost_variance = state.population().variance();
  info.best_cost = state.population().best();
  iterations_.push_back(info);
}


double FlowshopSolver::solution() const{
  return std::min(state.best(), state.population().best());
}
