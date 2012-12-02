#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>
#include <individual.h>


class Population{
  public:
    Population();
    virtual ~Population();

    const Individual * operator[] (int i) const;
    Individual * operator[] (int i);

    void update_stats();

    double mean() const;
    double variance() const;
    double best() const;
    double worst() const;
    int size() const;

    double adaptation_mean() const;
    double adaptation_variance() const;
    double worst_adaptation() const;

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
    double worst_;

    double adaptation_mean_;
    double adaptation_variance_;

    bool needs_update_;
};

#endif
