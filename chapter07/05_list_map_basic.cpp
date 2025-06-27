/*
 * 파일명: 05_list_map_basic.cpp
 * 
 * 주제: list와 map 기초 (List & Map Basics)
 * 정의: 연결 리스트와 키-값 쌍을 관리하는 STL 컨테이너
 * 
 * 핵심 개념:
 * - list: 이중 연결 리스트 구조의 순차 컨테이너
 * - map: 키-값 쌍을 저장하는 연관 컨테이너 (자동 정렬)
 * - 노드 기반: list는 각 요소가 독립적인 메모리에 저장
 * - 트리 구조: map은 일반적으로 레드-블랙 트리로 구현
 * 
 * list의 특징:
 * - 양방향 순회 가능 (이중 연결 리스트)
 * - 중간 삽입/삭제가 O(1) (위치를 알고 있을 때)
 * - 랜덤 액세스 불가 (인덱스로 직접 접근 안됨)
 * - 메모리가 연속적이지 않음
 * 
 * map의 특징:
 * - 키를 기준으로 자동 정렬 유지
 * - 중복 키 허용 안함 (유일한 키)
 * - 검색, 삽입, 삭제 모두 O(log n)
 * - 키-값 쌍 (pair) 형태로 저장
 * 
 * 사용 시기:
 * - list: 중간 삽입/삭제가 빈번하고 순서가 중요할 때
 * - map: 키를 통한 빠른 검색이 필요하고 정렬된 상태를 유지하고 싶을 때
 * 
 * 주요 멤버 함수:
 * - list: push_front/back, pop_front/back, insert, erase
 * - map: insert, find, count, erase, operator[]
 * 
 * 관련 컨테이너:
 * - vector vs list: 연속 메모리 vs 노드 기반
 * - map vs unordered_map: 정렬 vs 해시 테이블
 * - multimap: 중복 키를 허용하는 map
 * - set: 키만 저장하는 map (값 없음)
 * 
 * 장점:
 * - list: 효율적인 중간 삽입/삭제, 메모리 단편화 없음
 * - map: 빠른 검색, 자동 정렬, 직관적인 키-값 접근
 * 
 * 주의사항:
 * - list는 랜덤 액세스 불가 (for문에서 인덱스 사용 안됨)
 * - map의 operator[]는 키가 없으면 기본값으로 요소 생성
 * - 정렬 기준 변경 시 커스텀 비교 함수 필요
 */

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

int main() {
    cout << "=== list 기초 ===" << endl;
    list<string> todoList;

    // 요소 추가
    todoList.push_back("숙제하기");
    todoList.push_front("일어나기");
    todoList.push_back("운동하기");

    cout << "할 일 목록:" << endl;
    for (const string& todo : todoList) {
        cout << "- " << todo << endl;
    }

    // 요소 삭제
    todoList.pop_front();  // 첫 번째 요소 삭제
    cout << "\n첫 번째 일 완료 후:" << endl;
    for (const string& todo : todoList) {
        cout << "- " << todo << endl;
    }

    cout << "\n=== map 기초 ===" << endl;
    map<string, int> scores;

    // 키-값 쌍 추가
    scores["김철수"] = 90;
    scores["이영희"] = 95;
    scores["박민수"] = 88;
    scores.insert(make_pair("최정화", 92));

    cout << "학생 점수:" << endl;
    for (const auto& pair : scores) {
        cout << pair.first << ": " << pair.second << "점" << endl;
    }

    // 특정 키 검색
    string name = "이영희";
    if (scores.find(name) != scores.end()) {
        cout << "\n" << name << "의 점수: " << scores[name] << "점" << endl;
    }

    // 키 존재 여부 확인
    cout << "박민수 등록됨? " << (scores.count("박민수") ? "예" : "아니오") << endl;
    cout << "홍길동 등록됨? " << (scores.count("홍길동") ? "예" : "아니오") << endl;

    return 0;
}