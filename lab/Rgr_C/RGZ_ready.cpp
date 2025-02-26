#include <stdio.h>
#include <string.h>
#include <math.h> 

unsigned Z(unsigned count) // знак
{

	count >>= 31; // берем 1ый символ (знак)
	return count; // функция возвращает значение знака (1 или 0)

}

void Z_funct(unsigned count) // знак для вывода
{

	count >>= 31; // берем 1ый символ (знак)
	if (count == 1) // если 1, то "1"
		printf("%s", "-"); // выводим "-"

}

unsigned M(unsigned count) // выделение мантиссы
{

	count <<= 9; // выделение мантиссы
	count >>= 9; // выделение мантиссы
	count = count | 040000000; // маска добавляет необходимую единицу (которой не было)
	return count; // функция возвращает значние мантисcы

}

unsigned H(unsigned count) // выделение характеристику
{

	count <<= 1; // устраняем символ, ответственный за знак
	count >>= 1; // устраняем символ, ответственный за знак
	count >>= 23; // выделяем характерисику
	return count; // функция возвращает значние характеристики

}

unsigned dec_bin(unsigned dig) // перевод числа из десятичной в двоичную
{

	unsigned dv = 0, arg = 1; // необходимые значения (dv - хранение двоичной записи, arg - аргумент, необходимый для установления разрядов в двоичной записи)

	while (dig > 0)
	{

		dv += (dig % 2) * arg; // остаток от деления умножаем на аргумент
		arg *= 10; // аргумент меняет разряд
		dig /= 2; // целочисленное деления на 2

	}
	return dv; // функция возвращает значние двоичной записи

}

void null(float dig) // добавляем или не добавляем 0
{

	if (dig < 0.0) // проверяем отрицательное ли число
		dig *= -1; // делаем его положительным в случае "true"
	if ((dig < 2.0) && (dig >= 0.0)) // входит ли число в диапазон, в котором необходим 0
		printf("%d", 0); // выводим 0

}

void Binary(unsigned dig) // целое число в двоичной системе в массив (для вывода мантиссы)
{

	int i; char a[32]; // создаем необходимую переменую i, массив "a", в который бдем записывать мантиссу
	for (i = 0; i < 32; i++) // запускаем цикл
	{

		a[i] = dig % 2; // элемент массива равен остатку о=т деления на 2
		dig /= 2; // целочисленное деления на 2

	}

	for (i = 22; i >= 0; i--)
		printf("%d", a[i]); // вывод необходимого значения

}

void cel_dec_bin(int dig) // переводим из десятич в двоичное целое
{
	int B[100], h = 0;
	unsigned int dv = 0; // необходимые значения (dv - хранение двоичной записи)
	if (dig == 0) // если целая чатсть равна 0
		printf("%d", 0); // выводим 0
	if (dig < 0) // проверка знака числа
		dig *= -1; // если отрицательное, делаем его полоительным

	while (dig > 0) // пока целая часть больше 0
	{
		dv = (dig % 2); // остаток от деления
		B[h] = dv;
		dig /= 2; // целочисленное деление на 2
		h++;
	}
	for (int j = h - 1; j >= 0; j--) {
		printf("%d", B[j]);
	}
}

void necel_dec_bin(double ddig) // из десятич в двоич дробное 
{
	int dig = ddig;
	double fd;
	if (ddig >= 0.0)
		fd = ddig - dig;
	else
		fd = (ddig - dig) * -1;
	while (fd)
	{
		dig = fd * 2;
		if (dig >= 1)
			fd = fd * 2 - dig;
		else fd *= 2;

		printf("%d", dig);
	}
}

unsigned cel_M(unsigned long long count, int ord) // определение целой части по мантиссе 
{

	ord -= 127;
	unsigned long long a = 23 - ord;
	count >>= a;
	return count;

}

unsigned necel_M(unsigned long long count, int ord) // определение дробной части по мантиссе
{

	unsigned long long b = count;
	ord -= 127;
	count <<= 41 + ord;
	count >>= 41 + ord;
	return count;

}

void necel_bin_dec(unsigned k, int p) {// дробная двоичная часть форма в десятичную
	int digits[64] = {0}; // Инициализация массива нулями
	int num_digits = 0; // Количество значимых цифр в массиве
	p -= 127;
	int i; char a[32]; // создаем необходимую переменую i, массив "a", в который бдем записывать мантиссу
	for (i = 0; i < 64; i++) {// запускаем цикл
		if (p >= 0) { // если порядок больше или равен 0
			if (i < 23-p+2) {
				digits[i] = k % 2;  // элемент массива равен остатку от деления на 2
				k /= 2; // целочисленное деления на 2
				num_digits++;
			}
			else {
				k /= 2;
				num_digits++;

			}
		}
		else { // если порядок меньше 0
			if (i > 23) { 
				digits[i] = 0; // добавляем к мантиссе отсутствующий 0
				num_digits++;
			}
			else if (i == 23) { 
				digits[i] = 1; // добавляем к мантиссе отсутствующую 1
				num_digits++;
			}
			else if (i < 23) {
				digits[i] = k % 2;  // элемент массива равен остатку от деления на 2
				k /= 2; // целочисленное деления на 2
				num_digits++;
			}
		}
	}
	int shet = 0;
	for (i = 23-p-1; i >= 0; i--) {
		if (digits[i] == 1) { shet += 1; } // узнаем сколько единиц в массиве
	}
	int polam = 0;
	int result[64];
	// цикл который будет умножать все числа массива на 1010, осуществлять принцип умножения двоичных чисел в столбик и получать число в десятичной записи
	while (shet > 0) {
		for (int j = 0; j < 64; ++j) {
			digits[j] *= 1010; // умножение каждого элемента массива на 1010 (10 в двоичкой записи)
		}
		// далее идет осуществление принципа умножения в столбик
		// алгоритм переносов (каждый элемент массива должен иметь в своей записи только 1 или 0)
		for (int j = 0; j < num_digits; ++j)
		{
			if (digits[j] > 0) { // если число в массиве не 0
				digits[j + 1] += digits[j] / 10; // добавляе к след числу 10
				digits[j] %= 10; // активное становится 1
			}
		}
		// алгоритм для удаления 2
		for (int j = num_digits; j >0; --j) // этот цикл удаляет появившиеся 2 (2 = 10)
		{
			if (digits[j] == 2) { // если появилась 2
				int y = true, h = j;
				while (y) { // пока все плохо
					if (digits[h + 1] == 0) // если прошлый элемент равен 0
					{
						digits[h + 1] = 1; // то он становится 1
						digits[h] = 0; // а активный теперь 0
						y = false; // все хорошо
					}
					else // если же 1
						digits[h] = 0; // меняем активный элемент на 0
					h++; // двигаемся дальше по массиву и повторяем все
				}
			}
		}
		// далее готовые массив разделяем на целую и нецелую части
		int necel[64] = { 0 };
		int nec = 0;
		for (i = 0; i < 23 - p; i++) // отдельно нецелая часть нового числа
		{
			necel[i] = digits[i];
			nec++;
		}
		int cel[64] = { 0 };
		int c = 0;
		for (i = 23 - p; i < 64; i++) // отдельно целая часть нового числа
		{
			cel[i] = digits[i];
			c++;
		}
		int tmp = 0;
		for (i = 0; i < 64 / 2; i++) { // разворот массива
			tmp = cel[i];
			cel[i] = cel[64 - i - 1];
			cel[64 - i - 1] = tmp;
		}
		// далее из массива с целой частью с 0 достаем нужное число без лишних 0
		int number = 0, startIndex = 23; // Создаем переменную для хранения числа
		for (int i = startIndex; i < 41+p; i++) {
			number = number * 10 + cel[i]; // Умножаем число на 10 и добавляем очередной элемент массива
		}
		// Вычисляем количество цифр в числе
		int coun = 0;
		int temp = number;
		while (temp != 0) {
			coun++;
			temp /= 10;
		}
		int digit[64];
		// Заполняем массив цифрами числа
		int i = coun - 1;
		while (number != 0) {
			digit[i] = number % 10;
			number /= 10;
			i--;
		}
		int n = coun, sum = 0, po2 = 1; // n - количество бит, sum это наше десятичное число которое получится из двоичного
		for (i = n - 1; i > -1; i--) {// пошли по строке бит
			if (digit[i] == 1) {  // если i-й бит в строке = 1 ,
				sum += po2;
			}
			po2 *= 2; // подняли степень 2
		}
		result[polam] = sum; // позиция массива теперь хранит готовое 10ое число
		polam++; // сдвигаемся на +1 позицию в массиве "result"
		for (i = 64; i >= 0; i--) {
			digits[i] = necel[i]; // новая нецелая часть
		}
		shet = 0;
		for (i = 63; i >= 0; i--) {
			if (digits[i] == 1) { shet += 1; } // узнаем сколько 1 в новой записи нецелой части
		}
	}
	for (i = 0; i <= polam-1; i++) {
		printf("%d", result[i]); // вывод результата
	}
}


int main() // основная часть вывода результатов
{
	union // переменные имеют вид
	{
		unsigned count;
		float fcount;
	} a

		;

	printf("Enter the number: "); scanf("%f", &a.fcount); // ввод числа
	printf("\n1. Number in binary: %d ", Z(a.count)); null(a.fcount); printf("%d ", dec_bin(H(a.count))); Binary(M(a.count)); // число в машинном коде 
	printf("\n   1.1. Characteristics: "); null(a.fcount); printf("%d", dec_bin(H(a.count))); // характеристика
	printf("\n   1.2. Order: %d", H(a.count) - 127); // порядок 
	printf("\n   1.3. Mantissa: "); Binary(M(a.count)); // мантисса
	printf("\n2. Binary from decimal: ");
	printf("\n   2.1. Integer part in binary: "); Z_funct(a.count); cel_dec_bin(a.fcount);// целое в двоичном
	printf("\n   2.2. Float part in binary: "); Z_funct(a.count); printf("0."); necel_dec_bin(a.fcount); // дробное в двоичном
	printf("\n3. Decimal from binary: ");
	printf("\n   3.1. Integer part in decimal: "), Z_funct(a.count); printf("%d", cel_M(M(a.count), H(a.count))); // в десятичном
	printf("\n   3.2. Float part in decimal: "); Z_funct(a.count); printf("0."); necel_bin_dec(necel_M(M(a.count), H(a.count)), H(a.count)); // в двоичном
	printf("\n4. Number in decimal: "); Z_funct(a.count); printf("%d.", cel_M(M(a.count), H(a.count))); necel_bin_dec(necel_M(M(a.count), H(a.count)), H(a.count)); // число в десятичном
	printf("\n\n");
}