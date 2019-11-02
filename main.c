#include <stdio.h>
#include <stdlib.h>
#define Max 100//��������������λ��
char m[Max];//�洢ԭʼ����
char mm[Max];//�洢ԭʼ����
char p[Max];//�洢����
int q[Max];//�洢���ų��ֵĴ���
int hl[Max][Max];
#define N 100  //Ҷ����Ŀ
#define M (2*N-1)    //�������
#define maxval 10000.0
int level=10;//������
typedef struct
{
    char ch;
    float weight;
    int lchild,rchild,parent;
}hufmtree;

typedef struct
{
    char bits[N];   //λ��
    int start;      //������λ���е���ʼλ��
    char ch;        //�ַ�
}codetype;

void huffman(hufmtree tree[],int n)//������������
{
    int i,j,p1,p2;//p1,p2�ֱ��סÿ�κϲ�ʱȨֵ��С�ʹ�С�������������±�
    float small1,small2;
    for(i=0;i<M;i++)    //��ʼ��
    {
        tree[i].parent=0;
        tree[i].lchild=-1;
        tree[i].rchild=-1;
        tree[i].weight=0.0;
    }
    for(i=0;i<n;i++)  //����ǰn�������ַ���Ȩֵ
    {

        tree[i].ch=p[i];
        tree[i].weight=q[i];

    }
    for(i=n;i<M;i++)      //����n-1�κϲ�������n-1���½��
    {
        p1=0;p2=0;
        small1=maxval;small2=maxval;   //maxval��float���͵����ֵ
        for(j=0;j<i;j++)    //ѡ������Ȩֵ��С�ĸ����
        if(tree[j].parent==0)
            if(tree[j].weight<small1)
            {
                small2=small1;  //�ı���СȨ����СȨ����Ӧ��λ��
                small1=tree[j].weight;
                p2=p1;
                p1=j;
            }
        else
            if(tree[j].weight<small2)
            {
                small2=tree[j].weight;  //�ı��СȨ��λ��
                p2=j;
            }
    tree[p1].parent=i;
    tree[p2].parent=i;
    tree[i].lchild=p1;  //��СȨ��������½�������
    tree[i].rchild=p2;  //��СȨ��������½����Һ���
    tree[i].weight=tree[p1].weight+tree[p2].weight;
    }
}



void huffmancode(codetype code[],hufmtree tree[],int n,char p[])//���ݹ��������������������
{
    printf("Each word translate to:\n");
    int i,c,x;
    int kk=0;
    codetype cd;   //�������
    for(i=0;i<n;i++)
    {
        printf("%c---",p[i]);
        cd.start=n;
        cd.ch=tree[i].ch;
        c=i;       //��Ҷ���������ϻ���
        x=tree[i].parent;   //tree[p]��tree[i]��˫��
      //  while(x!=0)
      while(kk<level)
        {
            cd.start--;
            if(tree[x].lchild==c)
                cd.bits[cd.start]='0';   //tree[i]�������������ɴ���'0'
            else
                cd.bits[cd.start]='1';   //tree[i]�������������ɴ���'1'
            c=x;
            x=tree[x].parent;
            printf("%c",cd.bits[cd.start]);
            hl[i][kk]=cd.bits[cd.start];
            kk++;
        }
        code[i]=cd;    //��i+1���ַ��ı������code[i]
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

    hufmtree tree[M];//hufmtree tree[]Ϊ����Ĺ�������
    codetype code[N];//codetype code[]Ϊ����Ĺ���������
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
