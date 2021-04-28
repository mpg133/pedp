//Miguel Pérez Giménez
//DNI: 74395666G
#ifndef __TCALENDARIO__
#define __TCALENDARIO__
#include <iostream>

using namespace std;

class TCalendario {

// Sobrecarga del operador salida
  friend ostream& operator << (ostream &,const TCalendario &);

private:
  int dia,mes,anyo;
  char* mensaje;
  bool CheckDate(int dia, int mes,int anyo);
  bool isLeap(int year);
  void sumaDia();
  void restaDia();
public:
  //constructor por defecto inicializa dia mes y anyo a 1/1/1900 y mensaje a NULL
  TCalendario();
  //Constructorque inicializa calendario con parametros pasados
  TCalendario (int dia,  int mes, int anyo ,char * mens);

  //Constructor de copia
  TCalendario (const TCalendario &tcalendario);
  //Destructor
  ~TCalendario ();
  //Sobrecarga del operador asignación
  TCalendario  &operator = (const TCalendario &);

  // Sobrecarga del operador: SUMA de fecha + un número de dias;
  TCalendario operator+(int) const ; //al ser un entero const no hace falta;
  // Sobrecarga del operador: RESTA de fecha - un número de dias;
  TCalendario operator-(int);
  // Modifica la fecha incrementándola en un dia (con postincremento);
  TCalendario operator++(int);
  // Modifica la fecha incrementándola en un dia (con preincremento);
  TCalendario &operator++();
  // Modifica la fecha decrementándola en un dia (con postdecremento);
  TCalendario operator--(int);
  // Modifica la fecha decrementándola en un día (con predecremento);
  TCalendario &operator--();
  // Modifica la fecha
  bool ModFecha (int, int, int);
  // Modifica el mensaje
  bool ModMensaje(const char *);
  // Sobrecarga del operador igualdad;
  bool operator ==(const TCalendario &) const;
  // Sobrecarga del operador desigualdad;
  bool operator !=(const TCalendario &) const;
  // Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
  bool operator>(const TCalendario &) const;
  // Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
  bool operator<(const TCalendario &) const;
  //TCalendario vacío
  bool EsVacio();
  // Devuelve el día del calendario;
  int Dia() const {return dia;}
  // Devuelve el mes del calendario;
  int Mes() const {return mes;}
  // Devuelve el año del calendario;
  int Anyo() const {return anyo;}
  // Devuelve el mensaje del calendario;
  char *Mensaje() const;



};
#endif
