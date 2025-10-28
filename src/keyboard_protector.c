#include "keyboard_protector.h"

// 전역 변수: 후크 핸들 및 실행 상태 플래그
HHOOK g_keyboardHook = NULL;
volatile BOOL g_running = TRUE;

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
                // 프로그램 종료 신호 전송
                g_running = FALSE;
                PostQuitMessage(0);
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
    // 관리자 권한 확인 (선택사항, Windows 7 이상에서만 동작)
    // TOKEN_ELEVATION은 Windows Vista 이상에서만 지원됨
    // Windows XP 호환성을 위해 조건부로 처리
    BOOL isAdmin = FALSE;
    
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    
    // Windows Vista (6.0) 이상에서만 관리자 권한 확인
    if (GetVersionEx(&osvi) && osvi.dwMajorVersion >= 6) {
        HANDLE hToken = NULL;
        if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
            // TOKEN_INFORMATION_CLASS 20 = TokenElevation
            typedef struct _TOKEN_ELEVATION_INFO {
                DWORD TokenIsElevated;
            } TOKEN_ELEVATION_INFO;
            
            TOKEN_ELEVATION_INFO elevation;
            DWORD size = sizeof(elevation);
            
            if (GetTokenInformation(hToken, (TOKEN_INFORMATION_CLASS)20, 
                                    &elevation, size, &size)) {
                isAdmin = elevation.TokenIsElevated;
            }
            CloseHandle(hToken);
        }
    }
    // Windows XP에서는 관리자 권한 확인을 건너뜀
    // 후크는 성공하면 자동으로 실행됨

    // WH_KEYBOARD_LL (저수준 키보드 후크)를 시스템 전역에 설치
    g_keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,           // 후크 타입
        LowLevelKeyboardProc,     // 후크 프로시저
        GetModuleHandle(NULL),    // 인스턴스 핸들
        0                         // 스레드 ID (0 = 시스템 전역)
    );

    if (g_keyboardHook == NULL) {
        DWORD error = GetLastError();
        fprintf(stderr, "[오류] 키보드 후크 설치에 실패했습니다. (Error Code: %lu)\n", error);
        if (error == ERROR_ACCESS_DENIED) {
            fprintf(stderr, "[경고] 관리자 권한이 필요할 수 있습니다.\n");
        }
        exit(1);
    }
    
    printf("[성공] 키보드 보안 툴이 실행되었습니다. 모든 키 입력이 차단됩니다.\n");
    if (isAdmin) {
        printf("[정보] 관리자 권한으로 실행 중입니다.\n");
    }
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