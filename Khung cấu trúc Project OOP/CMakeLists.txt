cmake_minimum_required(VERSION 3.16)

project(QuizApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QuizApp
    main.cpp
    QuizApp.cpp
)

target_include_directories(QuizApp PRIVATE
    ../QuestionManagement
    ../QuestionRepository
    ../ExamProcessing
    ../UserInterface
)