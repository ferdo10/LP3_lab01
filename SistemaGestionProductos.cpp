/*@article{takeyasmanejo,
  title={Manejo de Archivos en Lenguaje C++},
  author={Takeyas, Bruno L{\'o}pez}
}*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include<string>
#include <iomanip>
using namespace std;



struct Producto {
    char nombre[50];
    char indice[20];
    int cantidad;
    float precio;
    char garantia[10];
};

void agregarProducto() {
    ofstream archivo("inventario.dat", ios::binary | ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    Producto producto;

    cout << "Ingrese el nombre del producto: ";
    cin.getline(producto.nombre, sizeof(producto.nombre));

    cout << "Ingrese el número de indice del producto: ";
    cin.getline(producto.indice, sizeof(producto.indice));

    cout << "Ingrese la cantidad del producto: ";
    cin >> producto.cantidad;

    cout << "Ingrese el precio del producto: ";
    cin >> producto.precio;

    cout << "Ingrese la garantía del producto (Sí/No): ";
    cin.ignore();//descartar los caracteres de nueva línea adicionales.
    cin.getline(producto.garantia, sizeof(producto.garantia));

    archivo.write(reinterpret_cast<const char*>(&producto), sizeof(Producto));// convertir el puntero de la estructura producto a un puntero de tipo char*.
    //Esto se hace porque la función read() espera un puntero de tipo char* para almacenar los bytes leídos.
    archivo.close();

    cout << "Producto agregado exitosamente." << endl;
}

void mostrarInventario() {
    ifstream archivo("inventario.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    cout << "Inventario completo:" << endl;

    Producto producto;
    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(Producto))) {
        cout << "Nombre: " << producto.nombre << endl;
        cout << "Número de serie: " << producto.indice << endl;
        cout << "Cantidad: " << producto.cantidad << endl;
        cout << "Precio: " << fixed << setprecision(2) << producto.precio << endl;
        cout << "Garantía: " << producto.garantia << endl;
        cout << "--------------------------" << endl;
    }

    archivo.close();
}

void buscarProducto() {
    ifstream archivo("inventario.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string buscar;
    cout << "Ingrese el nombre o número de indice del producto a buscar: ";
    getline(cin, buscar);

    Producto producto;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(Producto))) {
        if (strcmp(producto.nombre, buscar.c_str()) == 0 || strcmp(producto.indice, buscar.c_str()) == 0) {
            cout << "Nombre: " << producto.nombre << endl;
            cout << "Número de serie: " << producto.indice << endl;
            cout << "Cantidad: " << producto.cantidad << endl;
            cout << "Precio: " << fixed << setprecision(2) << producto.precio << endl;
            cout << "Garantía: " << producto.garantia << endl;
            cout << "--------------------------" << endl;

            encontrado = true;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado." << endl;
    }
}

void actualizarProducto() {
    fstream archivo("inventario.dat", ios::binary | ios::in | ios::out);//in lectura de datos, out escritura de datos desde el archivo
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string buscar;
    cout << "Ingrese el nombre o número de indice del producto a actualizar: ";
    getline(cin, buscar);

    Producto producto;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(Producto))) {
        if (strcmp(producto.nombre, buscar.c_str()) == 0 || strcmp(producto.indice, buscar.c_str()) == 0) {
            cout << "Producto encontrado. Ingrese los nuevos datos:" << endl;

            cout << "Ingrese el nombre del producto: ";
            cin.getline(producto.nombre, sizeof(producto.nombre));

            cout << "Ingrese el número de indice del producto: ";
            cin.getline(producto.indice, sizeof(producto.indice));

            cout << "Ingrese la cantidad del producto: ";
            cin >> producto.cantidad;

            cout << "Ingrese el precio del producto: ";
            cin >> producto.precio;

            cout << "Ingrese la garantía del producto (Sí/No): ";
            cin.ignore();
            cin.getline(producto.garantia, sizeof(producto.garantia));

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&producto), sizeof(Producto));

            cout << "Producto actualizado exitosamente." << endl;

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado." << endl;
    }
}

void eliminarProducto() {
    ifstream archivo("inventario.dat", ios::binary);//lee
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    ofstream archivoTemp("temp.dat", ios::binary);//escribe
    if (!archivoTemp) {
        cout << "Error al abrir el archivo temporal." << endl;
        archivo.close();
        return;
    }

    string buscar;
    cout << "Ingrese el nombre o número de indice del producto a eliminar: ";
    getline(cin, buscar);

    Producto producto;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(Producto))) {
        if (strcmp(producto.nombre, buscar.c_str()) != 0 && strcmp(producto.indice, buscar.c_str()) != 0) {
            archivoTemp.write(reinterpret_cast<const char*>(&producto), sizeof(Producto));
        }
        else {
            encontrado = true;
        }
    }

    archivo.close();
    archivoTemp.close();

    remove("inventario.dat");
    rename("temp.dat", "inventario.dat");

    if (encontrado) {
        cout << "Producto eliminado exitosamente." << endl;
    }
    else {
        cout << "Producto no encontrado." << endl;
    }
}
void realizarVenta() {
    fstream archivo("inventario.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string buscar;
    cout << "Ingrese el nombre o número de indice del producto a vender: ";
    getline(cin, buscar);

    Producto producto;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(Producto))) {
        if (strcmp(producto.nombre, buscar.c_str()) == 0 || strcmp(producto.indice, buscar.c_str()) == 0) {
            cout << "Producto encontrado. Ingrese la cantidad a vender: ";
            int cantidadVenta;
            cin >> cantidadVenta;

            if (cantidadVenta <= producto.cantidad) {
                producto.cantidad -= cantidadVenta;

                archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);//comando desplazamientos
                archivo.write(reinterpret_cast<const char*>(&producto), sizeof(Producto));

                cout << "Venta realizada exitosamente." << endl;
            }
            else {
                cout << "No hay suficiente cantidad disponible para realizar la venta." << endl;
            }

            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado." << endl;
    }
}

void mostrarMenu() {
    cout << "------ MENU ------" << endl;
    cout << "1. Agregar producto" << endl;
    cout << "2. Mostrar inventario" << endl;
    cout << "3. Buscar producto" << endl;
    cout << "4. Actualizar producto" << endl;
    cout << "5. Eliminar producto" << endl;
    cout << "6. Realizar una venta" << endl;
    cout << "7. Salir" << endl;
    cout << "Ingrese su opción: ";
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            agregarProducto();
            break;
        case 2:
            mostrarInventario();
            break;
        case 3:
            buscarProducto();
            break;
        case 4:
            actualizarProducto();
            break;
        case 5:
            eliminarProducto();
            break;
        case 6:
            realizarVenta();
            
            break;
        case 7:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;
    } while (opcion != 7);

    return 0;
}
