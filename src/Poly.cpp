#include "Poly.h"

#include <iostream>
#include <fstream>
#include <cmath> // pow
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

// sobrecarga do operador []
double Poly::operator[](int posicao) const{ return getCoef(posicao);}

// metodo para redefinir o grau e os coeficientes
void Poly::recriar(int new_grau){
    if(grau != new_grau){
        if(new_grau < 0){
            *this = Poly();
        }else if(new_grau == 0){
            *this = Poly(0);
        }else{
            *this = Poly(new_grau);
        } 
    }
    return;
}

// sobrecarga do operador ==
bool Poly::operator==(const Poly &P) const{
    if(this->grau == P.grau){
        for(int i=0; i<=grau; i++){
            if(this->a[i] != P.a[i]) return false;
        }
        return true;
    }
    return false;
}

// sobrecarga do operador !=
bool Poly::operator!=(const Poly &P) const{
    if(*this==P){
        return false;
    }
    return true;
}

// metodo de consulta empty
bool Poly::empty() const{
    if(grau < 0){
        return true;
    }
    return false;
}

// metodo de consulta isZero
bool Poly::isZero() const{
    if(grau == 0 && a[0] == 0.0){
        return true;
    }
    return false;
}

// metodo de consulta getValor
double Poly::getValor(const double x) const{
    if(empty()){
        return 0.0;
    }
    double result = 0.0;
    for(int i=0; i <=grau; i++){ 
        result += a[i] * pow(x, i);
    }
    return result;
}

// sobrecarga do operador ()
double Poly::operator()(double x) const{ return getValor(x);}

// output de dados
ostream &operator<<(ostream &X, const Poly &P){
    for(int i=P.grau; i>=0; i--){
        if(P.a[i]==0.0){
            if(i==0 && P.grau == 0) X << P.a[i];
        }else{
            if(P.a[i] < 0.0){
                X << '-';
            }else{
                if(i != P.grau) X << '+';
            }
            if(fabs(P.a[i]) != 1.0 || i == 0) X << fabs(P.a[i]);
            if( i != 0){
                if(fabs(P.a[i]) != 1.0) X << '*';
                X << 'x';
                if(i > 1){
                    X << '^';
                    X << i;
                }
            }
        }
    }
    return X;
}

// input de dados
istream &operator>>(istream &X, const Poly &P){
    if(P.empty()){
        return X;
    }else{
        if(P.grau == 0){
            cout << 'x^' << P.grau << ':';
            X >> P.a[0];
        }else{
            for(int i = P.grau; i>= 0; i--){
                if(i == P.grau){
                    do{
                        cout << 'x^' << i << ':';
                        X >> P.a[P.grau];
                    }while(P.a[P.grau] == 0.0);
                }else{
                    cout << 'x^' << i << ':';
                    X >> P.a[i];
                }
            }
        }
    }
    return X;
}

// metodo para escrever um poly em arquivo 
bool Poly::salvar(const string &arquivo) const{
    ofstream output(arquivo);
    if(!output.is_open()){
        return false;
    }
    output << "POLY " << grau << endl;
    if( grau < 0){
        return true;
    }
    for (int i = 0; i<=grau; i++){
        output << a[i] <<" ";
    }
    output << endl;
    return true;
}

