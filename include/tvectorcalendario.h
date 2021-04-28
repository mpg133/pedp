//Miguel Pérez Giménez
//DNI: 74395666G
#ifndef __TVECTORCALENDARIO__
#define __TVECTORCALENDARIO__
#include "tcalendario.h"
using namespace std;

class TVectorCalendario {

  // Sobrecarga del operador salida
  friend ostream & operator<<(ostream &, const TVectorCalendario &);

private:
    TCalendario *c;
    int tamano;
    TCalendario error;
    bool mayorFecha(int,int,int,const TCalendario);
    bool CheckDate(int dia, int mes,int anyo);
    bool isLeap(int year);
 public:
    // Constructor por defecto
    TVectorCalendario();
    // Constructor a partir de un tamaño
    TVectorCalendario(int);
    // Constructor de copia
    TVectorCalendario( const TVectorCalendario &);
    // Destructor
    ~TVectorCalendario();
    // Sobrecarga del operador asignación
    TVectorCalendario & operator=(TVectorCalendario &);
    // Sobrecarga del operador igualdad
    bool operator==(const TVectorCalendario &);
    // Sobrecarga del operador desigualdad
    bool operator!=(const TVectorCalendario &);
    // Sobrecarga del operador corchete (parte IZQUIERDA)
    TCalendario & operator[](const int);
    // Sobrecarga del operador corchete (parte DERECHA)
    TCalendario operator[](const int) const;
    // Tamaño del vector (posiciones TOTALES)
    int Tamano(){return tamano;}
    // Cantidad de posiciones OCUPADAS (no vacías) en el vector
    int Ocupadas();
    // Devuelve TRUE si existe el calendario en el vector
    bool ExisteCal(const TCalendario &);
    // Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O
    //POSTERIOR a la pasada
    void MostrarMensajes(int,int,int);
    // REDIMENSIONAR el vectorde TCalendario
    bool Redimensionar(int);

};
#endif
