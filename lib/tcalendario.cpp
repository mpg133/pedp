//Miguel Pérez Giménez
//DNI: 74395666G
#include <iostream>
#include <cstring>
#include "../include/tcalendario.h"

using namespace std;

//---------------------------------Funciones auxliares---------------------------------
bool TCalendario::isLeap(int year){
  bool Leap=false;
  //check if is leap(bisiesto)

    if(year%4==0){
      if(year%100==0 && !(year%400==0)){Leap=false;}
      else{Leap=true;}
    }
  return Leap;
}
//Función que comprueba si la fecha es correcta
bool TCalendario::CheckDate(int day,int month,int year){
  bool ret=false;

  bool leap=isLeap(year);


  if(0<month && month<13 && 0<day && day<32 && year>=1900){
      //Months 4,6,9,11 have 30 days
      if((month==4 || month==6 || month == 9 || month ==11) && day<=30){
          ret=true;
      }
      else{
        if(month==2 && leap && day<=29){
          ret=true;
        }else if(month==2 && day<=28){
          ret=true;
        }else if(month!=2 && !(month==4 || month==6 || month == 9 || month ==11)){//meses con 31
          ret=true;
        }
      }
  }
  return ret;

}
//Función que suma un dia a la fecha:
void TCalendario::sumaDia(){
  dia++;
  //comprobamos que la fecha que devuelva sea correcta:
  if(mes==4 || mes == 6 || mes==9 || mes==11){ //el mes tiene 30 dias
    if(dia==31){ //cambio de mes
      mes++;
      dia=1;
    }
  }else if(mes!=2){ //el mes tiene 31 dias
    if(dia==32){ //cambio de mes
      mes++;
      if(mes==13){ //cambio de año si es diciembre
        anyo++;
        mes=1;
      }
      dia=1;
    }
  }else{//febrero
    if(isLeap(anyo)){
      if(dia==30){//cambio de mes
          mes++;
          dia=1;
      }
    }else{
      if(dia==29){
        mes++;
        dia=1;
      }
    }
  }

}
//función que resta un dia a la fecha
void TCalendario::restaDia(){
bool error=false;
  if(anyo==1900 && mes==1 && dia==1){
    error=true;
  }

  if(dia>=1 && mes>=1 && anyo>=1900 && !error){

    dia--;
      if(dia==0){
        //30 dias
        if(mes==4 || mes== 6 || mes==9 || mes==11){
          mes--;
          dia=30;
        }else if(mes==3){//febrero
          mes--;
          if(isLeap(anyo)){
            dia=29;
          }else{
            dia=28;
          }
        }else if(mes==1){//cambio de anyo
          mes=12;
          anyo--;
          dia=30;
        }
        else{//31 dias
            mes--;
            dia=31;
          }
      }



  }else{
        dia=1;
        mes=1;
        anyo=1900;
        mensaje=NULL;
      }

}
//------------------Funciones Principales--------------------------------
//constructor por defecto
TCalendario::TCalendario(){
  dia=1;
  mes=1;
  anyo=1900;
  mensaje=NULL;
}
//Constructor icializa calendario con parametros pasados
TCalendario::TCalendario( int dia2 ,int mes2 , int anyo2, char* msg){
  if(CheckDate(dia2,mes2,anyo2)){
    dia = dia2;
    mes = mes2;
    anyo = anyo2;
    if(msg==NULL){
      mensaje=NULL;
    }else{
      mensaje= new char[strlen(msg) +1];
      strcpy(mensaje,msg);
    }
  }
  else{
    dia=1;
    mes=1;
    anyo=1900;
    mensaje=NULL;
  }
}
//constructor de copia
TCalendario::TCalendario(TCalendario const &tcalendario){
  dia = tcalendario.dia;
  mes = tcalendario.mes;
  anyo = tcalendario.anyo;
  if(tcalendario.mensaje==NULL){
    mensaje=NULL;
  }else{
    mensaje= new char[strlen(tcalendario.mensaje) +1];
    strcpy(mensaje,tcalendario.mensaje);
  }
}
//Destructor
TCalendario::~TCalendario(){
  dia=1;
  mes=1;
  anyo=1900;
  if(mensaje!=NULL){
    delete [] mensaje;
    mensaje=NULL;
  }
}
bool TCalendario::operator == (const TCalendario& tcalendario) const{

  bool ret=false;
  if(this && &tcalendario){
    if(dia==tcalendario.dia && mes==tcalendario.mes && anyo==tcalendario.anyo){
      if(tcalendario.mensaje==NULL && mensaje==NULL){
        ret=true;
      }else if((tcalendario.mensaje!=NULL &&  mensaje==NULL)){
        ret=false;
      }else if((tcalendario.mensaje==NULL &&  mensaje!=NULL)){
        ret=false;
      }
      else if(strcmp(mensaje,tcalendario.mensaje)==0){
          ret=true;
      }

      }
  }


      return ret;

}
bool TCalendario::operator != (const TCalendario& tcalendario) const{
  return !(*this==tcalendario);
}
//sobrecarga del operador asignación
TCalendario& TCalendario:: operator=(const TCalendario &tcalendario){

  if((*this)!= tcalendario){ //si no son iguales
   //eliminas el TCalendario
   this->~TCalendario();
    dia = tcalendario.Dia();
    mes = tcalendario.Mes();
    anyo = tcalendario.Anyo();
    if(tcalendario.Mensaje()==NULL){
      mensaje=NULL;
    }else{
      mensaje= new char[strlen(tcalendario.Mensaje()) +1];
      strcpy(mensaje,tcalendario.Mensaje());
    }

  }
  return *this;//devuelves el obj
}
//----------------------Sobrecarga booleana----------------------------

bool TCalendario::operator > (const TCalendario& tcalendario) const{
  bool ret=false;
  if(anyo>tcalendario.anyo){
    ret=true;
  }else if(anyo==tcalendario.anyo && mes>tcalendario.mes){

      ret=true;

  }else if(anyo==tcalendario.anyo && mes==tcalendario.mes && dia>tcalendario.dia){
      ret=true;
  }else if(anyo==tcalendario.anyo && mes==tcalendario.mes && dia==tcalendario.dia){
    if(mensaje!=NULL && tcalendario.mensaje==NULL){
      ret=true;
    }if(mensaje!=NULL && tcalendario.mensaje!=NULL){
      if(strlen(mensaje)>strlen(tcalendario.mensaje)){
        ret=true;
      }
    }
  }

return ret;

}
bool TCalendario::operator < (const TCalendario& tcalendario) const{
bool ret=false;
  if( (*this != tcalendario)  && ( tcalendario > *this  ) ){
    ret=true;;
  }
    return ret;

}




//------------------------Sobrecargo post y pre incremento/decremento------------------


//-------------------incremento--------------
//++a;
TCalendario & TCalendario::operator ++(){
  this->sumaDia();
  return *this;
}
//a++
TCalendario TCalendario::operator ++(int opt){
  TCalendario temp(*this);//copio el objeto de la izq
  ++(*this);
  return temp;//devuelves temp sin modificar
}
//-----------decremento--------
//--a;
TCalendario & TCalendario::operator --(void){
this->restaDia();
return *this;
}
//a--;
TCalendario TCalendario::operator --(int opt){
  TCalendario temp(*this); //copio el objeto de la izquierda
  --(*this);
  return temp;
}
//----------------------( sobrecarga +, - ) --------------------------
TCalendario TCalendario::operator+(int dia2) const{
  TCalendario aux(dia,mes,anyo,mensaje);
  if(dia2>0 ){
    while(dia2>0){
        aux++;
        dia2--;
    }
  }

return aux;
}
TCalendario TCalendario::operator-(int dia2){
  TCalendario aux(dia,mes,anyo,mensaje);
  if(dia2>0){
    while(dia2>0){
      aux--;
      dia2--;
    }
  }

return aux;
}




bool TCalendario::ModFecha(int dia2, int mes2, int anyo2 ){
  bool ret=false;
  if(CheckDate(dia2,mes2,anyo2)){
    dia = dia2;
    mes = mes2;
    anyo = anyo2;
    ret=true;
  }
  return ret;

}
bool TCalendario::EsVacio(){
  if(mensaje==NULL && dia==1 && mes==1 && anyo==1900){
    return true;
  }else{
    return false;
  }
}

bool TCalendario::ModMensaje(const char* mensaje2){
  bool ret=false;
  if(mensaje2==NULL){
    mensaje=NULL;
    ret=true;
  }else{
      strcpy(mensaje,mensaje2);
      ret=true;
    }


return ret;

}
char * TCalendario::Mensaje() const {
    if(mensaje==NULL){
      return NULL;
    }
    return mensaje;

}
ostream& operator << (ostream &os,const TCalendario &tcalendario){

  if(tcalendario.dia<10){
    os<<"0";
  }
  os<<tcalendario.dia<<"/";

  if(tcalendario.mes<10){
    os<<"0";
  }
  os<<tcalendario.mes<<"/"<<tcalendario.anyo<<" "<<"\"";
  if(tcalendario.Mensaje()==NULL){
    os<<"\"";
  }else{
    os<<tcalendario.Mensaje()<<"\"";

  }


  return os;
}
