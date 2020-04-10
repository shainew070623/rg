/*【问题描述】

1、按先序遍历序列建立链式存储结构的二叉树；
2、实现二叉数先序、中序、后序的递归遍历算法，并输出结果；
3、实现二叉树按层次进行遍历，并输出结果。

【输入形式】按照先序输入二叉树中结点的值，字符*表示空树，每个字符之间用空格隔开

【输出形式】输出遍历结果
【样例输入】A B * C D * * * E * F G H * * K * * *
【样例输出】
A B C D E F G H K
B D C A E H G K F
D C B H K G F E A
A B E C F D G H K */

#include<iostream>
#include<queue>
using namespace std;

typedef struct node //队列节点
{
	char data;
	struct node *lchild;
	struct node *rchild;
}Node, *Bnode;

//二叉链表的建立
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

//先序遍历二叉树
void pretraverse(Bnode &T)
{
	if (T)
	{
		cout << T->data << " ";
		pretraverse(T->lchild);
		pretraverse(T->rchild);
	}

}

//中序遍历二叉树
void midtraverse(Bnode &T)
{
	if (T)
	{
		midtraverse(T->lchild);
		cout << T->data << " ";
		midtraverse(T->rchild);
	}
}

//后序遍历二叉树
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

