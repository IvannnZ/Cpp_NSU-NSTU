#include <cstring>
#include <iostream>
#include <stdio.h>

#define SIZE_BUFF_TO_READ 512

int Hash(std::string data) {
  const size_t len = data.length();
  int hash = 0;

  for (int i = 0; i < len; i++) {
    hash += data[i] * i;
  }
  return hash;
}


void print_from_bin_file(FILE *file_read, std::string file_name) {
  unsigned char len_line;
  char hash = Hash(file_name);
  while (fread(&len_line, sizeof(unsigned char), 1, file_read)) {
    char *buffer = new char[len_line];

    fread(buffer, sizeof(char), len_line, file_read);
    buffer[len_line] = '\0';
    for (int i = 0; i < len_line-1; i++) {
      buffer[i] = buffer[i] ^ hash;
    }
    std::cout << buffer;
    delete[] buffer;
  }
}
void convert_from_file_to_bin_file(FILE *finput, FILE *foutput,
                                   std::string file_name) {
  long ptr_to_start_line = ftell(finput);
  unsigned char len_line = 0;
  int c;
  char hash = Hash(std::move(file_name));
  char buffer[SIZE_BUFF_TO_READ];

  while (fgets(buffer, SIZE_BUFF_TO_READ, finput)) {
    while (buffer[strlen(buffer) - 1] != '\n' && !feof(finput)) {
      fgets(buffer, SIZE_BUFF_TO_READ, finput);
    }
    len_line = (unsigned char)(ftell(finput) - ptr_to_start_line);
    fwrite(&len_line, sizeof(unsigned char), 1, foutput);

    fseek(finput, ptr_to_start_line, SEEK_SET);
    fgets(buffer, SIZE_BUFF_TO_READ, finput);
    for (int i = 0; i < SIZE_BUFF_TO_READ; i++) {
      if (buffer[i] != '\n') {
        buffer[i] = buffer[i] ^ hash;
      } else {
        break;
      }
    }
    fputs(buffer, foutput);
    while (buffer[strlen(buffer) - 1] != '\n' && !feof(finput)) {
      fgets(buffer, SIZE_BUFF_TO_READ, finput);
      for (int i = 0; i < SIZE_BUFF_TO_READ; i++) {
        if (buffer[i] != '\n') {
          buffer[i] = buffer[i] ^ hash;
        } else {
          break;
        }
      }
      fputs(buffer, foutput);
    }
    ptr_to_start_line = ftell(finput);
  }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Error no file name in argument\n";
        return 42;
    }

    std::string input_filename = argv[1];
    FILE *finput = fopen(input_filename.c_str(), "r");
    if (finput == NULL) {
        std::cout << "Error can't open input file\n";
        return 52;
    }

    if (input_filename.length() < 4) {
        std::cout << "Incorrect file name\n";
        return 94;
    }
    std::string output_filename = argv[1];
    output_filename.erase(output_filename.length() - 4, 4);
    output_filename += ".bin";

    FILE *foutput = fopen(output_filename.c_str(), "wb");
    if (foutput == NULL) {
        std::cout << "Error can't open output file\n";
        fclose(finput);
        return 53;
    }

    convert_from_file_to_bin_file(finput, foutput, std::string(argv[1]));
    fclose(finput);
    fclose(foutput);

    FILE *file_read = fopen(output_filename.c_str(), "rb");

    print_from_bin_file(file_read, std::string(argv[1]));
    fclose(file_read);

    return 0;
}

