#include <conio>
#include <math>
#include <graphics>
#include <dos>
#include <process>
#include <stdlib>
#include <fstream>
//#include <string>
#define pi 3.14159

int lx[50][2],ly[50][2];
int arcd[50][2],rad=25;
int t=0,n;																		  //Player number
int health[2];
int X[2],Y[2];
int tot=4;
int driver=VGA,mode=VGAHI;
//-----------------------------------Fns----------------------------------------

int rdof(double);
int atoi(char a[]);
void credits();
void load(int);
void mapcreate();
void mapcreat();
void terraincnt();
//terrain tester
int lassess(int X,int Y,int x[][2]=lx,int y[][2]=ly);
int cassess(int trn,int X,int Y,int T);
//health
void win(int w);
void hlth();
void hred(int tnk);
//drawing
void slidetxtxy(int x,int y1,int y2,char a[],char b[],int col,int d=2,int sp=1);
void exp(int T=t,int r=rad,int A[][2]=arcd);
void tank(int A,int t,int col=15);
void terrain();
void parab(int t,int A,int u,int d=0);
void outergame();
//-----------------------------------Fns----------------------------------------

void outergame()
{
 int driver=VGA,mode= VGAHI,i;
 initgraph (&driver,&mode,"c:/bc5/bgi");

 setcolor(13);

 setcolor(2);

 outtextxy(265,220,"Loading Map...");
 setcolor(14);
 rectangle(279,238,354,248);
 for(i=280;i<349;i++)                             //progress bar
  {
   delay (40);
   outtextxy(i,240,"|");
  }
 outtextxy(265,260,"Press any key");
 getch();
}


void mainmenu()
{
 ::t=0;
 terraincnt();
 initgraph(&driver,&mode,"c:/bc5/bgi/");
 char inp,inp2;
 sleep(2);

 settextstyle(9,0,4);
 slidetxtxy(350,100,50,"ZONE","BLAST",4,1,2);

 settextstyle(6,0,2);
 slidetxtxy(275,200,350,"1. new gAme","4 eXit",2,1,7);
 slidetxtxy(260,250,300,"2 terrain Builder","3 Credits",2,1,7);

 settextstyle(2,0,4);
 slidetxtxy(300,10,450,"Version1.1","keerthik(r),copyright 2005-06",4,1,7);

choose:
 float i=0;
 int mnum='0';
 char min[5];
 getch();
 setcolor(0);
 outtextxy(100,400,"Invalid input!!Press any key to reenter");
 inp=getch();

 switch(inp)
 {
  case '1':case 'a':case 'A':
   initgraph(&driver,&mode,"c:/bc5/bgi");
   settextstyle(2,0,9);
   slidetxtxy(300,160,320,"1. Enter Map","2. Random Map!!",8,1,2);
  choose2:
   getch();
	setcolor(0);
	outtextxy(100,400,"Invalid input!!Press any key to reenter");
   setcolor(8);
   inp2=getch();
   switch(inp2)
    {
     case '1':
      initgraph(&driver,&mode,"c:/bc5/bgi");
     chose:
      outtextxy(100,100,"Enter Mapnum [0 or non-numerics for random]: ");
      gotoxy(20,8);
      cout<<"     ";
      gotoxy(20,8);
      cin>>min;
      mnum=atoi(min);
      if(mnum<0||mnum>tot)
		 {
		  gotoxy(17,15);
		  cout<<"Invalid map no...Enter between 1 and "<<tot<<" [maximum so far]";
        goto chose;
		 }
     break;
     case '2':
	   mnum=0;
     break;
  	  default:
      setcolor(9);
      outtextxy(100,400,"Invalid input!!Press any key to reenter");
		goto choose2;
    }
   load(mnum);
  break;
  case '2':case 'b':case 'B':mapcreat();mainmenu();break;
  case '3':case 'c':case 'C':credits();break;
  case '4':case 'x':case 'X':case char(27):exit(1);break;
  default:setcolor(9);
   		 outtextxy(100,400,"Invalid input!!Press any key to reenter");
          while(i<100&&!kbhit())
           i+=.01;
  		    goto choose;
 }

}

//-------------------------------Support funtions-------------------------------------

//---------convert string to integer
int atoi(char a[])
{
 int l=strlen(a);
 int x=0;

 for(int i=1;i<=l;i++)
  if(int(a[l-i])<48||int(a[l-i])>57)
   return 0;

 for(int i=1;i<=l;i++)
  x+=pow(10,i-1)*(int(a[l-i])-48);

 return x;
}

//--------Round off numbers
int rdof(double x)
{
 float k=x-int(x);
 if(k>.5)
  return int(x)+1;
 else
  return int(x);
}

//--------total maps in file
void terraincnt()
{
 int a;
 tot=-1;
 ifstream fin;

 fin.open("map.txt");
 while(!fin.eof())
  {
   fin>>n;
   for(int j=0;j<(2*n+2);j++)
    fin>>a;
   tot++;
  }
 fin.close();
}
//-------------------------------Styletext--------------------------------------
void slidetxtxy(int x,int y,int y2,char a[],char b[],int col,int d,int sp)
{
 int i=0;
 float j=1;

 do
  {
   setcolor(col);
   outtextxy(i,y,a);
   outtextxy(580-i,y2,b);
   if(i>.7*x)
    j++;
   delay(rdof(j/sp));
   setcolor(0);
   outtextxy(i,y,a);
   outtextxy(580-i,y2,b);
   i++;
  }while(i<x&&!kbhit());
 setcolor(col);
 outtextxy(x,y,a);
 outtextxy(580-x,y2,b);
 if(d==1)
  goto end;

 i=x;
 do
  {
   setcolor(col);
   outtextxy(i,y,a);
   outtextxy(580-i,y2,b);
   if(i<(x+.3*(580-x))&&j>1)
    j--;
   delay(rdof(j/sp));
   setcolor(0);
   outtextxy(i,y,a);
   outtextxy(580-i,y2,b);
   i++;
  }while(i<580&&!kbhit());

end:
 delay(100);
}
//------------------------------------Credits-----------------------------------
void credits()
{
 initgraph(&driver,&mode,"c:/bc5/bgi/");

 setcolor(15);
 sleep(1);
 settextstyle(9,0,3);
 outtextxy(270,25,"CREDITS");
 settextstyle(100,0,3);
 slidetxtxy(220,100,380,"Graphics","Keerthik",1);
 slidetxtxy(200,220,260,"Gameplay","Keerthik",1);
 slidetxtxy(275,150,190,"Coding","Keerthik",1);
 slidetxtxy(240,290,330,"Documentation","Keerthik",1);

 getch();
 mainmenu();
}

//-----------------------------------Victory------------------------------------
void win(char w)
{

 char winner[14]="Player   WINS";
 winner[7]=w;

 settextstyle(9,0,4);
 slidetxtxy(240,170,300,"GAME OVER",winner,4);
 getch();
 credits();

}
//-------------------------------Draw health bars-------------------------------
void hlth()
{
 setcolor(2);

 for(int i=20;i<health[0];i++)
  line(i,430,i,440);

 for(int i=620;i>health[1];i--)
  line(i,430,i,440);
}

void hred(int tnk)
{
 setcolor(0);

 switch(tnk)
 {
 case 0:
  if(health[0]>50)
   {
    for(int i=health[0];i>health[0]-35;i--)
     {
      delay(25);
      line(i,430,i,440);
     }
    health[0]-=35;
   }
  else
   {
    for(int i=health[0];i>20;i--)
     {
      delay(25);
      line(i,430,i,440);
     }
    health[0]=20;
    win('2');
   }
  break;

 case 1:
  if(health[1]<590)
   {
    for(int i=health[1];i<health[1]+35;i++)
     {
      delay(25);
      line(i,430,i,440);
     }
    health[1]+=35;
   }
  else
   {
    for(int i=health[1];i<620;i++)
     {
      delay(25);
      line(i,430,i,440);
     }
    health[1]=620;
    win('1');
   }
  break;

 default:;

 }
}

//------------------------------draw exploded regions---------------------------
void exp(int T,int r,int A[][2])
{
 double X1,X2,Y1,Y2;
 for(X1=A[T][0]+r;X1>A[T][0]-r;X1--)
  {
   Y1=A[T][1]+sqrt(pow(r,2)-pow(X1-A[T][0],2));
   Y2=A[T][1]-sqrt(pow(r,2)-pow(X1-A[T][0],2));
   if(lassess(X1,rdof(Y1))!=0&&cassess(T,X1,rdof(Y1),0)==0)
    putpixel(X1,rdof(Y1),7);
   if(lassess(X1,rdof(Y2))!=0&&cassess(T,X1,rdof(Y2),0)==0)
    putpixel(X1,rdof(Y2),7);
  }
 for(Y1=A[T][1]+r;Y1>A[T][1]-r;Y1--)
  {
   X1=A[T][0]+sqrt(pow(r,2)-pow(Y1-A[T][1],2));
   X2=A[T][0]-sqrt(pow(r,2)-pow(Y1-A[T][1],2));
   if(lassess(rdof(X1),Y1)!=0&&cassess(T,rdof(X1),Y1,0)==0)
    putpixel(rdof(X1),(Y1),7);
   if(lassess(rdof(X2),Y1)!=0&&cassess(T,rdof(X1),Y1,0)==0)
    putpixel(rdof(X2),(Y1),7);
  }
}

//-------------------------------draw tank--------------------------------------
void tank(int A,int t,int col)
{
 setcolor(col);

 double a=(A*pi)/180;
 double x,y;
 int k=t%2;
 if(k==0)
  {
   x=X[k]+15*cos(a);
   y=Y[k]-tan(a)*(x-X[k]);
  }
 else
  {
   x=X[k]-15*cos(a);
   y=Y[k]+tan(a)*(x-X[k]);
  }

 line(X[k],Y[k],rdof(x),rdof(y));
 rectangle(X[k]-8,Y[k],X[k]+8,Y[k]+10);
}

//------------------------------Load terrain------------------------------------

void load(int randchoose=0)
{
 int a;
 int mnum;
 ifstream fin;
 fin.open("map.txt");
 randomize();
 if(randchoose==0)
  mnum=random(tot);
 else
  if(randchoose<=tot)
   mnum=randchoose-1;
  else
   {
    gotoxy(25,15);
    cout<<"Invalid map no.  total="<<tot;
    sleep(2);
    mainmenu();
   }

 for(int i=0;i<mnum;i++)
  {
   fin>>n;
   for(int j=0;j<(2*n+2);j++)
    fin>>a;
  }
 fin>>n;
 fin>>lx[0][0]>>ly[0][0];
 for(int i=0;i<n;i++)
  {
   fin>>lx[i][1]>>ly[i][1];
   lx[i+1][0]=lx[i][1];
   ly[i+1][0]=ly[i][1];
  }
 fin.close();

 X[0]=10;
 Y[0]=ly[0][0]-10;
 health[0]=120;

 X[1]=630;
 Y[1]=ly[n-1][1]-10;
 health[1]=520;
}

//----------------------------Terrain Editor------------------------------------
/*
void preview()
{
 load(tot);
 terrain();
}

void out(char x[])
{
 if(atoi(x)==0)
  mainmenu();
}

void mapcreate()
{
 initgraph(&driver,&mode,"c:/bc5/bgi/");
 char y[4]="310",x[4]="30",n2[3];
 int t=atoi(x),t2;

 setcolor(15);
 cout<<"\t\t\t\tTERRAIN BUILDER(TM)\n\n\t\t[Enter 0 or non-numeric characters \
at any point to exit]";

strt1:
 cout<<"\n\nEnter desired number of non-horizontal terrain segments[>0 & <8]: ";
 cin>>n2;
 out(n2);
 n=atoi(n2);
 if(n>8)
  {cout<<"invalid\n";goto strt1;}

strt2:
 cout<<"\nEnter height of start of terrain[>50 and <475]: ";
 cin>>y;
 out(y);
 if(atoi(y)<50||atoi(y)>475)
  {cout<<"invalid\n";goto strt2;}

 ofstream fout;
 fout.open("map.txt",ios::app);
 fout<<"\n"<<n+2<<' '<<0<<' '<<y;
 cout<<"Start Non-parallel segments:\nSegment 1:\n";
strt3:
 cout<<"Enter terrain x-coord[>"<<t<<" and <610]: ";
 cin>>x;
 out(x);
 outtextxy(245,20,"--PREVIEW(background)--");
 t2=atoi(y);
 line(0,t2,atoi(x),t2);
 if(atoi(x)<=t||atoi(x)>=610)
  {cout<<"invalid\n\n";goto strt3;}
 t=atoi(x);

 fout<<' '<<x<<' '<<y;

 for(int i=0;i<n-1;i++)
  {
   strt4:
   cout<<"Segment "<<i+2<<":\n";
   cout<<"Enter next terrain x-coord[>"<<t<<" and <610]: ";
   cin>>x;
   out(x);
   cout<<"Enter next terrain y-coord[>50 and <450]: ";
   cin>>y;
   out(y);
   if(atoi(x)<=t||atoi(x)>610||atoi(y)<50||atoi(y)>450)
    {cout<<"invalid\n";goto strt4;}
   line(t,t2,atoi(x),atoi(y));
   fout<<' '<<x<<' '<<y;
   t=atoi(x);
   t2=atoi(y);
  }

strt5:
 cout<<"\n--Non-parallel segments complete--\nEnter starting x-coord[>"<<t;
 cout<<" and <620] of last terrain segment: ";
 cin>>x;
 out(x);
 cout<<"\nEnter height of finish of terrain[>50 and <450]: ";
 cin>>y;
 out(y);

 if(atoi(x)<t||atoi(x)>620||atoi(y)<50||atoi(y)>450)
  {cout<<"invalid\n\n";goto strt5;}
 line(t,t2,atoi(x),atoi(y));
 fout<<' '<<x<<' '<<y<<' '<<640<<' '<<y;
 t2=atoi(y);
 line(t,t2,640,atoi(y));
 fout.close();

 terraincnt();

 cout<<"\n\t\t\t\tCREATING MAP NUMBER "<<tot<<" !!!";
 rectangle(268,428,372,442);
 setcolor(0);
 rectangle(267,427,373,443);
 setcolor(15);

 for(int i=270;i<371;i++)
  {
   delay(25);
   line(i,430,i,440);
  }
 preview();

 getch();

}
*/
//-------------alternate mapcreator------------------

void crosshair(int x,int y)
{
 circle(x,y,2);
 line(x,y-5,x,y+5);
 line(x-5,y,x+5,y);
}

void mapcreat()
{
 initgraph(&driver,&mode,"c:/bc5/bgi/");
 int x[50]={0},y[50]={0},n=0,a=0;

 setcolor(3);
 outtextxy(245,10,"--TERRAIN BULDER --");
 outtextxy(245,30,"Press [Esc] to exit");
 setcolor(15);
 outtextxy(5,450,"Cursor keys to move the crosshair, enter to\
  place map vertex");
 while(x[n]!=640)
  {
   a=getch();
   while(a!=13)
    {
     setcolor(0);
     crosshair(x[n],y[n]);
     if(a==77&&x[n]<640&&n!=0)
      x[n]+=2;
     if(a==75&&x[n]>x[n-1])
      x[n]-=2;
     if(a==80&&y[n]<450)
      y[n]+=2;
     if(a==72&&y[n]>35)
      y[n]-=2;
     if(a==27)
      mainmenu();
     setcolor(4);
     crosshair(x[n],y[n]);
     a=getch();
    }
   setcolor(15);
   circle(x[n],y[n],3);
   line(x[n-1],y[n-1],x[n],y[n]);
   x[n+1]=x[n];
   y[n+1]=y[n];
   n++;
  }

 n-=1;
 ofstream fout;
 fout.open("map.txt",ios::app);
 fout<<"\n"<<n<<' ';
 for(int i=0;i<n+2;i++)
  fout<<x[i]<<' '<<y[i]<<' ';
 fout.close();

 terraincnt();

 outtextxy(200,410,"CREATING MAP");
 gotoxy(40,10);
 cout<<tot;
 rectangle(268,428,372,442);
 setcolor(0);
 rectangle(267,427,373,443);
 setcolor(15);

 for(int i=270;i<371;i++)
  {
   delay(25);
   line(i,430,i,440);
  }

}

//------------------------------Draw terrain------------------------------------

void terrain()
{
 setcolor(15);
 for(int i=0;i<n;i++)										//Terrain
  line(lx[i][0],ly[i][0],lx[i][1],ly[i][1]);
 for(int i=0;i<t;i++)
  exp(i,rad,arcd);

 setcolor(0);
 setfillstyle(0,0);
 for(int i=0;i<t;i++)
  for(int j=0;j<rad;j++)                           //removed terrain
   fillellipse(arcd[i][0],arcd[i][1],j,j);

 setcolor(15);                                     //Health bar
 rectangle(18,428,121,442);
 rectangle(622,428,519,442);
 hlth();

}

//------------------------Fns:Chk if pt lies within terrain---------------------

int lassess(int X,int Y,int x[][2],int y[][2])
{
 int i=0;
 strt:
 float dy=y[i][1]-y[i][0],dx=x[i][0]-x[i][1];

 if(dx==0)
  {
   if(X==x[i][0])
    if((dy>0&&Y<y[i][1]&&Y>y[i][0])||(dy<0&&Y>y[i][1]&&Y<y[i][0]))
     return i+1;
    else
     return 0;
   else
    i++;
  }
 else
{
 double m=dy/dx;

 double y2=y[i][0]+m*(x[i][0]-X);

 if(X>=x[i][0]&&X<=x[i][1])
  {
   if(Y>y2)
    return i+1;
   else
    return 0;                                            //valid
  }
 else
  i++;
}
 if(i<n)
  goto strt;

}

int cassess(int trn,int X,int Y,int T=0)
{
 int hit=0;
 strt:
 if(pow(X-arcd[T][0],2)+pow(Y-arcd[T][1],2)<pow(rad,2))
  {
   hit=T;
   return -1;															//valid
  }
 else
  if(T<trn)
   {
    T++;
    goto strt;
   }
 return hit;
}

//---------------------------Draw parabola--------------------------------------

void parab(int t,int A,int u,int d)
{
 double a=(A*pi)/180;
 int x=0;

 int p=t%2;
 double k=9.8/(2*pow(u*cos(a),2)),y=Y[p]-((tan(a)*x)-(k*x*x));
//double r=u*u*sin(2*a)/9.8,

 if(p!=0)
  a=pi-a;

 do
  {
   y=Y[p]-((tan(a)*x)-(k*x*x));

   delay(d);
//   setcolor(0);
   putpixel(x+X[p],rdof(y),4);

   if(t%2==0)
    x++;
   else
    x--;
  }while( x+X[p]>0&&x+X[p]<640 && rdof(y)<460 &&
  			(lassess(x+X[p],rdof(y))==0||cassess(t,x+X[p],rdof(y))==-1) );

 setcolor(4);
 setfillstyle(1,12);
 for(int i=0;i<rad;i++)
  {
   delay(d);
   fillellipse(x+X[p],rdof(y),i,i);
  }
 setcolor(0);
 setfillstyle(1,0);
 for(int i=0;i<rad;i++)
  {
   delay(d);
   fillellipse(x+X[p],rdof(y),i,i);
  }

 arcd[t][0]=x+X[p];
 arcd[t][1]=rdof(y);

 exp(t,rad,arcd);
}

//-------------------------------------Main-------------------------------------

void main()
{
 restrt:
 ::t=0;
 mainmenu();
 outergame();
 strt:
 initgraph(&driver,&mode,"c:/bc5/bgi/");
 int A=15,a=0,u=10;                              //Angle,input var,init velocity

 terrain();

 while(a!=13)
 {
  gotoxy(t%2==0?1:60,1);
  cout<<"Angle:    ";
  gotoxy(t%2==0?1:60,2);
  cout<<"Launch vel.:     ";

  gotoxy(t%2==0?7:67,1);
  cout<<A;
  gotoxy(t%2==0?13:73,2);
  cout<<u;

  tank(A,t);
  tank(15,t+1);
  a=getch();
  tank(A,t,0);

  if((a==75&&t%2==0&&A<88)||(a==77&&t%2!=0&&A<88))
   A++;
  if((a==75&&t%2!=0&&A>2)||(a==77&&t%2==0&&A>2))
   A--;
  if(a==72&&u<100)
   u++;
  if(a==80&&u>2)
   u--;
  if(a==27)
   goto restrt;
 }
 tank(A,t);
 parab(t,A,u,10);
 t++;

 if(cassess(t,X[0],Y[0],t-1)==-1)
  {
   hred(0);
   X[0]=arcd[t-1][0];
   Y[0]=arcd[t-1][1]+rad-10;
  }
 if(cassess(t,X[1],Y[1],t-1)==-1)
  {
   hred(1);
   X[1]=arcd[t-1][0];
   Y[1]=arcd[t-1][1]+rad-10;
  }

 a=getch();
 if(a==13)
  a++;
 goto strt;
}
