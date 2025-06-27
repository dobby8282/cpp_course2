
/*
 * 간단한 템플릿 특수화 예제
 * 
 * 상황: 다양한 타입의 값을 출력하는데
 *       특정 타입은 특별하게 출력하고 싶다!
 */

#include <iostream>
#include <string>
using namespace std;

// ===== 1. 기본 템플릿 =====
template<typename T>
void show(T value) {
    cout << "값: " << value << endl;
}

// ===== 2. string 특수화 =====
template<>
void show<string>(string value) {
    cout << "문자열: \"" << value << "\"" << endl;
}

// ===== 3. bool 특수화 =====
template<>
void show<bool>(bool value) {
    cout << "불린: " << (value ? "참" : "거짓") << endl;
}

int main() {
    cout << "=== 템플릿 특수화 비교 ===" << endl;
    
    // 일반 템플릿 사용
    show(42);           // int → 기본 템플릿
    show(3.14);         // double → 기본 템플릿
    
    // 특수화된 템플릿 사용
    show(string("안녕")); // string → 특수화 버전
    show(true);         // bool → 특수화 버전
    show(false);        // bool → 특수화 버전
    
    
    return 0;
}

/*
출력:
값: 42
값: 3.14
문자열: "안녕"
불린: 참
불린: 거짓
*/
