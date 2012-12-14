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
#include <limits>
#include <sstream>





int main(int argc, char ** argv){

  if(argc != 5){
    printf("usage: ./taboo_search problem_set problem_index execution_index num_individuals\n");
    return -1;
  }

  const char * filename = argv[1];
  char * test_set_name = strdup(filename);
  int l = strlen(filename);
  test_set_name[l-7] = 0;
  const int instance_index = atoi(argv[2]);
  const int execution_index = atoi(argv[3]);
  const int num_individuals = atoi(argv[4]);

  BenchmarkCollection bc;
  try{
    bc.load(filename);
  }
  catch(std::exception e){
    printf("unable to open problem set\n");
    return -1;
  }

  srand(time(0));
  const FlowshopInstance & instance = bc.instance(instance_index);

  int best = std::numeric_limits<int>::max();

  TabooSearch ls(instance, 1000, 800);

  int processed = 0;
  int start = time(0);
  while(processed < num_individuals){
    Individual Ind(instance.num_tasks());
    Ind.randomize();
    LocalSearch::Result r = ls(&Ind);
    processed += r.num_processed;
    int val = instance.evaluate(&(r.second));
    if(val < best) best = val;
    printf("best: %d found :%d\n", best, val);
  }
  int duration = time(0) - start;

  printf("\n\n\nbest found solution: %d, feasible solution: %d\n", best, instance.feasible_solution());

  // save results
  std::stringstream fname;
  fname << test_set_name << "_" << instance_index << "_" << execution_index << ".taboo";
  FILE * out = fopen(fname.str().c_str(), "w");
  fprintf(out, "best taboo solution : %d\n", best);
  fprintf(out, "time (s) : %d\n", duration);
  fclose(out);
  return 0;
}
