//#include <stdafx.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
struct element{
	int value;
	int i, j;
};
struct matrix{
	int c, v, t;
	struct element *data;
};

int main(int argc, char* argv[])
{
	int m, n, t;
	int i, j, d;
	int index;
	matrix *mt, *lm;//lm��ת�ú�ľ���
	element *e;

	//ԭ�Ǿ��������
	printf("������������������������Ԫ����\n");
	scanf("%d%d%d", &m, &n, &t);
	mt = new matrix;
	mt->c = m;
	mt->v = n;
	mt->t = t;
	mt->data = new element[t];
	printf("�������������ķ���Ԫ������Ԫ����ʽ:�� �� ����\n");
	index = 0;
	do{
		scanf("%d%d%d", &i, &j, &d);
		e = new element;
		e->i = i; e->j = j; e->value = d;
		mt->data[index] = *e;
		index++;
	} while (index<t);

	//�Ծ���ת��
	lm = new matrix;
	lm->data = new element[t];
	i = 0; j = 0; index = 0;
	int k = 0;
	lm->c = n;//�����������Ե�������Ԫ��������
	lm->v = m;
	lm->t = t;
	for (i = 0; i<n; i++){//��������Ԫ��ɨ��
		for (j = 0; j<t; j++){//��ԭʼ�����ÿһ��ɨ��

			if (mt->data[j].j == i){//��ÿһ�н���ת��
				//�Դ����ϵ�Ԫ�ضԵ���Ϣ
				lm->data[k].i = mt->data[j].j;
				lm->data[k].j = mt->data[j].i;
				lm->data[k].value = mt->data[j].value;
				k++;
			}
			else continue;

		}
	}
	index = 0;
	printf("ת�ú�ľ���\n");
	printf("�� �� ֵ\n");
	while (index<t){
		printf("(%d  %d  %d)\n", lm->data[index].i, lm->data[index].j, lm->data[index].value);
		index++;
	}
	system("pause");
	return 0;
}
