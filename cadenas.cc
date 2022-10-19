// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  cadenas.cc
//    Contiene las funciones implementadas para la clase Cadena.

#include "cadenas.h"

// Cosntructor por defecto
Cadena::Cadena() {
  cadena_.clear();
}

// Constructor
Cadena::Cadena(Alfabeto& alfabeto_entrada, std::vector<Simbolo>& cadena) {
  alfabeto_ = alfabeto_entrada;
  cadena_ = cadena;
}

Cadena::Cadena(Alfabeto& alfabeto_entrada, Simbolo& simbolo) {
  alfabeto_ = alfabeto_entrada;
  cadena_.push_back(simbolo);
}

// Establece el alfabeto de la cadena
void Cadena::SetAlfabeto(Alfabeto& alfabeto_entrada) {
  alfabeto_ = alfabeto_entrada;
}

// Inserta un simbolo en la cadena
void Cadena::InsertarSimbolo(Simbolo& simbolo_entrada) {
  cadena_.push_back(simbolo_entrada);
}

// Devuelve la longitud de la cadena
int Cadena::Longitud() {
  return cadena_.size();
}

// Calcula la inversa de la cadena
Cadena Cadena::Inversa() {
  Cadena cadena_inversa;
  for (unsigned int index = cadena_.size(); index > 0; index--) {
    cadena_inversa.InsertarSimbolo(cadena_[index - 1]);
  }
  cadena_inversa.SetAlfabeto(alfabeto_);
  return cadena_inversa;
}

// Calcula los prefijos de la cadena
std::vector<Cadena> Cadena::Prefijos() {
  std::vector<Cadena> prefijos;
  InsartarCadenaVacia(prefijos);
  for (unsigned int index = 0; index < cadena_.size(); index++) {
    std::vector<Simbolo> prefijo;
    for (unsigned int index2 = 0; index2 <= index; index2++) {
      prefijo.push_back(cadena_[index2]);
    }
    Cadena Cadena(alfabeto_, prefijo);
    prefijos.push_back(Cadena);
  }
  return prefijos;
}

// Calcula los sufijos de la cadena
std::vector<Cadena> Cadena::Sufijos() {
  std::vector<Cadena> sufijos;
  InsartarCadenaVacia(sufijos);
  for (unsigned int index = cadena_.size(); index > 0; index--) {
    std::vector<Simbolo> sufijo;
    for (unsigned int index2 = index - 1; index2 < cadena_.size(); index2++) {
      sufijo.push_back(cadena_[index2]);
    }
    Cadena cadena(alfabeto_, sufijo);
    sufijos.push_back(cadena);
  }
  return sufijos;
}

// Calcula las subcadenas de la cadena
std::vector<Cadena> Cadena::Subcadenas() {
  std::vector<Cadena> subcadenas;
  InsartarCadenaVacia(subcadenas);
  for (unsigned int index = 0; index < cadena_.size(); index++) {
    for (unsigned int index2 = index; index2 < cadena_.size(); index2++) {
      std::vector<Simbolo> subcadena;
      for (unsigned int index3 = index; index3 <= index2; index3++) {       
        subcadena.push_back(cadena_[index3]);
        if (!CompruebaRepetidos(subcadena, subcadenas)) {
          Cadena Subcadena(alfabeto_, subcadena);
          subcadenas.push_back(Subcadena);
        }
      }
    }
  }

  return subcadenas;
}

// Inserta una cadena vacia en el vector de cadenas de las operaciones
void Cadena::InsartarCadenaVacia(std::vector<Cadena>& cadenas) {
  Simbolo simbolo_vacio(VACIA);
  Cadena Cadena_vacia;
  Cadena_vacia.InsertarSimbolo(simbolo_vacio);
  cadenas.push_back(Cadena_vacia);
}

// Devuelve la cadena
std::vector<Simbolo> Cadena::GetCadena() {
  return cadena_;
}

// Sobrecarga del operador == para comparar cadenas
bool Cadena::operator==(Cadena& cadena) {
  if (cadena_.size() != cadena.cadena_.size()) {
    return false;
  }
  for (unsigned int index = 0; index < cadena_.size(); index++) {
    if (cadena_[index] != cadena.cadena_[index]) {
      return false;
    }
  }
  return true;
}

// Metodo que comprueba si una subcadena esta repetida en el vector de subcadenas
bool Cadena::CompruebaRepetidos(std::vector<Simbolo>& subcadena, std::vector<Cadena>& subcadenas) {
  for (unsigned int index = 0; index < subcadenas.size(); index++) {
    if (subcadena == subcadenas[index].GetCadena()) {
      return true;
    }
  }
  return false;
}

// Sobrecarga del operador << para imprimir cadenas
std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  for (unsigned int index = 0; index < cadena.cadena_.size(); index++) {
    os << cadena.cadena_[index];
  }
  return os;
}

bool Cadena::operator<(const Cadena& cadena) const {
  if (cadena_.size() < cadena.cadena_.size()) {
    return true;
  } else if (cadena_.size() > cadena.cadena_.size()) {
    return false;
  } else {
    for (unsigned int index = 0; index < cadena_.size(); index++) {
      if (cadena_[index] < cadena.cadena_[index]) {
        return true;
      } else if (cadena_[index] > cadena.cadena_[index]) {
        return false;
      }
    }
  }
  return false;
}