#include <stdio.h>
#include "..\headers\compression.h"
#include "..\headers\decompression.h"
int main(){
    const char* fin_name = "C:\\Users\\admin\\Desktop\\C programs\\RLE\\txt_files\\fin.txt";
    const char* fout_name = "C:\\Users\\admin\\Desktop\\C programs\\RLE\\txt_files\\fout.txt";
    FILE *fin = fopen(fin_name, "r");
    FILE *fout = fopen(fout_name, "wb");

    compress(fin, fout);

    const char* deccFile_name = "C:\\Users\\admin\\Desktop\\C programs\\RLE\\txt_files\\decompressFile.txt";
    const char* cFile_name = "C:\\Users\\admin\\Desktop\\C programs\\RLE\\txt_files\\fout.txt";
    FILE *deccFile = fopen(deccFile_name, "w");
    FILE *cFile = fopen(cFile_name, "rb");

    decompress(cFile, deccFile);
    fclose(cFile);
    fclose(deccFile);
}
