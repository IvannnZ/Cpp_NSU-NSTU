#include "Polynomial.h"
#include  <iostream>

int main() {
//  Polynomial p1({1, -2, 3}); // 3x^2 - 2x + 1
//  Polynomial p2({0, 2, -1}); // -x^2 + 2x
//  Polynomial p;
//  p.print(); // 0
//  p1.print(); // 3x^2 - 2x + 1
//
//  p2.print(); // -x + 2x
//
//  Polynomial sum = p1 + p2;
//  sum.print();  // Вывод результата сложения
//
//  Polynomial product = p1 * p2;
//  product.print();  // Вывод результата умножения
//
//  p1 += p2;
//  p1.print();  // Вывод результата накопительного сложения
//
//  std::cout << "Value of p1 at x=2: " << p1.evaluate(2) << std::endl;  // Вычисление значения при x=2
//
//  return 0;

  std::cout << "Testing constructors:" << std::endl;
  Polynomial p1;             // Конструктор по умолчанию
  Polynomial p2({1, -2, 3}); // Конструктор с параметрами
  Polynomial p3(p2);         // Конструктор копирования

  std::cout << "Ожидается: 0" << std::endl << "p1: ";
  p1.print(); // Ожидается: 0 (нулевой полином)

  std::cout << "Ожидается: 3x^2 - 2x + 1" << std::endl << "p2: ";
  p2.print();

  std::cout << "Ожидается: 3x^2 - 2x + 1 (копия p2)" << std::endl << "p3: ";
  p3.print();
  std::cout << std::endl;

  // --- Тестирование оператора присваивания ---
  std::cout << "Testing assignment operator:" << std::endl;
  p1 = p2;
  std::cout << "Ожидается: 3x^2 - 2x + 1 (после p1 = p2)" << std::endl << "p1: ";
  p1.print();
  std::cout << std::endl;

  // --- Тестирование оператора [] ---
  std::cout << "Testing operator []:" << std::endl;
  std::cout << "Ожидается: 3 (p2[2])" << std::endl
            << "p2[2]: " << p2[2] << std::endl;
  std::cout << "Ожидается: -2 (p2[1])" << std::endl
            << "p2[1]: " << p2[1] << std::endl;
  p2[0] = 5;
  std::cout << "Ожидается: 3x^2 - 2x + 5 (после p2[0] = 5)" << std::endl
            << "p2: ";
  p2.print();
  std::cout << std::endl;

  // --- Тестирование арифметических операторов (+, -, *, /) ---
  Polynomial p4({1, 1});
  Polynomial p5({-1, 0, 1});

  std::cout << "Testing arithmetic operators:" << std::endl;
  Polynomial sum = p4 + p5;
  std::cout << "Ожидается: x^2 + x" << std::endl << "p4 + p5: ";
  sum.print();

  Polynomial diff = p4 - p5;
  std::cout << "Ожидается: -x^2 + x + 2" << std::endl << "p4 - p5: ";
  diff.print();

  Polynomial prod = p4 * p5;
  std::cout << "Ожидается: x^3 + x^2 - x - 1" << std::endl << "p4 * p5: ";
  prod.print();

  Polynomial scalarProd = p4 / 2;
  std::cout << "Ожидается: 2 + 2x" << std::endl << "p4 * 2: ";
  scalarProd.print();
  std::cout << std::endl;

  // --- Тестирование операторов с накоплением (+=, -=) ---
  std::cout << "Testing compound assignment operators:" << std::endl;
  p4 += p5;
  std::cout << "Ожидается: x^2 + x (p4 += p5)" << std::endl << "p4: ";
  p4.print();

  p4 -= p5;
  std::cout << "Ожидается: 1 + x (p4 -= p5)" << std::endl << "p4: ";
  p4.print();
  std::cout << std::endl;

  // --- Тестирование операторов инкремента и декремента (++, --) ---
  std::cout << "Testing increment and decrement operators:" << std::endl;
  ++p4;
  std::cout << "Ожидается: 1 + x (после ++p4)" << std::endl << "p4: ";
  p4.print();

  p4--;
  std::cout << "Ожидается: 1 + x - 1 (после p4--)" << std::endl << "p4: ";
  p4.print();
  std::cout << std::endl;

  // --- Тестирование логических операторов (<, >, ==, !=) ---
  std::cout << "Testing logical operators:" << std::endl;
  std::cout << "Ожидается: true (p2 == p3)" << std::endl
            << "p2 == p3: " << (p2 == p3) << std::endl;
  std::cout << "Ожидается: true (p2 != p4)" << std::endl
            << "p2 != p4: " << (p2 != p4) << std::endl;
  std::cout << "Ожидается: результат может быть true или false (p2 < p4)"
            << std::endl
            << "p2 < p4: " << (p2 < p4) << std::endl;
  std::cout << "Ожидается: результат может быть true или false (p4 > p3)"
            << std::endl
            << "p4 > p3: " << (p4 > p3) << std::endl;
  std::cout << std::endl;

  // --- Тестирование функции evaluate ---
  std::cout << "Testing evaluate function:" << std::endl;
  int x = 2;
  int result = p2.evaluate(x);
  std::cout << "Ожидается: значение полинома p2 при x = 2: 3*4 - 2*2 + 1 = 7"
            << std::endl;
  std::cout << "p2.evaluate(2): " << result << std::endl;

  return 0;
}
