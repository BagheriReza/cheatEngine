#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream> //for std::stringstream 
#include <string>  //for std::string

using namespace std;
// functions declaration
DWORD findingProcessId();
//DWORD findingAddress(int PointerLevel, HANDLE hProcess, DWORD offsets[], DWORD BaseAddress);
//bool readFromMemory(HANDLE hprocess);
//bool writeToMemory(HANDLE hprocess);

//Global variable
std::string nameOfGame = "AssaultCube";




int main(void){

    DWORD processID = findingProcessId();

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
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
    DWORD baseAddrress =  0x0057B0B8;
    DWORD tempPointer ;
    DWORD offset = 0x140;
    
    BOOL rpmReturn0 = ReadProcessMemory(hProcess,(LPCVOID)baseAddrress,&tempPointer,(sizeof(tempPointer)),0);
    if (rpmReturn0 == FALSE) {
	cout << "ReadProcessMemory0 failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
    
    //ptr2intRead = ptr2intRead - 34359738368 ;
    printf("The address of ptr2intRead                          (0x%p) \n", tempPointer);

    DWORD pointerAddress;
    pointerAddress = tempPointer + offset;
    printf("The address of pointerAddress                          (0x%p) \n", pointerAddress);
/*
    BOOL rpmReturn1 = ReadProcessMemory(hProcess,(LPCVOID)pointerAddress,&tempPointer,(sizeof(tempPointer)),0);
    if (rpmReturn1 == FALSE) {
	cout << "ReadProcessMemory1 failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
    
    //ptr2intRead = ptr2intRead - 34359738368 ;
    printf("The address of AddressPtr1       (0x%p) \n", tempPointer);
*/

    int intRead = 0;
    
    BOOL rpmReturn2 = ReadProcessMemory(hProcess,(LPCVOID)pointerAddress,&intRead,sizeof(intRead),0);
    if (rpmReturn2 == FALSE) {
	cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
    cout << "intRead = " << dec << intRead << endl;
    
   



    //cout << "Press ENTER to quit." ;

    //getchar();



}


// With the help of this address, we can use the name of game to find the ProcessID
DWORD findingProcessId()
{
    //Finding the game window named
	LPCTSTR LGameWindow = nameOfGame.c_str();
	HWND hGameWindow = FindWindow(NULL, LGameWindow);
	if (!hGameWindow)
	{
		cout << "AssaultCube not found. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	//cout << "Game window found." << endl;
 
	//Finding the processID of the game window
	DWORD processID = NULL;
	GetWindowThreadProcessId(hGameWindow, &processID);
	if (processID == NULL)
	{
		cout << "Getting window PID failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	//cout << "Game PID found." << endl;

    return processID;
}
