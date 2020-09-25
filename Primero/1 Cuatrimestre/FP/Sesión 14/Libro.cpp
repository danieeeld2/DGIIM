/*	Programa que trabaja con múltiples clases
	para representar la estructura de una
	biblioteca */
	 
#include<iostream>
#include<vector>

using namespace std;

/*	Clase que implementa el
	nombre del libro y métodos para comparar
	libros por el nombre */
	
class Identificador{
	private:
		string ID;	
	public:
		Identificador(){
			ID = " ";
		}
		
		void SetIdentificador(string a){
			ID = a;
		}
		
		string GetCadena(){
			return ID;
		}
		
		bool Es_Menor(string a){
			bool es_menor = false;
			
			if(ID.compare(a) < 0)
				es_menor = true;
			else
				es_menor = false;
				
			return es_menor;
		}
		
		bool Iguales(string a){
			bool iguales = false;
			
			if(ID.compare(a) == 0){
				iguales = true;
			}
			else
				iguales = false;
				
			return iguales;
		} 
};

class Fecha{
	private:
		int dia;
		int mes;
		int anio;
		
		bool FechaCorrecta(){
			bool condicion1, condicion2, condicion3;
			bool meses_pares;
			bool febrero;
			bool bisiesto;
			bool es_valido;
	
			condicion1 = anio > 0;
			condicion2 = mes > 0 && mes < 13;
			condicion3 = dia > 0 && dia < 32;
	
			meses_pares = (mes % 2 != 0) && (mes != 7);
			if(meses_pares)
				condicion3 = dia > 0 && dia < 31;
		
			febrero = mes == 2;
			if(febrero)
				condicion3 = dia > 0 && dia < 29;	
		
			bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
			if(febrero && bisiesto)
				condicion3 = dia > 0 && dia < 30;
		
			es_valido = condicion1 && condicion2 && condicion3;
			if(es_valido)
				return true;
			else
				return false;	
		}		
	public:
		Fecha(){
			dia = 1;
			mes = 1;
			anio = 1;
		}
		
		void SetFecha(int a, int b, int c){
			dia = a;
			mes = b;
			anio = c;
			
			if(!FechaCorrecta()){
				dia = 1;
				mes = 1;
				anio = 1;
			}
		}
		
		bool Es_Menor(Fecha fecha){
			bool es_menor = false;
			
			if(anio < fecha.anio){
				es_menor = true;
			}else{
				if(mes < fecha.mes){
					es_menor = true;
				}else{
					if(dia < fecha.dia){
						es_menor = true;
					}
				}
			}
			
			return es_menor;
		}
		
		bool Es_Igual(Fecha fecha){
			bool iguales = false;
			
			if(anio == fecha.anio)
				if(mes == fecha.mes)
					if(dia == fecha.dia)
						iguales = true;
						
			return iguales;
		}
		
		int GetDia(){
			return dia;
		}
		
		int GetMes(){
			return mes;
		}
		
		int GetAnio(){
			return anio;
		}
};

class Libro{
	private:
		Identificador identificacion;
		Fecha publicacion;
	public:
		Libro(){
			identificacion.SetIdentificador(" ");
			publicacion.SetFecha(1, 1, 1);
		}
		
		void SetLibro(Identificador a, Fecha b){
			identificacion = a;
			publicacion = b;
		}
		
		Identificador GetIndentificacion(){
			return identificacion;
		}
		
		Fecha GetPublicacion(){
			return publicacion;
		}
		
		bool Es_Menor(Libro a){
			bool es_menor = false;
			
			if(publicacion.Es_Menor(a.publicacion))
				es_menor = true;
			else
				es_menor = false;
				
			return es_menor;
		}
				
		bool Es_Igual(Libro a){
			bool es_igual = false;
			
			if(publicacion.Es_Igual(a.publicacion))
				es_igual = true;
			else
				es_igual = false;
				
			return es_igual;
		}
};

class Biblioteca{
	private:
		vector<Libro> biblio;
	public:
		Biblioteca(){
			biblio.clear();
		}
		
		void SetLibro(Libro a){
			biblio.push_back(a);
		}
		
		void EliminarLibro(Libro b){
			int posicion;
			Libro comparar;
			Identificador id1;
			Identificador id2;
			
			id2 = b.GetIndentificacion();
			
			for(unsigned i = 0; i != biblio.size(); i++){
				comparar = biblio[i];
				id2 = comparar.GetIndentificacion();				
				if(id1.Iguales(id2.GetCadena()))
					posicion = i;
			}
			
			for(unsigned j = posicion; j != biblio.size(); j++){
				biblio[j] = biblio[j + 1];
			}
			
			biblio.pop_back();
		}
		
		vector<Libro> GetBiblio(){
			return biblio;
		}
		
		int NumeroLibros(){
			return biblio.size();
		}
};

class ImprimirBiblioteca{
	private:
		Biblioteca mi_biblioteca;
	public:
		ImprimirBiblioteca(Biblioteca biblio){
			mi_biblioteca = biblio;
		}
		
		void Leer(){
			vector<Libro> comparar;
			Libro imprimiendo1;
			Identificador imprimiendo2;
			Fecha imprimiendo3;
			
			comparar = mi_biblioteca.GetBiblio();
			
			for(int i = 0; mi_biblioteca.NumeroLibros(); i++){
				imprimiendo1 = comparar[i];
				imprimiendo2 = imprimiendo1.GetIndentificacion();
				imprimiendo3 = imprimiendo1.GetPublicacion();
				
				cout << " " << imprimiendo2.GetCadena() << " " << imprimiendo3.GetDia() << " " << imprimiendo3.GetMes() << " " << imprimiendo3.GetAnio();
			}
		}
				
		
};
		

int main(){
	Identificador id1;
	Identificador id2;
	Fecha fecha1;
	Fecha fecha2;
	Libro libro1;
	Libro libro2;
	Biblioteca biblioteca1;
	
	id1.SetIdentificador("AAAA");
	id2.SetIdentificador("BBBB");
	
	fecha1.SetFecha(14, 11, 2012);
	fecha2.SetFecha(29, 2, 2020);
	
	libro1.SetLibro(id1, fecha1);
	libro2.SetLibro(id2, fecha2);
	
	biblioteca1.SetLibro(libro1);
	biblioteca1.SetLibro(libro2);
	
	ImprimirBiblioteca impr(biblioteca1);
	impr.Leer();	
	
	cout  << "\n\n";
	system("pause");
	
	return 0;
}
	

		
