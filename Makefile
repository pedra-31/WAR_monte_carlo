# Variáveis
TARGET := build/main.exe

#Se der erro de compilação usar o compilador:
#   https://github.com/brechtsanders/winlibs_mingw/releases/download/15.2.0posix-13.0.0-ucrt-r3/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r3.zip
#Extrair em toolchain e descomentar essas linhas 
#Eu sei que é gambiarra, mas c++ não tem npm

# TOOLCHAIN_DIR := toolchain/mingw64
# GCC := $(TOOLCHAIN_DIR)/bin/g++.exe

GCC := g++ 
GCCFLAGS := -Wall -Wextra -std=c++17 #-finput-charset=UTF-8 -fexec-charset=UTF-8

# Lista de todos os .cpp 
SRCS := \
	src/Sistema.cpp \
	src/Autenticador.cpp \
	src/Usuario.cpp \
	src/Admin.cpp \
	src/Feed.cpp \
	src/Postagem.cpp \
	src/Comentario.cpp \
	src/Perfil.cpp \
	src/main.cpp
# Transforma src/foo.cpp -> bin/foo.o
OBJS := $(SRCS:src/%.cpp=bin/%.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	@if not exist build mkdir build
	$(GCC) $(GCCFLAGS) $(OBJS) -o $(TARGET)
# 	copy "$(TOOLCHAIN_DIR)\bin\libgcc_s_seh-1.dll" build >nul
# 	copy "$(TOOLCHAIN_DIR)\bin\libstdc++-6.dll" build >nul
# 	copy "$(TOOLCHAIN_DIR)\bin\libwinpthread-1.dll" build >nul

bin/%.o: src/%.cpp
	@if not exist bin mkdir bin
	$(GCC) $(GCCFLAGS) -c $< -o $@
clean:
	@if exist bin rmdir /s /q bin
	@if exist build rmdir /s /q build

.PHONY: all clean