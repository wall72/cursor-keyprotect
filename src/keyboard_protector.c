#include "keyboard_protector.h"

// 전역 변수: 후크 핸들
HHOOK g_keyboardHook = NULL;

// 후크 프로시저: 키보드 입력이 발생할 때마다 호출됨
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // nCode가 0보다 작으면 시스템에서 후크를 처리해야 함
    if (nCode >= 0) {
        // 키 다운 이벤트 (키가 눌리는 순간)
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            
            // 키보드 데이터 구조체 포인터
            KBDLLHOOKSTRUCT* pKbdStruct = (KBDLLHOOKSTRUCT*)lParam;
            
            // 1. 키보드 입력 감지 및 처리
            printf("[키 감지] KeyCode: %lu\n", pKbdStruct->vkCode);

            // Esc 키 (VK_ESCAPE)는 종료를 위해 예외적으로 허용
            if (pKbdStruct->vkCode == VK_ESCAPE) {
                printf("\n[알림] Esc 키가 눌렸습니다. 후크를 해제하고 종료합니다.\n");
                // 다음 후크로 전달 (즉, 차단하지 않음)
                return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
            }

            // 2. 키 입력 차단 로직 (핵심)
            printf("[차단] 키 입력이 성공적으로 차단되었습니다. (다음 앱으로 전달되지 않음)\n");
            
            // 1을 리턴하여 메시지를 '흡수'하고 다음 애플리케이션으로 전달되는 것을 차단합니다.
            return 1; 
        }
    }
    
    // 이외의 모든 메시지는 다음 후크로 전달
    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

// 후크를 설정하는 함수
void SetHook() {
    // WH_KEYBOARD_LL (저수준 키보드 후크)를 시스템 전역에 설치
    g_keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,           // 후크 타입
        LowLevelKeyboardProc,     // 후크 프로시저
        GetModuleHandle(NULL),    // 인스턴스 핸들
        0                         // 스레드 ID (0 = 시스템 전역)
    );

    if (g_keyboardHook == NULL) {
        fprintf(stderr, "[오류] 키보드 후크 설치에 실패했습니다.\n");
        exit(1);
    }
    printf("[성공] 키보드 보안 툴이 실행되었습니다. 모든 키 입력이 차단됩니다.\n");
    printf("---------------------------------------------------------\n");
    printf("Esc 키를 눌러 종료하십시오.\n\n");
}

// 후크를 해제하는 함수
void UnsetHook() {
    if (g_keyboardHook != NULL) {
        UnhookWindowsHookEx(g_keyboardHook);
        g_keyboardHook = NULL;
    }
}