/*
Цель: освоить стандартную библиотеку шаблонов (STL).
Общие требования:
    • Исходные данные из входного файла загружается в контейнер целиком.
Вся обработка и фильтрация должна выполняться в контейнере, а не на этапе
загрузки данных. • Для обращения к элементам заданного контейнера обязательно
использовать соответствующие итераторы. • При выполнении задания нужно
максимально задействовать алгоритмы STL (сортировка, поиск, обход контейнера и
т.д.). • Обработка ошибок должна быть реализована с помощью выбрасывания
исключений –объектов классов, унаследованных от std::exception (допускается
использовать std::runtime_error). • Алгоритм работы должен быть эффективен.
Работу программы проверить на файлах очень большого размера.

 typedef std::vector<std::string >	Strings;
std::map< char, Strings > Text;

Считать все строки заданного входного файла в указанную структуру данных,
сортируя строки при загрузке по первому символу. То есть все строки,
начинающиеся с буквы ‘a’, должны быть в одном векторе, с буквы ‘b’ в другом и
так далее. Векторы строк хранятся в контейнере map.

Вывести на экран (в файл) содержимое вектора с наибольшим количеством строк
*/

#include "algorithm"
#include "fstream"
#include "iostream"
#include "map"
#include "vector"

typedef std::vector<std::string> Strings;
typedef std::map<char, Strings> Text;

Text read_from_file(const std::string &file_name) {
  std::ifstream file(file_name);

  if (!file.is_open()) {
    throw std::runtime_error("can`t open file to read";
  }
  Text text;
  std::string str_read;
  while (std::getline(file, str_read)) {
    text['a'].push_back(str_read);
  }

  for (std::pair<const char, std::vector<std::basic_string<char>>> lines :text) {
    std::sort(lines.second.begin(), lines.second.end());
  }
}
