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

  int best = 20000000;

  localsearch GradualSinglePointOperator();

  for(int i = 0; i < 10000000; i++){
    Individual randomInd(instance.num_tasks());
    randomInd.randomize();
    int val = instance.evaluate(&randomInd);
    while(true){
      localsearch
      int val2 = 
    }
    val = instance.evaluate(&randomInd);
    if(val < best) best = val;
    if((i/50000)*50000 == i) printf("%d\n", best);
  }
  printf("\n\n\nbest foundsolution: %d, feasible solution: %d\n", best, instance.feasible_solution());
  return 0;
}
