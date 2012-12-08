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



const int num_parents = 100;
const int num_individuals = 400;

const double mutation_probability = 0.01;


void save_results(int aim, int result, int problem, const char * filename){
  std::stringstream name;
  name << filename << "_" << problem << ".solution";
  FILE * out = fopen(name.str().c_str(), "w");
  fprintf(out, "best known solution: %d\n", aim);
  fprintf(out, "our solution: %d\n", result);
  fclose(out);
}


void save_progress(const std::vector<IterationInfo> & iterations, 
  int problem, const char * problem_name)
{
  std::stringstream sname;
  sname <<  problem_name << "_" << problem << ".progress";
  std::string name = sname.str();
  FILE * out = fopen(name.c_str(), "w");
  fprintf(out, "# iteration best mean variance\n");
  for(unsigned int i = 0; i < iterations.size(); i++){
    fprintf(out, "%d %lf %lf %lf\n", 
      i,
      iterations[i].best_cost, 
      iterations[i].cost_mean, 
      iterations[i].cost_variance);
  }
  fclose(out);

  const char * titles[] = {"Best", "Mean", "Variance"};
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

  if(argc != 3){
    printf("usage: ./flowshop problem_set problem_index\n");
    return -1;
  }

  srand(time(0));

  const char * filename = argv[1];
  char * test_set_name = strdup(filename);
  int l = strlen(filename);
  test_set_name[l-7] = 0;
  const int instance_index = atoi(argv[2]);

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
  
  TabooSearch gsp(instance, 800, 50);
  //SinglePointOperator gsp(instance);
  SimpleStrategy ls(gsp);

  FlowshopSolver solver(
    parent_selector, 
    crossover_strategy,
    mutation_strategy,
    replacement_strategy,
    is, ls
  );

  NumIterationsCondition term(500);
  solver.run(bc.instance(instance_index), term, num_individuals);
  printf("\n");

  // save results
  save_results(instance.feasible_solution(), solver.solution(), instance_index, test_set_name);
  save_progress(solver.iterations(), instance_index, test_set_name);

  free(test_set_name);

  return 0;
}
