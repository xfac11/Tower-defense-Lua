#include<Tower-defense-Lua/Game.h>
#define _IRR_COMPILE_WITH_BMP_LOADER_
void static ConsoleThread(lua_State* L)
{
	char command[1000];
	while (GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
		
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	std::thread conThread(ConsoleThread, game.L);

	game.run();


	conThread.join();
	return 0;
}