#include<iostream>

using namespace std;

const int MAX = 10;

class EnteroLargo{
	private:
		static const int MAX = 100;
		bool signo;
		int longitud;
		int cifras[MAX];
	public:
		EnteroLargo(){
			longitud = 1;
			cifras[0] = 0;
		}
		
		EnteroLargo(int entero){
			int divisor;
			int longitud;
			
			if(entero < 0)
				singo = 1;
			else
				singo = 0;
				
			divisor = 1;
			longitud = 0;
			
			while (entero / 10 != 0){
				divisor = divisor * 10;
				cifras[longitud] = ((entero % divisor) - (entero % (divisor / 10)))) / (divsor / 10);
				longitud++;
			}
		}
		
		EnteroLargo(int l, int d[MAX], bool sig){
			signo = sig;
			
				
				
