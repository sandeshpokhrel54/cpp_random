#include<iostream>
#include<vector>
#include<string>
using namespace std;

int find_uniform(int x, int y)
{
    //
    unsigned int num_dig_x = std::to_string(x).size();
    unsigned int num_dig_y = std::to_string(y).size();
    std::vector<long> perf;
    for(unsigned int i=num_dig_x; i<=num_dig_y; i++)
    {
        for(unsigned int j=1;j<10;j++)
        {
            std::wstring je = std::to_wstring(j);
            std::wstring temp = je;
            for(unsigned int k=0;k<i-1;k++)
            {
                temp.append(je);
            }
            long val = std::stol(temp);
            std::cout<<val<<"\n";
            if (val >= x && val<=y)
                perf.push_back(val);
        }
        
    }
    
    return perf.size();
}

int main()
{
    // int x, y;
    
    long long x = 200;
    long long y = 5012045;
    int t = find_uniform(x,y);

    std::cout<<t<<"\n";
    return 0;
}