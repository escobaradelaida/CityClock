
#compiler
CC = g++

CFLAGS = -std=c++11 -Wall -Werror

#executable i want
TARGET = CityClock.exe

SOURCES = main.cpp CityClock.cpp

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)