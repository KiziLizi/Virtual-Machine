void ChangeValues(const void* a , const void* b, size_t size_one_elem); //функция для побайтово копирования.передаем указатели типа войд и размер одного элемента в массиве
void Sort(void* data, size_t SizeData, size_t size_one_elem, int (*CompareFunc)(const void* a, const void* b)); //функция сортировки. указатель типа войд на массив(не знаем его типа), колиество элементов массива, размер одноко элемента и компаратор(указатель на функцию)
void output(char** data, size_t SizeData);
int CompareUpForString(const void* a, const void* b);
struct Array ReadFromFile(const char* filename);
int CompareDownForString(const void* a, const void* b);
