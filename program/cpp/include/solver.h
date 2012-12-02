#ifndef FLOWSHOP_SOLVER_H_
#define FLOWSHOP_SOLVER_H_


#include <algorithm_state.h>
#include <parent_selector.h>
#include <crossover.h>
#include <mutation.h>
#include <replacement.h>
#include <termination.h>
#include <adaptation.h>
#include <instance.h>


struct IterationInfo{
  double cost_mean;
  double cost_variance;
  double best_cost;
};



class FlowshopSolver{
  public:
    FlowshopSolver(
      const ParentSelector & selector,
      const CrossoverStrategy & crossover,
      const MutationStrategy & mutation,
      const ReplacementStrategy & replacement,
      const AdaptationScaler & fadaptation
      )
    : parent_selector(selector), 
      crossover_strategy(crossover),
      mutation_strategy(mutation), 
      replacement_strategy(replacement),
      adaptation(fadaptation)
    {}

    void run(
      const FlowshopInstance & instance,
      const TerminationCondition & termination);

    const std::vector<IterationInfo> & iterations() const;

  private:
    AlgorithmState state;

    const ParentSelector & parent_selector;
    const CrossoverStrategy & crossover_strategy;
    const MutationStrategy & mutation_strategy;
    const ReplacementStrategy & replacement_strategy;  
    const AdaptationScaler & adaptation;

    std::vector<IterationInfo> iterations_;

    void update_population(const FlowshopInstance & instance);
    void save_iteration_info();
};

#endif
