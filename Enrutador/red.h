#ifndef RED_H
#define RED_H
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <enrutador.h>

using namespace std;

class Red
{
private:

    map<string,Enrutador> enrutadores;

    map<string,map<string,int>> tablasEnrutamiento;

public:

    void agregarEnrutador(const string &nombre)
    {
        if(enrutadores.find(nombre) ==
            enrutadores.end())
        {
            enrutadores.insert(
                {
                    nombre,
                    Enrutador(nombre)
                });
        }
    }

    void removerEnrutador(const string &nombre)
    {
        enrutadores.erase(nombre);

        for(auto &router : enrutadores)
        {
            router.second.eliminarEnlace(nombre);
        }
    }

    void agregarEnlace(const string &origen,
                       const string &destino,
                       int costo)
    {
        if(enrutadores.find(origen) !=
                enrutadores.end() &&

                enrutadores.find(destino) !=
                enrutadores.end())
        {
            enrutadores[origen]
                .agregarEnlace(destino,costo);

            enrutadores[destino]
                .agregarEnlace(origen,costo);
        }
    }

    void removerEnlace(const string &origen,
                       const string &destino)
    {
        if(enrutadores.find(origen) !=
            enrutadores.end())
        {
            enrutadores[origen]
                .eliminarEnlace(destino);
        }

        if(enrutadores.find(destino) !=
            enrutadores.end())
        {
            enrutadores[destino]
                .eliminarEnlace(origen);
        }
    }

    void actualizarCosto(const string &origen,
                         const string &destino,
                         int nuevoCosto)
    {
        if(enrutadores.find(origen) !=
            enrutadores.end())
        {
            enrutadores[origen]
                .actualizarCosto(destino,
                                 nuevoCosto);
        }

        if(enrutadores.find(destino) !=
            enrutadores.end())
        {
            enrutadores[destino]
                .actualizarCosto(origen,
                                 nuevoCosto);
        }
    }

    void cargarDesdeArchivo(const string &nombreArchivo)
    {
        enrutadores.clear();

        ifstream archivo(nombreArchivo);

        string linea;

        while(getline(archivo, linea))
        {
            string origen = "";

            string destino = "";

            string costoTexto = "";

            int i = 0;

            while(linea[i] != ',')
            {
                origen += linea[i];

                i++;
            }

            i++;

            while(linea[i] != ',')
            {
                destino += linea[i];

                i++;
            }

            i++;

            while(i < linea.size())
            {
                costoTexto += linea[i];

                i++;
            }

            int costo = stoi(costoTexto);

            agregarEnrutador(origen);

            agregarEnrutador(destino);

            agregarEnlace(origen,
                          destino,
                          costo);
        }

        archivo.close();
    }

    void guardarEnArchivo(const string &nombreArchivo)
    {
        ofstream archivo(nombreArchivo);

        for(const auto &router :
             enrutadores)
        {
            string origen =
                router.first;

            for(const auto &enlace :
                 router.second.getEnlaces())
            {
                string destino =
                    enlace.first;

                int costo =
                    enlace.second;

                if(origen < destino)
                {
                    archivo
                        << origen
                        << ","
                        << destino
                        << ","
                        << costo
                        << endl;
                }
            }
        }

        archivo.close();
    }

    void mostrarRed() const
    {
        cout << endl;

        for(const auto &router :
             enrutadores)
        {
            cout
                << "Enrutador: "
                << router.first
                << endl;

            for(const auto &enlace :
                 router.second.getEnlaces())
            {
                cout
                    << " -> "
                    << enlace.first
                    << " | costo: "
                    << enlace.second
                    << endl;
            }

            cout << endl;
        }
    }

    void bfs(const string &origen)
    {
        map<string,bool> visitados;

        map<string,int> distancias;

        vector<string> cola;

        for(const auto &router :
             enrutadores)
        {
            visitados[router.first] =
                false;

            distancias[router.first] =
                -1;
        }

        cola.push_back(origen);

        visitados[origen] = true;

        distancias[origen] = 0;

        int inicio = 0;

        while(inicio < cola.size())
        {
            string actual =
                cola[inicio];

            inicio++;

            for(const auto &vecino :
                 enrutadores[actual]
                     .getEnlaces())
            {
                string destino =
                    vecino.first;

                if(!visitados[destino])
                {
                    visitados[destino] =
                        true;

                    distancias[destino] =
                        distancias[actual] + 1;

                    cola.push_back(destino);
                }
            }
        }

        tablasEnrutamiento[origen] =
            distancias;
    }

    void mostrarTablaEnrutamiento(
        const string &origen)
    {
        if(tablasEnrutamiento.find(origen)
            ==
            tablasEnrutamiento.end())
        {
            bfs(origen);
        }

        cout << endl;

        cout
            << "TABLA DE ENRUTAMIENTO"
            << endl;

        cout
            << "Origen: "
            << origen
            << endl
            << endl;

        for(const auto &destino :
             tablasEnrutamiento[origen])
        {
            cout
                << origen
                << " -> "
                << destino.first
                << " | saltos: "
                << destino.second
                << endl;
        }

        cout << endl;
    }
};


#endif // RED_H
