#include <stdio.h>
#include <algorithm>
 
using namespace std;
 
struct Point
{
    int x1=0,y1=0;
    int x2=0,y2=0;
};
 
void Swap(struct Point *p)
{
    int tem1=0,tem2=0;
    tem1=p->x1,tem2=p->y1;
    p->x1=p->x2;
    p->y1=p->y2;
    p->x2=tem1;
    p->y2=tem2;
}
 
bool rulex(struct Point a,struct Point b)
{
    return a.x1<b.x1;
}
bool ruley(struct Point a,struct Point b)
{
    return a.y1<b.y1;
}
 
int min(int a,int b)
{
    if(a<=b)
    {
        return a;
    }
    return b;
}
int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    return b;
}
int cross(struct Point a,struct Point b,int index)
{
    if(index==1)
    {
        return (a.x2-a.x1) * (b.y1-a.y1) - (a.y2-a.y1) * (b.x1-a.x1);
    }
    else
    {
        return (a.x2-a.x1) * (b.y2-a.y1) - (a.y2-a.y1) * (b.x2-a.x1);
    }
 
} 
 
bool Parallel(struct Point a,struct Point b,int index)//端點共線或共點 
{
    if(index==1)
    {
        if(min(a.x1,a.x2)<=b.x1&&b.x1<=max(a.x1,a.x2)&&min(a.y1,a.y2)<=b.y1&&b.y1<=max(a.y1,a.y2))
        {
            return true;
        }
    }
    else
    {
        if(min(a.x1,a.x2)<=b.x2&&b.x2<=max(a.x1,a.x2)&&min(a.y1,a.y2)<=b.y2&&b.y2<=max(a.y1,a.y2))
        {
            return true;
        }
    }
    return false;
} 
 
 
bool intersect(struct Point a,struct Point b)
{
       int c1 = cross(a,b,1);
       int c2 = cross(a,b,2);
       int c3 = cross(b,a,1);
       int c4 = cross(b,a,2);
 
    //printf("%f  %f  %f  %f\n",c1,c2,c3,c4);
       // 端點不共線
    if (c1 * c2 < 0 && c3 * c4 < 0) 
    {
        //printf("here\n");
        return true;    
    }
       // 端點共線
    if (c1 == 0 && Parallel(a,b,1) )
    {
        return true;    
    }
    if (c2 == 0 && Parallel(a,b,2) )
    {
        return true;    
    }
    if (c3 == 0 && Parallel(b,a,1) )
    {
        return true;    
    }
    if (c4 == 0 && Parallel(b,a,2) )
    {
        return true;    
    }
 
 
       return false;
}
 
 
int main()
{
    int num=0;
    scanf("%d",&num);
 
    struct Point p[60];
 
    for(int i=0;i<num;i+=1)  
    {
        scanf("%d%d%d%d",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
        if(p[i].x1>p[i].x2)
        {
            Swap(p+i);    
        }
 
 
    }
    sort(p,p+num,ruley);
    sort(p,p+num,rulex);
    /*for(int i=0;i<num;i+=1)
    {
        printf("%d %d  %d %d\n",p[i].x1,p[i].y1,p[i].x2,p[i].y2);
    }*/
 
    int matrix[60]={};
    int group=1;
    int check[60]={};
    for(int i=0;i<num-1;i+=1)
    {
 		bool flag =true;
		//printf("%d\n",group);
        if(matrix[i]==0)
            {
                flag =false;
                matrix[i]=group;
                group+=1;    
            } 
        for(int j=i+1;j<num;j+=1)
        {
 
            if(matrix[j]==0&&intersect(p[i],p[j]))
            {
                matrix[j]=matrix[i];
                flag =true;
                //printf("%d:%d %d:%d here\n",i,matrix[j],j,matrix[i]);
            }
            else if(matrix[j]!=0&&intersect(p[i],p[j]))
            {
                if(matrix[i]==0)
                {
                    group-=1;    
                }
                else
                {
                    check[matrix[i]]=matrix[j];
                }
                matrix[i]=matrix[j];
                flag =true;
                //printf("%d:%d %d:%d\n",i,matrix[j],j,matrix[i]);
            }
           
        }
         /*for(int k=0;k<num;k++)
            {
            	printf("%d ",matrix[k]);
			}
			printf("\n");*/
        if(flag==false)//do not have any connected edge
        {
            matrix[i]=0;
            group-=1;
            //printf("nooo\n");
        }
        //printf("%d\n",group);
    }
 
 
    /*for(int i=0;i<num;i++)
    {
        printf("%d ",check[i]);
    }
    printf("\n");
    for(int i=0;i<num;i++)
    {
        printf("%d ",matrix[i]);
    }
    printf("\n");*/
    int a[60]={};
    for(int i=0;i<num;i+=1)
    {
        if(check[matrix[i]]!=0)
        {
            matrix[i]=check[matrix[i]];
        }
        if(matrix[i]!=0)
        {
            a[matrix[i]]+=1;
        }
    }
 
    /*for(int i=1;i<group;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");*/
 
    int pair=0;
    for(int i=1;i<group;i+=1)
    {
        pair+=a[i]*(a[i]-1)/2;
    }
    printf("%d",pair); 
 
 
 
}
