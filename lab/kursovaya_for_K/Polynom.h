#ifndef POLYNOM_H
#define POLYNOM_H

#include "iostream"
#include "vector"

#pragma once

// Класс для работы с полиномами
class Polynom {
private:
  // Вектор коэффициентов полинома
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
  Polynom operator+(const Polynom & other) const; // Сложение полиномов
  Polynom operator-(const Polynom & other) const; // Вычитание полиномов
  Polynom operator*(const Polynom & other) const; // Умножение полиномов
  Polynom operator*(int scal) const;              // Умножение на скаляр
  Polynom operator/(int scal) const;              // Деление на скаляр

  // Дружественные функции для операций с полиномами и скалярами
  friend Polynom operator+(int scal, const Polynom & poly);
  friend Polynom operator-(int scal, const Polynom & poly);
  friend Polynom operator*(int scal, const Polynom & poly);
  friend Polynom operator/(int scal, const Polynom & poly);

  // Арифметика с накоплением
  Polynom & operator+=(const Polynom & other); // Добавить и присвоить
  Polynom & operator-=(const Polynom & other); // Вычесть и присвоить

  // Унарные операторы
  Polynom & operator++();  // Префиксный инкремент
  Polynom operator++(int); // Постфиксный инкремент
  Polynom & operator--();  // Префиксный декремент
  Polynom operator--(int); // Постфиксный декремент

  // Логические операторы
  bool operator==(const Polynom & other) const; // Проверка на равенство
  bool operator!=(const Polynom & other) const; // Проверка на неравенство
  bool operator<(const Polynom & other) const;  // Меньше (по числу членов)
  bool operator>(const Polynom & other) const;  // Больше (по числу членов)

  // Операторы доступа к элементам
  int operator[](size_t index) const; // Доступ по индексу (константный)
  int& operator[](size_t index);      // Доступ по индексу (изменяемый)

  // Функция вывода полинома
  void print() const;

  // Преобразование типов
  operator int() const;      // Преобразование в int (старший коэффициент)
  operator double() const;   // Преобразование в double (значение при x = 1)

  // Вычисление значения полинома при определённом x
  int evaluate(int x) const;
};

#endif // POLYNOM_H
