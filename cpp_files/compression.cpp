#include <stdio.h>
#include "..\headers\compression.h"
void compress(FILE* fin, FILE* fout){

    if (fin == NULL)  {printf("error fout\n"); return;}
    if (fout == NULL) {printf("error fin\n"); return;}

    unsigned char buffer[256] = {};
    int p_buf = 0;
    int currChar = 0;
    int oldChar = 0;
    int summCurrChars = 0;

    if (!feof(fin)){
        currChar = fgetc(fin);

        summCurrChars = 1;
        oldChar = currChar;
    }

    while (1){
        currChar = fgetc(fin);
        if (currChar == oldChar){
            summCurrChars += 1;
        } else {
            if (summCurrChars > 1  || summCurrChars == 127) {
                if (p_buf == 253){
                    buffer[p_buf++] = (unsigned char)(summCurrChars + 128);
                    buffer[p_buf++] = (char)oldChar;
                    buffer[p_buf] = '\0';
                    fwrite(buffer, p_buf, sizeof(char), fout);
                    p_buf = 0;
                } else {
                    buffer[p_buf++] = (unsigned char)(summCurrChars + 128);
                    buffer[p_buf++] = (char)oldChar;
                }
            } else {
                if (p_buf == 254){
                    buffer[p_buf++] = (char)oldChar;
                    buffer[p_buf] = '\0';
                    fwrite(buffer, p_buf, sizeof(char), fout);
                    p_buf = 0;
                } else {
                    buffer[p_buf++] = (char)oldChar;
                }
            }
            oldChar = currChar;
            summCurrChars = 1;
            if (currChar == EOF) break;
        }
    }
    buffer[p_buf] = '\0';
    fwrite(buffer, p_buf, sizeof(char), fout);

    fclose(fin);
    fclose(fout);
}
