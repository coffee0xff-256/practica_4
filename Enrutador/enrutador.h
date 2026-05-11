#ifndef ENRUTADOR_H
#define ENRUTADOR_H
using namespace std;
#include <string>
#include <map>

class Enrutador{

public:

    Enrutador(const string &nombre)
    {
        this->nombre = nombre;
    }

    string getNombre() const
    {
        return nombre;
    }

    const map<string,int> &getEnlaces() const
    {
        return enlaces;
    }

    void agregarEnlace(const string &destino, int costo)
    {
        enlaces[destino] = costo;
    }

    void eliminarEnlace(const string &destino)
    {
        enlaces.erase(destino);
    }

    void actualizarCosto(const string &destino, int nuevoCosto)
    {
        enlaces[destino] = nuevoCosto;
    }


private:
    string nombre;
    map<string,int> enlaces;
};
#endif // ENRUTADOR_H
