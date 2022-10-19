// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  cadenas.h.
//    Contiene la declaración de la clase Cadena.

#include <iostream>
#include <vector>

#include "simbolos.h"
#include "alfabetos.h"

#pragma once

const std::string VACIA = "&";

class Cadena {
  public:
    Cadena();
    Cadena(Alfabeto& Alfabeto, std::vector<Simbolo>& cadena);
    Cadena(Alfabeto& Alfabeto, Simbolo& simbolo);

    void SetAlfabeto(Alfabeto& alfabeto_entrada);
    void InsertarSimbolo(Simbolo& simbolo_entrada);

    int Longitud();
    Cadena Inversa();
    std::vector<Cadena> Prefijos();
    std::vector<Cadena> Sufijos();
    std::vector<Cadena> Subcadenas();

    void InsartarCadenaVacia(std::vector<Cadena>& cadenas);
    std::vector<Simbolo> GetCadena();
    bool CompruebaRepetidos(std::vector<Simbolo>& subcadena, std::vector<Cadena>& subcadenas);

    friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);
    bool operator==(Cadena& cadena);
    bool operator<(const Cadena& cadena) const;
  private:
    std::vector<Simbolo> cadena_;
    Alfabeto alfabeto_;
};
