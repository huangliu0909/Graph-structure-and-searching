#include <stdio.h>
#include <stdlib.h>
#define Max 100//哈夫曼编码的最大位数
char m[Max];//存储原始数据
char mm[Max];//存储原始数据
char p[Max];//存储符号
int q[Max];//存储符号出现的次数
int hl[Max][Max];
#define N 100  //叶子数目
#define M (2*N-1)    //结点总数
#define maxval 10000.0
int level=10;//最大层数
typedef struct
{
    char ch;
    float weight;
    int lchild,rchild,parent;
}hufmtree;

typedef struct
{
    char bits[N];   //位串
    int start;      //编码在位串中的起始位置
    char ch;        //字符
}codetype;

void huffman(hufmtree tree[],int n)//建立哈夫曼树
{
    int i,j,p1,p2;//p1,p2分别记住每次合并时权值最小和次小的两个根结点的下标
    float small1,small2;
    for(i=0;i<M;i++)    //初始化
    {
        tree[i].parent=0;
        tree[i].lchild=-1;
        tree[i].rchild=-1;
        tree[i].weight=0.0;
    }
    for(i=0;i<n;i++)  //读入前n个结点的字符及权值
    {

        tree[i].ch=p[i];
        tree[i].weight=q[i];

    }
    for(i=n;i<M;i++)      //进行n-1次合并，产生n-1个新结点
    {
        p1=0;p2=0;
        small1=maxval;small2=maxval;   //maxval是float类型的最大值
        for(j=0;j<i;j++)    //选出两个权值最小的根结点
        if(tree[j].parent==0)
            if(tree[j].weight<small1)
            {
                small2=small1;  //改变最小权、次小权及对应的位置
                small1=tree[j].weight;
                p2=p1;
                p1=j;
            }
        else
            if(tree[j].weight<small2)
            {
                small2=tree[j].weight;  //改变次小权及位置
                p2=j;
            }
    tree[p1].parent=i;
    tree[p2].parent=i;
    tree[i].lchild=p1;  //最小权根结点是新结点的左孩子
    tree[i].rchild=p2;  //次小权根结点是新结点的右孩子
    tree[i].weight=tree[p1].weight+tree[p2].weight;
    }
}



void huffmancode(codetype code[],hufmtree tree[],int n,char p[])//根据哈夫曼树求出哈夫曼编码
{
    printf("Each word translate to:\n");
    int i,c,x;
    int kk=0;
    codetype cd;   //缓冲变量
    for(i=0;i<n;i++)
    {
        printf("%c---",p[i]);
        cd.start=n;
        cd.ch=tree[i].ch;
        c=i;       //从叶结点出发向上回溯
        x=tree[i].parent;   //tree[p]是tree[i]的双亲
      //  while(x!=0)
      while(kk<level)
        {
            cd.start--;
            if(tree[x].lchild==c)
                cd.bits[cd.start]='0';   //tree[i]是左子树，生成代码'0'
            else
                cd.bits[cd.start]='1';   //tree[i]是右子树，生成代码'1'
            c=x;
            x=tree[x].parent;
            printf("%c",cd.bits[cd.start]);
            hl[i][kk]=cd.bits[cd.start];
            kk++;
        }
        code[i]=cd;    //第i+1个字符的编码存入code[i]
        printf("\n");
        kk=0;
    }
 //   int j=0;
//    for(i=0;i<s;i++)
 //   {
 //       for(j=0;j<n;j++)
 //       {
 //           if(m[i]==p[j])
 //           {
  //              for(kk=0;kk<5;kk++)
  //              {
  //                  printf("%c",hl[j][kk]);
  //              }
  //          }
  //      }
  //  }
}//huffmancode


int main()
{
   FILE *fp;
   char ch;
   int i=0;
   fp=fopen("test.txt","r");
    if(fp==NULL)
    {
        printf("Reading failed!\n");
        exit(0);
    }
    else
    {
        printf("the words are: \n");
        do
        {
            ch=fgetc(fp);
            if(ch==EOF)
                break;
                m[i]=ch;
                mm[i]=ch;
                printf("%c",ch);
                i++;
        }while(ch!=EOF);
    }
    printf("\n");
   int sum;
   sum=i;
   printf("total num :%d\n",sum);
   fclose(fp);
   i=1;
   int x=1;
   char c;
   c=m[0];
   for(i=1;i<sum;i++)
   {
       if(m[i]==c)
        x++;
   }
   printf(" '%c'--num=%d\n ",m[0],x);

   p[0]=m[0];
   q[0]=x;
   i=1;x=0;
   c=m[1];
   char ck;
   ck=m[0];
   int j;

   int aa=1;
    while(i<sum)
    {
        if(m[i]!=ck)
        {
            p[aa]=m[i];
            printf("'%c'",p[aa]);
            for(j=1;j<sum;j++)
            {
                if(m[j]!=ck)
                {
                    if(m[j]==c)
                    {
                    x++;
                    m[j]=ck;
                    }
                }
            }
            q[aa]=x;
            printf("--num=%d\n ",q[aa]);
            aa++;
        }

        i++;x=0;
        c=m[i];
    }

    int all;
    all=aa;
    printf("\nthe word all : %d\n\n",all);

    hufmtree tree[M];//hufmtree tree[]为求出的哈夫曼树
    codetype code[N];//codetype code[]为求出的哈夫曼编码
    huffman(tree,sum);
    huffmancode(code,tree,all,p);
    printf("\n\nthe final result is:\n");
    int k=0;

    FILE *fpp;
    fpp=fopen("result.txt","w");

    for(k=0;k<sum;k++)
    {
     //   printf("%d  %c--",k,mm[k]);
        for(i=0;i<all;i++)
        {
            if(mm[k]==p[i])
            {
                for(j=0;j<level;j++)
                {
                    printf("%c",hl[i][j]);
                    fprintf(fpp,"%c",hl[i][j]);

                }
            }

        }
        printf("\n");
    }
    printf("\n\n");
    printf("You can also see the result in the result.txt\n\n");
 //   decode(tree,code);
    return 0;
}
