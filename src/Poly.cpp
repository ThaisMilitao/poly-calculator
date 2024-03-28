#include "Poly.h"

#include <iostream>
using namespace std;
//Construtor default
Poly::Poly(): grau(-1), a(nullptr){}

// Construtor por copia
Poly::Poly(const Poly &P): grau(P.grau),a(nullptr){
    if(grau>=0) a = new double[grau+1];
    for(int i=0; i <=grau; i++) a[i] = P.a[i];
}

// Construtor por movimento
Poly::Poly(Poly &&P): grau(P.grau),a(P.a){
    P.grau = -1;
    P.a = nullptr;
}

// Construtor por especifico
Poly::Poly(int grau_p){
    if(grau_p < 0){
        grau = -1;
        a = nullptr;
        return;
    }else{
        grau = grau_p;
        a = new double[grau+1];
        for(int i=0; i <=grau; i++){ 
            a[i] = 0.0;
        }
        if(grau > 0) a[grau] = 1.0;
    }
}

// destrutor
Poly::~Poly(){ delete[] a;}

// operador de atribuição por copia
Poly &Poly::operator=(const Poly &P){
    if(this != &P){
        if(this->grau != P.grau){
            delete[] a;
            this->grau = P.grau;
            if(grau>=0) this->a = new double[grau+1];
            else this->a = nullptr;
        }
        for(int i=0; i <=grau; i++){ 
            a[i] = P.a[i];
        }
    }
    return *this;
}

// operador de atribuição por movimento
Poly &Poly::operator=(Poly &&P){
    delete[] a;
    grau = P.grau;
    a = P.a;

    P.grau = -1;
    P.a = nullptr;

    return *this;
}

// metodo de consulta do grau
int Poly::getGrau() const{return grau;}

// metodo de consulta do coef
double Poly::getCoef(int posicao) const{
    if(posicao < 0 || posicao > grau){
        return 0.0;
    }
    return a[posicao];
}

// metodo de alterar o coef
void Poly::setCoef(int posicao, double new_coef){
    if(posicao < 0 || posicao > grau){
        cerr << "Indice invalido\n";
        return;
    }else if ( grau != 0 && posicao == grau && new_coef == 0.0){
        cerr << "Indice invalido\n";
        return;
    }
    a[posicao] = new_coef;
}