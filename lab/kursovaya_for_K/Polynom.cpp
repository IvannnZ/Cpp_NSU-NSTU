#include "Polynom.h"
#include "iostream"
#include <cmath>
#include <stdexcept>


Polynom::Polynom() : coef(1, 0) {}

Polynom::Polynom(const std::vector<int> &coef) : coef(coef) {}

Polynom::Polynom(const Polynom &other)
    : coef(other.coef) {}

Polynom::~Polynom() {

}

Polynom &Polynom::operator=(const Polynom &other) {
  if (this != &other) {
    coef = other.coef;
  }
  return *this;
}

Polynom Polynom::operator+(const Polynom &other) const {
  size_t maxSize = std::max(coef.size(), other.coef.size());
  std::vector<int> resCoef(maxSize, 0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a;
    if (i < coef.size()) {
      a = coef[i];
    } else {
      a = 0;
    }
    int b;
    if (i < other.coef.size()) {
      b = other.coef[i];
    } else {
      b = 0;
    }
    resCoef[i] = a + b;
  }
  Polynom ret = Polynom(resCoef);
  return ret;
}

Polynom Polynom::operator-(const Polynom &other) const {
  size_t maxSize = std::max(coef.size(), other.coef.size());
  std::vector<int> resCoef(maxSize, 0.0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a;
    if (i < coef.size()) {
      a = coef[i];
    } else {
      a = 0.0;
    }
    int b;
    if (i < other.coef.size()) {
      b = other.coef[i];
    } else {
      b = 0.0;
    }
    resCoef[i] = a - b;
  }
  Polynom ret = Polynom(resCoef);
  return ret;
}

Polynom Polynom::operator*(const Polynom &other) const {
  std::vector<int> resCoef(coef.size() + other.coef.size() - 1, 0.0);

  for (size_t i = 0; i < coef.size(); ++i) {
    for (size_t j = 0; j < other.coef.size(); ++j) {
      resCoef[i + j] += coef[i] * other.coef[j];
    }
  }
  Polynom ret = Polynom(resCoef);
  return ret;
}

Polynom Polynom::operator*(int scal) const {
  if (scal == 0) {
    Polynom a;
    return a;
  }
  std::vector<int> resCoef(coef.size());

  for (size_t i = 0; i < coef.size(); ++i) {
    resCoef[i] = coef[i] * scal;
  }
  Polynom ret = Polynom(resCoef);
  return ret;
}

Polynom Polynom::operator/(int scal) const {
  if (scal == 0)
    throw std::runtime_error("Division by zero");
  std::vector<int> resCoef(coef.size());

  for (size_t i = 0; i < coef.size(); ++i) {
    resCoef[i] = coef[i] / scal;
  }
  Polynom ret = Polynom(resCoef);
  return ret;
}

// Арифметика с накоплением
Polynom &Polynom::operator+=(const Polynom &other) {
  *this = *this + other;
  return *this;
}

Polynom &Polynom::operator-=(const Polynom &other) {
  *this = *this - other;
  return *this;
}

// Унарные операторы
Polynom &Polynom::operator++() {
  coef[0] += 1;
  return *this;
}

Polynom Polynom::operator++(int) {
  Polynom temp = *this;
  ++(*this);
  return temp;
}

Polynom &Polynom::operator--() {
  coef[0] -= 1;
  return *this;
}

Polynom Polynom::operator--(int) {
  Polynom temp = *this;
  --(*this);
  return temp;
}

// Логические операторы
bool Polynom::operator==(const Polynom &other) const {
  return coef == other.coef;
}

bool Polynom::operator!=(const Polynom &other) const {
  return !(*this == other);
}

bool Polynom::operator<(const Polynom &other) const {
  return coef.size() < other.coef.size();
}

bool Polynom::operator>(const Polynom &other) const {
  return coef.size() > other.coef.size();
}

// Оператор доступа к элементу
int Polynom::operator[](size_t index) const {
  if (index >= coef.size())
    throw std::out_of_range("Index out of range");
  return coef[index];
}

int &Polynom::operator[](size_t index) {
  if (index >= coef.size())
    throw std::out_of_range("Index out of range");
  return coef[index];
}


void Polynom::print() const {
  bool first = true;

  if (coef.size() == 1){
    std::cout<< coef[0]<<std::endl;
    return;
  }
  for (int i = coef.size() - 1; i >= 0; --i) {
    int coeff = coef[i];

    // Пропускаем нулевые коэффициенты
    if (coeff == 0) continue;

    if (coeff < 0) {
      if (!first) {
        std::cout << " - ";
      } else {
        std::cout << "-";
      }
      coeff = -coeff;
    } else {
      if (!first) {
        std::cout << " + ";
      }
    }
    first = false;

      // Выводим коэффициент, если он не 1 и не -1, или если степень 0
      if (coeff != 1 || i == 0) {
        std::cout << coeff;
      }

      // Выводим степень x, если она больше 0
      if (i > 0) {
        std::cout << "x";
        if (i > 1) {
          std::cout << "^" << i;
        }
      }
  }
  std::cout << std::endl;
}

// Оператор преобразования в int
// возвращает старший коэффициент
Polynom::operator int() const {

  if (coef.empty()) {
    return 0;
  }
  return coef.back();  // Старший коэффициент — последний элемент в vector
}

// Оператор преобразования в double
// Вычисляет значение полинома при x = 1
Polynom::operator double() const {
  double result = 0.0;
  for (int coeff : coef) {
    result += coeff;  // Сумма всех коэффициентов как значение при x = 1
  }
  return result;
}

// Вспомогательная функция для вычисления значения полинома при x
int Polynom::evaluate(int x) const {
  int result = 0;
  for (size_t i = 0; i < coef.size(); ++i) {
    result += coef[i] * std::pow(x, i);
  }
  return result;
}

Polynom operator+(int scal, const Polynom & poly) {
  // Складываем скаляр только с нулевым коэффициентом
  std::vector<int> resCoef = poly.coef;
  if (!resCoef.empty()) {
    resCoef[0] += scal;
  } else {
    resCoef.push_back(scal);
  }
  return Polynom(resCoef);
}

Polynom operator-(int scal, const Polynom & poly) {
  // Вычитаем полином из скаляра, инвертируем знак всех коэффициентов полинома
  std::vector<int> resCoef(poly.coef.size());
  for (size_t i = 0; i < poly.coef.size(); ++i) {
    resCoef[i] = -poly.coef[i];
  }
  if (!resCoef.empty()) {
    resCoef[0] += scal;
  } else {
    resCoef.push_back(scal);
  }
  return Polynom(resCoef);
}

Polynom operator*(int scal, const Polynom & poly) {
  // Просто умножаем все коэффициенты на скаляр
  std::vector<int> resCoef(poly.coef.size());
  for (size_t i = 0; i < poly.coef.size(); ++i) {
    resCoef[i] = poly.coef[i] * scal;
  }
  return Polynom(resCoef);
}

Polynom operator/(int scal, const Polynom & poly) {
  throw std::runtime_error("Operation 'scalar / Polynomial' is not supported");
  // Если нужно реализовать, это более сложная задача,
  // связанная с разбиением полинома.
}
