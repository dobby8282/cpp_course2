# 간단한 클래스 분리 예제 🧮

C++의 헤더/구현 파일 분리를 가장 간단하게 배우는 예제입니다.

## 📁 프로젝트 구조

```
simple_class/
├── include/Calculator.h   # 클래스 선언 (헤더)
├── src/Calculator.cpp     # 클래스 구현
├── main.cpp              # 메인 프로그램
├── compile.sh           # 컴파일 스크립트
└── README.md            # 이 파일
```

## 🚀 빠른 시작

```bash
# 1. 파일 생성
python3 create_simple_class.py

# 2. 폴더 이동
cd simple_class

# 3. 컴파일
./compile.sh              # Linux/Mac
# 또는 compile.bat        # Windows

# 4. 실행
./calculator
```

## 📚 핵심 학습 내용

### 🔍 파일 분리 패턴

#### 📄 헤더 파일 (Calculator.h)
```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
private:
    double result;

public:
    Calculator();           // 선언만
    double add(double a, double b);  // 선언만
};

#endif
```

#### 💻 구현 파일 (Calculator.cpp)
```cpp
#include "../include/Calculator.h"

// :: 연산자로 구현
Calculator::Calculator() : result(0.0) {
    // 생성자 구현
}

double Calculator::add(double a, double b) {
    // 함수 구현
    return a + b;
}
```

#### 🎯 메인 파일 (main.cpp)
```cpp
#include "include/Calculator.h"

int main() {
    Calculator calc;        // 객체 생성
    calc.add(10, 5);       // 함수 호출
    return 0;
}
```

## 💡 핵심 개념

### 1️⃣ 헤더 가드
```cpp
#ifndef CALCULATOR_H    // 중복 포함 방지
#define CALCULATOR_H
// 내용
#endif
```

### 2️⃣ :: 연산자
```cpp
// 헤더: 선언
class Calculator {
    void add();
};

// 구현: :: 사용
void Calculator::add() {  // Calculator 클래스의 add 함수
    // 구현
}
```

### 3️⃣ const 함수
```cpp
double getResult() const;  // 값 변경 안함 보장
```

### 4️⃣ 접근 지정자
```cpp
class Calculator {
private:    // 외부 접근 불가
    double result;

public:     // 외부 접근 가능
    void add();
};
```

## 📊 결과 예시

```
🧮 Simple Calculator Example

=== Basic Operations Test ===
Calculator created (default)
10 + 5 = 15
20 - 8 = 12
6 * 7 = 42
100 / 4 = 25

=== Calculator Info ===
Current result: 25
Operations performed: 4
Status: Non-zero
```

## 🎯 왜 파일을 분리할까?

1. **📦 모듈화**: 기능별로 파일 분리
2. **🔄 재사용**: 헤더 파일을 다른 프로젝트에서 사용
3. **⚡ 컴파일 속도**: 변경된 부분만 재컴파일
4. **👥 협업**: 여러 개발자가 다른 파일 작업
5. **📖 가독성**: 선언과 구현 분리로 구조 명확

## 🔧 컴파일 원리

```bash
# 1. 전처리: 헤더 파일 내용 복사
# 2. 컴파일: .cpp → .o (오브젝트 파일)
# 3. 링크: 여러 .o 파일 → 실행 파일

g++ -I./include -o calculator main.cpp src/Calculator.cpp
#   ^^^^^^^^^^^                ^^^^^^^^ ^^^^^^^^^^^^^^^^^^^^
#   헤더 경로                   메인     구현 파일
```

---
🐍 **Python으로 생성** | 📚 **헤더 분리 학습** | 🎯 **:: 연산자 마스터**