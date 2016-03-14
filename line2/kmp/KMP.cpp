#include <iostream>
#include <string.h>
#include <stdio.h>
#include <memory.h>
using namespace std;

void getNext(char *p, int *next)
{
	int j, k;
	next[0] = -1;
	j = 0;
	k = -1;
	while (j<strlen(p) - 1)
	{
		if (k == -1 || p[j] == p[k])    //匹配的情况下,p[j]==p[k]
		{
			j++;
			k++;
			next[j] = k;
		}
		else                   //p[j]!=p[k]
			k = next[k];
	}
}

int KMPMatch(char *s, char *p)
{
	int next[100];
	int i, j;
	i = 0;
	j = 0;
	getNext(p, next);
	while (i<strlen(s))
	{
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];       //消除了指针i的回溯
		}
		if (j == strlen(p))
			return i - strlen(p);
	}
	return -1;
}

int main()
{
	char*s;
	char*p;
	s = (char*)malloc(100);
	p = (char*)malloc(100);
	while (1)
	{
		cin >> s >> p;
		cout << KMPMatch(s, p) << endl;
	}
	return 0;

};
