#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>
#include <individual.h>
#include <instance.h>


class Population{
  public:
    Population();
    virtual ~Population();
    
    void update(const FlowshopInstance & instance);
    double mean() const;
    double variance() const;
    double best() const;
    int size() const;

    void add(Individual * individual);
    void remove(Individual * individual);
    
    bool needs_update() const;
    
  private:
    // disable copying
    Population(const Population & population);
    Population & operator=(const Population & population);

    std::vector<Individual *> individuals_;
    double mean_;
    double variance_;
    double best_;
    bool needs_update_;
};

#endif
