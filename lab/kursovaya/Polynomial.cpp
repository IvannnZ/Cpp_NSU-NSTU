#include "Polynomial.h"
#include "iostream"
#include <cmath>
#include <stdexcept>

// Конструктор по умолчанию создает нулевой полином
Polynomial::Polynomial() : coefficients(1, 0) {}

// Конструктор с параметрами
Polynomial::Polynomial(const std::vector<int> &coeffs) : coefficients(coeffs) {}

// Конструктор копирования
Polynomial::Polynomial(const Polynomial &other)
    : coefficients(other.coefficients) {}

// Деструктор
Polynomial::~Polynomial() {
  // так как std::vector стандартная функция, она может сама управлять своей
  // памятью, и потом сам освободится
}

// Перегрузка оператора присваивания
Polynomial &Polynomial::operator=(const Polynomial &other) {
  if (this != &other) {
    coefficients = other.coefficients;
  }
  return *this;
}

// Арифметические операторы
Polynomial Polynomial::operator+(const Polynomial &other) const {
  size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
  std::vector<int> resultCoeffs(maxSize, 0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a = i < coefficients.size() ? coefficients[i] : 0;
    int b = i < other.coefficients.size() ? other.coefficients[i] : 0;
    resultCoeffs[i] = a + b;
  }
  return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator-(const Polynomial &other) const {
  size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
  std::vector<int> resultCoeffs(maxSize, 0.0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a = i < coefficients.size() ? coefficients[i] : 0.0;
    int b = i < other.coefficients.size() ? other.coefficients[i] : 0.0;
    resultCoeffs[i] = a - b;
  }
  return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator*(const Polynomial &other) const {
  std::vector<int> resultCoeffs(
      coefficients.size() + other.coefficients.size() - 1, 0.0);

  for (size_t i = 0; i < coefficients.size(); ++i) {
    for (size_t j = 0; j < other.coefficients.size(); ++j) {
      resultCoeffs[i + j] += coefficients[i] * other.coefficients[j];
    }
  }
  return Polynomial(resultCoeffs);
}

Polynomial Polynomial::operator/(int scalar) const {
  if (scalar == 0)
    throw std::runtime_error("Division by zero");
  std::vector<int> resultCoeffs(coefficients.size());

  for (size_t i = 0; i < coefficients.size(); ++i) {
    resultCoeffs[i] = coefficients[i] / scalar;
  }
  return Polynomial(resultCoeffs);
}

// Арифметика с накоплением
Polynomial &Polynomial::operator+=(const Polynomial &other) {
  *this = *this + other;
  return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &other) {
  *this = *this - other;
  return *this;
}

// Унарные операторы
Polynomial &Polynomial::operator++() {
  coefficients[0] += 1;
  return *this;
}

Polynomial Polynomial::operator++(int) {
  Polynomial temp = *this;
  ++(*this);
  return temp;
}

Polynomial &Polynomial::operator--() {
  coefficients[0] -= 1;
  return *this;
}

Polynomial Polynomial::operator--(int) {
  Polynomial temp = *this;
  --(*this);
  return temp;
}

// Логические операторы
bool Polynomial::operator==(const Polynomial &other) const {
  return coefficients == other.coefficients;
}

bool Polynomial::operator!=(const Polynomial &other) const {
  return !(*this == other);
}

bool Polynomial::operator<(const Polynomial &other) const {
  return coefficients.size() < other.coefficients.size();
}

bool Polynomial::operator>(const Polynomial &other) const {
  return coefficients.size() > other.coefficients.size();
}

// Оператор доступа к элементу
int Polynomial::operator[](size_t index) const {
  if (index >= coefficients.size())
    throw std::out_of_range("Index out of range");
  return coefficients[index];
}

int &Polynomial::operator[](size_t index) {
  if (index >= coefficients.size())
    throw std::out_of_range("Index out of range");
  return coefficients[index];
}

// Преобразование типа
//Polynomial::operator int() const {
//  return evaluate(1.0); // Значение полинома при x = 1
//}

// Функция вывода
void Polynomial::print() const {
  bool first = true;  // Флаг, чтобы правильно обрабатывать плюс в начале

  for (int i = coefficients.size() - 1; i >= 0; --i) {
    int coeff = coefficients[i];

    // Пропускаем нулевые коэффициенты
    if (coeff == 0) continue;

    // Для первого коэффициента просто выводим его
    if (first) {
      if (coeff < 0) {
        std::cout << "-";  // Если первый коэффициент отрицательный, ставим минус
        coeff = -coeff;
      }
      if (i == 0 || coeff != 1) {  // Если степень 0 или коэффициент не 1
        std::cout << coeff;
      }
      if (i > 0) {
        std::cout << "x";  // Добавляем "x" только если степень больше 0
      }
      first = false;  // Дальше уже будем добавлять знаки плюс или минус
    }
    else {
      // Для остальных коэффициентов
      if (coeff < 0) {
        std::cout << " - ";
        coeff = -coeff;  // Делаем коэффициент положительным
      } else {
        std::cout << " + ";
      }

      // Выводим коэффициент, если он не 1 и не -1, или если степень 0
      if (coeff != 1 || i == 0) {
        std::cout << coeff;
      }

      // Выводим степень x, если она больше 0
      if (i > 0) {
        std::cout << "x";
        if (i > 1) {
          std::cout << "^" << i;  // Если степень больше 1, добавляем ^ и степень
        }
      }
    }
  }
  std::cout << std::endl;
}



// Вспомогательная функция для вычисления значения полинома при x
int Polynomial::evaluate(int x) const {
  int result = 0;
  for (size_t i = 0; i < coefficients.size(); ++i) {
    result += coefficients[i] * std::pow(x, i);
  }
  return result;
}
