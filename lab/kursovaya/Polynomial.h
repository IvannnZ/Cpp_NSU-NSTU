#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "iostream"
#include "vector"

#pragma once

class Polynomial {
private:
  std::vector<int> coefficients;

public:
  // Конструкторы
  Polynomial();  // Конструктор по умолчанию
  Polynomial(const std::vector<int>& coeffs);  // Конструктор с параметрами
  Polynomial(const Polynomial& other);  // Конструктор копирования

  // Деструктор
  ~Polynomial();

  // Перегрузка оператора присваивания
  Polynomial& operator=(const Polynomial& other);

  // Арифметические операторы
  Polynomial operator+(const Polynomial& other) const;
  Polynomial operator-(const Polynomial& other) const;
  Polynomial operator*(const Polynomial& other) const;
  Polynomial operator*(int scalar) const;
  Polynomial operator/(int scalar) const;  // Деление на скаляр

  // Арифметика с накоплением
  Polynomial& operator+=(const Polynomial& other);
  Polynomial& operator-=(const Polynomial& other);

  // Унарные операторы
  Polynomial& operator++();  // Префиксный инкремент
  Polynomial operator++(int);  // Постфиксный инкремент
  Polynomial& operator--();  // Префиксный декремент
  Polynomial operator--(int);  // Постфиксный декремент

  // Логические операторы
  bool operator==(const Polynomial& other) const;
  bool operator!=(const Polynomial& other) const;
  bool operator<(const Polynomial& other) const;
  bool operator>(const Polynomial& other) const;

  // Оператор доступа к элементу
  int operator[](size_t index) const;
  int& operator[](size_t index);


  // Функция вывода
  void print() const;

  // Вспомогательная функция для вычисления значения полинома при x
  int evaluate(int x) const;
};

#endif // POLYNOMIAL_H
