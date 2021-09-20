#include <psp2/kernel/processmgr.h>

#include <iostream>
using namespace std;

#include <CApp.h>

int main(int argc, char *argv[]) {
	cout << "Entering SnakeCPP Vita" << endl;

	CApp theApp;
	
	cout << "Exiting  SnakeCPP Vita" << endl;
	
	sceKernelExitProcess(0);
    return 0;
}
