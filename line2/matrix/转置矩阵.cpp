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
	matrix *mt, *lm;//lm是转置后的矩阵
	element *e;

	//原是矩阵的输入
	printf("输入矩阵的行数，列数，非零元个数\n");
	scanf("%d%d%d", &m, &n, &t);
	mt = new matrix;
	mt->c = m;
	mt->v = n;
	mt->t = t;
	mt->data = new element[t];
	printf("按行序输入矩阵的非零元，按三元组形式:行 列 数据\n");
	index = 0;
	do{
		scanf("%d%d%d", &i, &j, &d);
		e = new element;
		e->i = i; e->j = j; e->value = d;
		mt->data[index] = *e;
		index++;
	} while (index<t);

	//对矩阵转置
	lm = new matrix;
	lm->data = new element[t];
	i = 0; j = 0; index = 0;
	int k = 0;
	lm->c = n;//行数和列数对掉，非零元总数不变
	lm->v = m;
	lm->t = t;
	for (i = 0; i<n; i++){//对所有三元组扫描
		for (j = 0; j<t; j++){//对原始矩阵的每一列扫描

			if (mt->data[j].j == i){//对每一列进行转置
				//对此列上的元素对掉信息
				lm->data[k].i = mt->data[j].j;
				lm->data[k].j = mt->data[j].i;
				lm->data[k].value = mt->data[j].value;
				k++;
			}
			else continue;

		}
	}
	index = 0;
	printf("转置后的矩阵\n");
	printf("行 列 值\n");
	while (index<t){
		printf("(%d  %d  %d)\n", lm->data[index].i, lm->data[index].j, lm->data[index].value);
		index++;
	}
	system("pause");
	return 0;
}
