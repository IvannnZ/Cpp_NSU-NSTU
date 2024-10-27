#include <stdint.h>
#include <stdio.h>

void print_binary_(int num, int len_in_byte) {
  for (int i = len_in_byte; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
}

// Функция для представления целого числа в виде двоичной строки
void print_binary(int num) {
  printf("Двоичное представление целого числа %d: ", num);
  for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
  printf("\n");
}

// Функция для представления числа float в виде двоичных компонент
void print_float_components(float num) {
  union {
    float f;
    uint32_t u;
  } float_union;

  float_union.f = num;

  uint32_t sign = (float_union.u >> 31) & 1;        // Знак
  uint32_t exponent = (float_union.u >> 23) & 0xFF; // Порядок (8 бит)
  uint32_t mantissa = float_union.u & 0x7FFFFF;     // Мантисса (23 бита)

  printf("Число float: %f\n", num);
  printf("Знак: %u\n", sign);
  printf("Порядок: %u (в десятичной системе)\n", exponent);
  printf("Мантисса: %u (в десятичной системе)\n", mantissa);

  // Печать в двоичном виде
  printf("Двоичное представление: знак = %u, порядок = ", sign);
  print_binary_(exponent, 7);

  printf(", мантисса = ");
  print_binary_(mantissa, 22);

  printf("\n");
}

int main() {
  int int_number;
  float float_number;

  // Ввод целого числа
  printf("Введите целое число: ");
  scanf("%d", &int_number);
  print_binary_(int_number, sizeof(int) * 8 - 1);
  printf("\b");
  // Ввод числа с плавающей точкой
  printf("Введите число с плавающей точкой: ");
  scanf("%f", &float_number);
  print_float_components(float_number);
  printf("\n");
  return 0;
}

/*
#include <stdio.h>

unsigned S(unsigned num) { return num >> 31; } // выделение знака

unsigned C(unsigned num) { return num << 1 >> 24; } // выделение характеристики

unsigned M(unsigned num) {
  num = num << 9 >> 9;
  return num | 040000000;
} // выделение мантиссы

void CAsBinNum(unsigned num) // вывод характеристики в двоичном виде
{
  int i, arr[8];

  for (i = 0; i < 8; i++) {
    arr[i] = num % 2;
    num /= 2;
  }

  for (i = 7; i >= 0; i--)
    printf("%d", arr[i]);
}

void MAsBinNum(unsigned num) // вывод мантиссы в двоичном виде
{
  int i, arr[23];

  for (i = 0; i < 23; i++) {
    arr[i] = num % 2;
    num /= 2;
  }

  for (i = 22; i >= 0; i--)
    printf("%d", arr[i]);
}

void iPartBinNum(int num) // вывод целой части числа в двоичном виде
{
  int i = 0, j, arr[32];

  if (num < 0) {
    num = -num;
    printf("-");
  }

  do {
    arr[i] = num % 2;
    num /= 2;
    i++;
  } while (num != 0);

  for (j = i - 1; j >= 0; j--)
    printf("%d", arr[j]);
}

void fPartBinNum(double num) // вывод дробной части числа в двоичном виде
{
  int r;
  num -= (int)num;

  if (num < 0) {
    num = -num;
    printf("-0.");
  } else
    printf("0.");

  do {
    num *= 2;
    r = (int)num;
    num -= r;
    printf("%d", r);
  } while (num);
}

unsigned iPartNum(unsigned long long num, int p) {
  p -= 127;
  return num >> (23 - p);
} // определeние целой части по мантиссе

unsigned long long fPartNum(unsigned long long num, int p) {
  p = -127;
  return num << (41 + p) >> (41 + p);
} // определение дробной части по мантиссе

int mul10(int *arr) // умножение двоичного числа на 1010
{
  int i, j, b = 0, arr1[132], arr2[132], res[132], r = 0;

  arr1[0] = 0;
  arr1[1] = 0;
  arr1[2] = 0;
  for (i = 3; i < 131; i++)
    arr1[i] = arr[i - 3];
  arr1[131] = 0;
  arr2[0] = 0;
  for (i = 1; i < 129; i++)
    arr2[i] = arr[i - 1];
  for (i = 129; i < 132; i++)
    arr2[i] = 0;

  for (i = 131; i >= 0; i--) {
    res[i] = arr1[i] + arr2[i] + b;
    if (res[i] == 3) {
      res[i] = 1;
      b = 1;
      continue;
    }
    if (res[i] == 2) {
      res[i] = 0;
      b = 1;
      continue;
    }
    b = 0;
  }

  for (i = 0; i < 4; i++) {
    b = 1;
    for (j = 0; j < 3 - i; j++)
      b *= 2;
    r += res[i] * b;
  }

  for (i = 0; i < 128; i++)
    arr[i] = res[i + 4];

  return r;
}

int isZero(int *arr) {
  int i;
  for (i = 0; i < 128; i++)
    if (arr[i] != 0)
      return 0;
  return 1;
} // определение нулевого массива

void translation(unsigned long long num,
                 long long p) // перевод из двоичного вида в десятичный
{
  int i, arr[128], res[128];

  p -= 127;
  num <<= (41 + p);

  for (i = 0; i < 64; i++)
    arr[i] = num << i >> 63;
  for (i = 64; i < 128; i++)
    arr[i] = 0;
  for (i = 0; i < 128; i++)
    res[i] = 0;

  i = 0;
  while (!isZero(arr)) {
    res[i] = mul10(arr);
    i++;
  }

  for (i = 0; i < 128; i++)
    printf("%d", res[i]);
}

int main() {
  union {
    unsigned i;
    float f;
  } u;

  u.f = 1.1;
  printf("Number: %f", u.f); // ввод числа
  printf("\nNumber in bin: %d ", S(u.i));
  CAsBinNum(C(u.i));
  printf(" ");
  MAsBinNum(M(u.i));              // число в машинном коде
  printf("\n\nSign: %d", S(u.i)); // знак
  printf("\n\nCharacteristic: ");
  CAsBinNum(C(u.i)); // характеристика
  printf("\n\nMantissa: ");
  MAsBinNum(M(u.i));                     // мантисса
  printf("\n\nOrder: %d", C(u.i) - 127); // порядок
  printf("\n\nInteger part in bin: ");
  iPartBinNum(u.f); // целое в двоичном
  printf("\n\nFloat part in bin: ");
  fPartBinNum(u.f); // дробное в двоичном
  printf("\n\nInteger part in dec: %d",
         S(u.i) == 1 ? -1 * iPartNum(M(u.i), C(u.i))
                     : iPartNum(M(u.i), C(u.i))); // целое в десятичном
  printf("\n\nFloat part in dec:%c0.", S(u.i) == 1 ? '-' : ' ');
  translation(fPartNum(M(u.i), C(u.i)), C(u.i)); // дробное в десятичном
  printf("\n\nNumber in dec:%c%d.", S(u.i) == 1 ? '-' : ' ',
         iPartNum(M(u.i), C(u.i)));
  translation(fPartNum(M(u.i), C(u.i)), C(u.i)); // число в десятичном

  return 0;
}
*/