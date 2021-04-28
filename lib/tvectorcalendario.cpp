//Miguel Pérez Giménez
//DNI: 74395666G
#include <iostream>
#include <cstring>
#include <vector>
#include "../include/tvectorcalendario.h"


using namespace std;


//-----------------------Funciones auxiliares----------------------------
//funcion que devuelve true si la fecha es igual o posterior a la dada
bool TVectorCalendario::mayorFecha(int dia2, int mes2, int anyo2,const TCalendario tcalendario){
  bool ret=false;
  if(anyo2>tcalendario.Anyo()){
    ret=true;
  }else if(anyo2==tcalendario.Anyo() && mes2>tcalendario.Mes()){
    ret=true;
  }else if(anyo2==tcalendario.Anyo() && mes2==tcalendario.Mes() && dia2>tcalendario.Dia()){
    ret=true;

  }else if(anyo2==tcalendario.Anyo() && mes2==tcalendario.Mes() && dia2==tcalendario.Dia()){
    ret=true;
  }


return ret;
}
//check if is leap(bisiesto)
bool TVectorCalendario::isLeap(int year){
  bool leap=false;
    if(year%4==0){
      if(year%100==0 && !(year%400==0)){leap=false;}
      else{leap=true;}
    }
  return leap;
}
//Función que comprueba si la fecha es correcta
bool TVectorCalendario::CheckDate(int dia,int mes,int anyo){
  bool ret=false;//variable that return if date is correct or not





  //check the date
  if(0<mes && mes<13 && 0<dia && dia<32 && anyo>=2000 && anyo<=2100){
      //mess 4,6,9,11 have 30 days
      if((mes==4 || mes==6 || mes == 9 || mes ==11) && dia<=30){
          ret=true;
      }
      else{
        if(mes==2 && isLeap(anyo) && dia<=29) {ret=true;}
        else if(mes==2 && !isLeap(anyo) && dia<=28) {ret=true;}
        else if(mes!=2){
            if(!(mes==4 || mes==6 || mes == 9 || mes ==11)  && dia<=31){
              ret=true;
            }
        }
      }
  }
  return ret;

}

//-----------------------Funciones Principales----------------------------
// Constructor por defecto
TVectorCalendario::TVectorCalendario(){
  //no se reserva memoria con new
  tamano=0;
  c=NULL;
}
// Constructor a partir de un tamaño
TVectorCalendario::TVectorCalendario(int newTamanyo){
  if(newTamanyo<0){
    tamano=0;
    c=NULL;
  }else{
    tamano=newTamanyo;
    c=new TCalendario[newTamanyo];
  }
}
//Destructor
TVectorCalendario::~TVectorCalendario(){

  if(c!=NULL){
    delete [] c;
    c=NULL;
  }
    //delete [] this;
  tamano=0;
}


// Constructor de copia
TVectorCalendario::TVectorCalendario(const TVectorCalendario &newVec){
  if(newVec.tamano!=0){
    tamano=newVec.tamano;
    c= new TCalendario[tamano];
    //rellenamos el vector con newVec
    for(int i=0;i<tamano;i++){
      c[i]=newVec.c[i];

    }
  }else{
    tamano=0;
    c=NULL;
  }
}
// Sobrecarga del operador igualdad
bool TVectorCalendario::operator==(const TVectorCalendario &newVec){

  if(tamano==newVec.tamano){//mismo tam
    for(int i=1;i<=tamano;i++){
      if(c[i-1]!=newVec.c[i]){
        return false;
      }
    }
  }else{
    return false;
  }

return true;
}
// Sobrecarga del operador desigualdad
bool TVectorCalendario::operator!=(const TVectorCalendario &newVec){
  if(*this==newVec){
    return false;
  }else{
    return true;
  }
}

// Sobrecarga del operador corchete (parte IZQUIERDA)
//modificas v[10]=a;
TCalendario & TVectorCalendario::operator[](const int pos){

    if(pos>0 && pos<=tamano){
      return c[pos-1];

    }else{
        return error;

    }

}
// Sobrecarga del operador corchete (parte DERECHA)
//no modificas V[10] + V[11]
TCalendario TVectorCalendario::operator[](const int pos) const{

      if(pos>0 && pos<=tamano){

          return c[pos-1];
      }else{

        return error;
      }
}
// Cantidad de posiciones OCUPADAS (no vacías) en el vector
int TVectorCalendario::Ocupadas(){
int ocupadas=0;
if(this!=NULL){
  for(int i=0;i<tamano;i++){
    if(c[i]!=error){
      ocupadas++;
    }
}
}

return ocupadas;

}
// Sobrecarga del operador asignación
TVectorCalendario & TVectorCalendario::operator=(TVectorCalendario &newVec){


          //se destruye vector inicial
           //this->~TVectorCalendario();
          tamano=newVec.tamano;

           if(newVec.tamano>0){
              c  = new TCalendario[tamano];
             for(int i = 0;i <tamano; i++){
                 c[i]=newVec.c[i];
              }
           }else{
             c=NULL;
           }


        //(*this)=newVec;

    return *this;//devuelves el obj
}
// Devuelve TRUE si existe el calendario en el vector
bool TVectorCalendario::ExisteCal(const TCalendario &tcalendario){
  bool ret=false;
  for(int i=0;i<tamano;i++){
    if(c[i]==tcalendario){
      ret=true;
    }
  }

return ret;
}
// Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O
//POSTERIOR a la pasada
void TVectorCalendario::MostrarMensajes(int dia2,int mes2,int anyo2){
  cout<<"[";
  if(CheckDate(dia2,mes2,anyo2)){
    for(int i=0;i<tamano;i++){
      if(mayorFecha(dia2,mes2,anyo2,c[i]) || (c->Dia()==dia2 && c->Mes()==mes2 && c->Anyo()==anyo2) ){
        cout<<c[i];

      }if(i>0 && (i+1)<tamano){
        cout<<", ";
      }
    }
  }
  cout<<"]"<<endl;
}
// REDIMENSIONAR el vector de TCalendario
bool TVectorCalendario::Redimensionar(int newTam){

  TCalendario *c2 = new TCalendario[newTam] ;
  if(newTam>0 && newTam!=tamano){

    //copiar componentes en vector nuevo
    if(newTam>tamano){//el tamaño es mayor
      for(int i=0;i<newTam;i++){
        if(i<tamano){
          c2[i]=c[i];
        }else{
          c2[i]=error;
        }
      }
      delete [] c;
      c=NULL;
      tamano=newTam;
      c=c2;
      return true;
    }
    //el tam es menor
    else{

      for(int i=0;i<newTam;i++){
        c2[i]=c[i];
      }
      delete [] c;
      c=NULL;
      tamano=newTam;
      c=c2;
      return true;

    }
  }

  return false;
}
// Sobrecarga del operador salida
 ostream & operator<<(ostream &os, const TVectorCalendario &tvectorcalendario){
  if(tvectorcalendario.tamano==0){
    return os<<"[]";
  }
    os<<"[";
    for(int i=1;i<=tvectorcalendario.tamano;i++){

        os<<"("<<i<<") "<<tvectorcalendario.c[i-1];
        if(i<tvectorcalendario.tamano){
          os<<", ";
        }


    }
    os<<"]";


  return os;
}
