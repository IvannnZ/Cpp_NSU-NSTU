#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

void print_from_bin_file(FILE *file_read) {
    unsigned char len_line;

    while (fread(&len_line, sizeof(unsigned char), 1, file_read) == 1) {
        unsigned char c;
        for (int i = 0; i < (int)len_line; i++) {
            if (fread(&c, sizeof(unsigned char), 1, file_read) == 1) {
                cout << c;
            } else {
                return;
            }
        }
    }
}


void convert_from_file_to_bin_file(FILE *finput, FILE *foutput) {
    long ptr_to_start_line = ftell(finput);
    int len_line = 0;
    int c;
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
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Error no file name in argument\n";
        return 42;
    }

    string input_filename = argv[1];
    FILE *finput = fopen(input_filename.c_str(), "r");
    if (finput == NULL) {
        cout << "Error can't open input file\n";
        return 52;
    }

    if (input_filename.length() < 4) {
        cout << "Incorrect file name\n";
        return 94;
    }
    string output_filename = argv[1];
    output_filename.erase(output_filename.length() - 4, 4);
    output_filename += ".bin";

    FILE *foutput = fopen(output_filename.c_str(), "wb");
    if (foutput == NULL) {
        cout << "Error can't open output file\n";
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
