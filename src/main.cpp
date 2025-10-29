#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstdlib> 
#include <cmath>
#include "math_utils.hpp"
#ifdef _WIN32
#  define CLEAR_CMD "cls"
#else
#  define CLEAR_CMD "clear"
#endif

void mostrarAyuda() {
    std::cout << "\nComandos disponibles:\n";
    std::cout << "  s, sumar          → suma dos números\n";
    std::cout << "  r, restar         → resta dos números\n";
    std::cout << "  m, multiplicar    → multiplica dos números\n";
    std::cout << "  d, dividir        → divide dos números\n";
    std::cout << "  e, exponencial    → eleva el primer numero con el segundo\n";
    std::cout << "  h o historial     → muestra el historial de operaciones\n\n";
    std::cout << "  salir             → termina el programa\n";
    std::cout << "  help o ?          → muestra esta ayuda\n\n";
}

void agregarAlHistorial(std::vector<std::string>& history, std::ostringstream& oss) {
    history.push_back(oss.str()); // sumo la operacion acual al history, transformando el oss en string
    oss.str(""); // borro el contenido de oss "buffer"   
    oss.clear(); // limpio flags (errores o fails) que se podria haber acumulado
}

void verHistorial(std::vector<std::string>& history, int n){

    if(history.empty()){
        std::cout << "No hay operaciones realizadas" << std::endl;
    } 
    
    if (n <= 0){
        for (const auto& line : history){
            std::cout << line << "\n";
        }
        return;
    }

    int total = static_cast<int>(history.size());
    if (n >= total) {
        for (const auto& line : history) std::cout << line << '\n';
        std::cout << "Superaste " << total << " no hay mas operaciones guardadas" << '\n';
        return;
    }

    int start = total - n;
    for (int i = start; i < total; ++i)
        std::cout << history[i] << '\n';
    return;
}

void menuInicio(){
    std::string nombre;
    std::cout << "Ingresá tu nombre completo: ";
    std::getline(std::cin, nombre);
    if(!nombre.empty()){
        std::transform(nombre.begin(), nombre.end(), nombre.begin(), [](unsigned char n){return std::tolower(n);});
        bool nuevaPalabra = true;
        for (char& c : nombre){
            if(std::isspace(static_cast<unsigned char>(c))){
                nuevaPalabra = true;
            }else {
                nuevaPalabra = false;
            }
            if(nuevaPalabra){
                c = std::toupper(static_cast<unsigned char>(c));
                nuevaPalabra = false;
            }
        }
        nombre[0] = std::toupper(static_cast<unsigned char>(nombre[0]));
        std::cout << "Hola, " << nombre << "! Bienvenido" << std::endl;
    }
    std::cout << "Esta es una calculadora basica, su fin es aprender a usar c++.\n";
    std::cout << "Las operaciones disponibles son (s (suma), m (multiplicacion), d (dividir), e (exponencial) y r (restar))\n";
    std::cout << "Escribí: <operacion> <a> <b>\n";
    std::cout << "Ejemplo: s 4 5\n";
    std::cout << "Escribí 'help' o '?' para ver comandos.\n";
    std::cout << "Escribí 'salir' para terminar.\n\n";
}

inline void clear_screen() {
  std::system(CLEAR_CMD);
}

int main() {

    menuInicio();

    std::cout << std::fixed << std::setprecision(2); // seteo el formato global, el mismo mostrara un maximo de 2 decimales y tendra formato fixed para evitar exponenciales
    std::vector <std::string> history;
    std::ostringstream oss;
    

    while (true){
        std::cout << "> ";

        std::string line;
        // miramos si la terminal esta ritando un error o si el usuario al finalizo, luego cargamos hacemos el cin para cargar line con get line guarda solo el 
        // texto, sin /n
        if (!std::getline(std::cin, line)) break; 
        //mira si se cargo algo en line, si esta vacio se reinicia el while
        if (line.empty()) continue;

        // se crea un stream de la lectura desde line, con el fin de poder hacer un parser luego y leer los datos separados
        // de esta manera nos aseguramos que no quede basura en la linea, dado que todo lo que se pase del rago de variables buscadas de deseche
        // ej si el usuario ingresa s 3 4 5 6, todo lo que venga despues del 4 se desecha y no interfiere en operaciones futuras.
        std::istringstream iss(line);

        std::string op;
        double a, b;

        //cuando se hace el iss >> variable, ya se esta parseando la infromacion de line, por mas que sea en una validacion
        // en este caso a demas de paresar estamos mirando si existe op
        if (!(iss >> op)) { 
            std::cout << "Falta la operación\n"; 
            continue; 
        }

        std::transform(op.begin(), op.end(), op.begin(), [](unsigned char c){ return std::tolower(c); });// transformo a minuscula el op

        if (op == "salir"){
            std::cout << "Adios" << std::endl;
            break;
        }

        if (op == "help" || op == "?"){
            mostrarAyuda();
            continue;
        }

        if (op == "c" || op == "clear"){
            clear_screen();
            continue;
        }

        if (op == "historial" || op == "h") {
            int n = -1;                 // -1 => mostrar todo
            if (iss >> n) { /* ok, n viene del input */ }
            verHistorial(history, n);   // ver abajo: verHistorial con int
            continue;
        }

        if (!(iss >> a)) { 
            std::cout << "Falta el primer número (a)\n"; 
            continue; 
        }

        if (!(iss >> b) && op != "raiz" && op != "ra") { 
            std::cout << "Falta el segundo número (b)\n"; 
            continue; 
        }

        try{
            double resultado = 0.0;
            
            if (op == "s" || op == "sumar"){
                resultado = math::sumar(a, b);
                oss << a << " + " << b << " = " << (a + b);
                agregarAlHistorial(history, oss);
            }
            else if (op == "m" || op == "multiplicar")  {
                resultado = math::multiplicar(a, b);
                oss << a << " * " << b << " = " << (a * b);
                agregarAlHistorial(history, oss);
            }
            else if (op == "r" || op == "restar")  {
                resultado = math::restar(a, b);
                oss << a << " - " << b << " = " << (a - b);
                agregarAlHistorial(history, oss);
            }
            else if (op == "d" || op == "dividir")   {
                resultado = math::dividir(a, b);
                oss << a << " / " << b << " = " << (a / b);
                agregarAlHistorial(history, oss);
            }
            else if (op == "e" || op == "exponencial")  {
                resultado = math::exponencial(a, b);
                oss << a << " ^ " << b << " = " << std::pow(a, b);
                agregarAlHistorial(history, oss);
            }
            else if (op == "ra" || op == "raiz")  {
                resultado = math::raiz(a);
                oss << "√(" << a << ") = " << std::sqrt(a);
                agregarAlHistorial(history, oss);
            }
            else {
                std::cout << "Operación desconocida: " << op << "\n";
                continue;
            }
            std::cout << "Resultado: " << resultado << "\n";
        }
        catch(const std::runtime_error& e){
            std::cout << "Error:" << e.what() << std::endl;
        }
        /*std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); saco los .ignore, porque con getline 
        consumo toda la linea, por lo que ya no me queda  "basura" */
    }
    
    return 0;
}