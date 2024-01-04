#include<iostream>
#include<vector>

long long getMinCodeEntryTime(int N, int M, std::vector<int> C) {
    int initial = 0;
    long long sum = 0;
    for(unsigned int i=0; i<M;i++)
    {
        if(i==0)
        {
            initial = std::min(abs(C[0]-1), abs( N - abs( C[0]-1 ))); //starts from 1
            sum+=initial;
        }
        else
        {
            sum += std::min(abs(C[i]-C[i-1]), abs(N- abs(C[i]-C[i-1]) ));
        }
            
    }

    return sum;
}


int main()
{

    std::vector<int> v = {9,4,4,8};
    long long h = getMinCodeEntryTime(10, 4, v);
    std::cout<<h<<std::endl;
    return 0;
}