#ifndef FLOWSHOP_INSTANCE_H_
#define FLOWSHOP_INSTANCE_H_

#include <individual.h>
#include <vector>

class FlowshopInstance{
  public:
    FlowshopInstance(int num_machines, int num_tasks);
    virtual ~FlowshopInstance();
    double evaluate(const Individual * individual) const; 

    double & operator() (int machine, int task);
    double operator() (int machine, int task) const;

    int num_machines() const;
    int num_tasks() const;
  
  private:
    double * data_;
    int num_machines_;
    int num_tasks_;
};

#endif
