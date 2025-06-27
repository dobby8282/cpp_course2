/*
 * 파일명: include/Calculator.h
 * 
 * 간단한 계산기 클래스 - 헤더 파일 분리 예제
 * 
 * 핵심 학습 내용:
 * 1. 헤더 가드 (#ifndef ~ #endif)
 * 2. 클래스 선언 (구현은 .cpp에서)
 * 3. public/private 접근 지정자
 * 4. 생성자/소멸자 선언
 * 5. 멤버 변수와 멤버 함수 선언
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>

/**
 * @brief 간단한 계산기 클래스
 * 
 * 기본적인 사칙연산과 결과 저장 기능을 제공합니다.
 * 헤더/구현 파일 분리의 기본 예제입니다.
 */
class Calculator {
private:
    // 🔒 Private 멤버 변수 (외부에서 직접 접근 불가)
    double result;        // 계산 결과 저장
    int operationCount;   // 연산 횟수

public:
    // 👷‍♂️ 생성자 선언 (구현은 .cpp에서)
    Calculator();
    Calculator(double initialValue);

    // 💀 소멸자 선언
    ~Calculator();

    // 🧮 계산 함수들 선언 (구현은 .cpp에서)
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);

};

#endif  // CALCULATOR_H