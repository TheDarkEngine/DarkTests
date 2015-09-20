#include <windows.h>
#include <string>
#include <iostream>
#include <thread>
#include "Main.hpp"

std::string PlayerName = "";

int main()
{
	HMODULE DarkCoreHandle = LoadLibrary("DarkCore.dll");
	if (DarkCoreHandle == NULL){
		std::cout << "------ WARNING DARKCORE.DLL NOT LODED -----\n";
		std::cout << GetLastErrorAsString();
		std::cout << "------ WARNING DARKCORE.DLL NOT LODED -----\n";
	}
	std::cout << "------------- Loaded DarkTests ------------\n";
	SetPlayerName();
	ShowPlayernameLoop();
	return 0;
}

void ShowPlayernameLoop()
{
	std::cout << "ShowPlayernameLoop()\n";
	while (true){
		std::cout << PlayerName + "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void SetPlayerName()
{
	std::cout << "SetPlayerName()\n";
	char NameRandom[24];
	gen_random(NameRandom, 3);
	PlayerName = "Dark" + std::string(NameRandom) +"Player";
}

void gen_random(char *s, const int len) 
{
    srand(time(0));
	std::cout << "gen_random()\n";
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
}

std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}