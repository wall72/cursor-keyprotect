#ifndef KEYBOARD_PROTECTOR_H
#define KEYBOARD_PROTECTOR_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// 함수 선언
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void SetHook(void);
void UnsetHook(void);

// 전역 변수 선언
extern HHOOK g_keyboardHook;

#endif // KEYBOARD_PROTECTOR_H