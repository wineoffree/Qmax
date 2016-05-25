#include<stdio.h>
#include<math.h>
#define m 3
bool cmp1(int x, int y){
	if (x > y){
		if ((x - y) < 2)
			return true;
		else return false;
	}
	else{
		if ((y - x) < 2)return true;
		else return false;
	}
}
bool cmp2(int x, int y){
	if (x > y){
		if ((x - y) < 50)
			return true;
		else return false;
	}
	else{
		if ((y - x) < 50)return true;
		else return false;
	}
}
struct circle
{
	int r;
	int mux;
	int muy;
};
circle Circle[m];
circle rm;	circle ca;
float ws(float x){//将所有小数保留3位数
	if (x == 1)return x;
	int y = x * 1000;
	y = y % 1000;
	x = float(float(y) / 1000);
	return x;
}
int qzl(circle a,circle b){
	int zl;
	zl = int(sqrt(float((a.mux - b.mux)*(a.mux - b.mux) + (a.muy - b.muy)*(a.muy - b.muy))));
	return zl;
}
int qdx(circle a){
	if (a.mux < 0)
		return (1000 + a.mux);
	if (a.mux>0)
		return (a.mux);
}
int qdy(circle a){
	if (a.muy < 0)
		return (1000+a.muy);
	if (a.muy>0)
		return (a.muy);
}
void Qmax3(int n){
	for (int i = 0; i < n-2; i++){
		for (int j = i + 1; j < n - 1;j++)
		for (int h = j + 1; h < n; h++){
			if ((qzl(ca, Circle[i]) - ws(Circle[i].r)) == (qzl(ca, Circle[j]) - ws(Circle[j].r)) == (qzl(ca, Circle[h]) - ws(Circle[h].r)))
			if (rm.r < (qzl(ca, Circle[i]) - ws(Circle[i].r)))
				rm.mux = ca.mux, rm.muy = ca.muy; rm.r = (qzl(ca, Circle[i]) - ws(Circle[i].r));
		}
	}
}
void Qmax2(int n){
		for (int j = 0; j < n - 1; j++)
		for (int h = j + 1; h < n; h++){
			if (qdx(ca) == (qzl(ca, Circle[j]) - ws(Circle[j].r)) == (qzl(ca, Circle[h]) - ws(Circle[h].r)))
			if (rm.r < (qzl(ca, Circle[j]) - ws(Circle[j].r)))
				rm.mux = ca.mux, rm.muy = ca.muy; rm.r = (qzl(ca, Circle[j]) - ws(Circle[j].r));
		}
		for (int j = 0; j < n - 1; j++)
		for (int h = j + 1; h < n; h++){
			if (qdy(ca) == (qzl(ca, Circle[j]) - ws(Circle[j].r)) == (qzl(ca, Circle[h]) - ws(Circle[h].r)))
			if (rm.r < (qzl(ca, Circle[j]) - ws(Circle[j].r)))
				rm.mux = ca.mux, rm.muy = ca.muy; rm.r = (qzl(ca, Circle[j]) - ws(Circle[j].r));

		}
}
void Qmax(int n){
	rm.r = 0;
	for (int i = -1000; i < 1000;i=i+1)
	for (int j = -1000; j < 1000; j=j+1){
		ca.mux = i;
		ca.muy = j;
		for (int h = 0; h < 1; h++){
			if (cmp1(qdx(ca), qdy(ca)) && cmp1(qdx(ca), (qzl(ca, Circle[h]) - (Circle[h].r))) && cmp1(qdy(ca), (qzl(ca, Circle[h]) - (Circle[h].r)))){
				int pd=1;
				for (int t = 0;t<n;t++)
				if (cmp2(ca.mux, Circle[t].mux) && cmp2(ca.muy, Circle[t].muy))
					pd = 0;
				if (pd)
				if ((qdx(ca)>rm.r) && !cmp2(qdx(ca),rm.r))
				{  
					rm.mux = i, rm.muy = j; rm.r = qdx(ca);
					
				}
			}
			
		}
		if (n>1)
			Qmax2(n);
		if (n>2)
			Qmax3(n);
	}
	Circle[n].mux = rm.mux;
	Circle[n].muy = rm.muy;
	Circle[n].r = rm.r;
}
int main(){

	Circle[0].mux = 0;
	Circle[0].muy = 0;
	Circle[0].r = 1000;
	for (int n = 1; n < m; n++){
		Qmax(n);
		printf("%.4d", Circle[n].mux);
		printf(" %.4d", Circle[n].muy);
		printf(" %.4d", Circle[n].r);
		printf("\n");
	}

}