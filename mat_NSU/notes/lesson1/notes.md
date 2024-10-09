# Организация разработки программ на c++ [ссылка на урок](https://www.youtube.com/watch?v=uC0jJGfDxtM&list=PLlb7e2G7aSpTFea2FYxp7mFfbZW-xavhL&index=2) 

# История создания  
Изначально был транслятор в си и писал его страуструп для себя


# Философия
* совместимость с си
* множество стилей
  * Обобщённое программирование
  * Процедурное
  * ООП
  * Метапрограммирование
* Не платить за то что не используешь 
* избегать платформа зависимых особенностей

# Плюсы ЯП

* Достаточно универсален, но не всегда удобен
* Програмы с высокими требованиями к памяти и процессору
   * Игры
   * ОС
   * Драйверы
   * Сервера
   * Научные программы
   * ...

# Минусы

* Высокий порог вхождения из-за универсальности
* Долго и сложно писать (на питоне быстрее)


# Библиотеки

* Стандартные: CTR, STL
  * Много структур данных
  * работа с примитивами ОС (Файлы, потоки)
* Работа с ОС (WinAPI - Windows, Posix - Linux)
* Общего назначения (Boost, Qt)

# Компиляция

Source code (.cpp, .c, .h) ->(Preprocessor) Translation units (Условно говоря просто подстановка кода из библиотек) ->(Compiler) {*.obj files + Ext Libraries (.a, .lib, .so)} ->(Linker) Executable Dynamic Lib (.exe, .dll, .so)  
  
# Пространство имён

Using namespace std

это то от куда сборщику брать функции, к примеру если 2 человека напишут в разных бибилиотеках функцию ABOBA(), то при помощи пространства имён мы сможем указать от куда брать это функцию  
Лучше подключать только в функциях, либо во всём файле, но не в .hpp (хедерах), для избежания проблем

# Объявление переменных 
(Тип данных) (имя)
Можно сразу присвоить значения

## Типы
* int
* float
* double
* string
Все кроме string объявляются с мусором
### string
при объявлении пустой, потому-что берётся из std, и так сказть не стандарнтый, не встроеный

# Циклы

* for(при запуске; проверка каждый раз; действие в конце){ тело }
* while(Условие конца){ Тело }
* и тд...

# Функции

Объявление

\[ Возвращаемый тип ] \[ Имя ] \[ (аргументы) ]{ тело }

Вызов

\[ Имя ] \[ (Аргументы) ]

# Простейший ввод/вывод (работа с файлами)

## Открытие

* ifstream in ("file_to_in_name.txt");  
Откртие файла для чтения


* ofstream out ("file_to_out_name.txt");  
Открытие файла для записи

## Работа

string a;

in >> a;

out << a;

## Закрытие

...