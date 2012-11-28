#include <instance.h>
#include <algorithm>
#include <cstdio>


FlowshopInstance::FlowshopInstance(int m, int t){
  num_machines_ = m;
  num_tasks_ = t;
  
  data_ = new double[m * t];
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


double & FlowshopInstance::operator() (int machine, int task){
  return data_[num_tasks_ * machine + task];
}


double FlowshopInstance::operator() (int machine, int task) const{
  return data_[num_tasks_ * machine + task];
}


double FlowshopInstance::evaluate(const Individual * individual) const{
  const FlowshopInstance & T = *this;
  const Individual & pi = *individual;
  
  double b[num_machines_][num_tasks_];
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
 
  double cost = b[num_machines_ - 1][num_tasks_ - 1] + 
    T(num_machines_ - 1, pi[num_tasks_ - 1]);
  return cost;
}
