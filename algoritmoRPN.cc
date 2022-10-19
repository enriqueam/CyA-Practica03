#include "algoritmoRPN.h"

AlgoritmoRPN::AlgoritmoRPN() {}

AlgoritmoRPN::AlgoritmoRPN(std::vector<Lenguaje>& lenguajes_entrada, std::string& elementos_entrada) {
  lenguajes_ = lenguajes_entrada;
  linea_operacion_ = elementos_entrada;
}


std::string AlgoritmoRPN::BuscarElemento(std::string& linea_operacion) {
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

bool AlgoritmoRPN::IsOperando(std::string& operacion) {
  std::size_t buscar_operador_2 = OPERADORES_2_OP.find(operacion);
  std::size_t buscar_operador_1 = OPERADORES_1_OP.find(operacion);

  if (buscar_operador_2 != std::string::npos || buscar_operador_1 != std::string::npos) {
    return false;
  } 
  return true;
}

Lenguaje AlgoritmoRPN::BuscarIdentificador(std::string& identificador) {
  for (unsigned int index = 0; index < lenguajes_.size(); index++) {
    if (lenguajes_[index].GetIdentificador() == identificador) {
      return lenguajes_[index];
    }
  }
  std::cout << "No se ha encontrado el identificador: " << identificador << std::endl;
  exit(1);
}

bool AlgoritmoRPN::Is2Operadores(std::string& operacion) {
  std::size_t buscar_operador_2 = OPERADORES_2_OP.find(operacion);
  if (buscar_operador_2 != std::string::npos) {
    return true;
  } 
  return false;
}
  
void AlgoritmoRPN::Ejectuar2OP(std::string& elemento) {
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

void AlgoritmoRPN::Ejectuar1OP(std::string& elemento) {
  Lenguaje lenguaje_1 = pila_.top();
  pila_.pop();
  switch (elemento[0]) {
    case '*':
      pila_.push(lenguaje_1.Potencia());
      break;
    case '!':
      pila_.push(lenguaje_1.Inversa());
      break;
    default:
      std::cout << "Operador no valido" << std::endl;
      exit(1);
  }
} 

void AlgoritmoRPN::Resolver() {
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