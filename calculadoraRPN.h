#include <iostream>
#include <stack>

#include "lenguajes.h"

const char SPACE = ' ';

const std::string CONCATENACION = "+";
const std::string UNION = "|";
const std::string POTENCIA = "*";
const std::string INTERSECCION = "^";
const std::string DIFERENCIA = "-";
const std::string INVERSA = "!";

const std::string OPERADORES_2_OP = "+|^-";
const std::string OPERADORES_1_OP = "*!";

class CalculadoraRPN {
  public:
    CalculadoraRPN();
    CalculadoraRPN(std::vector<Lenguaje>& lenguajes_entrada, std::string& elementos_entrada);

    std::string BuscarElemento(std::string& linea_operacion);
    bool IsOperando(std::string& operacion);
    Lenguaje BuscarIdentificador(std::string& identificador);
    bool Is2Operadores(std::string& operacion);
    void Ejectuar2OP(std::string& elemento);
    void Ejectuar1OP(std::string& elemento);
    void Resolver();

  private:
    std::stack<Lenguaje> pila_;
    std::vector<Lenguaje> lenguajes_;
    std::string linea_operacion_;

    Lenguaje resultado_;
};