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





int main(int argc, char ** argv){

  if(argc != 3){
    printf("usage: ./flowshop problem_set problem_index\n");
    return -1;
  }
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

  srand(time(0));
  const FlowshopInstance & instance = bc.instance(instance_index);

  int best = 200000;

  TabooSearch ls(instance, 18, 20);

  for(int i = 0; i < 2; i++){
    Individual Ind(instance.num_tasks());
    Ind.randomize();
    LocalSearch::Result r = ls(&Ind);
    int val = instance.evaluate(&(r.second));
    if(val < best) best = val;
    printf("%d\n", best);
  }
  printf("\n\n\nbest found solution: %d, feasible solution: %d\n", best, instance.feasible_solution());
  return 0;
}
