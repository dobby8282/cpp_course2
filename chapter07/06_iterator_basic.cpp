/*
 * 파일명: 06_iterator_basic.cpp
 * 
 * 주제: 반복자 기초 (Iterator Basics)
 * 정의: 컨테이너의 요소들을 순차적으로 접근하는 객체
 * 
 * 핵심 개념:
 * - 반복자: 컨테이너 요소에 접근하는 일반화된 포인터 역할의 객체
 * - 추상화: 다양한 컨테이너를 동일한 방식으로 순회할 수 있게 함
 * - STL 설계 원칙: 컨테이너와 알고리즘을 연결하는 다리 역할
 * - 포인터 문법: *, ->, ++, -- 등 포인터와 유사한 연산자 지원
 * 
 * 반복자 종류:
 * - begin()/end(): 시작과 끝(마지막 다음) 위치
 * - rbegin()/rend(): 역방향 시작과 끝
 * - cbegin()/cend(): const 반복자 (읽기 전용)
 * - iterator/reverse_iterator: 순방향/역방향 반복자 타입
 * 
 * 반복자 카테고리:
 * - Input Iterator: 읽기만 가능, 한 번만 순회
 * - Output Iterator: 쓰기만 가능, 한 번만 순회
 * - Forward Iterator: 읽기/쓰기, 다중 순회 가능
 * - Bidirectional Iterator: 양방향 이동 (list, map)
 * - Random Access Iterator: 임의 접근 (vector, array)
 * 
 * 사용 시기:
 * - 컨테이너 타입에 독립적인 코드 작성 시
 * - STL 알고리즘과 함께 사용할 때
 * - 일부 요소만 처리하거나 조건부 순회가 필요할 때
 * - 세밀한 제어가 필요한 순회 작업
 * 
 * 장점:
 * - 컨테이너 타입에 무관한 일관된 인터페이스
 * - STL 알고리즘과의 완벽한 호환성
 * - 타입 안전성과 효율성
 * - 범위 기반 for문의 기반 기술
 * 
 * 관련 개념:
 * - STL 알고리즘: sort, find, copy 등이 반복자 사용
 * - 범위 기반 for: 내부적으로 begin()/end() 사용
 * - auto 키워드: 복잡한 반복자 타입을 자동 추론
 * - 스마트 포인터: 메모리 관리 기능이 추가된 포인터 래퍼
 * 
 * 주의사항:
 * - end()는 마지막 요소가 아닌 그 다음을 가리킴
 * - 컨테이너 수정 시 반복자 무효화 가능
 * - 범위를 벗어난 접근 시 정의되지 않은 동작
 * - ++it가 it++보다 효율적 (후위 증가는 임시 객체 생성)
 */

#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

int main() {
    cout << "=== vector 반복자 ===" << endl;
    vector<int> numbers = {10, 20, 30, 40, 50};

    // 순방향 반복자
    cout << "순방향: ";
    for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 역방향 반복자
    cout << "역방향: ";
    for (vector<int>::reverse_iterator it = numbers.rbegin(); it != numbers.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // auto 키워드 사용 (C++11)
    cout << "auto 사용: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n=== list 반복자 ===" << endl;
    list<string> words = {"hello", "world", "STL"};

    for (auto it = words.begin(); it != words.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "\n=== map 반복자 ===" << endl;
    map<string, int> ages = {{"김철수", 25}, {"이영희", 23}, {"박민수", 27}};

    for (auto it = ages.begin(); it != ages.end(); ++it) {
        cout << it->first << ": " << it->second << "세" << endl;
    }

    cout << "\n=== 반복자로 요소 수정 ===" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        *it *= 2;  // 각 요소를 2배로
    }

    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}