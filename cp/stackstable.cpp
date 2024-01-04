#include<vector>
#include<iostream>
using namespace std;

int getMinimumDeflatedDiscCount(int N, std::vector<int> R) {
  
  
  //check if possible
  for(unsigned int i=0; i<N; i++)
  {
    if(i+1 > R[i])
        return -1;
  }

  //if possible count
  int count = 0;
  for(unsigned int i=R.size()-1; i>=1; i--)
  {
    if(R[i-1]>=R[i])
    {
        R[i-1] = (R[i]-1);
        count++;
    }

  }


  return count;
}

int main()
{
    int N =4;
    std::vector<int> R = {6,5,4,3};
    std::cout<<getMinimumDeflatedDiscCount(N,R);
    return 0;

}