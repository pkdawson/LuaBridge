#include <cstdlib>
#include <iostream>
#include <lua.hpp>
#include <LuaBridge.h>

using std::cout;
using std::endl;
using luabridge::LuaRef;
using luabridge::getGlobal;

void Multiply(int a, int b)
{
  cout << a << " x " << b << " = " <<  a * b << endl;
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    std::function<void(int,int)> X = &Multiply;
    std::function<void(int)> Y = std::bind(&Multiply, 42, std::placeholders::_1);
    luabridge::getGlobalNamespace(L)
      .addFunction("X", X)
      .addFunction("Y", Y);
    const char *source =
        "X( 10, 12 )\n"
        "Y( 5 )\n"
        "";
    cout << source << endl;
    if(luaL_dostring(L, source))
    {
        cout << lua_tostring(L, -1) << endl;
        lua_pop(L, 1);
        return 1;
    }
    lua_close(L);
    return 0;
}
