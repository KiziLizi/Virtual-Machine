int StackInit(Stack* stk, unsigned capacity);
int StackPush(Stack* stk, double value);
int StackPop(Stack* stk, double* value);
int StackDestroy(Stack* stk);
void StackPrint(Stack stk);
int StackVerify(Stack* stk);
void StackDump(FILE* log, Stack* stk);
void RunTests(Stack* stk);
