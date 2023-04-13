CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

all: Client Server

client: Client.cpp
	g++ -o Client Client.cpp

server: Server.cpp
	g++ -o Server Server.cpp
