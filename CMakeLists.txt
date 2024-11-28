cmake_minimum_required(VERSION 3.29)
project(Projet_etudiants_absence C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_etudiants_absence main.c
        Actions.c
        Trie.c)
