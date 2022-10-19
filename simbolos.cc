// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  simbolos.cc
//    Contiene las funciones implementadas para la clase Simbolo.

#include "simbolos.h"

// Constructor
Simbolo::Simbolo(std::string& simbolo_entrada) {
  simbolo_ = simbolo_entrada;
}

// Constructor
Simbolo::Simbolo(const std::string& simbolo_entrada) {
  simbolo_ = simbolo_entrada;
}

// Sobre carga del operador ==
bool Simbolo::operator==(const Simbolo& simbolo_entrada) const {
  return simbolo_ == simbolo_entrada.simbolo_;
}

// Sobrecarga del operador !=
bool Simbolo::operator!=(const Simbolo& simbolo_entrada) const {
  return simbolo_ != simbolo_entrada.simbolo_;
}

// Sobre carga operador de salida para imprimir el simbolo
std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo_entrada) {
  os << simbolo_entrada.simbolo_;
  return os;
}

bool Simbolo::operator<(const Simbolo& simbolo_entrada) const {
  return simbolo_ < simbolo_entrada.simbolo_;
}

bool Simbolo::operator>(const Simbolo& simbolo_entrada) const {
  return simbolo_ > simbolo_entrada.simbolo_;
}

std::string Simbolo::GetSimbolo() {
  return simbolo_;
}