#ifndef KEYBOARD_PROTECTOR_H
#define KEYBOARD_PROTECTOR_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 키 코드를 솔트와 키를 사용하여 암호화합니다.
 * @param key_code 암호화할 키 코드
 * @param salt 암호화에 사용할 솔트 값 (매번 다르게 생성 권장)
 * @return unsigned int 암호화된 키 코드
 */
unsigned int encrypt_keycode_with_salt(unsigned int key_code, unsigned int salt);

/**
 * @brief 암호화된 키 코드를 솔트와 키를 사용하여 복호화합니다.
 * @param encrypted_code 복호화할 암호화된 키 코드
 * @param salt 암호화에 사용했던 동일한 솔트 값
 * @return unsigned int 복호화된 (원래의) 키 코드
 */
unsigned int decrypt_keycode_with_salt(unsigned int encrypted_code, unsigned int salt);

/**
 * @brief 키보드 입력이 발생할 때마다 호출되는 저수준 키보드 후크 프로시저
 * @param nCode 후크 프로시저가 메시지를 처리할지 다음 프로시저로 전달할지 결정하는 코드
 * @param wParam 메시지 타입 (WM_KEYDOWN, WM_KEYUP, WM_SYSKEYDOWN, WM_SYSKEYUP)
 * @param lParam KBDLLHOOKSTRUCT 구조체에 대한 포인터
 * @return LRESULT 메시지를 차단하려면 0이 아닌 값을 반환, 전달하려면 CallNextHookEx의 반환값을 반환
 */
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

/**
 * @brief 키보드 후크를 설치하고 설정하는 함수
 * @details 관리자 권한을 확인하고 WH_KEYBOARD_LL 저수준 키보드 후크를 시스템 전역에 설치합니다.
 */
void SetHook(void);

/**
 * @brief 설치된 키보드 후크를 해제하는 함수
 */
void UnsetHook(void);

/**
 * @brief 전역 키보드 후크 핸들
 */
extern HHOOK g_keyboardHook;

#endif // KEYBOARD_PROTECTOR_H