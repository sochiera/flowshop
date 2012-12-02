#include <solver.h>
#include <vector>

void FlowshopSolver::run(
  const FlowshopInstance & instance,
  const TerminationCondition & termination  
)
{
  // generate random population TODO
  
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

    // replacement
    replacement_strategy(state, children);

    // delete unwanted children
    for(unsigned int i = 0; i < children.size(); i++)
      delete children[i];

    // evaluate again
    update_population(instance);

    // one more iteration...
    state.inc_iteration();
  }
}


void FlowshopSolver::update_population(const FlowshopInstance & instance){
  instance.update_cost(state);
  state.population().update_stats();
  adaptation.update(state);
}
