#ifndef POLY_H
#define POLY_H

class Poly
{   
    private:
    int grau;
    double *a;

    public:
        //Construtor default
        Poly();
        // Construtor por copia
        Poly(const Poly &P);
        // Construtor por movimento
        Poly(Poly &&P);
        // Construtor por especifico
        explicit Poly(int grau_p);
        // destrutor
        ~Poly();
        // operador de atribuição por copia
        Poly &operator=(const Poly &P);
        // operador de atribuição por movimento
        Poly &operator=(Poly &&P);
        // metodo de consulta do grau
        int getGrau() const;
        // metodo de consulta do coef
        double getCoef(int posicao) const;
        // metodo de alterar o coef
        void setCoef(int posicao, double new_coef);

};
#endif // POLY_H
