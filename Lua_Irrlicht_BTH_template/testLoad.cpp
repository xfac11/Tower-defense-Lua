#include"Game.h"
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
	En bra tumregel för att separera logik från C++ är att tänka på att C++-delen ska kunna användas till olika typer av spel.
	Det är i Lua vi faktiskt skapar spelet. I verkligheten är det självklart inte så extremt, men i uppgiften gör vi så för tydlighetens skull
	*/
	std::thread conThread(ConsoleThread, game.L);
	
	game.run();
	

	conThread.join();
	return 0;
}