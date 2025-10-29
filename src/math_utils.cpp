#include "math_utils.hpp"
#include <cmath>

namespace math {
    double sumar(double a, double b){
        return a + b;
    }
    
    double restar(double a, double b){
        return a - b;
    }

    double multiplicar(double a, double b){
        return a * b;
    }

    double dividir(double a, double b){
        if (b == 0.0) throw std::runtime_error("No se puede dividir por 0");
        return a / b;
    }

    double exponencial(double a, double b){
        
        if(std::floor(b) == b){
            double result = 1;
            int exp = static_cast<int>(b);
            if (exp < 0){
                for(int i = 0; i < -exp; i++){
                result *= a;
                }
                result = 1.0 / result;
            }
            else {
                for(int i = 0; i < exp; i++){
                result *= a;
                }
            }
            return result;
        }
        return std::pow(a, b);
    }

    double raiz(double a){
        if (a < 0) throw std::runtime_error("No se puede hacer raiz de numero negativos");
        return std::sqrt(a);
    }
}
