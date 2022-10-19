// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  calculator.cc
//    Programa principal de la calculadora de lenguajes formales.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>

#include "simbolos.h"
#include "alfabetos.h"
#include "cadenas.h"
#include "lenguajes.h"
#include "calculadoraRPN.h"

const char LLAVE_IZQ = '{';
const char LLAVE_DER = '}';

// Metodo que comprueba que los argumentos introducidos son correctos, además de
// que el fichero de entrada existe. Muestra también información sobre el uso
// del programa.
bool ComprobacionEntrada(int& argc, char* argv[]) {
  std::string help = "-h";
  std::string help_ = "--help";
  if (argc == 2) { 
    std::string fichero_entrada1 = argv[1];
    std::ifstream archivo_entrada1(fichero_entrada1);

    if (archivo_entrada1.is_open()) {
      return true;
    } else {
      std::cout << "No es posible abrir los ficheros o el opcode no es correcto." << std::endl;
      std::cout << "Ejecute para más información: ./p01_strings --help || ./p01_strings -h" << std::endl;
    return false;
    }
   } else if(argc == 2 && (argv[1] == help || argv[1] == help_)) {
      std::cout << "Modo de ejecución: ./p01_strings filein1.txt filein2.txt fileout.txt opcode" << std::endl;
  } else {
    std::cout << "El número o los parámetros de entrada no son correctos." << std::endl;
    return false;
  }
  return false;
}

// Métoodo que dada una linea que contiene un lenguaje, reconoce si este es
// vacío o no.
bool CompruebaVacio(std::string& linea) {
  std::size_t posicion_llave_izq = linea.find(LLAVE_IZQ);
  std::size_t posicion_llave_der = linea.find(LLAVE_DER);
  if (posicion_llave_der - posicion_llave_izq == 1) {
    return true;
  }
  return false;
}

// Método que dada una linea que contiene un lenguaje, extrae el alfabeto.
void ExtraerAlfabeto(std::string linea, Alfabeto& Alfabeto) {
  for (unsigned index = 0; index < linea.size() - 1; index++) {
    std::string simbolo_entrada = linea.substr(index, 1);
    if (simbolo_entrada != " " && simbolo_entrada != "{" && simbolo_entrada != "}" && simbolo_entrada != ",") {
      Simbolo simbolo(simbolo_entrada);
      Alfabeto.InsertarSimbolo(simbolo);
    }
  }
}

// Método que dada una cadena como string, la convierte en un objeto de la clase
// Cadena y la insera al lenguaje.
void CrearCadena(std::string linea, Alfabeto& Alfabeto, Lenguaje& Lenguaje) {
  Cadena Cadena;
  int iterador = 1;
  while(linea != "") {
    std::string simbolo_entrada = linea.substr(0, iterador);
    Simbolo Simbolo(simbolo_entrada);
    if (Simbolo == VACIA) {
      Cadena.InsertarSimbolo(Simbolo);
      linea.erase(0, iterador);
    } else if (Alfabeto.BuscarSimbolo(Simbolo)) {
      Cadena.InsertarSimbolo(Simbolo);
      linea.erase(0, iterador);
      iterador = 1;
    } else {
      iterador++;
    }
  }
  Cadena.SetAlfabeto(Alfabeto);
  Lenguaje.InsertarCadena(Cadena);
}

// Método que dado un lenguaje que contien varias cadenas, las extrae y las
// convierte en objetos de la clase Cadena para insertarlas en el lenguaje.
void VariasCadenas(std::string& linea, Alfabeto& Alfabeto, Lenguaje& Lenguaje) {
  std::size_t posicion_espacio = linea.find(SPACE);
  std::string cadena = linea.substr(0, posicion_espacio - 1);

  CrearCadena(cadena, Alfabeto, Lenguaje);
  linea.erase(0, posicion_espacio + 1);
  while(linea != "") {
    std::size_t posicion_espacio = linea.find(SPACE);
    if (posicion_espacio == std::string::npos) {
      std::size_t posicion_llave_der = linea.find(LLAVE_DER);
      std::string cadena = linea.substr(0, posicion_llave_der);
      CrearCadena(cadena, Alfabeto, Lenguaje);
      linea.erase(0, posicion_llave_der + 1);
    } else {
      std::string cadena = linea.substr(0, posicion_espacio - 1);
      CrearCadena(cadena, Alfabeto, Lenguaje);
      linea.erase(0, posicion_espacio + 1);
    }    
  }
}

// Método que dada una linea que contiene un lenguaje, comprueba el tamaño de
// este y extrae el alfabeto y las cadenas. Devuelve un objeto de la clase
// Lenguaje.
Lenguaje CrearLenguaje(std::string& linea) {
  Lenguaje Lenguaje;
  Alfabeto Alfabeto;
  
  std::size_t posicion_espacio_identificador = linea.find(SPACE);
  std::string indetificador_lenguaje = linea.substr(0, posicion_espacio_identificador);
  Lenguaje.InsertarIdentificador(indetificador_lenguaje);

  std::size_t posicion_llave1 = linea.find(LLAVE_IZQ);
  linea.erase(0, posicion_llave1 + 1);
  ExtraerAlfabeto(linea, Alfabeto);

  std::size_t posicion_espacio = linea.find(SPACE);
  if (posicion_espacio == std::string::npos) { // Hay una sola cadena
    if (!CompruebaVacio(linea)) { // Es un lenguaje no vacío
      std::size_t posicion_llave1 = linea.find(LLAVE_IZQ);
      std::size_t posicion_llave2 = linea.find(LLAVE_DER);
      Cadena Cadena;
      for (unsigned index = posicion_llave1 + 1; index < posicion_llave2; index++) {
        std::string simbolo_entrada = linea.substr(index, 1);
        Simbolo Simbolo(simbolo_entrada);
        Cadena.InsertarSimbolo(Simbolo);
      }
      Lenguaje.InsertarCadena(Cadena);
    } // else es vacio
  } else { // Hay varias cadenas
    VariasCadenas(linea, Alfabeto, Lenguaje);
  }
  std::cout << "Lenguaje: " << Lenguaje << std::endl;
  std::cout << "Alfabeto: " << Alfabeto << std::endl << std::endl;
  return Lenguaje;
}

// Metodo que dado un conjunto de entradas, recononce las lineas que contienen lenguajes y las que tienen operaciones en nota polaca inversa. Las lineas que tienen lenguajes son procesadas en otras funciones.
std::pair<std::vector<Lenguaje>, std::vector<std::string>> ProcesarEntradas(std::vector<std::string>& entradas) {
  std::vector<Lenguaje> lenguajes;
  std::vector<std::string> operaciones;
  for (unsigned int index = 0; index < entradas.size(); index++) {
    std::string linea = entradas[index];
    std::size_t buscar_igual = linea.find("=");
    if (buscar_igual != std::string::npos) {
      lenguajes.push_back(CrearLenguaje(linea));
    } else {
      operaciones.push_back(linea);
    }
  } 
  return std::make_pair(lenguajes, operaciones);
}

// Metodo que extrae y retorna las lineas de entrada del fichero de entrada.
std::vector<std::string> LeerFichero(std::string fichero_entrada) {
  std::ifstream archivo_entrada(fichero_entrada);
  std::vector<std::string> lineas;
  std::string linea;
  while (std::getline(archivo_entrada, linea)) {
    lineas.push_back(linea);
  }
  return lineas;
}

// Metodo principal que controla la ejecución del programa
int main(int argc, char* argv[]) {
  if (ComprobacionEntrada(argc, argv)) {
    std::vector<std::string> entradas_fichero1 = LeerFichero(argv[1]);
    std::pair<std::vector<Lenguaje>, std::vector<std::string>> entradas = ProcesarEntradas(entradas_fichero1);
    std::cout << "----------------------------------------" << std::endl;
    for (unsigned int index = 0; index < entradas.second.size(); index++) {
      std::cout << "Operacion: " << entradas.second[index] << std::endl;
      CalculadoraRPN CalculadoraRPN(entradas.first, entradas.second[index]);
      CalculadoraRPN.Resolver();
      std::cout << std::endl;
    }
  }
  return 0;
}