cmake_minimum_required(VERSION 3.23)
project(LabyrinthGenerator)

set(CMAKE_CXX_STANDARD 23)
#enable_language(ASM_NASM)
set(NASM_COMPILER nasm)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT}  -o <OBJECT> <SOURCE>")
#set_source_files_properties(Tools/rnd_by_seed.asm PROPERTIES LANGUAGE ASM_NASM)

set(SOURCE_FILES main.cpp Models/Classes/Grid.cpp Models/Headers/Grid.h Models/Classes/TileData.cpp) #Tools/rnd_by_seed.asm

add_executable(LabyrinthGenerator ${SOURCE_FILES})
#target_link_options(LabyrinthGenerator PRIVATE /lib64/ld-linux-x86-64.so.2)