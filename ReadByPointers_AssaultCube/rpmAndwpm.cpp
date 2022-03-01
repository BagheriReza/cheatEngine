#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream> //for std::stringstream 
#include <string>  //for std::string
#include <tlhelp32.h>


using namespace std;
// functions declaration
DWORD findingProcessId();
DWORD findingFinalPointer(int Pointerdepth, HANDLE hProcess, DWORD offsets[], DWORD BaseAddress);
bool readFromMemory(HANDLE hProcess, DWORD address);
bool writeToMemory(HANDLE hProcess, DWORD address, int value);
bool updateAmmo(HANDLE hProcess, int value);
bool updateHealthPoint(HANDLE hProcess, int value);

//Global variable
std::string nameOfGame = "AssaultCube";

// Ammo based address, offsets, target value
DWORD BaseAddress = { 0x0057B0B8 }; // Currently the playerBaseAddress
//DWORD baseAddress = 0x0;
DWORD AmmoOffsets[] = { 0x140, 0x0 };
DWORD healthPointOffsets[] = { 0xEC, 0x0 };

int ammoValue = 0;
int healthPointValue = 0;



int main(void){

    DWORD processID = findingProcessId();

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (hProcess == NULL) { // Failed to get a handle
	    cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
	    system("pause");
	    return EXIT_FAILURE;
    }
    ammoValue = 4321;
	updateAmmo(hProcess, ammoValue);

	// Healthpoint Read Update
	healthPointValue = 1234;
    updateHealthPoint(hProcess, healthPointValue);

   
   

}

bool updateAmmo(HANDLE hProcess, int value)
{
    // Ammo Value read and update
	DWORD finalPointer = findingFinalPointer(1, hProcess, AmmoOffsets, BaseAddress);

	printf("Reading Ammo Value .... \n");
    readFromMemory(hProcess, finalPointer);

	printf("Updating Ammo Value .... \n");
	writeToMemory(hProcess, finalPointer,value);
    
	printf("Reading Ammo Value .... \n");
	readFromMemory(hProcess, finalPointer);

	printf("\n\n");
}

bool updateHealthPoint(HANDLE hProcess, int value)
{
	DWORD finalPointer = findingFinalPointer(1, hProcess, healthPointOffsets, BaseAddress);
    printf("Reading Health Point Value .... \n");
    readFromMemory(hProcess, finalPointer);
	
	printf("Updating Health Point Value .... \n");
    writeToMemory(hProcess, finalPointer,value);
    
	printf("Reading Health Point Value .... \n");
	readFromMemory(hProcess, finalPointer);

	printf("\n\n");
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

//Find the final pointer address 
DWORD findingFinalPointer(int Pointerdepth, HANDLE hProcess, DWORD offsets[], DWORD BaseAddress)
{
	DWORD pointerAddress;
	DWORD tempPointer;
 
	for (int i = 0; i < Pointerdepth; i++)
	{
		if (i == 0)
        {
            ReadProcessMemory(hProcess, (LPCVOID)BaseAddress, &tempPointer, sizeof(tempPointer), 0);
            pointerAddress = tempPointer + offsets[i];
			//printf("The address of final address i=0 %p\n", pointerAddress);

        } else {
            ReadProcessMemory(hProcess,(LPCVOID) pointerAddress,&tempPointer,sizeof(tempPointer), 0);
            pointerAddress = tempPointer + offsets[i];
        }
        //printf("The value of i:%d \n",i);
	
	}
	return pointerAddress;
}

bool readFromMemory(HANDLE hProcess, DWORD address)
{
    int rAmmoValue = -1;
    BOOL rpmReturn2 = ReadProcessMemory(hProcess,(LPCVOID)address,&rAmmoValue,sizeof(rAmmoValue),0);
    if (rpmReturn2 == FALSE) {
	cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
    printf("The value is equal to %d \n",rAmmoValue);
    
}

bool writeToMemory(HANDLE hProcess, DWORD address, int value)
{
    BOOL rpmReturn2 = WriteProcessMemory(hProcess,(LPVOID)address,&value,sizeof(value),0);
    if (rpmReturn2 == FALSE) {
	cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
	system("pause");
	return EXIT_FAILURE;
    }
  
    printf("The value updated to %d \n",value);
}
