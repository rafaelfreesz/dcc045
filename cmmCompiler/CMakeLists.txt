cmake_minimum_required(VERSION 3.23)
project(cmmCompiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmmCompiler main.cpp ErrorManager.cpp ErrorManager.h SymbolTable.cpp SymbolTable.h LexicalAnalyzer.cpp LexicalAnalyzer.h Parser.cpp Parser.h)
