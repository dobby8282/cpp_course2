/*
 * 파일명: main.cpp
 * 
 * Calculator 클래스 사용 예제
 * 
 * 핵심 학습 내용:
 * 1. 헤더 파일 include
 * 2. 객체 생성 (생성자 호출)
 * 3. 멤버 함수 호출
 * 4. 객체 소멸 (소멸자 자동 호출)
 */

#include "include/Calculator.h"
#include <iostream>

using namespace std;


int main() {
   // 기본 생성자로 객체 생성
    Calculator calc;

    // 기본 사칙연산 테스트
    calc.add(10, 5);
    calc.subtract(20, 8);
    calc.multiply(6, 7);
    calc.divide(100, 4);

    return 0;
}