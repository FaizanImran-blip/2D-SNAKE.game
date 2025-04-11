#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>
using namespace std;
enum direct{st=0,left,right,up,down};
direct d;
int h=20;
int w=20;
int fx,fy;
int tx,ty;
int s;
int tail_x[100],tail_y[100];
int t_len;
bool g;
void set();
void logic();
void inp();
void dr();
int main()
{
cout<<"|--------------------------------|"<<endl;
cout<<"::::::::::::SNAKE GAME::::::::::::"<<endl;
cout<<"|--------------------------------|"<<endl;
cout<<"--Press enter to Start the game--"<<endl;
getch();
set();
while(!g)
{
    dr();
    inp();
    logic();
    Sleep(30);
    system("cls");
}
}
void set()
{
    d=st;
    g=false;
    tx=w/2;
    ty=h/2;
    fx=rand()%w;
    fy=rand()%h;
    s=0;
}
void dr()
{
    system("cls");
    cout<<"\t\t";
    for(int i=0;i<w-8;i++)
    {
        cout<<"||";
    }
    cout<<endl;
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            if(j==0)
            {
                cout<<"\t\t||";
            }
            else if(i==tx&&j==ty)
            {
                cout<<"O";
            }
            else if(i==fx&&j==fy)
            {
                cout<<"*";
            }
            else{
                bool p=false;
                for(int k=0;k<t_len;k++)
                {
                    if(tail_x[k]==j&&tail_y[k]==i)
                    {
                        cout<<"O";
                        p=true;
                    }
            
                }
                if (!p)
                {
                    cout<<" ";
                } 
            }
            if(j==w-1)
             {
              cout<<" ||";
             }
        }
        cout<<endl;
    }
    cout<<"\t\t";
    for(int i=0;i<w-8;i++)
    {
        cout<<"||";
    }
    cout<<endl;
    cout<<endl;
    cout<<"\t\t\tScore:"<<"["<<s<<"]"<<endl;
}
void inp()
{
  if(_kbhit())
switch(getch())
{
    case 'a':
    d=left;
    break;
    case 's':
    d=down;
    break;
    case 'w':
    d=up;
    break;
    case 'd':
    d=right;
    break;
    default:
    break;
}
}
void logic()
{
    int px = tail_x[0];
    int py = tail_y[0];
    int p2x, p2y;
    tail_x[0] = tx;
    tail_y[0] = ty;
    for(int i = 1; i < t_len; i++){
        p2x = tail_x[i];
        p2y = tail_y[i];
        tail_x[i] = px;
        tail_y[i] = py;
        px = p2x;
        py = p2y;
}
switch(d)
{
    case up:
    ty--;
    break;
    case down:
    ty++;
    break;
    case right:
    tx++;
    break;
    case left:
    tx--;
    break;
    default:
    break;
}
if(tx >= w){
    tx = 0;
}
else if(tx < 0){
    tx = w - 1;
}
if(ty >= h){
    ty = 0;
}
else if(ty < 0){
    ty = h - 1;
}
for(int i = 0; i < t_len; i++){
    if(tail_x[i] == tx && tail_y[i] == ty){
        g = true;
    }
}
if(tx == fx && ty == fy){
    s += 10;
    fx = rand()%w;
    fy = rand()%h;
    t_len++;
}
}
