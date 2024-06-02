CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lws2_32
SOURCE = main.c
TARGET = rokuecp.exe

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LIBS)
