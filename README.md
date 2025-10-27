# Keyboard Protector

Windows용 키보드 입력 차단 보안 도구입니다. 저수준 키보드 후크를 사용하여 시스템 전체의 키 입력을 차단합니다.

## 🔧 프로젝트 구조

```
copilot-keyprotect/
├── src/                    # 소스 파일들
│   ├── main.c             # 메인 함수
│   └── keyboard_protector.c # 키보드 후크 구현
├── include/               # 헤더 파일들
│   └── keyboard_protector.h # 함수 선언 및 구조체
├── bin/                   # 실행 파일 (빌드 후 생성)
├── obj/                   # 오브젝트 파일 (빌드 후 생성)
├── Makefile              # 빌드 설정 파일
├── README.md             # 프로젝트 설명서
└── .gitignore           # Git 무시 파일 목록
```

## ⚡ 빠른 시작

### 빌드 요구사항
- Windows 운영체제
- MinGW-w64 또는 Microsoft Visual C++ 컴파일러
- Make 도구

### 빌드 및 실행

1. **프로젝트 빌드:**
   ```cmd
   make
   ```

2. **실행:**
   ```cmd
   make run
   ```
   또는
   ```cmd
   bin\keyboard_protector.exe
   ```

3. **종료:**
   - `Esc` 키를 눌러 프로그램을 종료할 수 있습니다.

### 기타 Make 명령어

```cmd
make clean      # 빌드 파일 정리
make rebuild    # 정리 후 다시 빌드
make debug      # 디버그 모드로 빌드
make release    # 최적화된 릴리스 모드로 빌드
make help       # 사용 가능한 명령어 보기
```

## 🚀 주요 기능

- **전역 키보드 후킹**: Windows 저수준 키보드 후크 사용
- **키 입력 차단**: 모든 키 입력을 실시간으로 차단
- **안전한 종료**: ESC 키를 통한 안전한 프로그램 종료
- **실시간 모니터링**: 키 입력 감지 및 로그 출력

## ⚠️ 주의사항

- 이 프로그램은 **관리자 권한**이 필요할 수 있습니다.
- 키보드 입력을 완전히 차단하므로 주의해서 사용하세요.
- ESC 키만이 프로그램 종료를 위해 허용됩니다.
- 보안 도구 목적으로만 사용하세요.

## 📋 시스템 요구사항

- Windows 7 이상
- x86 또는 x64 아키텍처
- 최소 1MB의 디스크 공간

## 🔨 개발 환경 설정

### MinGW-w64 설치 (권장)
1. [MSYS2](https://www.msys2.org/) 설치
2. MinGW-w64 설치:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-make
   ```

### Visual Studio Build Tools
또는 Microsoft Visual Studio Build Tools를 사용할 수 있습니다.

## 📝 라이선스

이 프로젝트는 교육 및 보안 연구 목적으로 제작되었습니다. 
상업적 사용이나 악의적인 목적으로 사용하지 마세요.

## 🤝 기여하기

1. 이 저장소를 포크합니다
2. 새 기능 브랜치를 생성합니다 (`git checkout -b feature/AmazingFeature`)
3. 변경사항을 커밋합니다 (`git commit -m 'Add some AmazingFeature'`)
4. 브랜치에 푸시합니다 (`git push origin feature/AmazingFeature`)
5. Pull Request를 생성합니다

## 📞 문의

프로젝트에 대한 질문이나 제안사항이 있으시면 이슈를 생성해주세요.