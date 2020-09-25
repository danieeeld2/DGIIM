#include<iostream>

using namespace std;

class Examen{
	private:
		static const int MAX = 20;
		string asignatura;
		string preguntas[MAX];
		int num_preguntas;
		char respuestas[MAX];
	public: 
		Examen(){
			asignatura = ' ';
			num_preguntas = 0;
			for(int i = 0; i != MAX; i++){
				preguntas[i] = ' ';
				respuestas[i] = ' ';
			}
		}
		
		void Asignatura(string asig){
			asignatura = asig;
		}
		
		void NuevaPregunta(string pregun, char respu){
			preguntas[num_preguntas] = pregun;
			respuestas[num_preguntas] = respu;
			num_preguntas++;
		}
		
		int NumPreguntas(){
			return num_preguntas;
		}
		
		void GetEnunciado(int numero){
			cout << preguntas[numero];
		}
		
		void GetRespuesta(int numero){
			cout << respuestas[numero];
		}
	};

int main(){
	Examen exam1;
	string pregunta;
	char respuesta;
	int numero;
	string asignatura;
	
	cout << "\nNombre de la asignatura: ";
	cin >> asignatura;
	exam1.Asignatura(asignatura);
	
	cout << "\nIntroduce algunas preguntas. ";
	cout << "\nIntroduce la pregunta y la respuesta ";
	for(int i = 0; i != 5; i++){
		cin >> pregunta;
		cin >> respuesta;
		exam1.NuevaPregunta(pregunta, respuesta);
	}
	
	cout << "\nHay " << exam1.NumPreguntas() << " preguntas";
	
	cout << "\nIntroduce el numero de la pregunta ";
	cin >> numero;
	cout << "\nPregunta: ";
   exam1.GetEnunciado(numero);
	cout << "\nRespuesta: ";
	exam1.GetRespuesta(numero);
	
	cout << "\n\n";
	system("pause");
}
	
			
