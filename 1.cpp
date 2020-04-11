/*������������

1��������������н�����ʽ�洢�ṹ�Ķ�������
2��ʵ�ֶ������������򡢺���ĵݹ�����㷨������������
3��ʵ�ֶ���������ν��б���������������

��������ʽ��������������������н���ֵ���ַ�*��ʾ������ÿ���ַ�֮���ÿո����

�������ʽ������������
���������롿A B * C D * * * E * F G H * * K * * *
�����������
A B C D E F G H K
B D C A E H G K F
D C B H K G F E A
A B E C F D G H K */

#include<iostream>
#include<queue>
using namespace std;

typedef struct node //���нڵ�
{
	char data;
	struct node *lchild;
	struct node *rchild;
}Node, *Bnode;

//��������Ľ���
void creatBitree(Bnode &T)
{
	char ch;
	cin >> ch;
	T = new Node;
	if (ch == '*')
		T = NULL;
	else
	{
		T->data = ch;
		creatBitree(T->lchild);
		creatBitree(T->rchild);
	}
}

//�������������
void pretraverse(Bnode &T)
{
	if (T)
	{
		cout << T->data << " ";
		pretraverse(T->lchild);
		pretraverse(T->rchild);
	}

}

//�������������
void midtraverse(Bnode &T)
{
	if (T)
	{
		midtraverse(T->lchild);
		cout << T->data << " ";
		midtraverse(T->rchild);
	}
}

//�������������
void posttraverse(Bnode &T)
{
	if (T)
	{
		posttraverse(T->lchild);
		posttraverse(T->rchild);
		cout << T->data << " ";
	}
}

void gratraverse(Bnode &T)
{
	queue<Bnode>qu;
	Bnode t;
	if (T)
	{
		qu.push(T);
		while (!qu.empty())
		{
			t = qu.front();
			qu.pop();
			cout << t->data << " ";
			if (t->lchild)
				qu.push(t->lchild);
			if (t->rchild)
				qu.push(t->rchild);
		}
	}
}

int main()
{
	Bnode T;
	creatBitree(T);
	pretraverse(T);
	cout << endl;
	midtraverse(T);
	cout << endl;
	posttraverse(T);
	cout << endl;
	gratraverse(T);
	//system("pause");
	return 0;


}

