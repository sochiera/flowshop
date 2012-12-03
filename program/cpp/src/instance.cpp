#include <instance.h>
#include <algorithm>
#include <cstdio>


FlowshopInstance::FlowshopInstance(int m, int t, int s){
  num_machines_ = m;
  num_tasks_ = t;
  feasible_solution_ = s;
  data_ = new int[m * t];
  std::fill(data_, data_ + m * t, 0);
}


FlowshopInstance::~FlowshopInstance(){
  delete [] data_;
}


int FlowshopInstance::num_machines() const{
  return num_machines_;
}


int FlowshopInstance::num_tasks() const{
  return num_tasks_;
}

int FlowshopInstance::feasible_solution() const{
  return feasible_solution_;
}

int & FlowshopInstance::operator() (int machine, int task){
  return data_[num_tasks_ * machine + task];
}


int FlowshopInstance::operator() (int machine, int task) const{
  return data_[num_tasks_ * machine + task];
}


void FlowshopInstance::update_cost(AlgorithmState & state) const{
  Population & P = state.population();
  for(int i = 0; i < P.size(); i++){
    int cost = evaluate(P[i]);
    P[i]->set_cost(cost);
  }
}


int FlowshopInstance::evaluate(const Individual * individual) const{
  const FlowshopInstance & T = *this;
  const Individual & pi = *individual;
 
  int ** b = new int * [num_machines_];
  for(int i = 0; i < num_machines(); i++)
    b[i] = new int [num_tasks_];

  b[0][0] = 0;
  for(int t = 1; t < num_tasks_; t++)
    b[0][t] = b[0][t-1] + T(0, pi[t]);
  for(int m = 1; m < num_machines_; m++)
    b[m][0] = b[m-1][0] + T(m-1, pi[0]);
  
  for(int m = 1; m < num_machines_; m++)
    for(int t = 1; t < num_tasks_; t++)
      b[m][t] = std::max(
        b[m][t-1] + T(m, pi[t-1]), 
        b[m-1][t] + T(m-1, pi[t]));
 
  int cost = b[num_machines_ - 1][num_tasks_ - 1] + 
    T(num_machines_ - 1, pi[num_tasks_ - 1]);

  for(int i = 0; i < num_machines(); i++)
    delete [] b[i];
  delete [] b;

  return cost;
}
