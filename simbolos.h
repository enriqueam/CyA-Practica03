// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  simbolos.h
//    Contiene la declaración de la clase Simbolo.

#include <iostream>

#pragma once

class Simbolo {
  public:
    Simbolo(std::string& simbolo_entrada);
    Simbolo(const std::string& simbolo_entrada);
    
    bool operator==(const Simbolo& simbolo_entrada) const;
    bool operator!=(const Simbolo& simbolo_entrada) const;
    friend std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo_entrada);
    bool operator<(const Simbolo& simbolo_entrada) const;
    bool operator>(const Simbolo& simbolo_entrada) const;

    std::string GetSimbolo();
  private:
    std::string simbolo_;
};