#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const unsigned long long canary1 = 69;
const unsigned long long canary2 = 96;
const unsigned long long canary3 = 6677;
const unsigned long long canary4 = 7766;

#define STKDEBUG

#ifdef STKDEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...)
#endif

enum CHECK 
{
    BADPOINTER    = 1,
    GOODPOINTER   = 2, 
    INCORECTSIZE  = 3, 
    ALLOK         = 4,
    BADCANARY     = 5
};

struct Stack
{
    //ON_DEBUG (const char* file, int line, const char* function);
    unsigned long long canary1;
    size_t size;
    unsigned capacity;
    double* data;
    int error;
    unsigned long long canary2;  
};

int StackInit(Stack* stk, unsigned capacity);
int StackPush(Stack* stk, double value);
int StackPop(Stack* stk, double* value);
int StackDestroy(Stack* stk);
void StackPrint(Stack stk);
int StackVerify(Stack* stk);
void StackDump(FILE* log, Stack* stk);
void RunTests(Stack* stk);

int main()
{
    Stack stk = {};

    stk.canary1 = 69;
    stk.canary2 = 96;

    double a = 1.11, b = 2.22, c = 3.33, d = 4.44, e = 5.55, l = 6.66;

    StackInit(&stk, 5);
    StackPrint(stk);

    double value = 0;

    printf("Push something:\n");

    // StackPush(&stk, a);
    //  StackPush(&stk, b);
    //   StackPush(&stk, c);
    //    StackPush(&stk, d);
    //     StackPush(&stk, e);
    //      StackPush(&stk, l);

    RunTests(&stk);

    StackPrint(stk);
    //StackPop(&stk, &value);

    //StackPrint(stk);
    StackDestroy(&stk);
}

int StackInit (Stack* stk, unsigned capacity) //какое возвращающее значение ?
{
    //enum CHECK eq = BADPOINTER;
    assert(stk != NULL);

    stk->data = (double*) calloc(capacity, sizeof(double));
    assert(stk->data != NULL);

    // double canary3 = 2807;
    // double canary4 = 2009;

    stk->data = stk->data++;

    stk->capacity = capacity;

    // stk->data[0] = 6677;
    // stk->data[stk->capacity + 1] = 7766;

   // printf("%d", stk->data[stk->capacity]);

    if (StackVerify(stk) != 0) return 1;
    if (stk->error == INCORECTSIZE) (abort());

    // if (stk != NULL)
    // {
    //     return GOODPOINTER;
    // }
    // else if (stk == NULL) 
    // {
    //     return BADPOINTER;
    // }

    return ALLOK;
}

int StackPush(Stack* stk, double value) 
{
    //printf("pizda\n");
    assert(stk != NULL);
    //printf("pizda\n");

    // scanf("%lg", &value);

    //printf("value = [%lg]\n", value);
    // realloc (if) => отдельная функция //вызов функции, которая будет увеличивать выделенную память

    if (stk->size == stk->capacity) 
    {
        // printf("pizda\n");
        size_t new_capacity = stk->capacity * 2;
        // printf("%u", stk->capacity);
        // printf("pizda\n");
        stk->data = (double*) realloc(stk->data, new_capacity * sizeof(double));
        assert(stk->data != NULL);  
        stk->capacity = new_capacity;
        

        // printf("pizda\n");
        //stk->size++;  
        //printf("pizda\n");
    }

    stk->data[stk->size++] = value;

    if (StackVerify(stk) != 0) return 1;
    if (stk->error == INCORECTSIZE) (abort());

    return ALLOK;
}

// Stack stk;
// stk.a

// Stack* stk;
// (*stk).a = stk -> a

int StackPop(Stack* stk, double* value)
{
    assert(stk != NULL);
    assert(value != NULL);

    // printf("value = [%lg]\n", *value);

    if (stk->size == stk->capacity / 4) 
    {
        size_t new_capacity = stk->capacity / 2;
        //printf("pizda");
        stk->data = (double*) realloc (stk->data, new_capacity * sizeof(double));
        assert(stk->data != NULL);
        //printf("pizda");
        stk->size--;  
    }
    
    printf("stk->size = [%lu]\n", stk->size);
    *value = stk->data[--stk->size]; 
    printf("value = [%lg]\n", *value);

    if (StackVerify(stk) != 0) return 1;
    if (stk->error == INCORECTSIZE) (abort());

    return ALLOK;
}

int StackDestroy(Stack* stk)
{
    if (StackVerify(stk) != 0) return 1;
    if (stk->error == INCORECTSIZE) (abort());

    assert(stk != NULL);

    free(stk->data);
    printf("Stack free\n");

    return ALLOK;
}

void StackPrint(Stack stk)
{
    for (unsigned i = 0; i < stk.size; i++)
    {
        printf("%lg ", stk.data[i]); 
    }

    printf("\n");
}

int StackVerify(Stack* stk)
{
    if (stk->size > stk->capacity) 
    {
        printf("size = [%lu]\n", stk->size);
        printf("capacity = [%zu]\n", stk->capacity);
        stk->error = INCORECTSIZE;
        return 1;
    }

    if (stk->capacity == 0) 
    {
        stk->error = INCORECTSIZE;
        return 1;
    }
    if (stk->data == NULL) 
    {
        stk->error = BADPOINTER;
        return 1;
    }

    if (stk == NULL)  
    {
        stk->error = BADPOINTER;
        return 1;
    }

    if ((stk->canary1 != canary1) || (stk->canary2 != canary2)) 
    {
        stk->error = BADCANARY;
        return 1;
    }
   // if ((stk->data[0] != canary3) && (stk->data[stk->capacity] != canary4)) return BADCANARY;
         
    else 
    {
        stk->error = ALLOK;
        return 0;
    }
}                                                

void StackDump(FILE* log, Stack* stk) // error log
{
    // printf("log = [%p]\n", log);
    // printf("stack = [%p]\n", stack);

    
    fprintf(log, "file: %s\n"
            "function: %s\n"
            "line: %d\n"
            "struct: %p\n"
            "data: %p\n"
            "capacity: %zu\n"
            "size:  %lu\n", __FILE__, __FUNCTION__ , __LINE__, stk, stk->data, stk->capacity, stk->size);
    fflush(log);

    fprintf(log, "{\n");  

    for (int i = 0; i < stk->capacity; i++)
    {
        fprintf(log, "[%d] = %lg\n", i, stk->data[i]);
    }

    fflush(log);
    fprintf(log, "}\n");
            
    fprintf(log, "--------------------------------------------\n");
    fflush(log);
}

void RunTests(Stack* stk)
{
    double i = 0, n = 0;

    FILE* log = fopen("pizdalods.log", "w"); //"a" - дополнение 

    for (i = 0; i < stk->capacity; i++)
    {
        StackPush(stk, i);
        StackDump(log, stk);
    }

    StackPrint(*stk);

    for (n = stk->capacity; n > 1; n--)
    {
        StackPop(stk, &n);
        StackDump(log, stk);
    }

    StackPrint(*stk);

    fclose(log);
}

