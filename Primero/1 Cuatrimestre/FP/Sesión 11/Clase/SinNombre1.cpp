#include <iostream>
#include <cmath>

using namespace std;

class SegmentoDirigido{
public:
    double x_1, y_1, x_2, y_2;
public:
    SegmentoDirigido(double origen_abscisa,
                     double origen_ordenada,
                     double final_abscisa,
                     double final_ordenada){
        if (!SetCoordenadas(origen_abscisa, origen_ordenada,
                            final_abscisa, final_ordenada)){
            x_1 = y_1 = x_2 = y_2 = 0;
        }
    }
    bool SetCoordenadas(double origen_abscisa,
                        double origen_ordenada,
                        double final_abscisa,
                        double final_ordenada){
        bool es_correcto;
        
        es_correcto = !(origen_abscisa == final_abscisa && origen_ordenada == final_ordenada);
        
        if (es_correcto){
            x_1 = origen_abscisa;
            y_1 = origen_ordenada;
            x_2 = final_abscisa;
            y_2 = final_ordenada;
        }
        return es_correcto;
    }
    bool Longitud(){
        double lado1, lado2;
        
        lado1 = x_1-x_2;
        lado2 = y_1-y_2;
       
        return sqrt (lado1*lado1 + lado2*lado2);
    }
    double OrigenAbscisa(){
        return x_1;
    }
    double OrigenOrdenada(){
        return y_1;
    }
    double FinalAbscisa(){
        return x_2;
    }
    double FinalOrdenada(){
        return y_2;
    }
    void TrasladaHorizontal(double unidades){
        x_1 = x_1 + unidades;
        x_2 = x_2 + unidades;
    }
    void TrasladaVertical(double unidades){
        y_1 = y_1 + unidades;
        y_2 = y_2 + unidades;
    }
    void Traslada(double unidades_horiz, double unidades_vert){
        TrasladaHorizontal(unidades_horiz);
        TrasladaVertical(unidades_vert);
    }
};

int main(){
    SegmentoDirigido un_segmento(3.4, 5.6, 4.5, 2.3);
    
    cout << "\nLongitud del segmento = " << un_segmento.Longitud();
    
    un_segmento.TrasladaHorizontal(10.0);
    
    cout << "\n\n";
    system("pause");
}

