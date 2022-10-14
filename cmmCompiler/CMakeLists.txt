cmake_minimum_required(VERSION 3.23)
project(cmmCompiler C)

set(CMAKE_C_STANDARD 99)

add_executable(cmmCompiler main.c LexicalAnalyzer.c LexicalAnalyzer.h ErrorManager.c ErrorManager.h SymbleTable.c SymbleTable.h)
