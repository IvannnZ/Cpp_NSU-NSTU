#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "iostream"
#include "vector"

#pragma once

class Polynom {
private:
  std::vector<int> coef;

public:
  // Конструкторы
  Polynom();  // Конструктор по умолчанию
  Polynom(const std::vector<int>&coef);  // Конструктор с параметрами
  Polynom(const Polynom & other);  // Конструктор копирования

  // Деструктор
  ~Polynom();

  // Перегрузка оператора присваивания
  Polynom & operator=(const Polynom & other);

  // Арифметические операторы
  Polynom operator+(const Polynom & other) const;
  Polynom operator-(const Polynom & other) const;
  Polynom operator*(const Polynom & other) const;
  Polynom operator*(int scal) const;
  Polynom operator/(int scal) const;  // Деление на скаляр
  friend Polynom operator+(int scalar, const Polynom & poly);
  friend Polynom operator-(int scalar, const Polynom & poly);
  friend Polynom operator*(int scalar, const Polynom & poly);
  friend Polynom operator/(int scalar, const Polynom & poly);

  // Арифметика с накоплением
  Polynom & operator+=(const Polynom & other);
  Polynom & operator-=(const Polynom & other);

  // Унарные операторы
  Polynom & operator++();  // Префиксный инкремент
  Polynom operator++(int);  // Постфиксный инкремент
  Polynom & operator--();  // Префиксный декремент
  Polynom operator--(int);  // Постфиксный декремент

  // Логические операторы
  bool operator==(const Polynom & other) const;
  bool operator!=(const Polynom & other) const;
  bool operator<(const Polynom & other) const;
  bool operator>(const Polynom & other) const;

  // Оператор доступа к элементу
  int operator[](size_t index) const;
  int& operator[](size_t index);


  // Функция вывода
  void print() const;

  operator int() const;      // Преобразование в int (старший коэффициент)
  operator double() const;   // Преобразование в double (значение при x = 1)


  // Вспомогательная функция для вычисления значения полинома при x
  int evaluate(int x) const;
};

#endif // POLYNOMIAL_H
