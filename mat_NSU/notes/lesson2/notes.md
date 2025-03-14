# Сборка Программ [ссылка на урок](https://www.youtube.com/watch?v=c7CasTJKw7o&list=PLlb7e2G7aSpTFea2FYxp7mFfbZW-xavhL&index=2)


Source code (.cpp, .c, .h) ->(Preprocessor) Translation units (Условно говоря просто подстановка кода из библиотек) ->(Compiler) {*.obj files + Ext Libraries (.a, .lib, .so)} ->(Linker) Executable Dynamic Lib (.exe, .dll, .so)  
  
# Объявления и определения

* Объявления может быть много
* Определение одно

## Примеры 
* Объявление(declarations):  
int foo (int bar);
* Определения(definitions):  
int foo(int bar){
    return bar + 42;
}

Такое нужно для того чтобы к примеру если мы определяем функцию в файле 1, то для использования в файле 2 нам нужно её там объявить, НО такое редко используют.

### спец слово extern
Используется для того чтобы переменную можно было использовать в другом файле
это объявление, а определён он в другом месте

# internal linkage (внутренняя компоновка(линковка))
Это сделать так, чтобы данная переменная использовалась только в этом файле, и не забивало пространство имён

* Сделать константу (const)
* сделать static, но у неё есть ещё 4 применения 
  * статическая переменная внутри функции(при 1 посещении инициализируется, и дальше не удаляется, существует всё время работы программы)
  * внутренняя линковка
  * статическая функция класса, специфична не для объекта, а для всего класса
  * статическое поле класса  

### анонимный неймспейс

namespace **@file.cpp**  
{  
...  
}  
**using @file.cpp**  
То что выделено **жирным** компилятор допишет сам, при чём @file.cpp не пересекается с плюсовым идентефикатором, и этот @file.cpp специфичен для этого файла(единицы трансляции)

При этом использование внутри единицы трансляции можно без namespace 

# Заголовочные файлы (headers)
Просто подставляются в начало файла препроцессором  
Что включать в header
* Определение типов: struct vector {int x; int y;};
* Определение/объявление шаблонов
* Объявление функций
* Определение встроенных функций (inline)
* объявление **ТОЛЬКО** переменных
* определение констант, ...
* можно константы, и анонимный неймспес, но они будут разные(не один и та же память)
Что не стоит
* определение функций
* определение данных или использовать extern
* анонимное пространства имён(перестанут ими быть)  
так как линкер увидит одну и ту-же функцию/переменную в разных файлах, и не поймёт что использовать

## inline функция  
 это такая функция которую можно поставить в хедер, и компилятор разместит её только в 1 единице трансляции (как я понял)  
 как я понял они для хедеров  
 **ВАЖНО** чтобы в разных единицах они совпадали, лексема за лексемой, смысл лексем должен быть одинаков  
* выбирается одна из единиц трансляции
* может встраиваться в код для оптимизации

### Глобальные переменные в хидере (.h)

* если нет cpp файла для определения переменной  
использовать inline функцию которая возвращает static переменную (это переменная которая определяется при 1 проходе этой строчки, и больше не меняется, да можно использовать в синглтоне, даже со сложными конструкторами, но только с с++11)

# Комапановка с кодом не на с++ или с библиотекой компилированной другой версией языка

Нужно написать  
extern "C" перед функций и структурой

extern "C" int footbar(int value);  
extern "C"{  
    void foo();  
    void bar();  
    extern double x;  
};


* Совместимо с C Assembler
* Не меняет правил компиляции, только линковки
* Name managing
    * C: _footbar@8
    * C++: ?footbar@@YAHN@Z   

*** после собаки пишется размер

# Про объявление несколько раз

Чтобы несколько раз не подключать header несколько раз нужно использовать прекомпеляцию  
либо исполльзовать: #pragma once

# Инициализация глобальных переменных

* Между различными еденицами трансляции порядок объявления не определён  

**РЕКОМЕНДОВАНО** если нужно использовать inlinne функцию, которая объявит её в static  
но лучше не использовать  

# Компиляция

Компилятор {Исходные файлы} -o выходной файл  
либо системы сборки ***Почитай потом***

# Precompiled headers

***Почитай потом***

Позволяют ускорить сборку  

Они большие, и долго перекомпилируются, но если их не трогать то это быстро