#include<bits/stdc++.h>
#define inf 0x7fffffff
using namespace std;

const int N=20;
const int t0=1;
const int maxValue=10000;
const int minValue=0;
const float Times=100.0;

struct task
{
    float t=inf,T=0;
    int num=0;
};

struct preAnsshet
{
    int n;
    float st=0,step=0;
    task memory_tasks[N+5];
};

struct Ansshet
{
    int n=0;
    float p=0,st=0;
    task memory_tasks[N+5];
};


float T0;
preAnsshet preAns;
Ansshet Ans;


int main()
{
    unsigned seed=time(0);
    srand(seed);
    freopen("Solve2.txt","r",stdin);
    freopen("Solve3.txt","w",stdout);
    scanf("T0=%f\n",&T0);
    scanf("Max number for Task: %d, st=%f, step=%f\n",&preAns.n,&preAns.st,&preAns.step);
    for(int i=1;i<=preAns.n;i++)
    {
        scanf("Task%d: t=%f, T=%f\n",&preAns.memory_tasks[i].num,&preAns.memory_tasks[i].t,&preAns.memory_tasks[i].T);
    }

    for(int P=1;P<=10;P++)
    {
        float Tin=((rand()%(int(T0*Times)-minValue+1))+minValue)/Times;
        float t=((rand()%(int(maxValue-t0*Times)-minValue+1))+minValue)/Times;
        float T=((rand()%(int(maxValue)-int((t+t0)*Times)+1))+int(t*Times))/Times;
        
        printf("Time%d:\nTin=%f, t=%f\n",P,Tin,t);        

        int i=1,num=preAns.n;
        float st=0;
        bool mark[N+5];
        memset(mark,0,sizeof(mark));

        while(st<Tin&&i<=preAns.n)
        {
            st+=preAns.memory_tasks[i].t;
            i++;
        }

        Ans.st=Tin;

        float cntTime=Tin;

        while(cntTime<t+Tin)
        {
            cntTime+=preAns.memory_tasks[i].t;
            mark[i]=1;
            num--;
            i++;
        }

        int cnt_task=1;
        Ans.n=num;
        Ans.p=1-float(num)/float(preAns.n);
        for(int j=1;j<=preAns.n;j++)
        {
            if(mark[j]) continue;
            Ans.memory_tasks[cnt_task]=preAns.memory_tasks[j];
            cnt_task++;
        }


        printf("Add at %f, p=%f\n",Ans.st,Ans.p);
        for(int j=1;j<=Ans.n;j++)
        {
            printf("Task%d: t=%f, T=%f\n",Ans.memory_tasks[j].num,Ans.memory_tasks[j].t,Ans.memory_tasks[j].T);
        }
        printf("\n");
    }

    printf("\n\n\nT0=%f\ndatasets:\n",T0);
    for(int i=1;i<=preAns.n;i++)
    {
        printf("Task%d: t=%f, T=%f\n",preAns.memory_tasks[i].num,preAns.memory_tasks[i].t,preAns.memory_tasks[i].T);
    }

    return 0;

}