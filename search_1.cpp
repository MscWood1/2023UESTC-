#include<bits/stdc++.h>
#define inf 0x7fffffff
using namespace std;

const int N=20;
int Mode=1; //1-->N*Tkill max;   2-->N max;   3-->Tkill max;

struct task
{
    float t=inf,T=0;
    int num=0;
}Tasks[N+5];

struct Ansshet
{
    task memory_tasks[N+5];
    int n=0;
    float Tkill=0,st=0;
}Ans[N+5];

task memory_for_task[N+5];
bool memory_for_task_choose[N+5];
float T0;

bool camp(task a,task b)
{
    return (T0/a.T)*a.t<(T0/b.T)*b.t;
}

bool camp_for_ans(Ansshet a,Ansshet b)
{
    if(Mode==1) return a.n*a.Tkill<b.n*b.Tkill;
    if(Mode==2) return a.n<b.n;
    if(Mode==3) return a.Tkill<b.Tkill;
    return 1;
}

bool evaluate_ans(Ansshet a,int n,float Tkill)
{
    if(Mode==1)
    {
        if(a.n*a.Tkill<n*Tkill) return 1;
        return 0;        
    }
    if(Mode==2)
    {
        if(a.n<n) return 1;
        return 0;        
    }
    if(Mode==3)
    {
        if(a.Tkill<Tkill) return 1;
        return 0;        
    }
    return 0;
}

bool Check_same(task ans[],int n)
{
    int i=1;
    bool flag=1;
    int num_ans[N+5],num[N+5];
    while(Ans[i].n!=0)
    {
        if(Ans[i].n!=n)
        {
            i++;
            continue;
        }
        memset(num_ans,0,sizeof(num_ans));
        memset(num,0,sizeof(num));
        for(int j=1;j<=Ans[i].n;j++)
        {
            num_ans[j]=Ans[i].memory_tasks[j].num;
        }
        for(int j=1;j<=n;j++)
        {
            num[j]=ans[j].num;
        }
        sort(num_ans+1,num_ans+Ans[i].n+1);
        sort(num+1,num+n+1);
        int x1=0,x2=0,tag=0;
        for(int j=1;j<=n;j++)
        {
            if(num_ans[j]!=num[j])
            {
                tag=1;
                break;
            }
        }
        if(!tag)
        {
            flag=0;
            break;
        }
        i++;
    }

    return flag;
}

void check_answer(int num)
{
    int n=0;
    float Tkill=T0;
    float Tmin=inf,st=0,end=inf;

    task memory_for_task_1[N+5];

    for(int i=1;i<=num;i++) memory_for_task_1[i]=memory_for_task[i];

    sort(memory_for_task_1+1,memory_for_task_1+num+1,camp);

    for(int i=1;i<=num;i++)
    {
        Tmin=min(Tmin,st+memory_for_task_1[i].T);
        if(st+memory_for_task_1[i].t<=end)
        {
            st=st+memory_for_task_1[i].t;
            end=Tmin;
            n++;
            Tkill=end;
            if(st>end)
            {
                Tkill=end;
                break;
            }
        }
    }

    if(n<3) return;

    if( Ans[1].n==0 || (evaluate_ans(Ans[1],n,Tkill) && Check_same(memory_for_task_1,n)))
    {
        Ans[1].n=n;
        Ans[1].Tkill=Tkill;
        Ans[1].st=st;
        for(int i=1;i<=n;i++)
        {
            Ans[1].memory_tasks[i].num=memory_for_task_1[i].num;
            Ans[1].memory_tasks[i].t=memory_for_task_1[i].t;
            Ans[1].memory_tasks[i].T=memory_for_task_1[i].T;
        }
        sort(Ans+1,Ans+6,camp_for_ans);
    }


    return;
}


void dfs_for_tasks(int goal,int now_n)
{
    int cnt=now_n;
    if(goal==now_n)
    {
        check_answer(goal);
        return;
    }
    for(int i=memory_for_task[cnt].num;i<=N;i++)
    {
        if(memory_for_task_choose[i]) continue;
        cnt++;
        memory_for_task[cnt].num=i;
        memory_for_task[cnt].t=Tasks[i].t;
        memory_for_task[cnt].T=Tasks[i].T;
        memory_for_task_choose[i]=1;
        dfs_for_tasks(goal,cnt);
        memory_for_task_choose[i]=0;
        cnt--;
    }
    return;
}

int main()
{
    printf("Mode:1-->N*Tkill max;   2-->N max;   3-->Tkill max;\nMode:");
    scanf("%d",&Mode);
    freopen("datasets.txt","r",stdin);
    if(Mode==1) freopen("Solve1-Mode1.txt","w",stdout);
    if(Mode==2) freopen("Solve1-Mode2.txt","w",stdout);
    if(Mode==3) freopen("Solve1-Mode3.txt","w",stdout);
    memset(memory_for_task_choose,0,sizeof(memory_for_task_choose));
    scanf("%f",&T0);
    for(int i=1;i<=N;i++) scanf("%f",&Tasks[i].t);
    for(int i=1;i<=N;i++) scanf("%f",&Tasks[i].T);

    for(int i=3;i<=N;i++)
    {
        dfs_for_tasks(i,0);
    }

    printf("T0=%f\n",T0);
    for(int i=5;i>=1;i--)
    {
        if(Ans[i].n==0) continue;
        printf("Best_Ans%d: N=%d,st=%f,Tkill=%f\n",6-i,Ans[i].n,Ans[i].st,Ans[i].Tkill);
        for(int j=1;j<=Ans[i].n;j++)
        {
            printf("Task%d:t=%f,T=%f\n",Ans[i].memory_tasks[j].num,Ans[i].memory_tasks[j].t,Ans[i].memory_tasks[j].T);
        }
        printf("\n");
    }
    printf("\n\n\nDatasets:\nT0=%f\n",T0);
    for(int i=1;i<=N;i++) printf("ti=%f Ti=%f\n",Tasks[i].t,Tasks[i].T);
    return 0;
}