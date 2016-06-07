#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#define m 3
int blocksn;
HANDLE pThread[100]; //producer线程句柄  
struct Circle
{
	int r;
	int mux;
	int muy;
};
struct wz
{
	int Rmax;
	int X;
	int Y;
};
int zj[200][200];
Circle circle[m];
Circle blocks[5];
wz wzs[100];
int n;
bool cmp(int a, int b){
	if (a > b)
	{
		if ((a - b) <= 1)
			return true;
		else
			return false;
	}
	else
	{
		if ((b - a) <= 1)
			return true;
		else
			return false;
	}
}
bool cmp2(int a, int b, int r){
	if (a > b)
	{
		if ((a - b) <= r)
			return true;
		else
			return false;
	}
	else
	{
		if ((b - a) <= r)
			return true;
		else
			return false;
	}
}
int qzl(Circle a, Circle b){
	int zl;
	zl = int(sqrt(float((a.mux - b.mux)*(a.mux - b.mux) + (a.muy - b.muy)*(a.muy - b.muy))));
	return zl;
}
DWORD WINAPI producer1(LPVOID IpParameter)
{
	Circle ci;
	int i = *(int *)IpParameter;
	int left = i * 10; int right = (i+1) * 10;
	wzs[i].Rmax = 0, wzs[i].X = 0, wzs[i].Y = 0;
	for (int a = left; a < right;a++)
	for (int j = 0; j < 200; j++)
	{
		int pd = 0;
		ci.mux = a;
		ci.muy = j;
		for (int ii = 0; ii < n; ii++)
		{
			if (cmp2(a, circle[ii].mux, circle[ii].r) && cmp2(j, circle[ii].muy, circle[ii].r))
				pd = 1;
		}
		if (pd)
			break;
		for (int r = 0; r < 100; r++)
		{
			ci.r = r;
			for (int t = 0; t < n; t++)
			{
				if (cmp(qzl(circle[n], circle[t]), (circle[n].r + circle[t].r)))
				{
					if (r >= wzs[i].Rmax)
					{
						wzs[i].Rmax = r;
						wzs[i].X = i;
						wzs[i].Y= j;
					}
					pd = 1;
					break;
				}
			}

			if ((a - r <= 0) || (a + r >= 199) || (j + r >= 199) || (j - r <= 0))
			{
				pd = 1;
				if (r >= wzs[i].Rmax)
				{
					wzs[i].Rmax = r;
					wzs[i].X = a;
					wzs[i].Y = j;
				}
			}
			for (int h = 0; h < blocksn; h++)
			{
				if (cmp(qzl(ci, blocks[h]), (ci.r + blocks[h].r)))
				{

					if (r >= wzs[i].Rmax)
					{
						wzs[i].Rmax = r;
						wzs[i].X = a;
						wzs[i].Y = j;
					}
					pd = 1;
					break;
				}

			}
			if (pd)
				break;
		}

	}
	return 0;
}

void Qrmax()
{  
	int x, y, rmax;
	for (int i1 = 0; i1 < 10; i1++){
		pThread[i1] = CreateThread(NULL, 0, producer1, (void*)(&i1), 0, NULL);
	}
	for (int j = 0; j < 10; j++)
		WaitForSingleObject(pThread[j], INFINITE);
	for (int t = 0; t < 10; t++)
	CloseHandle(pThread[t]);
	rmax = wzs[0].Rmax; x = wzs[0].X; y = wzs[0].Y;
	for (int i = 1; i < 10; i++)
	{
		if (wzs[i].Rmax >= rmax){
			x = wzs[i].X;
			y = wzs[i].Y;
			rmax = wzs[i].Rmax;
		}
	}
	circle[n].mux = x;
	circle[n].muy = y;
	circle[n].r = rmax;
}
int main()
{
	srand(time(0));
	int i, j;
	blocksn = (rand() % 5 + 1);//随机生成1-5个块
	for (int h = 0; h < blocksn; h++)
	{
		i = rand() % 200;
		j = rand() % 200;
		if (zj[i][j] == 0)
		{
			zj[i][j] = 1;
			blocks[h].mux = i;
			blocks[h].muy = j;
		}
		else h--;
	}
	for (int t = 0; t < m; t++){
		n = t;
		Qrmax();

	}

	printf("小块数目%d\n", blocksn);
	printf("圆的数量%d\n", m);
	for (int i = 0; i < blocksn; i++)
	{
		printf("块(x,y)%.2f %.2f", float(blocks[i].mux - 100) / 100, float(blocks[i].muy - 100) / 100);
	}
	printf("\n");
	for (int i = 0; i < m; i++)
	{
		printf(" %.2f %.2f %.2f", float(circle[i].mux - 100) / 100, float(circle[i].muy - 100) / 100, float(circle[i].r) / 100);
		printf("\n");
	}
	return 0;
}