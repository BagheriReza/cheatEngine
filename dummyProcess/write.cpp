#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream> //for std::stringstream 
#include <string>  //for std::string

using namespace std;

int main(void){

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 7904);
    if (hProcess == NULL) { // Failed to get a handle
	    cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
	    system("pause");
	    return EXIT_FAILURE;
    }
/*
 //Write the intVar
    LPVOID Address = (LPVOID) 0x0000008af5bff748;
    int intRead = 987654;
    SIZE_T bytesRead = 0;

    BOOL wpmReturn = WriteProcessMemory(hProcess,Address,&intRead,sizeof(int),0);
    if (wpmReturn == FALSE) {
	cout << "WriteProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
    cout << "Overwrite successfully" ;
*/

// Reading the pointer
    LPCVOID AddressPtr = (LPCVOID) 0x0000008af5bff698;
    SIZE_T bytesRead = 0;
    uintptr_t * ptr2intRead;

    BOOL rpmReturn1 = ReadProcessMemory(hProcess,AddressPtr,&ptr2intRead,(sizeof(int)+sizeof(int)),0);
    if (rpmReturn1 == FALSE) {
	cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }

    printf("The address of varInt       (0x%p) \n", ptr2intRead);


    int intRead = 0;
    bytesRead = 0;

    LPCVOID Address = (LPCVOID) ptr2intRead;

    BOOL rpmReturn2 = ReadProcessMemory(hProcess,Address,&intRead,sizeof(int),0);
    if (rpmReturn2 == FALSE) {
	cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
    cout << "intRead = " << dec << intRead << endl;
    
   



    cout << "Press ENTER to quit." ;

    //getchar();



}
