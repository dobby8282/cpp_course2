/*
 * 파일명: 04_vector_basic.cpp
 * 
 * 주제: vector 기초 (Vector Basics)
 * 정의: 동적 배열을 제공하는 STL 컨테이너
 * 
 * 핵심 개념:
 * - 동적 배열: 실행 시간에 크기를 변경할 수 있는 배열
 * - 자동 메모리 관리: new/delete 없이 자동으로 메모리 할당/해제
 * - 연속 메모리: 요소들이 메모리에 연속적으로 저장됨
 * - 랜덤 액세스: 인덱스로 O(1) 시간에 임의 요소 접근 가능
 * 
 * 주요 멤버 함수:
 * - push_back(): 끝에 요소 추가
 * - pop_back(): 끝에서 요소 제거
 * - size(): 현재 요소 개수 반환
 * - empty(): 비어있는지 확인
 * - front()/back(): 첫/마지막 요소 접근
 * - at(): 범위 검사를 포함한 요소 접근
 * 
 * vector vs 배열:
 * - 크기: vector는 동적, 배열은 고정
 * - 메모리 관리: vector는 자동, 배열은 수동
 * - 안전성: vector는 범위 검사 옵션, 배열은 없음
 * - 기능: vector는 많은 멤버 함수, 배열은 기본적
 * 
 * 사용 시기:
 * - 컴파일 타임에 크기를 알 수 없을 때
 * - 실행 중 크기 변경이 필요할 때
 * - 안전한 메모리 관리가 필요할 때
 * - STL 알고리즘과 함께 사용할 때
 * 
 * 장점:
 * - 사용하기 쉬운 인터페이스
 * - 자동 메모리 관리로 메모리 누수 방지
 * - STL 알고리즘과 호환성
 * - 타입 안전성
 * 
 * 관련 개념:
 * - STL 컨테이너: list, deque, set, map 등
 * - 반복자 (Iterator): 컨테이너 요소에 접근하는 일반화된 방법
 * - 알고리즘: sort, find, copy 등 STL 알고리즘
 * - 용량 vs 크기: capacity()와 size()의 차이
 * 
 * 주의사항:
 * - 중간 삽입/삭제는 O(n) 시간 복잡도
 * - 재할당 시 모든 반복자 무효화
 * - at()은 범위 검사, []는 범위 검사 안 함
 * - 메모리 재할당으로 인한 성능 이슈 가능
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // vector 생성과 초기화
    vector<int> numbers;
    vector<int> scores = {90, 85, 92, 78, 96};
    vector<string> names(3, "unknown");  // 3개 요소를 "unknown"으로 초기화

    cout << "=== 요소 추가 ===" << endl;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    cout << "numbers 크기: " << numbers.size() << endl;

    cout << "\n=== 요소 접근 ===" << endl;
    for (int i = 0; i < numbers.size(); i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }

    cout << "\n=== range-based for loop ===" << endl;
    for (int score : scores) {
        cout << score << " ";
    }
    cout << endl;

    cout << "\n=== 요소 수정 ===" << endl;
    scores[0] = 95;
    scores.at(1) = 88;  // 범위 검사 포함

    cout << "\n=== 요소 삭제 ===" << endl;
    cout << "삭제 전 크기: " << scores.size() << endl;
    scores.pop_back();  // 마지막 요소 삭제
    cout << "삭제 후 크기: " << scores.size() << endl;

    cout << "\n=== vector 정보 ===" << endl;
    cout << "비어있는가? " << (numbers.empty() ? "예" : "아니오") << endl;
    cout << "첫 번째 요소: " << numbers.front() << endl;
    cout << "마지막 요소: " << numbers.back() << endl;

    return 0;
}