/*
 * 파일명: 07_abstract_class.cpp
 * 
 * 주제: 추상 클래스 (Abstract Class)
 * 정의: 하나 이상의 순수 가상 함수를 가진 클래스로, 인터페이스 역할
 * 
 * 주제: 순수 가상 함수 (Pure Virtual Function)
 * 정의: 구현이 없는 가상 함수로, 자식 클래스에서 반드시 구현해야 함
 * 
 * 핵심 개념:
 * - 추상 클래스: 직접 인스턴스화할 수 없는 불완전한 클래스
 * - 인터페이스 정의: 자식 클래스들이 구현해야 할 공통 규약 제시
 * - 코드 재사용: 공통 멤버 변수와 함수는 추상 클래스에서 구현
 * - 다형성 활용: 추상 클래스 포인터로 다양한 자식 객체 관리
 * 
 * 추상 클래스의 특징:
 * - 순수 가상 함수: 반드시 자식에서 구현해야 하는 함수들
 * - 일반 함수: 공통 기능은 추상 클래스에서 구현 가능
 * - 멤버 변수: 자식 클래스들이 공유할 데이터 정의
 * - 생성자/소멸자: 객체 초기화와 정리 작업 담당
 * 
 * 사용 시기:
 * - 여러 클래스가 공통 인터페이스를 가져야 할 때
 * - 공통 속성은 있지만 동작이 다른 클래스들을 설계할 때
 * - 템플릿 메서드 패턴을 구현할 때
 * - 플러그인이나 확장 가능한 시스템 설계 시
 * 
 * 설계 패턴:
 * - 템플릿 메서드: 알고리즘 구조는 부모가, 세부 구현은 자식이
 * - 전략 패턴: 알고리즘을 교체 가능하게 캡슐화
 * - 팩토리 패턴: 객체 생성을 추상화하여 유연성 제공
 * 
 * 장점:
 * - 일관된 인터페이스 강제
 * - 코드 중복 최소화
 * - 확장성과 유지보수성 향상
 * - 다형성을 통한 유연한 설계
 * 
 * 주의사항:
 * - 모든 순수 가상 함수를 구현해야 인스턴스화 가능
 * - 가상 소멸자 필수 (메모리 누수 방지)
 * - 과도한 추상화는 복잡성 증가
 */

#include <iostream>
#include <vector>
using namespace std;

// 추상 클래스 - 게임 캐릭터 인터페이스
class GameCharacter {
protected:
    string name;
    int health;

public:
    GameCharacter(string n, int h) : name(n), health(h) {}

    // 순수 가상 함수들 (인터페이스)
    virtual void attack() = 0;
    virtual void defend() = 0;
    virtual void useSkill() = 0;

    // 공통 기능
    void takeDamage(int damage) {
        health -= damage;
        cout << name << "이(가) " << damage << " 피해를 받았습니다. (체력: " << health << ")" << endl;
    }

    bool isAlive() { return health > 0; }
    virtual ~GameCharacter() {}
};

class Warrior : public GameCharacter {
public:
    Warrior(string n) : GameCharacter(n, 100) {}

    void attack() override {
        cout << name << " 전사가 검으로 공격합니다!" << endl;
    }

    void defend() override {
        cout << name << " 전사가 방패로 방어합니다!" << endl;
    }

    void useSkill() override {
        cout << name << " 전사가 강력한 베기를 사용합니다!" << endl;
    }
};

class Mage : public GameCharacter {
public:
    Mage(string n) : GameCharacter(n, 80) {}

    void attack() override {
        cout << name << " 마법사가 파이어볼을 시전합니다!" << endl;
    }

    void defend() override {
        cout << name << " 마법사가 마법 보호막을 생성합니다!" << endl;
    }

    void useSkill() override {
        cout << name << " 마법사가 번개 마법을 사용합니다!" << endl;
    }
};

int main() {
    vector<GameCharacter*> party;
    party.push_back(new Warrior("김전사"));
    party.push_back(new Mage("이마법사"));

    // 다형성을 활용한 일괄 처리
    for (GameCharacter* character : party) {
        character->attack();
        character->defend();
        character->useSkill();
        character->takeDamage(20);
        cout << endl;
    }

    // 메모리 해제
    for (GameCharacter* character : party) {
        delete character;
    }

    return 0;
}