#include "Polynom.h"
#include "iostream"
#include <cmath>
#include <stdexcept>

// Конструктор по умолчанию, создающий полином с одним коэффициентом 0
Polynom::Polynom() : coef(1, 0) {}

// Конструктор с параметром, принимающим вектор коэффициентов
Polynom::Polynom(const std::vector<int> &coef) : coef(coef) {}

// Конструктор копирования
Polynom::Polynom(const Polynom &other) : coef(other.coef) {}

// Деструктор
Polynom::~Polynom() {}

// Оператор присваивания
Polynom &Polynom::operator=(const Polynom &other) {
  if (this != &other) {
    coef = other.coef; // Копируем вектор коэффициентов
  }
  return *this;
}

// Сложение двух полиномов
Polynom Polynom::operator+(const Polynom &other) const {
  size_t maxSize = std::max(coef.size(), other.coef.size());

  std::vector<int> resCoef(maxSize, 0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a= (i < coef.size()) ? coef[i] : 0;
    // Коэффициент первого полинома или 0
    int b = (i < other.coef.size()) ? other.coef[i] : 0;
    // Коэффициент второго полинома или 0
    resCoef[i] = a + b;                  // Складываем коэффициенты
  }

  return Polynom(resCoef);
}

// Вычитание двух полиномов
Polynom Polynom::operator-(const Polynom &other) const {
  size_t maxSize = std::max(coef.size(), other.coef.size());
  std::vector<int> resCoef(maxSize, 0.0);

  for (size_t i = 0; i < maxSize; ++i) {
    int a = (i < coef.size()) ? coef[i] : 0;
    int b = (i < other.coef.size()) ? other.coef[i] : 0;
    resCoef[i] = a - b; // Вычитаем коэффициенты
  }

  return Polynom(resCoef);
}

// Умножение двух полиномов
Polynom Polynom::operator*(const Polynom &other) const {
  // Размер нового полинома будет равен сумме степеней полиномов минус 1
  std::vector<int> resCoef(coef.size() + other.coef.size() - 1, 0);

  for (size_t i = 0; i < coef.size(); ++i) {
    for (size_t j = 0; j < other.coef.size(); ++j) {
      resCoef[i + j] +=
          coef[i] * other.coef[j]; // Перемножаем и складываем степени
    }
  }

  return Polynom(resCoef);
}

// Умножение полинома на скаляр
Polynom Polynom::operator*(int scal) const {
  if (scal == 0) {
    return Polynom(); // Если скаляр равен 0, возвращаем нулевой полином
  }

  std::vector<int> resCoef(coef.size());
  for (size_t i = 0; i < coef.size(); ++i) {
    resCoef[i] = coef[i] * scal;
  }

  return Polynom(resCoef);
}

// Деление полинома на скаляр
Polynom Polynom::operator/(int scal) const {
  if (scal == 0)
    throw std::runtime_error("Division by zero"); // Проверка на деление на ноль

  std::vector<int> resCoef(coef.size());
  for (size_t i = 0; i < coef.size(); ++i) {
    resCoef[i] = coef[i] / scal; // Делим каждый коэффициент на скаляр
  }

  return Polynom(resCoef);
}

// Операторы сложения и вычитания с накоплением
Polynom &Polynom::operator+=(const Polynom &other) {
  *this = *this + other; // Вызываем оператор сложения
  return *this;
}

Polynom &Polynom::operator-=(const Polynom &other) {
  *this = *this - other; // Вызываем оператор вычитания
  return *this;
}

// Унарные операторы увеличения и уменьшения
Polynom &Polynom::operator++() {
  coef[0] += 1; // Увеличиваем свободный коэффициент
  return *this;
}

Polynom Polynom::operator++(int) {
  Polynom temp = *this;
  ++(*this); // Вызываем префиксный инкремент
  return temp;
}

Polynom &Polynom::operator--() {
  coef[0] -= 1; // Уменьшаем свободный коэффициент
  return *this;
}

Polynom Polynom::operator--(int) {
  Polynom temp = *this;
  --(*this); // Вызываем префиксный декремент
  return temp;
}

// Логические операторы сравнения
bool Polynom::operator==(const Polynom &other) const {
  return coef == other.coef; // Сравниваем коэффициенты
}

bool Polynom::operator!=(const Polynom &other) const {
  return !(*this == other); // Проверяем на неравенство
}

bool Polynom::operator<(const Polynom &other) const {
  return coef.size() < other.coef.size(); // Сравниваем размеры полиномов
}

bool Polynom::operator>(const Polynom &other) const {
  return coef.size() > other.coef.size(); // Сравниваем размеры полиномов
}

// Операторы доступа к элементам
//int Polynom::operator[](size_t index) const {
//  if (index >= coef.size())
//    throw std::out_of_range("Index out of range"); // Проверяем диапазон
//  return coef[index];
//}

int &Polynom::operator[](size_t index) {
  if (index >= coef.size())
    throw std::out_of_range("Index out of range");
  return coef[index];
}

// Метод вывода полинома в консоль
void Polynom::print() const {
  bool first = true;

  if (coef.size() == 1) {
    std::cout << coef[0] << std::endl;
    return;
  }

  for (int i = coef.size() - 1; i >= 0; --i) {
    int coeff = coef[i];

    if (coeff == 0)
      continue; // Пропускаем нулевые коэффициенты

    if (coeff < 0) {
      if (!first) {
        std::cout << " - ";
      } else {
        std::cout << "-";
      }
      coeff = -coeff; // Меняем знак для вывода
    } else if (!first) {
      std::cout << " + ";
    }

    first = false;

    if (coeff != 1 || i == 0) {
      std::cout << coeff; // Выводим коэффициент
    }

    if (i > 0) {
      std::cout << "x";
      if (i > 1) {
        std::cout << "^" << i; // Выводим степень
      }
    }
  }
  std::cout << std::endl;
}

// Преобразование в int: возвращает старший коэффициент
Polynom::operator int() const {
  if (coef.empty()) {
    return 0; // Если коэффициентов нет, возвращаем 0
  }
  return coef.back(); // Последний элемент в векторе — старший коэффициент
}

// Преобразование в double: вычисляет значение при x = 1
Polynom::operator double() const {
  double result = 0.0;
  for (int coeff : coef) {
    result += coeff; // Суммируем все коэффициенты
  }
  return result;
}

// Вычисление значения полинома при заданном x
int Polynom::evaluate(int x) const {
  int result = 0;
  for (size_t i = 0; i < coef.size(); ++i) {
    result += coef[i] * std::pow(x, i); // Вычисляем значение по формуле
  }
  return result;
}

// Арифметические операции с полиномом и скаляром
Polynom operator+(int scal, const Polynom &poly) {
  std::vector<int> resCoef = poly.coef;
  if (!resCoef.empty()) {
    resCoef[0] += scal; // Добавляем скаляр к свободному коэффициенту
  } else {
    resCoef.push_back(scal); // Если полином пуст, создаем новый
  }
  return Polynom(resCoef);
}

Polynom operator-(int scal, const Polynom &poly) {
  std::vector<int> resCoef(poly.coef.size());
  for (size_t i = 0; i < poly.coef.size(); ++i) {
    resCoef[i] = -poly.coef[i]; // Инвертируем все коэффициенты
  }
  if (!resCoef.empty()) {
    resCoef[0] += scal; // Добавляем скаляр к свободному коэффициенту
  } else {
    resCoef.push_back(scal);
  }
  return Polynom(resCoef);
}

Polynom operator*(int scal, const Polynom &poly) {
  std::vector<int> resCoef(poly.coef.size());
  for (size_t i = 0; i < poly.coef.size(); ++i) {
    resCoef[i] = poly.coef[i] * scal; // Умножаем все коэффициенты на скаляр
  }
  return Polynom(resCoef);
}

Polynom operator/(int scal, const Polynom &poly) {
  if (scal == 0) {
    throw std::runtime_error(
        "Division by zero scalar is not allowed"); // Проверка на деление на 0
  }

  std::vector<int> resCoef(poly.coef.size());
  for (size_t i = 0; i < poly.coef.size(); ++i) {
    if (poly.coef[i] == 0) {
      throw std::runtime_error(
          "Division by zero coefficient in polynomial"); // Проверка
                                                         // коэффициентов
    }
    resCoef[i] = scal / poly.coef[i]; // Делим скаляр на каждый коэффициент
  }

  return Polynom(resCoef);
}
