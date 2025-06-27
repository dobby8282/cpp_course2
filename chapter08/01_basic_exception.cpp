/*
 * 파일명: 01_basic_exception.cpp
 * 
 * 주제: 기본 예외 처리 (Basic Exception Handling)
 * 정의: try-catch 구문을 사용하여 런타임 오류를 안전하게 처리
 * 
 * 핵심 개념:
 * - 예외 처리: 프로그램 실행 중 발생하는 오류를 안전하게 처리하는 메커니즘
 * - try 블록: 예외가 발생할 수 있는 코드를 감싸는 영역
 * - catch 블록: 특정 타입의 예외를 처리하는 블록
 * - throw 문: 예외를 의도적으로 발생시키는 키워드
 * 
 * 예외 처리 흐름:
 * - 정상 실행: try 블록 실행 → catch 블록 건너뜀 → 계속 실행
 * - 예외 발생: try 블록에서 예외 발생 → 해당 catch 블록 실행 → 계속 실행
 * - 스택 되감기: 예외 발생 시 지역 객체들이 자동으로 소멸됨
 * 
 * 표준 예외 클래스:
 * - std::exception: 모든 표준 예외의 기본 클래스
 * - std::invalid_argument: 잘못된 인수 전달 시
 * - std::out_of_range: 범위를 벗어난 접근 시
 * - std::runtime_error: 실행 시간 오류
 * 
 * 사용 시기:
 * - 복구 불가능한 오류가 발생할 수 있는 상황
 * - 함수가 정상적으로 수행될 수 없는 조건
 * - 입력 검증이나 자원 부족 등의 상황
 * - 라이브러리나 시스템 호출에서 오류가 예상될 때
 * 
 * 장점:
 * - 오류 처리와 정상 로직의 분리
 * - 함수 중간에서 즉시 오류 상황 처리 가능
 * - 자동 자원 정리 (RAII와 함께)
 * - 오류 정보를 상세하게 전달 가능
 * 
 * 관련 개념:
 * - RAII: 자원 획득이 초기화, 예외 안전성 보장
 * - 예외 안전성: 강한 보장, 기본 보장, 예외 없음 보장
 * - 스마트 포인터: 예외 발생 시에도 메모리 누수 방지
 * - noexcept: 예외를 던지지 않음을 명시하는 키워드
 * 
 * 주의사항:
 * - 예외는 예외적인 상황에만 사용 (일반적인 제어 흐름 아님)
 * - 성능 오버헤드 존재 (예외 발생 시)
 * - catch(...) 사용 시 예외 정보 손실 가능
 * - 소멸자에서는 예외 던지기 금지
 */

#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("0으로 나눌 수 없습니다!");
    }
    return a / b;
}

int getArrayElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("배열 인덱스가 범위를 벗어났습니다!");
    }
    return arr[index];
}

int main() {
    cout << "=== 기본 예외 처리 ===" << endl;

    // 나누기 예외 처리
    try {
        cout << "10 / 2 = " << divide(10, 2) << endl;
        cout << "10 / 0 = " << divide(10, 0) << endl;  // 예외 발생
    }
    catch (const invalid_argument& e) {
        cout << "오류 발생: " << e.what() << endl;
    }

    // 배열 접근 예외 처리
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;

    try {
        cout << "\n배열[2] = " << getArrayElement(numbers, size, 2) << endl;
        cout << "배열[10] = " << getArrayElement(numbers, size, 10) << endl;  // 예외 발생
    }
    catch (const out_of_range& e) {
        cout << "배열 오류: " << e.what() << endl;
    }

    // 여러 예외 처리
    try {
        cout << "\n5 / 1 = " << divide(5, 1) << endl;
        cout << "배열[0] = " << getArrayElement(numbers, size, 0) << endl;
        cout << "3 / 0 = " << divide(3, 0) << endl;  // 예외 발생
    }
    catch (const invalid_argument& e) {
        cout << "나누기 오류: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cout << "범위 오류: " << e.what() << endl;
    }
    catch (...) {  // 모든 예외 처리
        cout << "알 수 없는 오류가 발생했습니다." << endl;
    }

    cout << "\n프로그램이 정상적으로 계속됩니다." << endl;
    return 0;
}