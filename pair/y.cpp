
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
void qingkong();//��ʼ��ȫ�ֱ���
char s[50],n='1';  //s[50]���ڴ������ĸ�ֵ���ʽ
char Table[50][3];  //�����м��������ķ��ű�
int SIGN,sym,leap=0;  //symΪs[50]�е�ǰ������ŵ��±�,sym�ȵ�ǰ����ַ���һλ
int list_n=0;  //���ű���±�
/*������ݹ鼰����
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
void A()  //  A -> V:=E,E��Լ���ٹ�Լ:=
{
    V();
    if(s[sym]==':'&&s[sym+1]=='=') //�жϸ�ֵ���Ƿ���ƴд����
    {
       sym+=2;
       E();
       printf("%s:=%s",Table[list_n-2],Table[list_n-1]);
       printf("     (:=,%s,-,%s)\n",Table[list_n-1],Table[list_n-2]);
    }
   
}
void V()  // V -> a|b|c|d|e...|z,�����ַ�
{
    if(islower(s[sym]))
    {
        Table[list_n][0] = s[sym];              //�Ѷ�ȡ��Сд��ĸ������ű����ڷ����������м����
        Table[list_n][1] = '\0';                //��̬������ĸ���ά����
        list_n++;
        sym++;
    }
   
}
void E()    //E -> TE',������ݹ�
{
    if(SIGN==0)
    {
        T();//������ݹ��һ��,�ȹ�Լ*,/��
        E1();//������ݹ�ڶ���,��Լ+,-��
    }
}
void T()  // T -> FT'
{
    if(SIGN==0)
    {
        F();//����()��
        T1();//��Լ*,/��,
    }
}
void E1()              //E'-> +TE'|-TE'|null
{
    int p;
    if(SIGN==0)
    {
        if(s[sym] == '+'||s[sym]=='-')
        {
            p=sym;                  //��p��¼����'+'��'-'ʱsym��ֵ
            sym++;
            T();
            char ch[3];
            ch[0] = 'T';
            ch[1] = n;
            ch[2] = '\0';
            if(s[p] == '+')
            {
                 printf("%s:=%s+%s",ch,Table[list_n-2],Table[list_n-1]);                //�������ַ����
                 printf("     (+,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);            //�����Ԫʽ
            }
        else
        {
            printf("%s:=%s-%s",ch,Table[list_n-2],Table[list_n-1]);              //�������ַ����
            printf("     (-,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);        //�����Ԫʽ
        }
        strcpy(Table[list_n-2],ch);          //����ǰ������ʽ���ڷ��ű���
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
                  printf("%s:=%s*%s",ch,Table[list_n-2],Table[list_n-1]);  //�������ַ����
                  printf("     (*,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);//�����Ԫʽ
             }
        else
        {
             printf("%s:=%s/%s",ch,Table[list_n-2],Table[list_n-1]);  //�������ַ����
             printf("     (/,%s,%s,%s)\n", Table[list_n-2],Table[list_n-1],ch);//�����Ԫʽ
        }
        strcpy(Table[list_n-2],ch);      //����ǰ������ʽ���ڷ��ű���
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
                printf("ERROR!����\n");
                SIGN=1;leap=1;
				main();
                exit(0);
            }
        }
        else if(islower(s[sym]))  //�ж�s[sym]�Ƿ���Сд��ĸ
        V();
        else
        {
            printf("ERROR!����\n");
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
/*ֵ����Ϣ,���ű�,����,������
�򵥸�ֵ���
�ݹ��½���������ԭ�������ú���֮��ĵݹ����ģ���﷨�����϶��µĹ�����̣�����ʵ�ַ����������£�

1��ÿ�����ս����Ӧһ������������

2������ʽ�Ҳ�Ϊ�ò���ʽ�����ս������Ӧ���������ġ������塱��

3������ʽ�Ҳ��ս����Ӧ�����봮�С����ġ����ս���Ĳ�����

4������ʽ�еġ�|����Ӧ�������еġ�if-else����䣻

5��������չ��BNF�ķ�������ʽ�еġ�{}����Ӧ�������еġ�while����䡣*/
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
char string[MAX];   //���ڴ�ű��ʽ  
int main() {      
	int p[MAX];     
	char ch;     
	int c=-1,q=0;           
	printf("�����븳ֵ���:\n");       
	while((ch = getchar())!='\n')     {
		string[m++]=ch;          
		if(ch=='='||ch=='+'||ch=='-'||ch=='*'||ch=='/')count++;          
		else if(ch=='(') {               
			p[++c]=m-1; }           
		else if(ch==')'){               
			q=m-1;
			SET_Mul_Div(p[c],q);    //�������Ŵ���������             
			SET_Add_Sub(p[c],q);             
			temp=(int)tempvar-1;             
			tempvar=(char)temp;               
			string[p[c]]=string[m-1]=tempvar;              
			c--;               
			temp=(int)tempvar+1;
			tempvar=(char)temp; }}       
	/********����������Ԫʽ�ĺ���********/      
	/*print();       
	/*********�ж��Ƿ�ɹ�**********/      
	/*if(count==0)          
		printf("Successful��\n");      
	else           
		printf("Wrong��");     
	printf("\n");     
	system("pause");  
}   
void SET_Mul_Div(int i,int m) //����˳����� 
{for(i++;i<=m-1;i++){
	if(string[i]=='*'||string[i]=='/') {
		printf("(%c   %c   %c   %c)\n",string[i],string[i-1],string[i+1], tempvar);
		string[i-1]=string[i]=string[i+1]=tempvar;
		count--;
		temp=(int)tempvar+1;
		tempvar=(char)temp;}}} 
void SET_Add_Sub(int j,int m) //����Ӽ�����
{j++;
for(;j<=m-1;j++){
	if(string[j]=='+'||string[j]=='-') {
		printf("(%c  %c  %c  %c)\n",string[j],string[j-1],string[j+1],tempvar);
		string[j-1]=string[j]=string[j+1]=tempvar; 
		count--;
		temp=(int)tempvar+1;
		tempvar=(char)temp; }}}
/*��ӡ*/
/*void print(){
	int i;
	for(i=0;i<=m-1;i++)//����˳�����
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
	for(j=0;j<=m-1;j++)//����Ӽ�����
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
	for(k=0;k<=m-1;k++)  //����ֵ����
	{
		if(string[k]=='='){
			temp=(int)tempvar--;
			tempvar=(char)temp;
			printf("(%c  %c     %c)  \n",string[k],string[k+1], string[k-1],tempvar);
			count--;
			string[k-1]=tempvar; }}} */