/*Programa para trabajar con una clase tipo
	fecha*/

#include <iostream>

using namespace std;

class Fecha{
	private:
		int day, month, year;
	public:
		Fecha(int d, int m, int y){
			day = d;
			month = m;
			year = y;
		}
		
		int SetFecha(int d, int m, int y){
			day = d;
			month = m;
			year = y;
		}
		
		bool bisiesto(int year){
			bool salida=false;
			if(year%100==0){
				if(year%400==0)
					salida=true;
			}
			else{
				if(year%4==0)
					salida=true;
				}	
			return salida;
		}
		
		bool mes(int month){
			bool salida;
			if(month<=0 || month >12)
				salida=false;
			else
				salida=true;
				
			return salida;
		}

		bool dia(int day, int month, int year){
			bool salida=true;
			if(day<=0 || day > 31)
				salida=false;
			else{
				if(month==4 || month==6 || month == 9 || month == 11){
					if(day==31)
						salida=false;
				}
				if(month==2){
					if (bisiesto(year)==false){
						if(day>28)
							salida=false;
					}
					else{
						if (day>29)
							salida=false;
					}	
				}
			}

			return salida;
		}
		
		bool valido(int day, int month, int year){
			if(mes(month)==true && dia(day,month,year)==true)
				return true;
			else{
				return false;
			}
		}
		
		int Yesterday(int _day,int _month, int _year){
			if(_day>1)
				day=_day-1;
			if(_day==1){
				if(_month==2||_month==4||_month==6||_month==8||_month==9||_month==11){
					day=31;
					month=_month-1;
				}
				if(_month==5||_month==7||_month==10||_month==12){
					day=30;
					month=_month-1;
				}
				if(_month==1){
					day=31;
					month=12;
					year=_year-1;
				}
				if(_month==3){
					if(bisiesto(_year)==true){
						day=29;
						month=_month-1;
					}
					else{
						day=28;
						month=_month-1;
					}
				}
			}
			cout << "El dia anterior es: " << day << "/" << month << "/" << year << "\n";
		}
		int Tomorrow(int _day, int _month, int _year){
			if(_month==1||_month==3||_month==5||_month==7||_month==8||_month==10||_month==12){
				if (_day<31)
					day=_day+1;
				else{
					day=1;
					if(_month!=12)
						month=_month+1;
					else{
						month=1;
						year=_year+1;
					}
				}
			}
			else{
				if(_day<28)
					day=_day+1;
				else{
					if(_month!=2){
						if(_day<30)
							day=_day+1;
						else{
							day=1;
							month=_month+1;
						}
					}
					else{
						if(bisiesto(_year)==true)
							day=_day+1;
						else{
							day=1;
							month=_month+1;
						}
					}
				}
			}
			cout << "El dia siguiente es: " << day << "/" << month << "/" << year << "\n";
		}
};

int main(){
	int day;
	int month;
	int year;
	Fecha hoy(0,0,0);
	Fecha ayer(0,0,0);
	Fecha maniana(0,0,0);
	
	cout << "Introduzca una fecha (Dia Mes Anio): ";
	cin >> day >> month >> year;
	hoy.SetFecha(day,month,year);
	ayer.SetFecha(day,month,year);
	maniana.SetFecha(day,month,year);
	
	if (hoy.valido(day,month,year)==false){
		cout << "La fecha no existe. \n";
		goto final;
	}
	else
		cout << "La fecha existe. \n";
	
	ayer.Yesterday(day,month,year);
	maniana.Tomorrow(day,month,year);
	
	final:
		system ("pause");
}
