#include <replacement.h>
#include <algorithm>
#include <vector>


void BestOfReplacement::operator() 
  (AlgorithmState & state, std::vector<Individual *> & children) const
{
  using std::make_pair;

  std::vector< std::pair<int, Individual *> > pairs;
  
  for(unsigned int i = 0; i < children.size(); i++)
    pairs.push_back(make_pair(children[i]->cost(), children[i]));

  Population & p = state.population();
  for(int i = 0; i < p.size(); i++)
    pairs.push_back(make_pair(p[i]->cost(), p[i]));

  std::sort(pairs.begin(), pairs.end());
  
  const unsigned int n = p.size();
  p.clear();

  for(unsigned int i = 0; i < pairs.size(); i++){
    Individual * individual = pairs[i].second;
  
    if(i < n)
      p.add(individual);
    else
      delete individual;
  }
}


void TournamentReplacement::operator() 
  (AlgorithmState & state, std::vector<Individual *> & children) const
{
  using std::make_pair;

  std::vector< std::pair<int, Individual *> > pairs;
  
  for(unsigned int i = 0; i < children.size(); i++)
    pairs.push_back(make_pair(children[i]->cost(), children[i]));

  Population & p = state.population();
  for(int i = 0; i < p.size(); i++)
    pairs.push_back(make_pair(p[i]->cost(), p[i]));

  if(pairs.size() %2 != 0) {
    delete pairs[pairs.size()-1].second;
    pairs.pop_back();
  }
  std::random_shuffle(pairs.begin(), pairs.end());
  
  const unsigned int n = p.size();
  p.clear();

  for(unsigned int i = 0; pairs.size() < 2*n; i++){
    pairs.push_back(pairs[i]);
  }

  for(unsigned int i = 0; i < pairs.size(); i+=2){
    Individual * a = pairs[i].second;
    Individual * b = pairs[i+1].second;
    if(pairs[i].first < pairs[i+1].first){
      p.add(a);
      delete b;
    }
    else{
      p.add(b);
      delete a;
    }
  }
}
