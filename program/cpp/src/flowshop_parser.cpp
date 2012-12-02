#include <vector>
#include <instance.h>
#include <algorithm_state.h>
#include <flowshop_parser.h>
#include <cstdlib>
#include <cstdio>

FlowshopInstance FlowshopParser::Parse(int n){
  n %= BenchmarkCount;


  FILE *fp;
  fp=fopen("all.in", "r");



  int t, m;
  int garbage;
  int solution;


  while(n >= 0){

    fscanf(fp, "%d %d %d ", &t, &m, &garbage);
    fscanf(fp, "%d %d ", &solution, &garbage);
    while(t--){
      while(m--){
        fscanf(fp, "%d ", &garbage);
      }
    }
    n--;
  }

  int tasks, machines;
  fscanf(fp, "%d %d %d ", &tasks, &machines, &garbage);
  fscanf(fp, "%d %d ", &solution, &garbage);

  double s = (double)(solution);

  FlowshopInstance I(m, t, s);
  for(int m = 0; m < machines; m++){
    for(int t = 0; t < tasks; t++){
      fscanf(fp, "%d ", &garbage);
      I(m,t) = (double)(garbage);
    }
  }

  fclose (fp); 

  return I;

}
