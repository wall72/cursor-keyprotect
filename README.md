# Keyboard Protector

Windows용 키보드 입력 차단 보안 도구입니다. 저수준 키보드 후크를 사용하여 시스템 전체의 키 입력을 차단합니다.

## 🚀 주요 기능

- **전역 키보드 차단**: Windows 저수준 키보드 후크로 모든 키보드 입력 차단
- **안전한 종료**: ESC 키를 통한 안전한 프로그램 종료
- **실시간 모니터링**: 키 입력 감지 및 로그 출력
- **관리자 권한 확인**: 실행 시 관리자 권한 상태 표시
- **강화된 에러 처리**: 상세한 에러 메시지 및 안전한 종료

## 📋 시스템 요구사항

- **운영체제**: Windows 7 이상 (32비트/64비트)
- **권한**: 관리자 권한 권장
- **아키텍처**: 32비트 및 64비트 지원 (WOW64)

## 🔧 프로젝트 구조

```
cursor-keyprotect/
├── src/
│   ├── main.c              # 메인 진입점
│   └── keyboard_protector.c # 후크 구현
├── include/
│   └── keyboard_protector.h # 헤더 파일
├── bin/                    # 실행 파일 (빌드 후 생성)
├── obj/                    # 오브젝트 파일 (빌드 후 생성)
├── Makefile               # 빌드 설정
├── build_universal.bat    # 유니버설 빌드 스크립트
└── README.md              # 이 파일
```

## ⚡ 빠른 시작

### 1. 빌드

#### Windows 64비트 환경

```cmd
make
```

#### Windows 32비트 환경 (또는 64비트에서 32비트 빌드)

```cmd
build_universal.bat
```

### 2. 실행

```cmd
bin\keyboard_protector.exe
```

### 3. 종료

ESC 키를 눌러 프로그램을 종료합니다.

## 🛠️ 빌드 방법

### 자동 빌드 스크립트 (권장)

```cmd
build_universal.bat
```

이 스크립트는 OS 아키텍처를 자동 감지하고 적절한 빌드를 실행합니다.

### 수동 빌드

#### 64비트 빌드

```cmd
make clean
make
```

#### 32비트 빌드

```cmd
make clean
make build32
```

### Make 명령어

```cmd
make          # 64비트 빌드
make build32  # 32비트 빌드 (모든 Windows 지원)
make clean    # 빌드 파일 정리
make rebuild  # 정리 후 다시 빌드
make debug    # 디버그 모드로 빌드
make release  # 릴리스 모드로 빌드
make run      # 빌드 후 실행
make help     # 도움말 표시
```

## 📦 빌드 요구사항

- **컴파일러**: MinGW-w64 또는 GCC
- **Make**: Make 도구
- **라이브러리**: 
  - `user32` (Windows GUI)
  - `advapi32` (관리자 권한 확인)

### MinGW-w64 설치

**Chocolatey 사용:**
```cmd
choco install mingw make -y
```

**수동 설치:**
- https://www.mingw-w64.org/downloads/
- 또는 https://winlibs.com/

## ⚠️ 주의사항

### 보안

- 이 프로그램은 **관리자 권한**이 필요할 수 있습니다.
- 키보드 입력을 완전히 차단하므로 주의해서 사용하세요.
- **ESC 키만**이 프로그램 종료를 위해 허용됩니다.
- 보안 도구 목적으로만 사용하세요.

### 사용 전 확인

```cmd
# 테스트 전 가상머신 사용 권장
# 또는 작업 관리자로 강제 종료하는 방법 알고 있기

# 강제 종료 방법
taskkill /F /IM keyboard_protector.exe
```

## 🐛 알려진 문제 및 해결책

### 1. "관리자 권한 필요" 오류

**증상:** 후크 설치 실패

**해결:**
- 관리자 권한으로 실행
- 또는 가상머신에서 테스트

### 2. 32비트와 64비트 호환성

**문제:** 64비트 호스트에서 32비트 빌드 불가능

**해결:**
- 32비트 가상머신에서 직접 빌드
- 생성된 32비트 exe는 WOW64로 64비트에서도 작동

**빌드 방법:**
```cmd
# 32비트 VM에서
build_universal.bat
# 또는
make build32
```

## 🔍 동작 원리

1. **저수준 키보드 후크 설치** (`WH_KEYBOARD_LL`)
2. **모든 키 입력 감지**
3. **대부분의 키 차단** (메시지 흡수)
4. **ESC 키만 허용** (종료 신호)
5. **메시지 루프 실행** (`GetMessage`)
6. **종료 시 후크 해제**

## 🎯 주요 개선사항

### ESC 키 종료 기능

ESC 키 입력 시 `PostQuitMessage(0)`을 호출하여 메시지 루프를 정상 종료합니다.

### 에러 처리 강화

- `GetMessage()` 반환값 검사 (-1 에러 처리)
- 시스템 에러 코드 출력
- 적절한 Exit code 반환

### 관리자 권한 확인

Windows Vista 이상에서 자동으로 관리자 권한을 확인하고 표시합니다.

### Windows XP 호환성

32비트 환경에서 Windows XP와의 호환성을 위해 조건부 컴파일을 사용합니다.

## 📚 기술 스택

- **언어**: C99
- **플랫폼**: Windows API
- **후크 타입**: `WH_KEYBOARD_LL` (저수준 키보드 후크)
- **컴파일러**: GCC (MinGW-w64)

## 🤝 기여하기

1. 이 저장소를 포크합니다
2. 새 기능 브랜치를 생성합니다 (`git checkout -b feature/AmazingFeature`)
3. 변경사항을 커밋합니다 (`git commit -m 'Add some AmazingFeature'`)
4. 브랜치에 푸시합니다 (`git push origin feature/AmazingFeature`)
5. Pull Request를 생성합니다

## 📝 라이선스

이 프로젝트는 교육 및 보안 연구 목적으로 제작되었습니다.

**주의:** 상업적 사용이나 악의적인 목적으로 사용하지 마세요.

## 📞 문의

프로젝트에 대한 질문이나 제안사항이 있으시면 이슈를 생성해주세요.

---

## 📖 추가 정보

### 빌드 확인

```cmd
# 실행 파일 정보 확인
file bin\keyboard_protector.exe

# 또는
wmic datafile where name="C:\path\to\keyboard_protector.exe" get version
```

### 실행 시 출력 예시

```
[성공] 키보드 보안 툴이 실행되었습니다. 모든 키 입력이 차단됩니다.
[정보] 관리자 권한으로 실행 중입니다.
---------------------------------------------------------
Esc 키를 눌러 종료하십시오.

[키 감지] KeyCode: 65
[차단] 키 입력이 성공적으로 차단되었습니다.

[키 감지] KeyCode: 27  (ESC)
[알림] Esc 키가 눌렸습니다. 후크를 해제하고 종료합니다.

[종료] 키보드 보안 툴이 정상적으로 종료되었습니다.
```

### 지원되는 Windows 버전

| OS | 32비트 | 64비트 |
|----|-------|--------|
| Windows XP | ✅ | ❌ |
| Windows Vista | ✅ | ✅ |
| Windows 7 | ✅ | ✅ |
| Windows 8/10/11 | ✅ | ✅ |

**참고:** 32비트 빌드는 WOW64를 통해 64비트 Windows에서도 자동 실행됩니다.
