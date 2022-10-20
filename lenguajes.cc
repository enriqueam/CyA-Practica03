// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes formales
// Autor: Enrique Álvarez Mesa
// Correo: alu0101142104@ull.es
// Fecha: 18/10/2022
// Archivo  lenguajes.cc
//    Contiene las funciones implementadas para la clase Lenguaje.

#include "lenguajes.h"

// Constructor
Lenguaje::Lenguaje() {}

// Constructor
Lenguaje::Lenguaje(Alfabeto& alfabeto_entrada) {
  alfabeto_ = alfabeto_entrada;  
}

// Inserta una cadena en el lenguaje
void Lenguaje::InsertarCadena(Cadena& cadena_entrada) {
  lenguaje_.insert(cadena_entrada);
}

// Inserta la cadena vacia en el lenguaje
void Lenguaje::InsertarCadenaVacia(Lenguaje& lenguaje) {
  Simbolo simbolo_vacio(VACIA);
  Cadena cadena_vacia;
  cadena_vacia.InsertarSimbolo(simbolo_vacio);
  lenguaje.InsertarCadena(cadena_vacia);
}

void Lenguaje::InsertarIdentificador(std::string& identificador_entrada) {
  identificador_ = identificador_entrada;
}

std::string Lenguaje::GetIdentificador() {
  return identificador_;
}

// Operacion de concatenacion. Recorro ambos leguajes y creo nuevas cadenas a 
// partir de las anteriores
Lenguaje Lenguaje::Concatenacion(Lenguaje& lenguaje_entrada) {
  Alfabeto Alfabeto_lenguaje = alfabeto_;
  Alfabeto_lenguaje.UnirAlfabeto(lenguaje_entrada.alfabeto_);
  Lenguaje Lenguaje_concatenado(Alfabeto_lenguaje);
  if (lenguaje_.empty() || lenguaje_entrada.lenguaje_.empty()) {
    return Lenguaje_concatenado;
  } else {
    for (auto cadena1 : lenguaje_) {
    for (auto cadena2 : lenguaje_entrada.lenguaje_) {
      Cadena cadena_concatenada;
      for (auto simbolo : cadena1.GetCadena()) {
        if (simbolo != VACIA) {
          cadena_concatenada.InsertarSimbolo(simbolo);
        }
      }
      for (auto simbolo : cadena2.GetCadena()) {
        if (simbolo != VACIA) {
          cadena_concatenada.InsertarSimbolo(simbolo);
        }
      }
      if (cadena_concatenada.GetCadena().size() == 0) {
        InsertarCadenaVacia(Lenguaje_concatenado);
      } else {
        cadena_concatenada.SetAlfabeto(Alfabeto_lenguaje);
        Lenguaje_concatenado.InsertarCadena(cadena_concatenada);
      }
    }
  }
  return Lenguaje_concatenado;
  }
}

// Operacion de Union. Inserto las cadenas de ambos Lenguajes en uno nuevo
Lenguaje Lenguaje::Union(Lenguaje& lenguaje_entrada) {
  Alfabeto Alfabeto_lenguaje = alfabeto_;
  Alfabeto_lenguaje.UnirAlfabeto(lenguaje_entrada.alfabeto_);
  Lenguaje Lenguaje_unido(Alfabeto_lenguaje);
  for (auto cadena1 : lenguaje_) {
    Lenguaje_unido.InsertarCadena(cadena1);
  }
  for (auto cadena2 : lenguaje_entrada.lenguaje_) {
    Lenguaje_unido.InsertarCadena(cadena2);
  }
  return Lenguaje_unido;
}

// Operacion de Interseccion. Recorro ambos lenguajes y compruebo si las cadenas
// son iguales. Si lo son, las inserto en el nuevo lenguaje
Lenguaje Lenguaje::Interseccion(Lenguaje& lenguaje_entrada) {
  Alfabeto Alfabeto_lenguaje = alfabeto_;
  Alfabeto_lenguaje.UnirAlfabeto(lenguaje_entrada.alfabeto_);
  Lenguaje Lenguaje_intersectado(Alfabeto_lenguaje);
  for (auto cadena1 : lenguaje_) {
    for (auto cadena2 : lenguaje_entrada.lenguaje_) {
      if (cadena1 == cadena2) {
        Lenguaje_intersectado.InsertarCadena(cadena1);
      }
    }
  }
  return Lenguaje_intersectado;
}

// Operacion de Diferencia. Recorro el primer lenguaje y compruebo si las
// cadenas estan en el segundo lenguaje. Si no lo estan, las inserto en el
// nuevo lenguaje
Lenguaje Lenguaje::Diferencia(Lenguaje& lenguaje_entrada) {
  Alfabeto Alfabeto_lenguaje = alfabeto_;
  Alfabeto_lenguaje.UnirAlfabeto(lenguaje_entrada.alfabeto_);
  Lenguaje Lenguaje_diferenciado(Alfabeto_lenguaje);
  for (auto cadena1 : lenguaje_) {
    bool encontrado = false;  
    for (auto cadena2 : lenguaje_entrada.lenguaje_) {
      if (cadena1 == cadena2) {
        encontrado = true;
      }
    }
    if (!encontrado) {
      Lenguaje_diferenciado.InsertarCadena(cadena1);
    }
  }
  return Lenguaje_diferenciado;
}

// Operacion de Inversa. Recorro las cadenas del lenguaje y realizo la operaion 
// de inversa sobre cada cadena
Lenguaje Lenguaje::Inversa() {
  Alfabeto Alfabeto_lenguaje = alfabeto_;
  Lenguaje Lenguaje_invertido(Alfabeto_lenguaje);
  Lenguaje_invertido.alfabeto_ = alfabeto_;
  for (auto cadena : lenguaje_) {
    Cadena cadena_invertida = cadena.Inversa();
    Lenguaje_invertido.InsertarCadena(cadena_invertida);
  }
  return Lenguaje_invertido;
}

// Operacion de Potencia. Recorro el lenguaje y concateno las cadenas con si
// mismas hasta llegar a la potencia indicada
Lenguaje Lenguaje::Potencia() {
  std::cout << "Introduce un valor para la potencia" << std::endl;
  std::cout << "=> ";
  int potencia;
  std::cin >> potencia;
  Lenguaje Lenguaje_potenciado;
  Lenguaje_potenciado.alfabeto_ = alfabeto_;
  if (potencia == 0) {
    InsertarCadenaVacia(Lenguaje_potenciado);
  } else {
    Lenguaje_potenciado.lenguaje_ = lenguaje_;
    for (int index = 0; index < potencia - 1; index++) {
      Lenguaje_potenciado = Lenguaje_potenciado.Concatenacion(*this);
    }
  }
  return Lenguaje_potenciado;
}

// Operacion de Potencia. Recorro el lenguaje y concateno las cadenas con si
// mismas hasta llegar a la potencia indicada
Lenguaje Lenguaje::Potencia(int& potencia) {
  Lenguaje Lenguaje_potenciado;
  Lenguaje_potenciado.alfabeto_ = alfabeto_;
  if (potencia == 0) {
    InsertarCadenaVacia(Lenguaje_potenciado);
  } else {
    Lenguaje_potenciado.lenguaje_ = lenguaje_;
    for (int index = 0; index < potencia - 1; index++) {
      Lenguaje_potenciado = Lenguaje_potenciado.Concatenacion(*this);
    }
  }
  return Lenguaje_potenciado;
}

// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream& os, Lenguaje& lenguaje) {
  if (lenguaje.lenguaje_.size() == 0) {
    os << "{}";
  } else {
    for (std::set<Cadena>::iterator it = lenguaje.lenguaje_.begin(); it != lenguaje.lenguaje_.end(); ++it) {
      os << *it << " ";
    }
  }
  return os;
}

// Devuelve el alfabeto del lenguaje
Alfabeto Lenguaje::GetAlfabeto() {
  return alfabeto_;
}