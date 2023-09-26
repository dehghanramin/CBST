###############################################################################
# File: Makefile
###############################################################################
# Programmer: Ramin Dehghan
# Date: May 22, 2021
# Class: CSCI 133 ("Data Structures Using C++")
# Time: Online
# Instructor: Dr. Rodriguez
# Project: Project CBST
#
# Description:
# Makefile for the project
###############################################################################

#compiler
CC = g++

#flags
CFLAGS = -g -Wall -std=c++11

#target
TARGET = CBST

$(TARGET): main.o CPersonInfo.o PrecondViolatedExcept.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o CPersonInfo.o PrecondViolatedExcept.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

CPersonInfo.o: CPersonInfo.cpp
	$(CC) $(CFLAGS) -c CPersonInfo.cpp

PrecondViolatedExcept.o: PrecondViolatedExcept.cpp
	$(CC) $(CFLAGS) -c PrecondViolatedExcept.cpp

#clean
clean:
ifneq (,$(wildcard $(TARGET)))
	rm $(TARGET) *.o
endif
