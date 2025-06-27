/*
 * 파일명: src/Calculator.cpp
 * 
 * Calculator 클래스 구현 파일
 * 
 * 핵심 학습 내용:
 * 1. #include로 헤더 파일 포함
 * 2. :: 연산자로 클래스 함수 구현
 * 3. 생성자/소멸자 구현
 * 4. 멤버 함수 구현
 * 5. const 함수 구현
 */

#include "../include/Calculator.h"

using namespace std;

// ============================================
// 🏗️ 생성자 구현 (:: 연산자 사용)
// ============================================

/**
 * @brief 기본 생성자 - 초기값 0으로 설정
 */
Calculator::Calculator() : result(0.0), operationCount(0) {
    cout << "Calculator created (default)" << endl;
}

/**
 * @brief 매개변수 생성자 - 초기값 지정
 * @param initialValue 초기 결과값
 */
Calculator::Calculator(double initialValue) : result(initialValue), operationCount(0) {
    cout << "Calculator created with initial value: " << initialValue << endl;
}

/**
 * @brief 소멸자
 */
Calculator::~Calculator() {
    cout << "Calculator destroyed (performed " << operationCount << " operations)" << endl;
}

// ============================================
// 🧮 계산 함수들 구현
// ============================================

double Calculator::add(double a, double b) {
    result = a + b;
    operationCount++;
    cout << a << " + " << b << " = " << result << endl;
    return result;
}

double Calculator::subtract(double a, double b) {
    result = a - b;
    operationCount++;
    cout << a << " - " << b << " = " << result << endl;
    return result;
}

double Calculator::multiply(double a, double b) {
    result = a * b;
    operationCount++;
    cout << a << " * " << b << " = " << result << endl;
    return result;
}

double Calculator::divide(double a, double b) {
    if (b == 0) {
        cout << "Error: Division by zero!" << endl;
        return result;  // 기존 값 유지
    }

    result = a / b;
    operationCount++;
    cout << a << " / " << b << " = " << result << endl;
    return result;
}
