#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(void){

    int varInt = 123456;

    string varString = "DefaultString";

    char arrChar[128] = "Long char array right there ->";

    int *ptr2int = &varInt;

    int **ptr2ptr = &ptr2int;

    int ***ptr2ptr2 = &ptr2ptr;
    while (true){

    printf("Process ID %d\n\n",GetCurrentProcessId());

    printf("varInt        (0x%p) = %d\n",&varInt, varInt);
    printf("varString     (0x%p) = %s\n",&varString, varString.c_str());
    printf("arrChar[128]  (0x%p) = %s\n\n",&arrChar, arrChar);

    printf("ptr2int       (0x%p) = 0x%p\n",&ptr2int, ptr2int);
    printf("ptr2ptr       (0x%p) = 0x%p\n",&ptr2ptr, ptr2ptr);
    printf("ptr2int       (0x%p) = 0x%p\n\n",&ptr2ptr2, ptr2ptr2);

    printf("Press ENTER to print again.\n\n");
    getchar();
    printf("--------------------------------------------------------------------");
    }





    return 0;

}





