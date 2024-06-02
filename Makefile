CC = gcc
CFLAGS = -Wall -Wextra
LIBS_WIN = -lws2_32
LIBS_LINUX = 
SOURCE = main.c src/*.c
TARGET_WIN = rokuecp.exe
TARGET_LINUX = rokuecp

ifeq ($(OS),Windows_NT)
	TARGET = $(TARGET_WIN)
else
	TARGET = $(TARGET_LINUX)
endif

all: $(TARGET)

clean:
	rm -f $(TARGET_WIN) $(TARGET_LINUX)

$(TARGET_WIN): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET_WIN) $(LIBS_WIN)

$(TARGET_LINUX): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET_LINUX) $(LIBS_LINUX)
