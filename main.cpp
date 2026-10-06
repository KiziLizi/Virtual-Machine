#include <stdio.h>
#include "bublsort.h"
#include "stack.h"

const char* FILENAME = "comand.txt";

struct Array
{
    char* start_buffer;
    char** start_index;
    int count_string;
};

struct Stack
{
    unsigned long long canary1;
    size_t size;
    unsigned capacity;
    double* data;
    int error;
    unsigned long long canary2;  
};

int main()
{
    char* string = {};
    int number = 0;

    FILE* comand = fopen("comand.txt", "r");
    FILE* bytecode = fopen("bytecode.txt", "w");

    fgets(string, 20, comand);

    struct Array data = ReadFromFile(FILENAME);

    int i = 0;
    int code_number = 0;
    char* ptr = data.start_buffer; 

    printf("%d", data.count_string);

    while (i < data.count_string) 
    {
        fscanf(comand, "%s%d", string, &number);
        printf("%s%d", string, number);

        if (string == "PUSH") code_number = 1;
        if (string == "ADD")  code_number = 2;
        if (string == "SUB")  code_number = 3;
        if (string == "DIV")  code_number = 4;
        if (string == "OUT")  code_number = 5;
        if (string == "HTL")  code_number = 0;

        i++;
        ptr++;

        fprintf(bytecode, "%d %d\n", code_number, number);
    }
   
    fclose(comand);
    fclose(bytecode);

    return 0;
}
