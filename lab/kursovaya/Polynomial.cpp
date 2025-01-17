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

// оператор присваивания
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
  Polynomial ret = Polynomial(resultCoeffs);
  return ret;
}

Polynomial Polynomial::operator-(const Polynomial &other) const {
  size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
  std::vector<int> resultCoeffs(maxSize, 0.0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a = i < coefficients.size() ? coefficients[i] : 0.0;
    int b = i < other.coefficients.size() ? other.coefficients[i] : 0.0;
    resultCoeffs[i] = a - b;
  }
  Polynomial ret = Polynomial(resultCoeffs);
  return ret;
}

Polynomial Polynomial::operator*(const Polynomial &other) const {
  std::vector<int> resultCoeffs(
      coefficients.size() + other.coefficients.size() - 1, 0.0);

  for (size_t i = 0; i < coefficients.size(); ++i) {
    for (size_t j = 0; j < other.coefficients.size(); ++j) {
      resultCoeffs[i + j] += coefficients[i] * other.coefficients[j];
    }
  }
  Polynomial ret = Polynomial(resultCoeffs);
  return ret;
}

Polynomial Polynomial::operator*(int scalar) const {
  if (scalar == 0) {
    Polynomial a;
    return a;
  }
  std::vector<int> resultCoeffs(coefficients.size());

  for (size_t i = 0; i < coefficients.size(); ++i) {
    resultCoeffs[i] = coefficients[i] * scalar;
  }
  Polynomial ret = Polynomial(resultCoeffs);
  return ret;
}

Polynomial Polynomial::operator/(int scalar) const {
  if (scalar == 0)
    throw std::runtime_error("Division by zero");
  std::vector<int> resultCoeffs(coefficients.size());

  for (size_t i = 0; i < coefficients.size(); ++i) {
    resultCoeffs[i] = coefficients[i] / scalar;
  }
  Polynomial ret = Polynomial(resultCoeffs);
  return ret;
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


void Polynomial::print() const {
  bool first = true;

  if (coefficients.size() == 1){
    std::cout<<coefficients[0]<<std::endl;
    return;
  }
  for (int deg_x = coefficients.size() - 1; deg_x >= 0; --deg_x) {
    int coeff = coefficients[deg_x];

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

      if (coeff != 1 || deg_x == 0) {
        std::cout << coeff;
      }

      if (deg_x > 0) {
        std::cout << "x";
        if (deg_x > 1) {
          std::cout << "^" << deg_x;
        }
      }
  }
  std::cout << std::endl;
}

// Оператор преобразования в int
// возвращает старший коэффициент
Polynomial::operator int() const {

  if (coefficients.empty()) {
    return 0;
  }
  return coefficients.back();
}

// Оператор преобразования в double
// Вычисляет значение полинома при x = 1
Polynomial::operator double() const {
  double result = 0.0;
  for (int coeff : coefficients) {
    result += coeff;
  }
  return result;
}

// Вспомогательная функция для вычисления значения полинома при x
int Polynomial::evaluate(int x) const {
  int result = 0;
  for (size_t i = 0; i < coefficients.size(); ++i) {
    result += coefficients[i] * std::pow(x, i);
  }
  return result;
}

Polynomial operator+(int scalar, const Polynomial& poly) {
  // Складываем скаляр только с нулевым коэффициентом
  std::vector<int> resultCoeffs = poly.coefficients;
  if (!resultCoeffs.empty()) {
    resultCoeffs[0] += scalar;
  } else {
    resultCoeffs.push_back(scalar);
  }
  return Polynomial(resultCoeffs);
}

Polynomial operator-(int scalar, const Polynomial& poly) {
  // Вычитаем полином из скаляра, инвертируем знак всех коэффициентов полинома
  std::vector<int> resultCoeffs(poly.coefficients.size());
  for (size_t i = 0; i < poly.coefficients.size(); ++i) {
    resultCoeffs[i] = -poly.coefficients[i];
  }
  if (!resultCoeffs.empty()) {
    resultCoeffs[0] += scalar;
  } else {
    resultCoeffs.push_back(scalar);
  }
  return Polynomial(resultCoeffs);
}

Polynomial operator*(int scalar, const Polynomial& poly) {
  // Просто умножаем все коэффициенты на скаляр
  std::vector<int> resultCoeffs(poly.coefficients.size());
  for (size_t i = 0; i < poly.coefficients.size(); ++i) {
    resultCoeffs[i] = poly.coefficients[i] * scalar;
  }
  return Polynomial(resultCoeffs);
}

Polynomial operator/(int scal, const Polynomial &poly) {
  if (scal == 0) {
    throw std::runtime_error(
        "Division by zero scalar is not allowed"); // Проверка на деление на 0
  }

  std::vector<int> resCoef(poly.coefficients.size());
  for (size_t i = 0; i < poly.coefficients.size(); ++i) {
    if (poly.coefficients[i] == 0) {
      throw std::runtime_error(
          "Division by zero coefficient in polynomial"); // Проверка
                                                         // коэффициентов
    }
    resCoef[i] =
        scal / poly.coefficients[i]; // Делим скаляр на каждый коэффициент
  }

  return Polynomial(resCoef);
}
