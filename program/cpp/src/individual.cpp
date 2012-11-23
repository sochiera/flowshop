#include <individual.h>
#include <cstring>
#include <algorithm>


Individual::Individual(int size)
  : std::vector<int>(size) 
{}


Individual::Individual(const char * code)
  : std::vector<int>(strlen(code))
{
  int n = strlen(code);
  for(int i = 0; i < n; i++){
    at(i) = code[i] - '0'; 
  }
}


bool Individual::operator == (const Individual & other) const{
  for(unsigned int i = 0; i < size(); i++){
    if(at(i) != other[i])
      return false;
  }
  return true;
}


bool Individual::valid() const{
  bool was[size()];
  std::fill(was, was + size(), false);
  for(unsigned int i = 0; i < size(); i++){
    if(was[at(i)])
      return false;
    was[at(i)] = true;
  }

  return true;
}



std::ostream & operator << 
  (std::ostream & out, const Individual & p)
{
  for(unsigned int i = 0; i < p.size(); i ++)
    out << p[i] << " ";
  out << std::endl;
  return out;
}


void Individual::swap(int i, int j){
  std::swap(at(i), at(j));
}


void  Individual::randomize(){
  for(unsigned int i = 0; i < size(); i++)
    at(i) = i;
  std::random_shuffle(begin(), end());
}


double Individual::cost() const{
  return cost_;
}

void Individual::set_cost(double cost){
  cost_ = cost;
}


bool Individual::operator < (const Individual & other) const{
  return cost_ < other.cost_;
}
