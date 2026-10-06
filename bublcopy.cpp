#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

const char* FILENAME = "Onegin.txt";

struct Array
{
    char* start_buffer;
    char** start_index;
    int count_string;
};

struct StringSize 
{
    size_t string,  //длина строки
    

      
};

void ChangeValues(const void* a , const void* b, size_t size_one_elem); //функция для побайтово копирования.передаем указатели типа войд и размер одного элемента в массиве
void Sort(void* data, size_t SizeData, size_t size_one_elem, int (*CompareFunc)(const void* a, const void* b)); //функция сортировки. указатель типа войд на массив(не знаем его типа), колиество элементов массива, размер одноко элемента и компаратор(указатель на функцию)
void output(char** data, size_t SizeData);
int CompareUpForString(const void* a, const void* b);
struct Array ReadFromFile(const char* filename);
int CompareDownForString(const void* a, const void* b);
struct StringSize My_Strlen(const char* ptr1, size_t count_string);
//int My_Puts(const char* str1);

// TODO: начать онегина (разобраться с разбиением файла на строки)

int main()
{
    // printf("pizda\n");
    struct Array data = ReadFromFile(FILENAME);
    struct StringSize line = My_Strlen(struct Array);
    printf("string1 = [%lu]", line.string);
    // puts(data.start_buffer);
//    printf("hui\n");

    // puts(data[0]);
    // puts(data[1]);

    // printf("data[0] = [%p]\n", &data[0]);
    // printf("data[1] = [%p]\n", &data[1]);

    size_t SizeData = data.count_string; //подсчет количества элементов
    // printf("siski\n");

    // printf("SizeData = [%lu]\n", SizeData);
    output(data.start_index, SizeData);
    // printf("sosok\n");
    Sort(data.start_index, SizeData, sizeof(char*), &CompareUpForString);
    output(data.start_index, SizeData);
    Sort(data.start_index, SizeData, sizeof(char*), &CompareDownForString);
    output(data.start_index, SizeData);

    //printf("SizeOfVoid = [%ld]", sizeof(void))
    free(data.start_buffer); 
    free(data.start_index); //отчистка буфера
    return 0;
}

// TODO Changevalues под любой тип данных

void ChangeValues(const void* a, const void* b, size_t size_one_elem)
{
    assert(a != NULL);
    assert(b != NULL);

   char* elem_1 = (char*) a; //приведение типа для побайтового копирования
   char* elem_2 = (char*) b; //приведение типа
    
   for (int i = 0; i < size_one_elem; i++) //копируем до тех пор, пока не дойдем до конца размера элемента в массиве
   {
        char temp = elem_1[i]; // temp - буферная переменная
        elem_1[i] = elem_2[i];
        elem_2[i] = temp;
   }

}


// TODO Sort обратно void*

void Sort(void* data, size_t SizeData, size_t size_one_elem, int (*CompareFunc)(const void* a, const void* b))
{
    assert(data != NULL);

    char** get_data = (char**) data;
    assert(get_data != NULL);
    // printf("get_data = [%p]\n", get_data); //приведение типа для произведение математических операций при подсчете адреса

    for (size_t n = SizeData; n > 0; n--) 
    {
        for (int i = 0; i < (n - 1); i++)
        {
           if (CompareFunc(get_data + i, get_data + (i + 1)) > 0) //в аргументах функции указаны адреса на переменные в массиве
           {
                //printf("adres = [%p]\n", *(get_data + i));
                ChangeValues(get_data + i, get_data + ( i + 1), size_one_elem); //в аргументах указаны адреса элементов в массиве и размер одного элемента
           }
           
           
           }
        }
    }

    //data[i] = *(data + i) = *(i + data) = i[data] 


void output(char** data, size_t SizeData)
{
    //printf("sosi\n");
    assert(data != NULL);
    // char LIZA[] = "01234567890";
    // char u = LIZA[i] ;   //My_Puts(data.start_buffer);
    char* curent_string = data[0];
    // printf("data = %s\n", data);
    // printf("data[0] = %c\n", data[0]);

    for (int i = 0; i < SizeData; i++)
    { 
        int n = 0;
        
        while (curent_string[n + 1] != '\0')
        {
            printf("%c", curent_string[n++]);
        }

        curent_string = data[i + 1];
        putchar('\n');
   // printf("%s\n", data[i]);
    }

    // fflush(stdout);

    printf("\n");
    fflush(stdout);
}

// int My_Puts(char* str1)
// {
//     int i = 0;

//     while (putchar(str1[i]) != '\0')
//     {
//         i++;
//     }

//     putchar('\n');

//     return i;
// }
/*int CompareUp(int a, int b)
{
    if (a < b) return -1;
    if (a > b) return 1;
    if (a == b) return 0;
} */

// TODO компаратор для строк

/*int CompareUpForInt(const void* a, const void* b)
{
    int value_a = *(int*) a; //приведение типа для мат.операций
    int value_b = *(int*) b;

    if (value_a < value_b)  return -1; //сравнение и вывод значения в цикл, чтоб знать нужно ли осуществлять смену элементов в массиве
    if (value_a > value_b)  return 1;
    if (value_a == value_b) return 0;
}*/

// TODO: сделать сравнение строк не только по первому символу

int CompareUpForString(const void* a, const void* b) // нам нужно сделать так, чтоб, если слова начинались с одной буквы, программа уходтла в начало
                                                                                        // и проверяла уже следующую букву
{
    assert(a != NULL);
    assert(b != NULL);

    char* value_a = *(char **) a; //приведение типа для мат.операций
    char* value_b = *(char **) b;

    // printf("value_a = [%c], code = [%d]\n", *value_a, value_a);
    // printf("value_b = [%c], code = [%d]\n", *value_b, value_b);

    assert(value_a != NULL);
    assert(value_b != NULL);

    // char* get_data = (char*) data;

    // printf("a = [%s]\n", (char*) a);

    //  printf("data[0] = [%p]\n", a);
    //  printf("data[1] = [%p]\n", b);
  
    if (*value_a < *value_b)  return -1; //сравнение и вывод значения в цикл, чтоб знать нужно ли осуществлять смену элементов в массиве
    if (*value_a > *value_b)  return 1;

    // printf("value_a = [%c], code = [%d]\n", *value_a, value_a);
    // printf("value_b = [%c], code = [%d]\n", *value_b, value_b);

    int i = 1;
    while(*value_a == *value_b && *value_a != '\0' && *value_b != '\0')
    { 
        value_a = *(char **) a + i;
        value_b = *(char **) b + i;
        i++;

        // printf("value_a = [%c], code = [%d]\n", *value_a, value_a);
        // printf("value_b = [%c], code = [%d]\n", *value_b, value_b);

        if (*value_a < *value_b)  return -1; //сравнение и вывод значения в цикл, чтоб знать нужно ли осуществлять смену элементов в массиве
        if (*value_a > *value_b)  return 1;
    }

    return 0;
}

int CompareDownForString(const void* a, const void* b)
{
    // printf("piska\n");
    assert(a != NULL);
    assert(b != NULL);

    char* value_a = *(char **) a; //приведение типа для мат.операций
    char* value_b = *(char **) b;

    assert(value_a != NULL);
    assert(value_b != NULL);

    size_t string_size_a = 0;
    char* ptr_a = value_a;

    int i = 1; 

    while (ptr_a[i] != '\0')
    {
        i++;
        string_size_a++;
    }

    value_a = ptr_a + string_size_a;

    char* ptr_b = value_b;
    size_t string_size_b = 0;

    int k = 1; 

    while (ptr_b[k] != '\0')
    {
        k++;
        string_size_b++;
    }
    
    value_b = ptr_b + string_size_b;

    if (*value_a < *value_b)  return -1; //сравнение и вывод значения в цикл, чтоб знать нужно ли осуществлять смену элементов в массиве
    if (*value_a > *value_b)  return 1;

    int n = 1;
    while(*value_a == *value_b && *value_a != '\0' && *value_b != '\0')
    { 
        value_a = *(char **) a + string_size_a - n;
        value_b = *(char **) b + string_size_b - n;
        n++;

        // printf("value_a = [%c], code = [%d]\n", *value_a, value_a);
        // printf("value_b = [%c], code = [%d]\n", *value_b, value_b);

        if (*value_a < *value_b)  return -1; //сравнение и вывод значения в цикл, чтоб знать нужно ли осуществлять смену элементов в массиве
        if (*value_a > *value_b)  return 1;
    }

    return 0;

}

// TODO: вернуть структурку  
struct Array ReadFromFile(const char* filename)
{
    FILE *file = fopen(filename, "r");

    assert(file != NULL); //ПРОВЕРКА!

    //определяем размер файла
    fseek(file, 0, SEEK_END); //перемещаем позицию в конец файла
                            //0 - Количество байт для смещения, относительно некоторого положения указателя
                            //SEEK_END - Позиция указателя, относительно которой будет выполняться смещение
                        
    // TODO: bit -> byte
    long size_byte = ftell(file); // размер файла в байтах
    //  printf("size_byte = [%ld]\n", size_byte); 
    //  fflush(stdout);
    char* buffer = (char*) calloc(size_byte + 2, sizeof(char));  //выделяем память под буфер
                                                                // +1 - нулевой байт в конце буфера 
    assert(buffer != NULL); //ПРОВЕРКА!
    // printf("buffer = [%p]\n", buffer);

    rewind(file);

    size_t result = fread(buffer + 1, 1, size_byte, file); //считываем файл в буфер
                                                        //buffer - указатель на блок памяти, размер которого должен быть не меньше size_bit 
                                                        //1 - размер одного считываемого элемента
    //puts(buffer);
    fclose(file); //закрытие файла

    char* start_buffer = buffer;
    // printf("start_buffer = [%p]\n", start_buffer);
    size_t count_string = 0;
    char* ptr1 = buffer;
    // printf("ptr1 = [%d\p]\n", ptr1);

    while ((ptr1 = strchr(buffer + 1, '\n')) && (ptr1 <= buffer + size_byte + 1))
    {
        *ptr1 = '\0';
        count_string++;
        buffer = ptr1 + 1;
    }

    // puts(buffer);

    // printf("count_string = [%lu]\n", count_string);
    
    buffer = start_buffer; 
    char** index = (char**)calloc(count_string + 10, sizeof(char*));
    // printf("index = [%p]\n", index);
    int i = 0;

    index[0] = buffer;
    // printf("index[0] = [%p]\n", index[0]);

    char* ptr2 = buffer; 
    // printf("ptr2 = [%p]\n", ptr2);
    char** start_index = index;
    // printf("start_index = [%p]\n", start_index);
 
    // printf("%p", strchr(start_buffer, '\0'));
    // fflush(stdout);

    while (ptr2 = strchr(buffer + 1, '\0'))
    {
        // TODO: /n - конец строки
        //  printf("ptr2 = [%d]\n", *(ptr2 - 1));
        index[++i] = ptr2 + 1;
        // puts(buffer);
        buffer = ptr2 + 1;

        if (ptr2 >= start_buffer + size_byte)
        {
            break;
        }
    }
    // printf("index[1] = [%p]\n", index[1]);
    struct Array arr = {start_buffer, start_index, count_string};

    return arr;
}

struct My_Strlen(const char ptr1, size_t count_string)
{
    size_t i = 0;
    str1 = buffer;

    while(ptr2 != count_string)
    {
        if (str1[i] != '\0')
        {
            i = i + 1;
        }
        else
        {
            ptr2++;
        }
    }

    
    struct StringSize size = {string}

    return ;
}