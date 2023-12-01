#include <iostream>
#include <string>
#include <vector> //permite usar vectores para almacenar datos mas facil
#include <ctime> //se utiliza para trabajar con el tiempo
#include <iomanip> //ayuda a formatear la salida
#include <fstream> //para el manejo de archivos 
#include <cstdlib>
#include <algorithm>

using namespace std;

// Función para generar un número de reserva aleatorio
int generarNumeroReserva() {
    return rand() % 10000 + 1000;  // Números aleatorios entre 1000 y 9999
}

//struct para representar una mesa
struct Mesa {
    int numero;
    int capacidad;
    bool reservada;
    string ocupadaPor; //info del cliente que reservó la mesa
};

//struct para representar una reserva
struct Reserva {
    string fecha;
    string hora;
    int numPersonas;
    int mesaAsignada;
    string nombreCliente;
    string correoCliente;
    string numeroReserva;
};

//función para mostrar mesas disponibles con capacidad suficiente
void mostrarMesasDisponibles(const vector<Mesa>& mesas, int numPersonas) {
    cout << "Mesas disponibles para " << numPersonas << " personas:" << endl;
//for que itera sobre el vector de mesas y muestra las mesas actualmente ocupadas con los nombres de los clientes
    for (const Mesa& mesa : mesas) {
        if (!mesa.reservada && mesa.capacidad >= numPersonas) {
            cout << "Mesa #" << mesa.numero << " (Capacidad: " << mesa.capacidad << " personas)" << endl;
        }
    }
}

//funcion para realizar una reserva
void hacerReserva(vector<Mesa>& mesas, vector<Reserva>& reservas) {
    string fecha, hora, nombre, correo;
    int numPersonas;

    time_t now = time(0); //obtiene la hora actual en segundos
    tm* localTime = localtime(&now); //convierte la hora actual a una estructura de tiempo


    char currentTime[9];
    strftime(currentTime, 9, "%H:%M:%S", localTime); //formatea la hora actual

    string currentHour(currentTime);

    char opcionDia;
    cout << "Desea hacer la reserva para hoy (H) o para un dia futuro (F)?: ";
    cin >> opcionDia;

    if (opcionDia == 'H' || opcionDia == 'h') {
        if (currentHour >= "08:00:00") { //comprueba si es después de las 8:00 AM
            currentHour = "08:00";
        }
        fecha = "hoy";
    } else if (opcionDia == 'F' || opcionDia == 'f') {
        cout << "Ingrese la fecha: ";
        cin >> fecha;
        currentHour = "08:00";  //reinicia la hora para futuras reservas a las 8:00 AM
    } else {
        cout << "Opcion no valida. Seleccione 'H' para hoy o 'F' para un dia futuro." << endl;
        return;
    }

    cout << "Horarios disponibles: 08:00, 11:00, 13:00, 15:00, 17:00, 19:00" << endl;
    cout << "Ingrese la hora (HH:MM): ";
    cin >> hora;

    //comprueba que la hora sea válida
    if (hora != "08:00" && hora != "11:00" && hora != "13:00" && hora != "15:00" && hora != "17:00" && hora != "19:00") {
        cout << "Las reservas solo se permiten en horarios ya especificados." << endl;
        return;
    }

    //pide al usuario el número de personas para la reserva
    cout << "Numero de personas (maximo 8 personas): ";
    cin >> numPersonas;
    system("cls");

    //verifica que el número de personas esté en el rango válido
    if (numPersonas >= 1 && numPersonas <= 8) {
        //muestra las mesas disponibles para el número de personas ingresado
        mostrarMesasDisponibles(mesas, numPersonas);

        //pide al usuario que seleccione el número de la mesa deseada
        int mesaSeleccionada;
        cout << "Seleccione el numero de la mesa deseada: ";
        cin >> mesaSeleccionada;
        system("cls");

        //busca la mesa seleccionada en el vector de mesas
        for (Mesa& mesa : mesas) {
            //verifica que la mesa esté disponible y tenga capacidad suficiente
            if (mesa.numero == mesaSeleccionada && !mesa.reservada && mesa.capacidad >= numPersonas) {
                cout << "Ingrese su nombre: ";
                cin.ignore(); //ignora el salto de línea pendiente en el búfer
                getline(cin, nombre);

                cout << "Ingrese su correo electronico: ";
                cin >> correo;
                system("cls");

                //marca la mesa como reservada y asigna el nombre del cliente a la mesa
                mesa.reservada = true;
                mesa.ocupadaPor = nombre; //asigna el nombre del cliente a la mesa

                //crea una nueva reserva con los detalles proporcionados y asignar un numero de reserva aleatorio
                Reserva nuevaReserva = {fecha, hora, numPersonas, mesa.numero, nombre, correo, to_string(generarNumeroReserva())}; //convierte el numero de reserva a su representación como string
                //agrega la nueva reserva al vector de reservas
                reservas.push_back(nuevaReserva);

                cout << "Reserva exitosa para la Mesa #" << mesa.numero << endl;
                cout << "Reserva exitosa! Su numero de reserva es: " << nuevaReserva.numeroReserva << endl;

                return;
            }
        }

        cout << "La mesa seleccionada no esta disponible." << endl;
    } else {
        cout << "El numero de personas debe estar entre 1 y 8." << endl;
    }
}

//función para ver las reservas
void verReservas(const vector<Reserva>& reservas) {
    cout << "Reservas hechas:" << endl;
    //for que itera sobre el vector de reservas y muestra los detalles de cada reserva
    for (const Reserva& reserva : reservas) {
        cout << "Fecha: " << reserva.fecha << " -- Hora: " << reserva.hora << " -- Mesa: #" << reserva.mesaAsignada
             << " -- Personas: " << reserva.numPersonas << " -- Nombre: " << reserva.nombreCliente << " -- Correo: " << reserva.correoCliente << endl;
    }
}

//función para mostrar las mesas ocupadas
void mostrarMesasOcupadas(const vector<Mesa>& mesas) {
    cout << "Mesas actualmente ocupadas:" << endl;
    //for que itera sobre el vector de mesas y muestra las mesas actualmente ocupadas con los nombres de los clientes
    for (const Mesa& mesa : mesas) {
        if (mesa.reservada) {
            cout << "Mesa #" << mesa.numero << " (Ocupada por: " << mesa.ocupadaPor << ")" << endl;
        }
    }
}

//función para limpiar la información de los vectores de reservas, opc solo para administrador
void eliminarReservas(vector<Reserva>& reservas) {
    //limpia el vector de reservas
    reservas.clear();
    cout << "Todas las reservas han sido eliminadas." << endl;
}

// Función para que el usuario cancele una reserva
void cancelarReserva(vector<Reserva>& reservas) {
    int numeroReserva;
    cout << "Ingrese el numero de reserva que desea cancelar: ";
    cin >> numeroReserva;

    auto it = find_if(reservas.begin(), reservas.end(), [numeroReserva](const Reserva& r) {
       return r.numeroReserva == to_string(numeroReserva);
    });

    if (it != reservas.end()) {
        // Elimina la reserva si se encuentra
        reservas.erase(it);
        cout << "Reserva cancelada exitosamente." << endl;
    } else {
        cout << "Numero de reserva no encontrado. Verifique e intente nuevamente." << endl;
    }
}

// Función para que el usuario modifique una reserva
void modificarReserva(vector<Reserva>& reservas) {
    int numeroReserva;
    cout << "Ingrese el numero de reserva que desea modificar: ";
    cin >> numeroReserva;

    auto it = find_if(reservas.begin(), reservas.end(), [numeroReserva](const Reserva& r) {
        return r.numeroReserva == to_string(numeroReserva);
    });

    if (it != reservas.end()) {
        // Muestra los detalles actuales de la reserva
        cout << "Detalles actuales de la reserva:" << endl;
        cout << "Fecha: " << it->fecha << " -- Hora: " << it->hora << " -- Mesa: #" << it->mesaAsignada
             << " -- Personas: " << it->numPersonas << " -- Nombre: " << it->nombreCliente << " -- Correo: " << it->correoCliente << endl;

        // Pide al usuario los nuevos detalles
        string nuevaFecha, nuevaHora, nuevoNombre, nuevoCorreo;
        int nuevaNumPersonas;

        cin.ignore();  // Ignora el carácter de nueva línea después de leer numeroReserva

        cout << "Ingrese la nueva fecha (o enter para mantener la actual): ";
        getline(cin, nuevaFecha);
        if (nuevaFecha.empty()) {
            nuevaFecha = it->fecha;
        }

        cout << "Ingrese la nueva hora (o enter para mantener la actual): ";
        getline(cin, nuevaHora);
        if (nuevaHora.empty()) {
            nuevaHora = it->hora;
        }

        // Validación y entrada del nuevo número de personas
        do {
            cout << "Ingrese el nuevo numero de personas (de 1 a 8, 0 para mantener el actual): ";
            cin >> nuevaNumPersonas;
            if (nuevaNumPersonas < 0 || nuevaNumPersonas > 8) {
                cout << "Error: El numero de personas debe estar entre 1 y 8. Intenta nuevamente." << endl;
            }
        } while (nuevaNumPersonas < 0 || nuevaNumPersonas > 8);

        if (nuevaNumPersonas == 0) {
            nuevaNumPersonas = it->numPersonas;
        }

        cin.ignore();  // Limpiar el buffer después de leer el número de personas

        cout << "Ingrese el nuevo nombre (o enter para mantener el actual): ";
        getline(cin, nuevoNombre);
        if (nuevoNombre.empty()) {
            nuevoNombre = it->nombreCliente;
        }

        cout << "Ingrese el nuevo correo (o enter para mantener el actual): ";
        getline(cin, nuevoCorreo);
        if (nuevoCorreo.empty()) {
            nuevoCorreo = it->correoCliente;
        }

        // Actualiza la reserva con los nuevos detalles
        it->fecha = nuevaFecha;
        it->hora = nuevaHora;
        it->numPersonas = nuevaNumPersonas;
        it->nombreCliente = nuevoNombre;
        it->correoCliente = nuevoCorreo;

        cout << "Reserva modificada exitosamente." << endl;
    } else {
        cout << "Numero de reserva no encontrado. Verifique e intente nuevamente." << endl;
    }
}

//función para generar los archivos de reservas y los de reseñas
void generarArchivos(const vector<Reserva>& reservas) {
    ofstream archivo("reservas_y_comentarios.txt");

    if (archivo.is_open()) {
        for (const Reserva& reserva : reservas) {
            //escribe la información en el archivo
            archivo << "Fecha: " << reserva.fecha << " -- Hora: " << reserva.hora << " -- Mesa: #" << reserva.mesaAsignada
                    << " -- Personas: " << reserva.numPersonas << " -- Nombre: " << reserva.nombreCliente << " -- Correo: " << reserva.correoCliente << endl;
        }

        archivo.close();
        cout << "Archivo generado exitosamente: reservas.txt" << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

//Funcion para que el usuario deje un comentario
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
cout<<"Esta seguro de dejar este comentario? (1: SI, 0: NO)\n";
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

//Funcion para ver las reseñas
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

//funcion que nos permitira ver las calificaciones de estrellas de los usuarios 
void verCalificaciones() {
    ifstream archivo_calificaciones("registro_de_estrellas.txt");
    string linea;

    if (archivo_calificaciones.is_open()) {
        cout << "Calificaciones de estrellas recibidas:" << endl;
        while (getline(archivo_calificaciones, linea)) {
            cout << linea << endl;
        }
        archivo_calificaciones.close();
    } else {
        cout << "No se pudo abrir el archivo de calificaciones." << endl;
    }
}

//Funcion para escribir una reseña
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

// Función para recomendar un plato aleatorio
void recomendacionPlatos() {
    // Inicializar la semilla para la generación de números aleatorios
    srand(time(0));

    // Lista de platos
    string platos[] = {"Pasta", "Carne asada", "Hamburguesa doble carne", "Ensalada de pollo", "Sushi"};

    // Elegir aleatoriamente un plato
    int indiceAleatorio = rand() % 5; // 5 es el número de platos en la lista
    string platoRecomendado = platos[indiceAleatorio];

    int confirmacion;
    cout << "La recomendacion del dia es: " << platoRecomendado << endl;
    cout << "Esta seguro de elegir este plato? (1: SI, 0: NO)\n";
    cin >> confirmacion;

    if (confirmacion == 1) {
        cout << "Se ha confirmado su pedido." << endl;
    }
    
     else {
        cout << "Vuelva a elegir una opcion, por favor." << endl;
        system("cls"); 
    }
    
} 

// Función para realizar un log de acciones
void registrarAccion(const string& mensaje) {
    ofstream logFile("log.txt", ios::app); // Abre el archivo de log en modo de agregar

    if (logFile.is_open()) {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        char currentTime[20];
        strftime(currentTime, 20, "%Y-%m-%d %H:%M:%S", localTime);

        logFile << "[" << currentTime << "] " << mensaje << endl;

        logFile.close();
    } else {
        cout << "Error al abrir el archivo de log." << endl;
    }
}

int main() {
    vector<Mesa> mesas = { 
        {1, 4, false},
        {2, 6, false},
        {3, 2, false},
        {4, 4, false},
        {5, 8, false},
        {6, 4, false},
        {7, 6, false},
        {8, 2, false},
        {9, 4, false},
        {10, 8, false},
        {11, 4, false},
        {12, 6, false},
        {13, 2, false},
        {14, 4, false},
        {15, 8, false},
        {16, 4, false},
        {17, 6, false},
        {18, 2, false},
        {19, 4, false},
        {20, 8, false}
    };

    vector<Reserva> reservas; //inicializa el vector de reservas

    string empleadoPassword = "1234";  //contraseña de empleado que se pide al ingresar al menu de admin

    while (true) {
        int opcion;
        cout << "Bienvenido a Sabor Celestial!" << endl;
        cout << "Menu principal:" << endl;
        cout << "1. Menu de administrador" << endl;
        cout << "2. Hacer una reserva" << endl;
        cout << "3. Ver horarios de servicio" << endl;
        cout << "4. Dejar un comentario sobre nustros servicios \n";
        cout << "5. Calificar nuestros servicio \n";
        cout << "6. Recomendacion de platos \n";
        cout << "7. Cancelar una reserva" << endl;
        cout << "8. Modificar una reserva" << endl;
        cout << "9. Ver calificaciones de estrellas" << endl;
        cout << "10. Salir" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system ("cls");

        string inputPassword;

        switch (opcion) {
            case 1:
                cout << "Ingrese la contrasena de empleado: ";
                cin >> inputPassword;
                system("cls");

                if (inputPassword == empleadoPassword) {
                    int opcionAdmin;
                    do {
                        cout << "Menu de administrador:" << endl;
                        cout << "1. Ver reservas hechas" << endl;
                        cout << "2. Ver resenas hechas" << endl;
                        cout << "3. Ver mesas ocupadas" << endl;
                        cout << "4. Eliminar reservas" << endl;
                        cout << "5. Generar archivos con las reservas hechas" << endl;
                        cout << "6. Modificar reserva en caso que el usuario lo pida." << endl;
                        cout << "7. Regresar al menu principal" << endl;
                        cout << "Seleccione una opcion: ";
                        cin >> opcionAdmin;
                        system("cls");

                        switch (opcionAdmin) {
                            case 1: 
                                verReservas(reservas);
                                registrarAccion("El administrador ha visto las reservas hechas.");
                                break;
                            case 2:
                                verResenias();
                                registrarAccion("El administrador ha visto las reseñas hechas.");
                                break;
                            case 3:
                                mostrarMesasOcupadas(mesas);
                                registrarAccion("El administrador ha visto las mesas ocupadas.");
                                break;
                            case 4:
                                eliminarReservas(reservas);
                                registrarAccion("El administrador ha eliminado todas las reservas.");
                                break;
                            case 5:
                                generarArchivos(reservas);
                                registrarAccion("El administrador ha generado archivos con las reservas hechas.");
                                break;
                            case 6:
                                cout << "Modificacion de reserva por peticion del usuario" << endl;
                                modificarReserva(reservas);
                                registrarAccion("Se ha modificado una reserva.");
                                break; 

                            case 7:
                                cout << "Regresando al menu principal" << endl;
                                registrarAccion("El administrador ha regresado al menu principal.");
                                break;    
                            default:
                                cout << "Opcion no valida en el menu de administrador." << endl;
                                break;
                        }
                    } while (opcionAdmin != 6); 
                } else {
                    cout << "Contrasenia equivocada \n";
                }
                break;
            case 2: {
                hacerReserva(mesas, reservas);
                registrarAccion("Se ha realizado una reserva.");
                break;
            }
            case 3:
                cout << "Horarios de servicio: 08:00, 11:00, 13:00, 15:00, 17:00, 19:00" << endl;
                registrarAccion("Se ha consultado el horario de servicio.");
                break;
            case 4:
                cout<<"--------Esta en el apartado de comentarios--------\n";
                comentariosUsuario();
                registrarAccion("El cliente ha dejado un comentario sobre nuestros servicios.");
                break;
            case 5:
                cout<<"--------Calificar nuestros servicios--------\n";
                resenia();
                registrarAccion("El cliente ha calificado nuestros servicios.");
                break;
            case 6:
                cout<<"--------Recomendacion de platos--------\n";
                recomendacionPlatos();
                registrarAccion("Se ha consultado la recomendación de platos.");
                break;   
            case 7:
                cancelarReserva(reservas);
                registrarAccion("Se ha cancelado una reserva.");
                break;   
            case 8:
                modificarReserva(reservas);
                registrarAccion("Se ha modificado una reserva.");
                break;   
            case 9:
                verCalificaciones();
                registrarAccion("Se han consultado las calificaciones de estrellas.");
                break;
            case 10:
                cout << "Gracias por visitarnos. Hasta luego." << endl;
                registrarAccion("El usuario ha salido del programa.");
                return 0;
            default:
                cout << "Por favor, seleccione una opcion valida." << endl;
                break;
        }
    }

    return 0;
}
