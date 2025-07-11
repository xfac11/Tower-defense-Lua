#include <catch2/catch_test_macros.hpp>
#include<Tower-defense-Lua/Game.h>
unsigned int Factorial(unsigned int number)
{
	return number > 1 ? Factorial(number - 1) * number : 1;
}

TEST_CASE( "Factorials are computed", "[factorial]" )
{
	REQUIRE( Factorial(0) == 1 );
	REQUIRE( Factorial(1) == 1 );
	REQUIRE( Factorial(2) == 2 );
	REQUIRE( Factorial(3) == 6 );
	REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "Game Object Try constructor and destructor", "[game engine]")
{
	Game* game = new Game();
	REQUIRE(game != nullptr);
	delete game;
	game = nullptr;
	REQUIRE(game == nullptr);
}

TEST_CASE( "Create game and load", "[game engine]")
{
	Game* game = new Game();
	REQUIRE(game != nullptr);
	//Test a load with a script with good paths
	int result = luaL_dofile(game->L, RESOURCES_PATH "LuaScripts/tests/testLoad.lua");
	if(result != LUA_OK)
	{
		std::string errormsg = lua_tostring(game->L, -1);
		FAIL(errormsg);
	}
	REQUIRE(result == LUA_OK);
	//Test a load with a script with bad paths
	result = luaL_dofile(game->L, RESOURCES_PATH "LuaScripts/tests/testLoadFail.lua");
	if(result != LUA_OK)
	{
		std::string errormsg = lua_tostring(game->L, -1);
		INFO(errormsg);
	}
	REQUIRE(result != LUA_OK);

	delete game;
	game = nullptr;
	REQUIRE(game == nullptr);
}
