#include <stdio.h>
#include "..\headers\compression.h"
void recordRepeatChars(unsigned char* buffer, int* p_buf, FILE* fout, int charToWrite, int summOfChars);
void recordNotRepeatChars(unsigned char* buffer, int* p_buf, FILE* fout, int charToWrite);
void writeChars(unsigned char* buffer, int* p_buf, FILE* fout, int* charToWrite, int* currChar, int* summOfChars);

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
        if (currChar == oldChar && summCurrChars < 128){
            summCurrChars += 1;
        } else {
            writeChars(buffer, &p_buf, fout, &oldChar, &currChar, &summCurrChars);
        }
        if (currChar == EOF) break;
    }
    buffer[p_buf] = '\0';
    printf("%s", buffer);
    fwrite(buffer, p_buf, sizeof(char), fout);

    fclose(fin);
    fclose(fout);
}

void writeChars(unsigned char* buffer, int* p_buf, FILE* fout, int* charToWrite, int* currChar, int* summOfChars){
    if (*summOfChars > 1) {
        recordRepeatChars(buffer, p_buf, fout, *charToWrite, *summOfChars);
    } else {
        recordNotRepeatChars(buffer, p_buf, fout, *charToWrite);
    }
    *charToWrite = *currChar;
    *summOfChars = 1;
}

void recordRepeatChars(unsigned char* buffer, int* p_buf, FILE* fout, int charToWrite, int summOfChars){
    if ((*p_buf) == 253){
        buffer[(*p_buf)++] = (unsigned char)(summOfChars + 128);
        buffer[(*p_buf)++] = (char)charToWrite;
        buffer[(*p_buf)] = '\0';
        fwrite(buffer, *p_buf, sizeof(char), fout);
        *p_buf = 0;
    } else {
        buffer[(*p_buf)++] = (unsigned char)(summOfChars + 128);
        buffer[(*p_buf)++] = (char)charToWrite;
    }
}

void recordNotRepeatChars(unsigned char* buffer, int* p_buf, FILE* fout, int charToWrite){
    if (*p_buf == 254){
        buffer[(*p_buf)++] = (char)charToWrite;
        buffer[*p_buf] = '\0';
        fwrite(buffer, *p_buf, sizeof(char), fout);
        *p_buf = 0;
    } else {
        buffer[(*p_buf)++] = (char)charToWrite;
    }
}
