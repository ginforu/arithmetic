//Created by 刘斌 on 17/10/22

#include <iostream>
#include <fstream>
using namespace std;
template<class Typew, class Typep>
Typep Knapsack(Typep p[ ], Typew w[ ], Typew c, int n,int bestx[])
{ //为Knap::Backtrack 初始化
    Typew W=0;
    Typep P=0;
    Object *Q=new Object[n];
    for(int i=1;i<=n;i++)
    {
        Q[i-1].ID=i;
        Q[i-1].d=1.0*p[i]/w[i];
        P+=p[i];
        W+=w[i];
    }
    if(W<=c)
    {
        for(int i=1;i<=n;i++)
        {
            bestx[i]=1;
        }
        return P; //装入所有物品
    }
    //依物品单位重量价值排序
    Sort(Q,n);
    Knap<Typew,Typep> K;
    K.p=new Typep[n+1];
    K.w=new Typew[n+1];
    K.bestx=new int[n+1];
    for(int i=1;i<=n;i++)
    {
     K.p[i]=p[Q[i-1].ID];
     K.w[i]=w[Q[i-1].ID];
    }
    K.bestx=bestx;
    K.cp=0;
    K.cw=0;
    K.c=c;
    K.n=n;
    K.bestp=0;
    // 回溯搜索
    K.Backtrack(1);
    delete [ ]Q;
    delete [ ]K.w;
    delete [ ]K.p;
    return K.bestp;
}

template<class Typew, class Typep>
class Knap{  //背包描述
    friend Typep Knapsack(Typep*, Typew *,Typew, int,int *);
    public:
        Typep Bound(int i);
        void  Backtrack(int i);
        Typew c;  //背包容量
        int n;        //物品数
        Typew * w; //物品重量数组
        Typep * p; //物品价值数组
        Typew cw; // 当前重量
        Typep cp;  //当前价值
        Typep bestp; //当前最优价值
        int *bestx;
};

class Object
{  //物品
   friend int Knapsack(int *, int *,int ,int ,int *);
   public:
       int operator<=(Object a)const
       {return (d>=a.d);}
       int ID;
       float d;  // 单位重量价值
};

void Sort(Object *Q,int n)
{
	int i,j;
	Object temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(Q[j].d<Q[j+1].d)
			{
				temp=Q[j];
				Q[j]=Q[j+1];
				Q[j+1]=temp;
			}
		}
	}
}



template<class Typew, class Typep>
void Knap<Typew, Typep>::Backtrack(int i)
{
    if(i>n)
    {
        bestp=cp;
        return;
    }
    if(cw+w[i]<=c)
    { //x[i] = 1
       cw+=w[i];
       cp+=p[i];
       Backtrack(i+1);
       cw-=w[i];
       cp-=p[i];
       bestx[i]=1;
    }
   if(Bound(i+1)>bestp) //x[i] = 0
   {
        bestx[i]=0;
       Backtrack(i+1);
   }
}

template<class Typew, class Typep>
Typep Knap<Typew, Typep>::Bound(int i)
{  //计算上界
    Typew cleft=c-cw;   //剩余容量
    Typep b=cp;
  //以物品单位重量价值递减序装入物品
    while(i<=n && w[i]<=cleft)
    {
        cleft -= w[i];
        b += p[i];
        i++;
    }
 //装满背包
    if(i<=n) b+= p[i]/w[i]*cleft;
    return b;
}

int main()
{
    int i,n,c;
    int *w,*p,*bestx;
    int bestp;
    fstream file1,file2;
    file1.open("input.txt",ios::in);
    file2.open("output.txt",ios::out);
    file1>>n;
    file1>>c;
    w=new int[n+1];
	p=new int[n+1];
	bestx=new int[n+1];
	for(i=1;i<=n;i++)
    {
        file1>>w[i];
        bestx[i]=0;
    }
    for(i=1;i<=n;i++)
    {
        file1>>p[i];
    }
    bestp=Knapsack(p,w,c,n,bestx);
    for(i=1;i<=n;i++)
    {
        cout<<bestx[i]<<" ";
        file2<<bestx[i];
    }
    file1.close();
	file2.close();
    return 0;
}
