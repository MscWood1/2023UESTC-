#include<bits/stdc++.h>
using namespace std;

const int N=20;
const int maxValue=10000;
const int minValue=100;
const float Times=100.0;

int main()
{
    int t0=1;
    float t[N+5];
    unsigned seed=time(0);
    srand(seed);
    freopen("datasets.txt","w",stdout);
    float T0=((rand()%(maxValue-minValue+1))+minValue)/Times;
    printf("%f\n",T0);
    for(int i=1;i<=N;i++) //ti
    {
        float x1=((rand()%(int(maxValue-t0*Times)-minValue+1))+minValue)/Times;
        t[i]=t0*x1;
        printf("%f\n",t[i]);
    }
    for(int i=1;i<=N;i++) //Ti
    {
        float x1=((rand()%(int(maxValue)-int((t[i]+t0)*Times)+1))+int(t[i]*Times))/Times;
        printf("%f\n",t0*x1);
    }
    fclose(stdout);
    return 0;
}