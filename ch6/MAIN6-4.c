/* main6-4.c ����bo6-4.c�������� */
#include "../ch1/c1.h"
typedef char TElemType;
TElemType Nil = ' '; /* �Կո��Ϊ�� */
#include "c6-4.h"
#include "bo6-4.c"

void vi(TElemType c)
{
	printf("%c ", c);
}

void main()
{
	int i;
	PTree T, p;
	TElemType e, e1;
	InitTree(&T);
	printf("���������,���շ�? %d(1:�� 0:��) ����Ϊ%c �������Ϊ%d\n", TreeEmpty(T), Root(T), TreeDepth(T));
	CreateTree(&T);
	printf("������T��,���շ�? %d(1:�� 0:��) ����Ϊ%c �������Ϊ%d\n", TreeEmpty(T), Root(T), TreeDepth(T));
	printf("���������T:\n");
	TraverseTree(T, vi);
	printf("��������޸ĵĽ���ֵ ��ֵ: ");
	scanf("%c%*c%c%*c", &e, &e1);
	Assign(&T, e, e1);
	printf("��������޸ĺ����T:\n");
	TraverseTree(T, vi);
	printf("%c��˫����%c,������%c,��һ���ֵ���%c\n", e1, Parent(T, e1), LeftChild(T, e1), RightSibling(T, e1));
	printf("������p:\n");
	InitTree(&p);
	CreateTree(&p);
	printf("���������p:\n");
	TraverseTree(p, vi);
	printf("����p�嵽��T�У�������T��p��˫�׽�� �������: ");
	scanf("%c%d%*c", &e, &i);
	InsertChild(&T, e, i, p);
	Print(T);
	printf("ɾ����T�н��e�ĵ�i��������������e i: ");
	scanf("%c%d", &e, &i);
	DeleteChild(&T, e, i);
	Print(T);
}