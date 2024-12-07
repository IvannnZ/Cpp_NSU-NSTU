#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "iostream"
#include "vector"

#pragma once

class Polynomial {
private:
  std::vector<int> coefficients;

public:

  Polynomial();
  Polynomial(const std::vector<int>& coeffs);
  Polynomial(const Polynomial& other);

  ~Polynomial();

  Polynomial& operator=(const Polynomial& other);

  Polynomial operator+(const Polynomial& other) const;
  Polynomial operator-(const Polynomial& other) const;
  Polynomial operator*(const Polynomial& other) const;
  Polynomial operator*(int scalar) const;
  Polynomial operator/(int scalar) const;
  friend Polynomial operator+(int scalar, const Polynomial& poly);
  friend Polynomial operator-(int scalar, const Polynomial& poly);
  friend Polynomial operator*(int scalar, const Polynomial& poly);
  friend Polynomial operator/(int scalar, const Polynomial& poly);

  Polynomial& operator+=(const Polynomial& other);
  Polynomial& operator-=(const Polynomial& other);

  Polynomial& operator++();  // Префиксный инкремент
  Polynomial operator++(int);  // Постфиксный инкремент
  Polynomial& operator--();  // Префиксный декремент
  Polynomial operator--(int);  // Постфиксный декремент

  bool operator==(const Polynomial& other) const;
  bool operator!=(const Polynomial& other) const;
  bool operator<(const Polynomial& other) const;
  bool operator>(const Polynomial& other) const;

  // Оператор доступа к элементу
  int operator[](size_t index) const;
  int& operator[](size_t index);


  void print() const;

  operator int() const;
  operator double() const;


  int evaluate(int x) const;
};

#endif // POLYNOMIAL_H
