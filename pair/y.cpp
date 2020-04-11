
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
void A();  //  A -> V:=E
void E();  //  E -> TE'
void T();  //  T -> FT'
void E1(); //  E'-> +TE'|-TE'|null
void T1(); //  T'-> *FT'|/FT'|null
void F();  //  F -> V|(E)
void V();  //  V -> a|b|c|d|e...|z
void qingkong();//初始化全局变量
char s[50],n='1';  //s[50]用于存放输入的赋值表达式
char Table[50][3];  //产生中间代码所需的符号表
int SIGN,sym,leap=0;  //sym为s[50]中当前读入符号的下标,sym比当前输出字符多一位
int list_n=0;  //符号表的下标
/*消除左递归及回溯
A -> V:=E
E -> TE'
E'-> +TE'|-TE'|null
T -> FT'
T'-> *FT'|/FT'|null
F -> V|(E)
V -> a|b|c|d|e...|z
*/
int main()

{
	qingkong();
    scanf("%s",s);
    A();
	system("pause");
    return 0;
}
void qingkong()
{
	leap=0;
	SIGN=0;
	
}
void A()  //  A -> V:=E,E规约完再规约:=
{
    V();
    if(s[sym]==':'&&s[sym+1]=='=') //判断赋值号是否有拼写错误
    {
       sym+=2;
       E();
       printf("%s:=%s",Table[list_n-2],Table[list_n-1]);
       printf("     (:=,%s,-,%s)\n",Table[list_n-1],Table[list_n-2]);
    }
   
}
void V()  // V -> a|b|c|d|e...|z,读入字符
{
    if(islower(s[sym]))
    {
        Table[list_n][0] = s[sym];              //把读取的小写字母存入符号表，便于分析是生成中间代码
        Table[list_n][1] = '\0';                //动态构造字母表二维数组
        list_n++;
        sym++;
    }
   
}
void E()    //E -> TE',消除左递归
{
    if(SIGN==0)
    {
        T();//消除左递归第一步,先规约*,/号
        E1();//消除左递归第二步,规约+,-号
    }
}
void T()  // T -> FT'
{
    if(SIGN==0)
    {
        F();//先算()号
        T1();//规约*,/号,
    }
}
void E1()              //E'-> +TE'|-TE'|null
{
    int p;
    if(SIGN==0)
    {
        if(s[sym] == '+'||s[sym]=='-')
        {
            p=sym;                  //用p记录出现'+'或'-'时sym的值
            sym++;
            T();
            char ch[3];
            ch[0] = 'T';
            ch[1] = n;
            ch[2] = '\0';
            if(s[p] == '+')
            {
                 printf("%s:=%s+%s",ch,Table[list_n-2],Table[list_n-1]);                //输出三地址代码
                 printf("     (+,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);            //输出四元式
            }
        else
        {
            printf("%s:=%s-%s",ch,Table[list_n-2],Table[list_n-1]);              //输出三地址代码
            printf("     (-,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);        //输出四元式
        }
        strcpy(Table[list_n-2],ch);          //将当前结果归结式放在符号表中
        list_n--;
        n++;
        E1();
       }
    }
}
void T1()  //  T'-> *FT'|/FT'|null
{
    int p;
    if(SIGN==0)
    {
        if(s[sym] == '*'||s[sym]=='/')
        {
             p=sym;
             sym++;
             F();
             char ch[3];
             ch[0] = 'T';
             ch[1] = n;
             ch[2] = '\0';
             if(s[p] == '*')
             {
                  printf("%s:=%s*%s",ch,Table[list_n-2],Table[list_n-1]);  //输出三地址代码
                  printf("     (*,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);//输出四元式
             }
        else
        {
             printf("%s:=%s/%s",ch,Table[list_n-2],Table[list_n-1]);  //输出三地址代码
             printf("     (/,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);//输出四元式
        }
        strcpy(Table[list_n-2],ch);      //将当前结果归结式放在符号表中
        list_n--;
        n++;
        T1();
        }
    }
}
void F()    //F -> V|(E)
{
    if(SIGN==0)
    {
        if(s[sym]=='(')
        {
            sym++;
            E();
            if(s[sym]==')')
            {
				sym++;
			}
			else
            {
                printf("ERROR!出错\n");
                SIGN=1;leap=1;
				main();
                exit(0);
            }
        }
        else if(islower(s[sym]))  //判断s[sym]是否是小写字母
        V();
        else
        {
            printf("ERROR!出错\n");
            SIGN=1;leap=1;
           main(); exit(0);
        }
    }
}


/*x:=a+b*c/d-(e+f)*/
/*
T1:=b*c     (*,b,c,T1)
T2:=T1/d     (/,T1,d,T2)
T3:=a+T2      (+,a,T2,T3)
T4:=e+f     (+,e,f,T4)
T5:=T3-T4     (-,T3,T4,T5)
x:=T5     (:=,T5,-,x)
*/
/*值的信息,符号表,类型,出错处理
简单赋值语句
递归下降分析法的原理是利用函数之间的递归调用模拟语法树自上而下的构造过程，具体实现方法概述如下：

1）每个非终结符对应一个解析函数；

2）产生式右侧为该产生式左侧非终结符所对应解析函数的“函数体”；

3）产生式右侧终结符对应从输入串中“消耗”该终结符的操作；

4）产生式中的‘|’对应函数体中的“if-else”语句；

5）对于扩展的BNF文法，产生式中的‘{}’对应函数体中的“while”语句。*/
/*#include<stdio.h> 
#include<stdlib.h>    
#define MAX 100  
void SET_Mul_Div(int i,int m);
void SET_Add_Sub(int j,int m); 
void print();   
int m=0; 
int count=0; 
char tempvar='A'; 
int temp;
char string[MAX];   //用于存放表达式  
int main() {      
	int p[MAX];     
	char ch;     
	int c=-1,q=0;           
	printf("请输入赋值语句:\n");       
	while((ch = getchar())!='\n')     {
		string[m++]=ch;          
		if(ch=='='||ch=='+'||ch=='-'||ch=='*'||ch=='/')count++;          
		else if(ch=='(') {               
			p[++c]=m-1; }           
		else if(ch==')'){               
			q=m-1;
			SET_Mul_Div(p[c],q);    //从左括号处理到又括号             
			SET_Add_Sub(p[c],q);             
			temp=(int)tempvar-1;             
			tempvar=(char)temp;               
			string[p[c]]=string[m-1]=tempvar;              
			c--;               
			temp=(int)tempvar+1;
			tempvar=(char)temp; }}       
	/********调用生成四元式的函数********/      
	/*print();       
	/*********判断是否成功**********/      
	/*if(count==0)          
		printf("Successful！\n");      
	else           
		printf("Wrong！");     
	printf("\n");     
	system("pause");  
}   
void SET_Mul_Div(int i,int m) //处理乘除运算 
{for(i++;i<=m-1;i++){
	if(string[i]=='*'||string[i]=='/') {
		printf("(%c   %c   %c   %c)\n",string[i],string[i-1],string[i+1], tempvar);
		string[i-1]=string[i]=string[i+1]=tempvar;
		count--;
		temp=(int)tempvar+1;
		tempvar=(char)temp;}}} 
void SET_Add_Sub(int j,int m) //处理加减运算
{j++;
for(;j<=m-1;j++){
	if(string[j]=='+'||string[j]=='-') {
		printf("(%c  %c  %c  %c)\n",string[j],string[j-1],string[j+1],tempvar);
		string[j-1]=string[j]=string[j+1]=tempvar; 
		count--;
		temp=(int)tempvar+1;
		tempvar=(char)temp; }}}
/*打印*/
/*void print(){
	int i;
	for(i=0;i<=m-1;i++)//处理乘除运算
	{
		if(string[i]=='*'||string[i]=='/')
		{printf("(%c  %c  %c  %c)\n",string[i],string[i-1],string[i+1],tempvar);
		string[i-1]=string[i]=string[i+1]=tempvar;
		count--;
		temp=(int)tempvar+1;
		tempvar=(char)temp; 
		}
	}
	int j;
	for(j=0;j<=m-1;j++)//处理加减运算
	{
		if(string[j]=='+'||string[j]=='-')
		{
			printf("(%c  %c  %c  %c)\n",string[j],string[j-1],string[j+1],tempvar);
			string[j-1]=string[j]=string[j+1]=tempvar;
			count--;
			temp=(int)tempvar+1;
			tempvar=(char)temp;
	}}
	int k;
	for(k=0;k<=m-1;k++)  //处理赋值运算
	{
		if(string[k]=='='){
			temp=(int)tempvar--;
			tempvar=(char)temp;
			printf("(%c  %c     %c)  \n",string[k],string[k+1], string[k-1],tempvar);
			count--;
			string[k-1]=tempvar; }}} */