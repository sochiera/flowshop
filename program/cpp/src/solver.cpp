#include <solver.h>
#include <vector>

void FlowshopSolver::run(
  const FlowshopInstance & instance,
  const TerminationCondition & termination  
)
{
  // generate random population TODO
  
  // evaluate individuals, sort them etc.
  state.population().update(instance);

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
    state.population().update(instance);

    // one more iteration...
    state.inc_iteration();
  }

}
