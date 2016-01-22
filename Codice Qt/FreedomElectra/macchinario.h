#ifndef MACCHINARIO_H
#define MACCHINARIO_H

#include<componente.h>

class Macchinario : public Componente{
private:
    int kw;
public:
    Macchinario(string, string, int, int, int, float, int, Cliente* =0, SalaCompressori* =0);
//    string getTipo() const;
    // get
    virtual int getKw() const;

    // set
    virtual void setKw(int);
};

#endif // MACCHINARIO_H
