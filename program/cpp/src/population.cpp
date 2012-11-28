#include <population.h>
#include <algorithm>


Population::Population(){
  needs_update_ = false;   
  mean_ = 0;
  variance_ = 0;
}


void Population::add(Individual * individual){
  needs_update_ = true;
  individuals_.push_back(individual);
}


void Population::remove(Individual * individual){ 
  needs_update_ = true;
  std::remove(individuals_.begin(), individuals_.end(), individual);
  delete individual;
}


bool ind_ptr_cmp(const Individual * a, const Individual * b){
  return a->cost() < b->cost();
}


void Population::update(const FlowshopInstance & instance){
  mean_ = 0;
  variance_ = 0;

  for(int i = 0; i < size(); i++)
    mean_ += individuals_[i]->cost();

  for(int i = 0; i < size(); i++){
    double x = mean_ - individuals_[i]->cost();
    x = x * x;
    variance_ += x;
  }

  // TODO: parallelize 
  for(int i = 0; i < size(); i++)
    individuals_[i]->set_cost(instance.evaluate(individuals_[i]));

  std::sort(individuals_.begin(), individuals_.end(), ind_ptr_cmp);

  needs_update_ = false;
}


double Population::mean() const{
  return mean_; 
}


double Population::variance() const{
  return variance_;
}


int Population::size() const{
  return individuals_.size();
}


bool Population::needs_update() const{
  return needs_update_;
}


Population::~Population(){
  for(int i = 0; i < size(); i++){
    delete individuals_[i]; 
  }
}
