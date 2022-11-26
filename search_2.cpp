#include<bits/stdc++.h>
#define inf 0x7fffffff
using namespace std;

const int N=20;

int memory_task_choose[N+5];
float T0;

struct task
{
    float t=inf,T=0;
    int num=0;
}Tasks[N+5];

struct preAnsshet
{
    task memory_tasks[N+5];
    int n=0;
    float Tkill=0,st=0;
}preAns;

struct Ansshet
{
    int n;
    float st=0,step=0;
    task memory_tasks[N+5];
}Ans;


task memory_for_task[N+5];

void Check_ans(int n)               
{
    int k[N+5],K=0,num[N+5];
    float st[N+5];
    memset(st,0,sizeof(st));
    memset(k,0,sizeof(k));
    memset(num,0,sizeof(num));
    for(int i=1;i<=n;i++)           
    {
        if(i!=1) st[i]=st[i-1]+memory_for_task[i-1].t;
        k[i]=ceil((T0-st[i])/memory_for_task[i].T);     
        K+=k[i];                                       
    }
    for(float i=0;i<memory_for_task[1].t;i=i+0.01)
    {
        bool not_find=0;
        float step=(T0-i)/K;                            
        for(int j=0;j<K;j++)                           
        {
            bool flag=0;
            float tag=j*step+i;                        
            for(int m=1;m<=n;m++)                   
            {
                for(int k1=0;k1<k[m];k1++)              
                {
                    if((k1*memory_for_task[m].T+st[m]<tag) && (k1*memory_for_task[m].T+memory_for_task[m].t+st[m]>tag))
                    {
                        num[m]++;
                        flag=1;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!flag)
            {
                not_find=1;
                break;
            }
        }

        for(int j=1;j<=n;j++)
        {
            if(num[j]!=k[j]) not_find=1;             
        }

        if(not_find) continue;

        int cnt=n;
        bool mark[n+5];
        memset(mark,0,sizeof(mark));

        for(int j=1;j<=n;j++)
        {
            if(st[j]>T0)
            {
                mark[j]=1;
                cnt--;
                continue;
            }
        }

        if(Ans.n<cnt)                           
        {
            int cnt_task=0;
            Ans.step=step;
            Ans.st=i;
            Ans.n=cnt;
            for(int j=1;j<=n;j++)
            {
                if(mark[j]) continue;
                cnt_task++;
                Ans.memory_tasks[cnt_task]=memory_for_task[j];
            }
            return;
        }
    }


    return;
}

void dfs_for_tasks(int goal,int now_n)
{
    int cnt=now_n;
    if(goal==now_n)                    
    {
        Check_ans(now_n);              
        return;
    }
    for(int i=1;i<=preAns.n;i++)
    {
        if(memory_task_choose[i]) continue;
        cnt++;
        memory_task_choose[i]=1;
        memory_for_task[cnt].num=preAns.memory_tasks[i].num;
        memory_for_task[cnt].T=preAns.memory_tasks[i].T;
        memory_for_task[cnt].t=preAns.memory_tasks[i].t;
        dfs_for_tasks(goal,cnt);
        cnt--;
        memory_task_choose[i]=0;
    }
    return;
}

int main()
{
    memset(memory_task_choose,0,sizeof(memory_task_choose));
    freopen("Solve1-Mode1.txt","r",stdin);
    freopen("Solve2.txt","w",stdout);
    scanf("T0=%f\n",&T0);
    scanf("Best_Ans1: N=%d,st=%f,Tkill=%f\n",&preAns.n,&preAns.st,&preAns.Tkill);
    for(int i=1;i<=preAns.n;i++)
    {
        scanf("Task%d:t=%f,T=%f\n",&preAns.memory_tasks[i].num,&preAns.memory_tasks[i].t,&preAns.memory_tasks[i].T);
    }

    for(int i=1;i<=preAns.n;i++)
    {
        dfs_for_tasks(i,0);
    }

    printf("T0=%f\n",T0);

    printf("Max number for Task: %d, st=%f, step=%f\n",Ans.n,Ans.st,Ans.step);
    for(int i=1;i<=Ans.n;i++)
    {
        printf("Task%d: t=%f, T=%f\n",Ans.memory_tasks[i].num,Ans.memory_tasks[i].t,Ans.memory_tasks[i].T);
    }

    printf("\n\n\ndatasets:\n");

    for(int i=1;i<=preAns.n;i++)
    {
        printf("Task%d: t=%f, T=%f\n",preAns.memory_tasks[i].num,preAns.memory_tasks[i].t,preAns.memory_tasks[i].T);
    }

    return 0;
}