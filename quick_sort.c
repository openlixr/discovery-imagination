/*************************************************************************
 * File Name: test0004.c
 *
 * Copyright (c) 2015, Spreadtrum Limited
 * All rights reserved.
 *
 *
 * xiaoran.li@spreadtrum.com  truth plaza  Haidian
 * 2016年07月20日 星期三 23时58分03秒
 ************************************************************************/

#include<stdio.h>

#define N 6

//int na[] = {4, 2, 1, 5, 6, 3};
//int na[] = {3, 2, 1, 4, 6, 5};
//int na[] = {6, 5, 4, 3, 2, 1};
int na[] = {1, 2, 3, 4, 5, 6};
//int na[] = {4, 2, 1, 3, 5};
//int na[] = {1, 2, 4, 3, 5};
//int na[] = {5, 2, 4, 3, 1};
//int na[] = {4, 3};

#if 1
/* @min is the lower index of @na, @max is upper index + 1 */
void func(int min, int max)
{
	int i = min, j = max + 1, a = na[min], b;

	if (min >= max)
		return;

	while (1) {
		for (i++; i < j; i++) {
			if (na[i] > a)
				break;
		}
		for (j--; j > i; j--) {
			if (na[j] < a)
				break;
		}

		if (i >= j)
			break;

		b = na[i];
		na[i] = na[j];
		na[j] = b;
	}
	na[min] = na[i - 1];
	na[i - 1] = a;

	//printf("%d\n", i - 1);

	func(min, i - 1 - 1);
	func(i, max);
}

int main()
{
	int b;

	for (b = 0; b < N; b++)
		printf("%d ", na[b]);
	printf("\n");

	func(0, N - 1);

	for (b = 0; b < N; b++)
		printf("%d ", na[b]);
	printf("\n");
}



#else
int main()
{
	int i = 0, j = N, a = na[0], b;

	for (b = 0; b < N; b++)
		printf("%d ", na[b]);
	printf("\n");

	while (1) {
		for (i++; i < j; i++) {
			if (na[i] > a)
				break;
		}
		for (j--; j > i; j--) {
			if (na[j] < a)
				break;
		}

		if (i >= j)
			break;

		b = na[i];
		na[i] = na[j];
		na[j] = b;
	}
	na[0] = na[i - 1];
	na[i - 1] = a;

	for (b = 0; b < N; b++)
		printf("%d ", na[b]);
	printf("\n");
}
#endif
