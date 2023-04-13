CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

all: Client Server TCPClient

tcpClient:
	g++ -o TCPClient TCPClient.cpp

client: Client.cpp
	g++ -o Client Client.cpp

server: Server.cpp
	g++ -o Server Server.cpp
