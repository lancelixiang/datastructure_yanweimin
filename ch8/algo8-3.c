/* algo8-3.c ʵ���㷨8.3�ĳ��� */
#include "../ch1/c1.h"
typedef char AtomType; /* ����ԭ������Ϊ�ַ��� */
#include "c8-3.h"
#include "../ch5/bo5-51.c"

Status CreateMarkGList(GList *L, SString S) /* ��bo5-51.c�� */
{ /* ����ͷβ�����洢�ṹ,�ɹ��������д��ʽ��S���������L����emp="()" */
	SString sub, hsub, emp;
	GList p, q;
	StrAssign(emp, "()");
	if (!StrCompare(S, emp))
		*L = NULL; /* �����ձ� */
	else
	{
		*L = (GList)malloc(sizeof(GLNode));
		if (!*L) /* ������� */
			exit(OVERFLOW);
		if (StrLength(S) == 1) /* SΪ��ԭ�� */
		{
			(*L)->tag = ATOM;
			(*L)->a.atom = S[1]; /* ������ԭ�ӹ���� */
			(*L)->mark = 0; /* �� */
		}
		else
		{
			(*L)->tag = LIST;
			(*L)->mark = 0; /* �� */
			p = *L;
			SubString(sub, S, 2, StrLength(S) - 2); /* ��������� */
			do
			{ /* �ظ���n���ӱ� */
				sever(sub, hsub); /* ��sub�з������ͷ��hsub */
				CreateMarkGList(&p->a.ptr.hp, hsub); /* �� */
				q = p;
				if (!StrEmpty(sub)) /* ��β���� */
				{
					p = (GLNode *)malloc(sizeof(GLNode));
					if (!p)
						exit(OVERFLOW);
					p->tag = LIST;
					p->mark = 0; /* �� */
					q->a.ptr.tp = p;
				}
			} while (!StrEmpty(sub));
			q->a.ptr.tp = NULL;
		}
	}
	return OK;
}

void MarkList(GList GL) /* �㷨8.3 */
{ /* �����ǿչ����GL(GL!=NULL��GL->mark==0),�Ա�������δ�ӱ�־�Ľ��ӱ�־��*/
	GList t, p, q;
	Status finished;
	if (GL != NULL&&GL->mark == 0)
	{
		t = NULL; /* tָʾp��ĸ�� */
		p = GL;
		finished = FALSE;
		while (!finished)
		{
			while (p->mark == 0)
			{
				p->mark = 1; /* MarkHead(p)��ϸ�� */
				q = p->a.ptr.hp; /* qָ��*p�ı�ͷ */
				if (q&&q->mark == 0)
					if (q->tag == 0)
						q->mark = 1; /* ATOM,��ͷΪԭ�ӽ�� */
					else
					{ /* ���������ӱ� */
						p->a.ptr.hp = t;
						p->tag = ATOM;
						t = p;
						p = q;
					}
			} /* ��ɶԱ�ͷ�ı�־ */
			q = p->a.ptr.tp; /* qָ��*p�ı�β */
			if (q&&q->mark == 0)
			{ /* ����������β */
				p->a.ptr.tp = t;
				t = p;
				p = q;
			}
			else /* BackTrack(finished)��ϸ�� */
			{
				while (t&&t->tag == 1) /* LIST,�����,�ӱ�β���� */
				{
					q = t;
					t = q->a.ptr.tp;
					q->a.ptr.tp = p;
					p = q;
				}
				if (!t)
					finished = TRUE; /* ���� */
				else
				{ /* �ӱ�ͷ���� */
					q = t;
					t = q->a.ptr.hp;
					q->a.ptr.hp = p;
					p = q;
					p->tag = LIST;
				} /* ����������β */
			}
		}
	}
}

void Traverse_GL(GList L, void(*v)(GList))
{ /* ���õݹ��㷨���������L,��bo5-5.c�� */
	if (L) /* L���� */
		if (L->tag == ATOM) /* LΪ��ԭ�� */
			v(L);
		else /* LΪ����� */
		{
			v(L);
			Traverse_GL(L->a.ptr.hp, v);
			Traverse_GL(L->a.ptr.tp, v);
		}
}

void visit(GList p)
{
	if (p->tag == ATOM)
		printf("mark=%d %c\n", p->mark, p->a.atom);
	else
		printf("mark=%d list\n", p->mark);
}

void main()
{
	char p[80];
	SString t;
	GList l;
	printf("����������l(��д��ʽ���ձ�:(),��ԭ��:a,����:(a,(b),b)):\n");
	gets(p);
	StrAssign(t, p);
	CreateMarkGList(&l, t);
	Traverse_GL(l, visit);
	MarkList(l);
	printf("�ӱ�־��:\n");
	Traverse_GL(l, visit);
}