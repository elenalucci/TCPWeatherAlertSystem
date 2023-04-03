CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

all: client server

client: client.cpp
	g++ -o client client.cpp

server: server.cpp
	g++ -o server server.cpp
