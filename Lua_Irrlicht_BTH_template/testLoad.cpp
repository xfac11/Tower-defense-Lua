#include"Game.h"
#define _IRR_COMPILE_WITH_BMP_LOADER_
void ConsoleThread(lua_State* L)
{
	char command[1000];
	while (GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

int main()
{
	Game game;
	/*
	En bra tumregel f?r att separera logik fr?n C++ ?r att t?nka p? att C++-delen ska kunna anv?ndas till olika typer av spel.
	Det ?r i Lua vi faktiskt skapar spelet. I verkligheten ?r det sj?lvklart inte s? extremt, men i uppgiften g?r vi s? f?r tydlighetens skull
	*/
	//std::thread conThread(ConsoleThread, game.L);

	game.run();


	//conThread.join();
	return 0;
}