#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include <sstream>

#include <benchmark_collection.h>
#include <parent_selector.h>
#include <crossover.h>
#include <mutation.h>
#include <replacement.h>
#include <adaptation.h>
#include <solver.h>
#include <termination.h>
#include <local_search.h>



const int num_parents = 1000;
const int num_individuals = 1000;
const int num_iterations = 1000;

const double max_immigrant_ratio = 0.3;
const int num_immigrant_search_iterations = 5;

const double mutation_probability = 0.05;


void save_results(int aim, int result, int time, int inum, int num_it, int problem, 
  const char * filename, int execution_number)
{
  std::stringstream name;
  name << filename << "_" << problem << "_" << execution_number << ".solution";
  FILE * out = fopen(name.str().c_str(), "w");
  fprintf(out, "best known solution: %d\n", aim);
  fprintf(out, "our solution: %d\n", result);
  fprintf(out, "time (s): %d\n", time);
  fprintf(out, "iterations: %d\n", num_it);
  fprintf(out, "number of processed individuals: %d\n", inum);
  fclose(out);
}


void save_progress(const std::vector<IterationInfo> & iterations, 
  int problem, const char * problem_name, int execution_number)
{
  std::stringstream sname;
  sname <<  problem_name << "_" << problem << "_" << execution_number << ".progress";
  std::string name = sname.str();
  FILE * out = fopen(name.c_str(), "w");
  fprintf(out, "# iteration best mean sdev diversity\n");
  for(unsigned int i = 0; i < iterations.size(); i++){
    fprintf(out, "%d %lf %lf %lf %lf\n", 
      i,
      iterations[i].best_cost, 
      iterations[i].cost_mean, 
      iterations[i].cost_sdev,
      iterations[i].diversity);
  }
  fclose(out);

  const char * titles[] = {"Best", "Mean", "Sdev"};
  const char * colors[] = {"red", "green", "blue"};

  sname << ".gplt";
  out = fopen(sname.str().c_str(), "w");
  fprintf(out, "plot ");
  for(int i = 0; i < 3; i++){
    fprintf(out, "\"%s\" using 1:%d with lines linecolor rgb \"%s\" title \"%s\"",
      name.c_str(),
      i + 2, 
      colors[i],
      titles[i]
      );

    if(i != 2)
      fprintf(out, ", ");
  }
  fprintf(out, ";\npause -1\n");
  fclose(out);
}


int main(int argc, char ** argv){

  if(argc != 4){
    printf("usage: ./flowshop problem_set problem_index execution_number\n");
    return -1;
  }

  srand(time(0));

  const char * filename = argv[1];
  char * test_set_name = strdup(filename);
  int l = strlen(filename);
  test_set_name[l-7] = 0;
  const int instance_index = atoi(argv[2]);
  const int execution_number = atoi(argv[3]);

  BenchmarkCollection bc;
  try{
    bc.load(filename);
  }
  catch(std::exception e){
    printf("unable to open problem set\n");
    return -1;
  }


  const FlowshopInstance & instance = bc.instance(instance_index);
  printf("Instance number: %d\n", instance_index);
  printf("number of tasks: %d\n", instance.num_tasks());
  printf("number of machines: %d\n", instance.num_machines());
  printf("best known solution: %d\n", instance.feasible_solution());

  KBestSelector parent_selector(num_parents);
  RankingScaler is(1);
  
  PMX pmx;
  RandomPairCrossoverStrategy crossover_strategy(pmx);

  RandomPermutationCrossover ps; 
	RandomMutationStrategy mutation_strategy(ps, mutation_probability);

  FamilyReplacement replacement_strategy; 
  
  SinglePointOperator gsp(instance);
  ParallelSearchStrategy ls(gsp);

  ProportionalImmigrationOperator immigration(0.0, max_immigrant_ratio, 
    ls, num_immigrant_search_iterations);

  FlowshopSolver solver(
    parent_selector, 
    crossover_strategy,
    mutation_strategy,
    replacement_strategy,
    is, ls,
    immigration
  );

  NumIterationsCondition term(num_iterations);

  int start = time(0);
  solver.run(bc.instance(instance_index), term, num_individuals);
  int duration = time(0) - start;
  
  printf("time = %d\n", duration);

  // save results
  int num_ind = solver.processed();
  int num_it = solver.num_iterations();
  save_results(instance.feasible_solution(), solver.solution(), duration, num_ind, num_it,
               instance_index, test_set_name, execution_number);
  save_progress(solver.iterations(), instance_index, 
                test_set_name, execution_number);

  free(test_set_name);

  return 0;
}
