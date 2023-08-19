#include <iostream>
#include <ctime>
#include <string>

using namespace std;

template <class T>
class Ruta {
private:
    T kilometro;
    T hora;
    T cliente;
    T correo;
    T fecha;


public:
    Ruta() {}

    T distanciaTiempo(T kilometro, T hora) {
        this->kilometro = kilometro;
        this->hora = hora;
        return kilometro * hora;
    }

    void informeEntrega(T cliente, T correo, T fecha) {
        this->cliente = cliente;
        this->correo = correo;
        this->fecha = fecha;


        cout << "Nombre del Comprador: " << cliente << endl;
        cout << "Correo: " << correo << endl;
        cout << "Fecha: " << fecha << endl;

    }
};

string currentDateTime() {
    time_t t = std::time(nullptr);
    tm* now = std::localtime(&t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    return buffer;
}

int main() {
    float kilometro = 12.3;
    int horas = 2;
    string cliente = "Fernando", correo = "ferna.dwcarl@gmail.com";


    Ruta<float> demora;
    float tiempo = demora.distanciaTiempo(kilometro, horas);
    cout << "Tiempo estimado: " << tiempo << endl;

    Ruta<string> informe;
    informe.informeEntrega(cliente, correo, currentDateTime());

    return 0;
}

