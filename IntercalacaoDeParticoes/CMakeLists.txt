cmake_minimum_required(VERSION 3.17)
project(ed2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ed2 main.c cliente.c cliente.h intercalacao.c intercalacao.h lista_clientes.c lista_clientes.h nomes.c nomes.h)