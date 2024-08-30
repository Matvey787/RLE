#include <stdio.h>
#include <ctype.h>
#include "..\headers\decompression.h"

void decompress(FILE* cFile, FILE* deccFile){
    if (cFile == NULL)  {printf("compresed file error\n"); return;}
    if (deccFile == NULL) {printf("decompressed file error\n"); return;}
    unsigned char buffer[256] = {};
    int p_buff = 0;
    int currChar = 0;
    if (!feof(cFile)){
        currChar = fgetc(cFile);
    }
    while (1){
        if (currChar == EOF) break;
        if (currChar > 128){
            int repit = currChar - 128;
            currChar = fgetc(cFile);
            for (int i = 0; i < repit; i++)
                buffer[p_buff++] = (unsigned char)currChar;
        } else {
            buffer[p_buff++] = (unsigned char)currChar;
        }
        currChar = fgetc(cFile);
    }
    buffer[p_buff] = '\0';
    fwrite(buffer, p_buff, sizeof(char), deccFile);
    //fwrite(buffer, buffer[0], sizeof(char), deccFile);
}
