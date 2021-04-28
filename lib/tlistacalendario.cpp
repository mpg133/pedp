//Miguel Pérez Giménez
//DNI: 74395666G
#include <iostream>
#include <cstring>
#include<cstdlib>
#include "../include/tlistacalendario.h"
using namespace std;
//--------------------------TNODO------------------------------
TNodoCalendario::TNodoCalendario(){
  siguiente=NULL;
}
TNodoCalendario::TNodoCalendario(const TNodoCalendario& newNodo){
  if(this!=&newNodo){
    if(siguiente!=NULL){
      delete siguiente;
    }
    c=newNodo.c;
    siguiente=newNodo.siguiente;
  }

}
TNodoCalendario::~TNodoCalendario(){
  siguiente=NULL;
}
TNodoCalendario& TNodoCalendario::operator=(const TNodoCalendario& newNodo){
  if(this!= & newNodo){
    if(siguiente!=NULL){
      delete siguiente;
    }
    if(this!=NULL){
      c=newNodo.c;
      siguiente=newNodo.siguiente;
    }
  }
  return *this;
}
//-------------------------------------TListaPos---------------------------------
TListaPos::TListaPos(){
  pos=NULL;
}
TListaPos::TListaPos(const TListaPos& newPos){
  if(this!=&newPos){
    if(!newPos.EsVacia()){
      delete pos;
    }else {
      pos=newPos.pos;
    }
  }
}
TListaPos::~TListaPos(){
  pos=NULL;

}
TListaPos & TListaPos::operator=(const TListaPos& newPos){
  if(this!= &newPos){
    pos=newPos.pos;
  }
return *this;

}

bool TListaPos::operator== (const TListaPos& newPos) {
    return pos == newPos.pos;
}


bool TListaPos::operator!= (const TListaPos& newPos) {
    return pos != newPos.pos;
}


TListaPos TListaPos::Siguiente () const{
  TListaPos p;

      p.pos=pos->siguiente;


  return p;
}


bool TListaPos::EsVacia () const
{
    return pos == NULL;
}

//-----------------------------------TListaCalendario------------------------------
TListaCalendario::TListaCalendario(){

  primero=NULL;
}
TListaCalendario::TListaCalendario (const TListaCalendario& lista){
    TListaPos sig,p;

	if (this != &lista){
		primero = new TNodoCalendario(*lista.primero);
		  p = lista.Primera();
      sig = p.Siguiente();

		if (!sig.EsVacia()){
			while (!sig.EsVacia()){
				//Borrar(p);
        p.Siguiente();
				p.pos = new TNodoCalendario(*sig.pos);
				p = sig;

				sig = sig.Siguiente();
			}
		}
    }
}


TListaCalendario::~TListaCalendario (){
    TListaPos p, q;

    q = Primera();
    while (!q.EsVacia())
    {
        p = q;
        q = q.Siguiente();
        delete p.pos;
    }

    primero = NULL;
}


TListaPos TListaCalendario::Primera () const{
  TListaPos p;

    if (!EsVacia())
        p.pos = primero;

    return p;
}


bool TListaCalendario::EsVacia () const{
    return primero == NULL;
}


ostream & operator<<(ostream& os, const TListaCalendario& lista){

	TListaPos p = lista.Primera();

	os << "<";

	while (!p.EsVacia()){
		os << lista.Obtener(p);
		p = p.Siguiente();

		if (!p.EsVacia())
			os << " ";
	}

	os << ">";

	return os;
}


bool TListaCalendario::Insertar (const TCalendario& newCalendario){

  TNodoCalendario* aux= new TNodoCalendario();
	aux->c = newCalendario;


	// "INSERTAR: en lista vacia \n";
	if(primero == NULL){
		aux->siguiente=NULL;
    primero=aux;
		return true;
	}else{
    if (!Buscar(newCalendario)){
      //es el más antiguo
      if (newCalendario < primero->c) {
        aux->siguiente=primero;
        primero=aux;
        return true;
      }
      TListaPos p =Primera();


      //buscando posicion a insertar \n";

        while (!p.Siguiente().EsVacia()){
    		    if (newCalendario > Obtener(p) && (newCalendario <Obtener(p.Siguiente()) )){
                p.Siguiente().Siguiente()=p.Siguiente();
                Obtener(p.Siguiente())=newCalendario;
                //aux->siguiente=primero->siguiente;
                //primero->siguiente=aux;
                primero=p.pos;
    		        return true;
    		    }
    		      p=p.Siguiente();
            }



          //insertar ultimo
          p.pos->siguiente=aux;
          return true;
  }
}

    return false;
}


TCalendario TListaCalendario::Obtener (const TListaPos& p) const{

		return p.pos->c;

}


bool TListaCalendario::Buscar (const TCalendario& calendario) const {



	TListaPos  p = Primera();
	while (!p.EsVacia()) {

		if (p.pos->c== calendario)
			return true;

		p = p.Siguiente();
	}

	return false;
}


int TListaCalendario::Longitud (){
	int cont = 0;

	TListaPos p = Primera();
	while (!p.EsVacia()) {
		cont++;
		p = p.Siguiente();
	}

	return cont;
}



TListaPos TListaCalendario::Ultima() const {
    TListaPos ultima;

    if (!EsVacia()) {
        ultima = Primera();
        while (!ultima.Siguiente().EsVacia())
            ultima = ultima.Siguiente();
    }

    return ultima;
}


bool TListaCalendario::Borrar (const TCalendario& c) {
  bool ret=false;
  TNodoCalendario *aux= new TNodoCalendario();
  TListaPos p=Primera();
  TListaPos sig=p.Siguiente();
  if(primero->c==c){
    primero=sig.pos;
    return true;
  }
  while(!sig.EsVacia()){

        if(c==Obtener(sig)){
          p.pos=sig.pos->siguiente;
          return true;
        }
        p=p.Siguiente();
        sig=sig.Siguiente();
  }



    return false;
}


bool TListaCalendario::Borrar (const TListaPos& p) {
    TCalendario calendario=Obtener(p);
    if(Borrar(calendario)){
      return true;
    }
    return false;
}


bool
TListaCalendario::Borrar (const int d, const int m, const int a) {
  TListaPos p=Primera();
  TListaPos sig=p.Siguiente();
    while(!sig.EsVacia() ){
      if(Obtener(sig).Anyo()>a ){
        return true;
      }else if(Obtener(sig).Mes()>m && Obtener(sig).Anyo()==a ){
        return true;
      }else if( Obtener(sig).Dia() >= d && Obtener(sig).Mes()==m && Obtener(sig).Anyo()==a ){
        return true;
      }
      sig=sig.Siguiente();
      Borrar(p);
      primero=sig.pos;
      p=sig;

    }
    return false;

}

TListaCalendario& TListaCalendario::operator= (const TListaCalendario& lista)  {
	if (this != &lista) {
		TListaPos p = lista.Primera();
		while (!p.EsVacia()){
      //Borrar
			Insertar(Obtener(p));
			p = p.Siguiente();
		}
	}

	return *this;
}

TListaCalendario TListaCalendario::operator + (const TListaCalendario& p_l) {
TListaCalendario lista;

  if(!primero && p_l.primero){
    lista=p_l;
  }else if(primero && !p_l.primero){
    lista.primero=primero;
  }else{

    lista=*this;
    TNodoCalendario *p= new TNodoCalendario();
    p= p_l.primero;

    while(p!=NULL){
      lista.Insertar(p->c);
      if(p->siguiente==NULL){
        break;
      }
      p=p->siguiente;
    }

  }

	return lista;
}
TListaCalendario TListaCalendario::operator - (const TListaCalendario& p_l) {

TListaCalendario lista;
  //devuleve los elementos de this que no existen en p_l
  TListaPos p=Primera();
  while(!p.EsVacia()){
    if(!p_l.Buscar(Obtener(p))){
      lista.Insertar(Obtener(p));
    }
    p=p.Siguiente();
  }
	return lista;
}
// Extraer un rango de nodos de la lista
/*Devuelve una lista con los elementos TCalendario comprendidos entre las posiciones n1 y n2 (ambas
incluidas) de la lista que invoca a la función. Los nodos comprendidos entre n1 y n2 (ambos incluidos)
deben borrarse de la lista que invoca a la función.
Cosas a tener en cuenta:
*/
TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2){
  TListaCalendario lista;
  TListaPos p=Primera();
  if(n2>Longitud()){
    n2=Longitud();
  }
  if(n1<=0){
    n1=1;
  }
  if(n1>n2){
    return lista;
  }
  for(int i=1;i<n1;i++){
    p=p.Siguiente();
  }
  for(int i=n1;i<=n2;i++){
    lista.Insertar(Obtener(p));
    Borrar(Obtener(p));
    p=p.Siguiente();
  }
  return lista;
}

// Suma de dos sublistas en una nueva lista

TListaCalendario TListaCalendario::SumarSubl(int I_l1,int F_l1 , TListaCalendario & l2,int I_l2,int F_l2){
TListaCalendario lista1;

  lista1= ExtraerRango(I_l1,F_l1);
  TListaCalendario lista2=l2.ExtraerRango(I_l2,F_l2);
  TListaCalendario resultado=lista1+lista2;
  return resultado;

}
