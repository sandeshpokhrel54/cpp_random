#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int getMinProblemCount(int N, vector<int> S) {
  // Write your code here

  auto it = std::max_element(S.begin(), S.end());
  auto max_val = *it;
  
  auto min_count = int(max_val / 2.0);


  int check = 0;
  for(unsigned int i=0; i<S.size(); i++)
  {
    if(S[i]%2 !=0)
    {
        check = 1;
    }
  }

  return min_count + check;
}
int main()
{
    int N = 4;
    std::vector<int> S = {2,4,6,8};
    std::cout<<getMinProblemCount(N, S);
}