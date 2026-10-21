#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int fult;
struct fream
{
int page_num;
int occupide;
int dirty;
int referance;
};
int main(int argc,char **argv)
{
FILE* fp;
int index;
if(argc!=6)
{
printf("uasg:v_size page fream file r/w\n");
return 0;
}
int d;
if(argv[5][0]=='d')
d=1;
else
d=0;
unsigned int page,page_size,frame,v_size,page_no;
v_size=1<<atoi(argv[1]);
page=atoi(argv[2]);
frame=atoi(argv[3]);
page_size=1<<page;
printf("virtual memory size:%d\n",v_size);
printf("number of pages:%d   each page size:%d\n",v_size/page_size,page_size);
printf("number of freams:%d\n",frame);


fp=fopen(argv[4],"r");
if(fp==0)
{
printf("file not found\n");
return 0;
}
unsigned long addr;
char op;
int i,foun=0;
struct fream f[100];
for(i=0;i<frame;i++)
{
f[i].page_num=0;
f[i].occupide=0;
f[i].dirty=0;
f[i].referance=0;
}
while(fscanf(fp,"%lu %c",&addr,&op)==2)
{
if(addr>=v_size)
{
printf("address :%lu of out of range\n",addr);
continue;
}
foun=0;
page_no=addr/page_size;
for(i=0;i<frame;i++)
{
if(f[i].occupide==1&&f[i].page_num==page_no)
{
  foun=1;
 if(f[i].referance<10)
 f[i].referance++;
 if(argv[5][0]=='d')
 printf("page no %d alredy exist\n",page_no);
 continue;
}
}
index=0;
if (foun == 0)
{
    for (int i = 0; i <frame; i++)
    {
        if (f[i].occupide == 0)
        {
            f[i].page_num = page_no;
            f[i].occupide = 1;
            if(op=='w')
             f[i].dirty=1;
             else
            f[i].dirty = 0;
            f[i].referance = 3;
            index=1;
            break;

        }
    }
}
if(index==1)
{
if(argv[5][0]=='d')
printf("empty fream filed with page no:%d\n",page_no);
continue;
}
else
{
fult++;
if(argv[5][0]=='d')
printf("fulty page exist\n");
while(1)
{
for(int i=0;i<frame;i++)
{
 if(f[i].referance==0)
     {      
            f[i].page_num = page_no;
            f[i].occupide = 1;
            if(op=='w')
             f[i].dirty=1;
             else
            f[i].dirty = 0;
            f[i].referance = 3;
            index=1;
            break;
     }
}
  if(index==1)
  break;
  else
  {
    for(i=0;i<frame;i++)
   {
    f[i].referance--;
  }
}
}
if(argv[5][0]=='d')
printf("fulty page replacement happen\n"); 
}
printf("address:%lu operation:%c page number:%d\n",addr,op,page_no);
}
printf("page fult:%d\n",fult);
}



