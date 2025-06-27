#!/bin/bash
# 간단한 클래스 예제 컴파일 스크립트

echo "🔨 Compiling Simple Class Example..."

g++ -std=c++17 -I./include -o calculator main.cpp src/Calculator.cpp

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo ""
    echo "Run: ./calculator"
else
    echo "❌ Compilation failed!"
fi