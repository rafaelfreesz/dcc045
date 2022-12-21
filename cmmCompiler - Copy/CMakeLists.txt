cmake_minimum_required(VERSION 3.23)
project(cmmCompiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmmCompiler main.c ErrorManager.c ErrorManager.h SymbolTable.cpp SymbolTable.h LexicalAnalyzer.c LexicalAnalyzer.h Parser.cpp Parser.h Utils.cpp Utils.h)
