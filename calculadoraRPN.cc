// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  calculadoraRPN.cc
//    Contiene los métodos implementados para la clase CalculadoraRPN.	

#include "calculadoraRPN.h"

// Constructor
CalculadoraRPN::CalculadoraRPN() {
  potencia_ = 0;
}

// Constructor
CalculadoraRPN::CalculadoraRPN(std::vector<Lenguaje>& lenguajes_entrada, std::string& elementos_entrada) {
  lenguajes_ = lenguajes_entrada;
  linea_operacion_ = elementos_entrada;
  potencia_ = 0;
}

// 
std::string CalculadoraRPN::BuscarElemento(std::string& linea_operacion) {
  std::size_t posicion_espacio = linea_operacion.find(SPACE);
  if (posicion_espacio == std::string::npos) {
    std::string elemento = linea_operacion;
    linea_operacion = "";
    return elemento;
  } else {
    std::string elemento = linea_operacion.substr(0, posicion_espacio);
    linea_operacion.erase(0, posicion_espacio + 1);
    return elemento;
  }
}

// Retorna true si el elemento es un operando.
bool CalculadoraRPN::IsOperando(std::string& operacion) {
  if (isdigit(operacion[0])) {
    return false;
  }
  std::size_t buscar_operador_2 = OPERADORES_2_OP.find(operacion);
  std::size_t buscar_operador_1 = OPERADORES_1_OP.find(operacion);
  if (buscar_operador_2 != std::string::npos || buscar_operador_1 != std::string::npos) {
    return false;
  } 
  return true;
}

// Comprueba si existe el identificador en el vector de lenguajes.
Lenguaje CalculadoraRPN::BuscarIdentificador(std::string& identificador) {
  for (unsigned int index = 0; index < lenguajes_.size(); index++) {
    if (lenguajes_[index].GetIdentificador() == identificador) {
      return lenguajes_[index];
    }
  }
  std::cout << "No se ha encontrado el identificador: " << identificador << std::endl;
  exit(1);
}

// Retorna true si el elemento es un operador de 2 operandos.
bool CalculadoraRPN::Is2Operadores(std::string& operacion) {
  std::size_t buscar_operador_2 = OPERADORES_2_OP.find(operacion);
  if (buscar_operador_2 != std::string::npos) {
    return true;
  } 
  return false;
}

// Ejecuta la operacion de 2 operandos.  
void CalculadoraRPN::Ejectuar2OP(std::string& elemento) {
  Lenguaje lenguaje_1 = pila_.top();
  pila_.pop();
  Lenguaje lenguaje_2 = pila_.top();
  pila_.pop();
  switch (elemento[0]) {
    case '+':
      pila_.push(lenguaje_2.Concatenacion(lenguaje_1));
      break;
    case '|':
      pila_.push(lenguaje_2.Union(lenguaje_1));
      break;
    case '^':
      pila_.push(lenguaje_2.Interseccion(lenguaje_1));
      break;
    case '-':
      pila_.push(lenguaje_2.Diferencia(lenguaje_1));
      break;
    default:
      std::cout << "Operador no valido" << std::endl;
      exit(1);
  }
}

// Ejecuta la operacion de 1 operando.
void CalculadoraRPN::Ejectuar1OP(std::string& elemento) {
  Lenguaje lenguaje_1 = pila_.top();
  pila_.pop();
  switch (elemento[0]) {
    case '*':
      pila_.push(lenguaje_1.Potencia(potencia_));
      break;
    case '!':
      pila_.push(lenguaje_1.Inversa());
      break;
    default:
      std::cout << "Operador no valido" << std::endl;
      exit(1);
  }
} 

// Algoritmo de la calculadora RPN.
void CalculadoraRPN::Resolver() {
  while (linea_operacion_ != "") {
    std::string elemento = BuscarElemento(linea_operacion_);
    if (IsOperando(elemento)) {
      pila_.push(BuscarIdentificador(elemento));
    } else {
      if (Is2Operadores(elemento)) {
        if (pila_.size() < 2) {
          std::cout << "No hay suficientes operandos para realizar la operacion" << std::endl;
          return;
        } else {
          Ejectuar2OP(elemento);
        }
      } 
       // Si el elemento es un numero entero, leer un elemento mas y hacer la potencia
      else if (isdigit(elemento[0])) {
        potencia_ = std::stoi(elemento);
      } else {
        if (pila_.size() < 1) {
          std::cout << "No hay suficientes operandos para realizar la operacion" << std::endl;
          return;
        } else {
          Ejectuar1OP(elemento);
        }
      }
    }
  }
  if (pila_.size() == 1) {
    resultado_ = pila_.top();
    std::cout << "Resultado: " << resultado_ << std::endl;
  } else {
    std::cout << "No se ha podido resolver la operacion" << std::endl;
  }
}