#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <benchmark_collection.h>
#include <parent_selector.h>
#include <crossover.h>
#include <mutation.h>
#include <replacement.h>
#include <adaptation.h>
#include <solver.h>
#include <termination.h>



const int instance_index = 3;
const int num_parents = 10000;
const int num_individuals = 20000;

const double mutation_probability = 0.01;



int main(int argc, char ** argv){
  srand(time(0));

  BenchmarkCollection bc;
  bc.load("tai100_20.txt.in");

  const FlowshopInstance & instance = bc.instance(instance_index);
  printf("Instance number: %d\n", instance_index);
  printf("number of tasks: %d\n", instance.num_tasks());
  printf("number of machines: %d\n", instance.num_machines());
  printf("best known solution: %d\n", instance.feasible_solution());

  KBestSelector parent_selector(num_parents);
  
  PMX pmx;
  RandomCrossoverStrategy crossover_strategy(pmx);

  PermutationShift ps; 
  RandomMutationStrategy mutation_strategy(ps, mutation_probability);

  BestOfReplacement replacement_strategy; 
  IdentityScaler is;

  FlowshopSolver solver(
    parent_selector, 
    crossover_strategy,
    mutation_strategy,
    replacement_strategy,
    is
  );

  NumIterationsCondition term(1000);
  solver.run(bc.instance(instance_index), term, num_individuals);

  return 0;
}
