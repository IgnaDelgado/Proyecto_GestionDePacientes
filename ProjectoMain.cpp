#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Definicion de la clase Pila utilizando templates para ser generica
template<typename T>
class Pila {
private:
    // Estructura interna Nodo para almacenar los elementos de la pila
    struct Nodo {
        T dato;         // El dato almacenado de tipo gen?rico T
        Nodo* siguiente; // Puntero al siguiente nodo en la pila

        // Constructor del Nodo
        Nodo(T dato, Nodo* siguiente = nullptr) : dato(dato), siguiente(siguiente) {}
    };

    Nodo* cima = nullptr; // Puntero al nodo en la cima de la pila, inicialmente nullptr

public:
    // Constructor por defecto
    Pila() : cima(nullptr) {}

    // M?todo para agregar un elemento a la pila
    void push(T dato) {
        Nodo* nuevoNodo = new Nodo(dato, cima); // Crea un nuevo nodo que apunta a la cima actual
        cima = nuevoNodo; // Actualiza la cima para que apunte al nuevo nodo
    }

    // M?todo para eliminar el elemento en la cima de la pila
    T pop() {
        if (estaVacia()) throw std::out_of_range("Pila vac?a.");
        Nodo* nodoEliminado = cima; // Guarda el nodo actual de la cima
        T dato = nodoEliminado->dato; // Extrae el dato del nodo
        cima = cima->siguiente; // Mueve la cima al siguiente nodo
        delete nodoEliminado; // Libera la memoria del nodo eliminado
        return dato; // Retorna el dato del nodo eliminado
    }

    // M?todo para verificar si la pila est? vac?a
    bool estaVacia() const {
        return cima == nullptr;
    }
};

// Definicion de la estructura Paciente
struct Paciente
{
    char nombre[50];
    char apellido[50];
    int DNI = 0;
    int edad = 0;
    int Genero = 0;
    Pila<int> Doctor;
    Pila<char> historial[30];
};

// Definicion de la clase Lista utilizando templates para ser generica
template<typename T>
class Lista {
private:
    // Definici?n interna de un nodo de la lista.
    struct Nodo {
        T dato;         // El dato almacenado en el nodo.
        Nodo* siguiente; // Puntero al siguiente nodo en la lista.

        // Constructor del nodo que inicializa el dato y el puntero siguiente.
        Nodo(T dato, Nodo* siguiente = nullptr) : dato(dato), siguiente(siguiente) {}
    };

    Nodo* cabeza = nullptr; // Puntero al primer nodo de la lista.

public:
    // Constructor por defecto
    Lista() : cabeza(nullptr) {}

    // Metodo para eliminar un paciente de la lista de verificacion
    void eliminarPaciente(int dniPaciente) {
        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        // Busca el nodo con el DNI dado
        while (actual != nullptr && actual->dato != dniPaciente) {
            anterior = actual;
            actual = actual->siguiente;
        }

        // Si se encuentra el nodo con el DNI dado, se elimina
        if (actual != nullptr) {
            if (actual == cabeza) {
                cabeza = cabeza->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
        }
    }

    // Metodo que devuelve el dato cabeza
    T datoCabeza() {
        return cabeza->dato;
    }

    // Metodo para agregar un elemento al inicio de la lista.
    void agregarAlInicio(T dato) {
        cabeza = new Nodo(dato, cabeza);
    }

    // Metodo para imprimir todos los elementos de la lista.
    void imprimir() const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        cout << "null" << std::endl;
    }

    // Metodo para verificar si un paciente se encuentra en espera
    bool verificarPaciente(int documento) {
        //Puntero a primer nodo de la lista
        Nodo* punteroVerif = cabeza;
        while (punteroVerif != nullptr) {
            //Recorre la lista verificando que documento no se encuentre en la lista
            if (punteroVerif->dato == documento)
            {
                return true;
            }
            punteroVerif = punteroVerif->siguiente;
        }
        return false;
    }

    // Metodo para buscar el indice de un paciente por su DNI
    bool buscarDNI(int dniPaciente) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            // Si encuentra el paciente con el DNI dado, devuelve su índice
            if (actual->dato.DNI == dniPaciente) {
                return true;
            }
            actual = actual->siguiente;
        }
        // Si no se encuentra el DNI en la lista, devuelve -1
        return false;
    }

    // Metodo para buscar los datos de un paciente
    Paciente& buscarPaciente(int dniPaciente) {
        //Puntero a primer nodo de la lista
        Nodo* punteroVerif = cabeza;
        while (punteroVerif != nullptr) {
            //Recorre la lista verificando que documento no se encuentre en la lista
            if (punteroVerif->dato.DNI == dniPaciente)
            {
                return punteroVerif->dato;
            }
            punteroVerif = punteroVerif->siguiente;
        }
        throw std::runtime_error("Paciente no encontrado"); // Lanza una excepción si el paciente no se encuentra
    }

};

// Definicion de la clase Cola utilizando templates para ser generica
template<typename T>
class Cola {
private:
    // Definicion del nodo interno de la cola
    struct Nodo {
        T dato;        // Dato almacenado en el nodo
        Nodo* siguiente; // Puntero al siguiente nodo en la cola

        // Constructor del Nodo
        Nodo(T dato, Nodo* sig = nullptr) : dato(dato), siguiente(sig) {}
    };

    Nodo* frente; // Puntero al primer nodo de la cola
    Nodo* final;  // Puntero al ?ltimo nodo de la cola

public:
    // Constructor de la cola
    Cola() : frente(nullptr), final(nullptr) {}

    // Metodo para agregar un elemento al final de la cola
    void enqueue(T dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (final == nullptr) {
            // Si la cola est? vac?a, frente y final apuntan al nuevo nodo
            frente = final = nuevoNodo;
        }
        else {
            // Si no est? vac?a, a?adir el nuevo nodo al final y actualizar el puntero final
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
    }

    // Metodo para eliminar el elemento al frente de la cola
    T dequeue() {
        if (frente == nullptr) {
            throw out_of_range("Intento de dequeue en cola vacia");
        }
        Nodo* temp = frente;
        T dato = frente->dato;
        frente = frente->siguiente;

        if (frente == nullptr) {
            final = nullptr; // Si la cola qued? vac?a, ajustar el puntero final
        }

        delete temp; // Liberar el nodo eliminado
        return dato; // Devolver el dato del nodo eliminado
    }

    // Metodo para comprobar si la cola est? vac?a
    bool estaVacia() const {
        return frente == nullptr;
    }

    // Metodo para obtener DNI del paciente del frente de la cola 
    int buscarDNI(int dniPaciente) {
        Nodo* actual = frente;
        int indice = 0;
        while (actual != nullptr) {
            // Si encuentra el paciente con el DNI dado, devuelve su índice
            if (actual->dato == dniPaciente) {
                return indice;
            }
            actual = actual->siguiente;
            indice++;
        }
        // Si no se encuentra el DNI en la lista, devuelve -1
        return -1;
    }


};

// Funcion para ingresar un paciente a la lista de espera
void ingresarPaciente(Lista<int>& listaVerificacion, Cola<int>& colaAtencion) {
    int dni = 0;

    cout << "Ingrese el dni del paciente" << endl;
    cin >> dni;

    if (listaVerificacion.verificarPaciente(dni) == true)
    {
        cout << "Usted ya tiene un turno asignado" << endl;
    }
    else
    {
        listaVerificacion.agregarAlInicio(dni);
        colaAtencion.enqueue(dni);
        cout << "Perfecto. Espera a ser llamado! " << endl;
    }
    return;
}

// Funcion para atender un paciente
void atenderPaciente(Lista<int>& listaVerificacion, Lista<Paciente>& listaPacientes, Cola<int>& colaPacientes, Cola<int>& colaPacientesUrgencias) {

    Paciente pacienteRegistrado;


    // Verificar si la cola de urgencias esta vacia
    if (!colaPacientesUrgencias.estaVacia())
    {
        int dni = colaPacientesUrgencias.dequeue(); // Obtener el DNI del paciente de la cola de urgencia y lo elimina

        bool indicePaciente = listaPacientes.buscarDNI(dni);

        if (indicePaciente)
        {
            pacienteRegistrado = listaPacientes.buscarPaciente(dni);
        }
        else
        {
            Paciente nuevoPaciente;
            nuevoPaciente.DNI = dni;
            cout << "Ingrese su nombre: ";
            cin >> nuevoPaciente.nombre;
            cout << "Ingrese su apellido: ";
            cin >> nuevoPaciente.apellido;
            cout << "Ingrese su edad: ";
            cin >> nuevoPaciente.edad;
            cout << "Ingrese 1 si su genero es Masculino y 2 si es Femenino: ";
            cin >> nuevoPaciente.Genero;
            // Agregar el nuevo paciente a la lista de pacientes
            listaPacientes.agregarAlInicio(nuevoPaciente);
            pacienteRegistrado = nuevoPaciente;

        }
        int num = 0;
        cout << "Ingrese a que doctor viene a visitar: " << endl;
        cout << "1. Dermatologo" << endl;
        cout << "2. Cardiologo" << endl;
        cout << "3. Oftalmologo" << endl;
        cin >> num;

        pacienteRegistrado.Doctor.push(num);

        char motivo[30] = "";
        cout << "Ingrese el motivo de la consulta" << endl;
        cin >> motivo;

        pacienteRegistrado.historial->push(*motivo);
        cout << endl;
        cout << "Se ha atendido al paciente de urgencia con dni " << dni << endl;

        // Eliminamos dni de la lista de verificacion
        listaVerificacion.eliminarPaciente(dni);
        return;

    }
    else if (!colaPacientes.estaVacia())
    {
		int dni = colaPacientes.dequeue(); // Obtener el DNI del paciente de la cola y lo elimina

        bool indicePaciente = listaPacientes.buscarDNI(dni);
        if (indicePaciente)
        {
            pacienteRegistrado = listaPacientes.buscarPaciente(dni);
        }
        else
        {
            Paciente nuevoPaciente;
            nuevoPaciente.DNI = dni;
            cout << "Ingrese su nombre: ";
            cin >> nuevoPaciente.nombre;
            cout << "Ingrese su apellido: ";
            cin >> nuevoPaciente.apellido;
            cout << "Ingrese su edad: ";
            cin >> nuevoPaciente.edad;
            cout << "Ingrese 1 si su genero es Masculino y 2 si es Femenino: ";
            cin >> nuevoPaciente.Genero;
            // Agregar el nuevo paciente a la lista de pacientes
            listaPacientes.agregarAlInicio(nuevoPaciente);
            pacienteRegistrado = nuevoPaciente;

        }
        int num = 0;
        cout << "Ingrese a que doctor viene a visitar: " << endl;
        cout << "1. Dermatologo" << endl;
        cout << "2. Cardiologo" << endl;
        cout << "3. Oftalmologo" << endl;
        cin >> num;

        pacienteRegistrado.Doctor.push(num);

        char motivo[30] = "";
        cout << "Ingrese el motivo de la consulta" << endl;
        cin >> motivo;

        pacienteRegistrado.historial->push(*motivo);
        cout << endl;
        cout << "Se ha atendido al paciente con dni " << dni << endl;

        // Eliminamos dni de la lista de verificacion
        listaVerificacion.eliminarPaciente(dni);
        return;
    }
    else
    {
        cout << "No hay pacientes en la fila." << endl;
    }
    return;
}

// Funcion para agregar un paciente de urgencia  
void agregarPacienteDeUrgencia(Lista<int>& listaVerificacion, Cola<int>& colaPacientesUrgencias) {
    int dni = 0;

    cout << "Ingrese el dni del paciente" << endl;
    cin >> dni;

    if (listaVerificacion.verificarPaciente(dni) == true) {
        cout << "Usted ya tiene un turno asignado" << endl;
    }
    else {
        listaVerificacion.agregarAlInicio(dni);
        colaPacientesUrgencias.enqueue(dni);
        cout << "Perfecto. Espera a ser llamado! " << endl;
    }
    return;
}

// Funcion prinpipal
int main() {

    Lista<Paciente> listaPacientes;
    Lista<int> listaVerificacion;

    Cola<int> colaPacientes;
    Cola<int> colaPacientesUrgencias;

    //Menu de opciones 
    int select = 0;
    while (select != 6) {
        cout << "Ingrese: " << endl;
        cout << "1. Para ingresar paciente a lista de espera" << endl;
        cout << "2. Para atender paciente" << endl;
        cout << "3. Para ingresar un paciente a la cola de urgencias" << endl;
        cout << "4. " << endl;
        cout << "5. " << endl;
        cout << "6. Salir " << endl;
        cin >> select;

        switch (select) {
        case 1:
            ingresarPaciente(listaVerificacion, colaPacientes);
            break;
        case 2:
            atenderPaciente(listaVerificacion, listaPacientes, colaPacientes, colaPacientesUrgencias);
            break;
        case 3:
            agregarPacienteDeUrgencia(listaVerificacion, colaPacientesUrgencias);
            break;
        case 4:

            break;
        case 5:

            break;
            //default del menu principal
        case 6:
            return 0;
            break;
        default:
            cout << "Opcion incorrecta" << endl;
            break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}
