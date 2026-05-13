#include <iostream>
#include <vector>
#include <red.h>

using namespace std;

// Función para limpiar la pantalla
void clearScreen()
{
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();

#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

// Menú de usuario
int main()
{
    Red red;

    int opcion;

    do
    {
        cout << "\n--- MENU RED DE ENRUTADORES ---\n";
        cout << "1. Cargar topologia desde archivo\n";
        cout << "2. Agregar enrutador\n";
        cout << "3. Remover enrutador\n";
        cout << "4. Agregar enlace\n";
        cout << "5. Eliminar enlace\n";
        cout << "6. Mostrar tabla de enrutamiento\n";
        cout << "7. Mostrar red\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        string nombre;
        string origen;
        string destino;
        string archivo;

        int costo;

        switch(opcion)
        {

        case 1:
            cout << "Nombre del archivo: ";
            cin >> archivo;

            red.cargarDesdeArchivo(archivo);

            cout << "Topologia cargada.\n";

            clearScreen();

            break;
            //


        case 2:

            cout << "Nombre del enrutador: ";
            cin >> nombre;

            red.agregarEnrutador(nombre);

            cout << "Enrutador agregado.\n";

            clearScreen();

            break;
            //


        case 3:
            cout << "Nombre del enrutador: ";
            cin >> nombre;

            red.removerEnrutador(nombre);

            cout << "Enrutador removido.\n";

            clearScreen();

            break;

            //


        case 4:
            cout << "Origen: ";
            cin >> origen;

            cout << "Destino: ";
            cin >> destino;

            cout << "Costo: ";
            cin >> costo;

            red.agregarEnlace(origen, destino, costo);

            cout << "Enlace agregado.\n";

            clearScreen();

            break;

            //
        case 5:

            cout << "Origen: ";
            cin >> origen;

            cout << "Destino: ";
            cin >> destino;

            red.removerEnlace(origen, destino);

            cout << "Enlace eliminado.\n";

            clearScreen();

            break;
            //


        case 6:


            //
            cout << "Enrutador origen: ";
            cin >> origen;

            red.mostrarTablaEnrutamiento(origen);

            clearScreen();

            break;

        case 7:

            red.mostrarRed();

            clearScreen();

            break;

        case 0:

            cout << "Saliendo...\n";

            break;

        default:

            cout << "Opcion invalida.\n";

            clearScreen();
        }

    }
    while(opcion != 0);

    return 0;
}
