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
    case 3:
        cout<<"--------calificar nuestros servicios--------\n";
        resenia();
        break;
    case 4:
        cout<<"--------Recomendacion de platos--------\n";
        recomendacionPlatos();
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

void resenia()
{
    int  estrellas;
    string nombre,apellidos;

    cin.ignore();
    cout<<"Ingrese sus nombres\n";
    getline(cin, nombre);
    cout<<"Ingrese sus apellidos\n";
    getline(cin, apellidos);

    ofstream archivo("registro_de_estrellas.txt", ios::app); // crea el archivo
    if (archivo.is_open())//abre el archivo y comienza a capturar los datos
    {
        do
        {
        cout<<"Califique nuestros servicios del 1 al 5, siendo 5 la maxima nota: \n";
        cout<<"Su calificacion es: ";
        cin>>estrellas;
        system("cls");

        if (estrellas >= 1 && estrellas <= 5)
        {
            
            cout << "Nombres del cliente: " << nombre << "\n";
            cout << "Apellidos del cliente: " << apellidos << "\n";
            cout << "Numero de estrellas que puso el cliente: ";

            for (int i = 0; i < estrellas; i++)
            {
                cout<<"*";
            }
            cout<<"\n";

            //escribe la información en el archivo
            archivo<<"Nombre del cliente: " << nombre << "\n";
            archivo<<"Apellidos del cliente: " << apellidos << "\n";
            archivo<<"Numero de estrellas que puso el cliente: ";
            for (int i = 0; i < estrellas; i++)
            {
                archivo << "*";
            }
            archivo<<"\n";
            archivo<<"\n";
        }
        else
            cout<<"Ponga un numero dentro del rango por favor\n";
    } while (estrellas < 1 || estrellas > 5);//se ocupara un do while por si el usuario ingresa un numero fuera del rango que  el programa le volvera a solicitar el numero

    archivo.close(); // cierra el archivo
        }else {
            cout<<"No se pudo abrir el archivo para guardar el comentario.\n";
        }    
}

void recomendacionPlatos(){
    int opcion;
    bool confirmacion;
    do
    {
    cout<<"Elija un plato por favor.\n";
    cout<<"Plato.                          Precio.\n";
    cout<<"1-Espagueti.                      $4\n";
    cout<<"2-Carne asada.                    $7\n";
    cout<<"3-Hamburguesa doble carne.        $10\n";
    cout<<"Su opcion es: ";
    cin>>opcion;
    system("cls");

    switch (opcion)
    {
    case 1:
        cout<<"Esta seguro de elegir espagueti? (1-si, 0-no)\n";
        cin>>confirmacion;
        system("cls");
        if (confirmacion == 1)
        {
            cout<<"Se a confirmado su pedido";
        }else cout<<"vuelva a elegir una opcion por favor";
        
        break;

    case 2:
        cout<<"Esta seguro de elegir carne asada? (1-si, 0-no)\n";
        cin>>confirmacion;
        system("cls");
        if (confirmacion == 1)
        {
            cout<<"Se a confirmado su pedido";
        }else cout<<"vuelva a elegir una opcion por favor";
        break;

    case 3:
        cout<<"Esta seguro de elegir Hamburguesa doble carne? (1-si, 0-no)\n";
        cin>>confirmacion;
        system("cls");
        if (confirmacion == 1)
        {
            cout<<"Se a confirmado su pedido";
        }else cout<<"vuelva a elegir una opcion por favor";
        break;        
    
    default:cout<<"Elija una opcion correcta por favor\n";
        break;
    }
    } while (opcion < 1 || opcion > 3);
    
};
