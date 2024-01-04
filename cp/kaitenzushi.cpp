#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<unordered_set>
using namespace std;

int dishes(int K, int M, std::vector<int> S)
{
    int Eaten = 0;
    std::map<int, int> Mp;

    for(unsigned int i=0; i<M; i++)
    {       
        auto val = Mp.find(S[i]);
        if((val == Mp.end()) || Eaten-Mp[S[i]] >  K)
        {
            Mp[S[i]] = Eaten;
            Eaten++;
        }

    }
    return Eaten;

}


int main()
{

    std::vector<int> v = {1, 2, 3, 3, 2, 1};
    int k =2;
    int M = v.size();
    auto d = dishes(k, M, v);
    std::cout<<"dishes: "<<d<<"\n";
    return 0;
}