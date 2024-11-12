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

// Поменять возврат из функций done

// переделать ошибки done

// переделать добавление в мапу done

#include "algorithm"
#include "fstream"
#include "iostream"
#include "map"
#include "vector"

typedef std::vector<std::string> Strings;
typedef std::map<char, Strings> Text;

Text read_from_file(const char *file_name, Text &text);

std::_Rb_tree_const_iterator<std::pair<const char, Strings>>
findLargestVector(const Text& text);

void print_Strings(const Strings &strings);

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error("incorrect number of args");
    }
    Text text;
    text = read_from_file(argv[1], text);

    Strings& strings = findLargestVector(text);

    print_Strings(strings);

  } catch (const std::exception &exception) {
    std::cout << exception.what();
  }
  return 0;
}

Text read_from_file(const char *file_name, Text &text) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error("can`t open file to read:"+std::string (file_name));
  }
  std::string str_read;
  while (std::getline(file, str_read)) {
    Text::iterator find_elem;
    find_elem = text.find(str_read[0]);
    if (find_elem == text.end()) {
      text.insert({str_read[0], {str_read}});
    } else {
      find_elem->second.push_back(str_read);
    }
  }
  if (text.empty()){
    throw std::runtime_error("file is empty");
  }

  for (std::pair<const char, Strings>& lines : text) {
    std::sort(lines.second.begin(), lines.second.end());
  }
  return text;
}

std::_Rb_tree_const_iterator<std::pair<const char, Strings>>
findLargestVector(const Text& text) {
  std::_Rb_tree_const_iterator<std::pair<const char, Strings>> maxElement =
      std::max_element(text.begin(), text.end(),
          [](const std::pair<const char, Strings> &c,
             const std::pair<const char, Strings> &b) { return c.second.size() < b.second.size(); });
  return maxElement;
}

void print_Strings(const Strings &string) {
  for (const std::string &str : string) {
    std::cout << str<<std::endl;
  }
}