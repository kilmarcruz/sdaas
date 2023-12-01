#include <iostream>
#include <fstream> //libreria para los archivos txt
using namespace std;
void comentariosUsuario();
void verResenias();
void resenia();
void recomendacionPlatos();

int main()
{
    int opcion,repiteMenu;
    cout<<"hola";
do {
    cout << "Seleccione una de las opciones\n";
    cout << "1.Dejar un comentario sobre nustros servicios \n";
    cout << "2.Ver resenias de otros clientes\n";
    cout << "3.Calificar nuestros servicio \n";
    cout << "4.Recomendacion de platos \n";
    cout << "Su opcion es: ";
    cin  >> opcion;
    system("cls");
    switch (opcion)
    {
    
    case 1:
        cout<<"--------Esta en el apartado de comentarios--------\n";
        comentariosUsuario();
        
        break;
    case 2:
        cout<<"--------Resenias de usuarios--------\n";
        verResenias();
        break;
        
    default:cout<<"Elija una opcion correcta \n";
        break;
    }
        cout << "\n";
        cout << "Desea regresar al menu otra vez? (1-Si, 0-No): \n";
        cout <<  "Su opcion es: ";
        cin  >> repiteMenu;
        system("cls");
} while (repiteMenu == 1);
cout<<"Muchas gracias por preferirnos :)";
    return 0;
}


void comentariosUsuario(){
string comentario,nombreCliente,apellido_cliente;
int opcion;

cin.ignore();//ignorara el bufer antes de usar el getline
cout<<"Ingrese su nombres por favor: \n";
getline(cin, nombreCliente);//guardara los nombres de los usuarios
cout<<"Ingrese su apellidos por favor: \n";
getline(cin, apellido_cliente);//guardara los dos apellidos del usuario 
cout<<"Esrcribra su comentario por favor y presione ENTER cuando termine: \n";
getline(cin, comentario);//guardara toda la reseña del usuario.
cout<<"Esta seguro de dejar este comentario? (1=si/0=no)\n";
cin>>opcion;
system("cls");

if (opcion == 1) {
        cout << "Muchas gracias por brindarnos sus comentarios. Los tomaremos en cuenta para mejorar la experiencia.\n";

        // Guardar el comentario en un archivo
        ofstream archivo_comentarios("comentarios.txt", ios::app); // Crea el archivo a nombre de comentarios.txt
        if (archivo_comentarios.is_open())//abre el archivo y comienza a capturar los datos
        {
            archivo_comentarios << "Nombres del cliente: " << nombreCliente << "\nApellidos del cliente: "<<apellido_cliente <<"\nComentario: " << comentario << "\n";
            archivo_comentarios << "\n";
            archivo_comentarios.close();//cierra el archivo y deja de capturar los datos
        } else {
            cout << "No se pudo abrir el archivo para guardar el comentario.\n";
        }
    }
}

void verResenias(){
    ifstream archivo_comentarios("comentarios.txt");
    string linea;

    if (archivo_comentarios.is_open()) {
        while (getline(archivo_comentarios, linea)) {
            cout << linea << endl;
        }
        archivo_comentarios.close();
    } else {
        cout << "No se pudo abrir el archivo de resenias." << endl;
    }

}

