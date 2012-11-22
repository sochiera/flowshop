#include <permutation.h>
#include <cstring>
#include <algorithm>


Permutation::Permutation(int size)
  : std::vector<int>(size) 
{}


Permutation::Permutation(const char * code)
  : std::vector<int>(strlen(code))
{
  int n = strlen(code);
  for(int i = 0; i < n; i++){
    at(i) = code[i] - '0'; 
  }
}


bool Permutation::operator == (const Permutation & other) const{
  for(int i = 0; i < size(); i++){
    if(at(i) != other[i])
      return false;
  }
  return true;
}


bool Permutation::valid() const{
  bool was[size()];
  std::fill(was, was + size(), false);
  for(int i = 0; i < size(); i++){
    if(was[at(i)])
      return false;
    was[at(i)] = true;
  }

  return true;
}



std::ostream & operator << 
  (std::ostream & out, const Permutation & p)
{
  for(int i = 0; i < p.size(); i ++)
    out << p[i] << " ";
  out << std::endl;
  return out;
}


void Permutation::swap(int i, int j){
  std::swap(at(i), at(j));
}


void  Permutation::randomize(){
  for(int i = 0; i < size(); i++)
    at(i) = i;
  std::random_shuffle(begin(), end());
}
