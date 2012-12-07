#ifndef FLOWSHOP_INSTANCE_H_
#define FLOWSHOP_INSTANCE_H_

#include <vector>

#include <algorithm_state.h>

class FlowshopInstance{
  public:
    FlowshopInstance(int num_machines, int num_tasks, int feasible_solution);
    virtual ~FlowshopInstance();
    int evaluate(const Individual * individual) const; 

    void update_cost(AlgorithmState & state) const;

    int & operator() (int machine, int task);
    int operator() (int machine, int task) const;

    int num_machines() const;
    int num_tasks() const;
    int feasible_solution() const;
  
  private:
    FlowshopInstance(const FlowshopInstance & instance);
    const FlowshopInstance & operator=(const FlowshopInstance & other);

    int * data_;
    int num_machines_;
    int num_tasks_;
    int feasible_solution_;
};

#endif
