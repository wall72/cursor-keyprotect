#include "keyboard_protector.h"

int main() {
    // 1. 후크 설치
    SetHook();

    // 2. 메시지 루프
    MSG msg;
    // WM_QUIT 메시지를 받을 때까지 루프를 계속 돌면서 후크가 동작하도록 합니다.
    BOOL bRet;
    int exitCode = 0;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        // GetMessage가 -1을 반환하면 오류 발생
        if (bRet == -1) {
            fprintf(stderr, "[오류] 메시지 루프 오류가 발생했습니다.\n");
            exitCode = 1;
            break;
        }
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
        // Esc 키는 LowLevelKeyboardProc에서 처리되므로, WM_QUIT을 명시적으로 체크할 필요는 없지만
        // 일반적으로 메시지 루프의 기본적인 형태를 유지합니다.
    }

    // 3. 후크 해제 및 종료
    UnsetHook();
    printf("[종료] 키보드 보안 툴이 정상적으로 종료되었습니다.\n");
    return exitCode;
}