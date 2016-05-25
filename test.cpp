#include<stdio.h>
#include<math.h>
int n;
long double r[100000];
long double g2 = sqrt(long double(2));
long double maxmum;
int Qmax(int n){
	r[n] = (g2-1)*r[n-1] / (1 + g2);
	if (r[n] == 0) return n;
	 n++; 
	 Qmax(n);
}
int main(){
	n = 1;
	//double g2 = sqrt(double(2));
	//printf("%f", g2);
	r[0] = 1;
	n=Qmax(n);
	for (int i = 0; i < n; i++){
		int pd = 1;	
		for (int j = 0; j < i; j++){
			pd = pd * 4;
		}
			maxmum = r[i] * r[i]*pd + maxmum;		
	}
	printf("%lf", maxmum);
}