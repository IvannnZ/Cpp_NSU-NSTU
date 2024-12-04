#include "Polynom.h"
#include <iostream>

int main() {
  // Конструкторы
  Polynom p1; // По умолчанию
  Polynom p2({1, -2, 3}); // Полином 3x^2 - 2x + 1
  Polynom p3 = p2; // Конструктор копирования

  // Вывод полиномов
  std::cout << "p1: ";
  p1.print();
  std::cout << "p2: ";
  p2.print();
  std::cout << "p3 (копия p2): ";
  p3.print();

  // Арифметические операторы
  Polynom sum = p2 + p3;
  Polynom diff = p2 - p3;
  Polynom prod = p2 * p3;
  Polynom scaled = p2 * 2;
  Polynom divided = p2 / 2;

  std::cout << "Сумма (p2 + p3): ";
  sum.print();
  std::cout << "Разность (p2 - p3): ";
  diff.print();
  std::cout << "Произведение (p2 * p3): ";
  prod.print();
  std::cout << "Умножение на скаляр (p2 * 2): ";
  scaled.print();
  std::cout << "Деление на скаляр (p2 / 2): ";
  divided.print();

  // Арифметика с накоплением
  p2 += p3;
  std::cout << "После p2 += p3: ";
  p2.print();
  p2 -= p3;
  std::cout << "После p2 -= p3: ";
  p2.print();

  // Унарные операторы
  Polynom p4 = p2;
  std::cout << "Префиксный инкремент: ";
  (++p4).print();
  std::cout << "Постфиксный инкремент: ";
  (p4++).print();
  std::cout << "После постфиксного инкремента: ";
  p4.print();

  // Логические операторы
  std::cout << "p2 == p3: " << (p2 == p3) << std::endl;
  std::cout << "p2 != p3: " << (p2 != p3) << std::endl;
  std::cout << "p2 < p3: " << (p2 < p3) << std::endl;
  std::cout << "p2 > p3: " << (p2 > p3) << std::endl;

  // Оператор доступа
  std::cout << "Коэффициент p2[1]: " << p2[1] << std::endl;
  p2[1] = 5;
  std::cout << "После изменения p2[1] = 5: ";
  p2.print();

  // Преобразование типов
  int leadingCoef = static_cast<int>(p2);
  double valueAtX1 = static_cast<double>(p2);
  std::cout << "Старший коэффициент p2: " << leadingCoef << std::endl;
  std::cout << "Значение p2 при x = 1: " << valueAtX1 << std::endl;

  // Вычисление значения полинома
  int valueAtX2 = p2.evaluate(2);
  std::cout << "Значение p2 при x = 2: " << valueAtX2 << std::endl;

  // Дружественные функции
  Polynom scalarSum = 3 + p2;
  Polynom scalarDiff = 3 - p2;
  Polynom scalarProd = 3 * p2;

  std::cout << "3 + p2: ";
  scalarSum.print();
  std::cout << "3 - p2: ";
  scalarDiff.print();
  std::cout << "3 * p2: ";
  scalarProd.print();

  return 0;
}
