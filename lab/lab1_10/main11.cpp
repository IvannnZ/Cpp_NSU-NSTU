#include <cstring>
#include <iostream>
#include <stdio.h>

#define SIZE_BUFF_TO_READ 512

int hash (std::string data){
    
    const size_t len = data.length();
    int hash = 0;

    for (int i = 0; i < len; i++){
        hash += data[i] * i;
    }

    return hash;
}

void print_from_bin_file(FILE *file_read) {
    unsigned char len_line;

    while (fread(&len_line, sizeof(unsigned char), 1, file_read) == 1) {
        unsigned char c;
        for (int i = 0; i < (int)len_line; i++) {
            if (fread(&c, sizeof(unsigned char), 1, file_read) == 1) {
                std::cout << c;
            } else {
                return;
            }
        }
    }
}

void convert_from_file_to_bin_file(FILE *finput, FILE *foutput, char hash) {
  long ptr_to_start_line = ftell(finput);
  int len_line = 0;
  int c;

  char buffer[SIZE_BUFF_TO_READ];

  while (fgets(buffer, SIZE_BUFF_TO_READ, finput)) {
    for (int i = 0; true; i++) {
      if (buffer[i] != '\n') {
        buffer[i] = buffer[i] ^ hash;
      } else {
        fputs(buffer, foutput);
        break;
      }
    }
    while (buffer[strlen(buffer) - 1] != '\n' && !feof(finput)) {
      fgets(buffer, SIZE_BUFF_TO_READ, finput);
      for (int i = 0; true; i++) {
        if (buffer[i] != '\n') {
          buffer[i] = buffer[i] ^ hash;
        } else {
          fputs(buffer, foutput);
          break;
        }
      }
    }
  }

  /*


    while ((c = getc(finput)) != EOF) {
        len_line++;

        if (c == '\n' || c == EOF) {
            fseek(finput, ptr_to_start_line, SEEK_SET);
            unsigned char len_line_byte = (unsigned char)len_line;
            fwrite(&len_line_byte, sizeof(unsigned char), 1, foutput);
            for (int i = 0; i < len_line; i++) {
                if (c == EOF){
                    return;
                }
                c = getc(finput);
                //cout<<c<<" ";
                fwrite(&c, sizeof(char), 1, foutput);
            }
            //cout<<endl;

            ptr_to_start_line = ftell(finput);
            len_line = 0;
        }
    }


    */
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

    convert_from_file_to_bin_file(finput, foutput);
    fclose(finput);
    fclose(foutput);

    FILE *file_read = fopen(output_filename.c_str(), "rb");

    print_from_bin_file(file_read);
    fclose(file_read);

    return 0;
}

