#include "Polynomial.h"
#include  <iostream>

int main() {
  Polynomial p1({1, -2, 3});  // Полином 3x^2 - 2x + 1
  Polynomial p2({0, 2, -1});  // Полином -x^2 + 2x

  p1.print();
  p2.print();


  Polynomial sum = p1 + p2;
  sum.print();  // Вывод результата сложения

  Polynomial product = p1 * p2;
  product.print();  // Вывод результата умножения

  p1 += p2;
  p1.print();  // Вывод результата накопительного сложения

  std::cout << "Value of p1 at x=2: " << p1.evaluate(2) << std::endl;  // Вычисление значения при x=2

  return 0;
}