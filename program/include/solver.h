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
#include <local_search.h>
#include <immigration.h>


struct IterationInfo{
  double cost_mean;
  double cost_variance;
  double cost_sdev;
  double diversity;
  double best_cost;
};



class FlowshopSolver{
  public:
    FlowshopSolver(
      const ParentSelector & selector,
      const CrossoverStrategy & crossover,
      const MutationStrategy & mutation,
      const ReplacementStrategy & replacement,
      const AdaptationScaler & fadaptation,
      const LocalSearchStrategy & local,
      const ImmigrationOperator & imm
      )
    : parent_selector(selector), 
      crossover_strategy(crossover),
      mutation_strategy(mutation), 
      replacement_strategy(replacement),
      adaptation(fadaptation),
      local_search(local),
      secondary_replacement_ptr(0),
      secondary_period(0),
      immigration(imm)
    {}

    void run(
      const FlowshopInstance & instance,
      const TerminationCondition & termination,
      int population_size
      );

    const std::vector<IterationInfo> & iterations() const;

    int solution() const;
    int processed() const;
    int num_iterations() const;

    void set_secondary_replacement(const ReplacementStrategy & rep, int period);

  private:
    AlgorithmState state;

    const ParentSelector & parent_selector;
    const CrossoverStrategy & crossover_strategy;
    const MutationStrategy & mutation_strategy;
    const ReplacementStrategy & replacement_strategy;  
    const AdaptationScaler & adaptation;
    const LocalSearchStrategy & local_search;

    const ReplacementStrategy * secondary_replacement_ptr;
    int secondary_period;

    const ImmigrationOperator & immigration;

    std::vector<IterationInfo> iterations_;

    void update_population(const FlowshopInstance & instance);
    void save_iteration_info();
};

#endif
