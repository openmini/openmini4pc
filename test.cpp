#include "api/main.hpp"
#include "api/screen.hpp"
#include "api/builtin.hpp"
#include "api/input.hpp"
#include <chrono>
#include <cstring>
#include <thread>

int main(void) {
	uint16_t fillColor = 0x8000;
	uint16_t grid[16*16];
	std::chrono::high_resolution_clock::time_point timer[16];
	bool active[16];
	int x = 0, y = 0;
	while (true) {
		for (int i = 0; i < 16; i++) active[i]=false;
		openmini::builtin::screen.fill(x*8, y*8, 8, 8, 0x8000);
		openmini::builtin::screen.fill(x*8+1, y*8+1, 6, 6, fillColor);
		openmini::builtin::screen.fill(x*8+2, y*8+2, 4, 4, 0x8000);
		openmini::builtin::screen.fill(x*8+3, y*8+3, 2, 2, grid[y*16+x]);
		openmini::builtin::screen.sync();
		openmini::builtin::screen.fill(x*8, y*8, 8, 8, grid[y*16+x]);
		openmini::builtin::input.poll();
		if (openmini::builtin::input.changed[openmini::input::button::up   ]) timer[openmini::input::button::up   ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::down ]) timer[openmini::input::button::down ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::left ]) timer[openmini::input::button::left ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::right]) timer[openmini::input::button::right]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::f1   ]) timer[openmini::input::button::f1   ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::f2   ]) timer[openmini::input::button::f2   ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::f3   ]) timer[openmini::input::button::f3   ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::back ]) timer[openmini::input::button::back ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::ok   ]) timer[openmini::input::button::ok   ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.changed[openmini::input::button::quit ]) timer[openmini::input::button::quit ]=std::chrono::high_resolution_clock::now();
		if (openmini::builtin::input.active[openmini::input::button::up   ]&&(timer[openmini::input::button::up   ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::up   ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::up   ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::down ]&&(timer[openmini::input::button::down ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::down ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::down ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::left ]&&(timer[openmini::input::button::left ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::left ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::left ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::right]&&(timer[openmini::input::button::right]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::right]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::right]=true;}
		if (openmini::builtin::input.active[openmini::input::button::f1   ]&&(timer[openmini::input::button::f1   ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::f1   ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::f1   ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::f2   ]&&(timer[openmini::input::button::f2   ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::f2   ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::f2   ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::f3   ]&&(timer[openmini::input::button::f3   ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::f3   ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::f3   ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::back ]&&(timer[openmini::input::button::back ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::back ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::back ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::ok   ]&&(timer[openmini::input::button::ok   ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::ok   ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::ok   ]=true;}
		if (openmini::builtin::input.active[openmini::input::button::quit ]&&(timer[openmini::input::button::quit ]<std::chrono::high_resolution_clock::now())) {timer[openmini::input::button::quit ]=std::chrono::high_resolution_clock::now()+std::chrono::milliseconds(100);active[openmini::input::button::quit ]=true;}
		
		if (active[openmini::input::button::up]) y--;
		if (active[openmini::input::button::down]) y++;
		if (active[openmini::input::button::left]) x--;
		if (active[openmini::input::button::right]) x++;
		if (active[openmini::input::button::f1]) fillColor=(fillColor&0b1000001111111111)|(((fillColor&0b0111110000000000)+0b0000010000000000)&0b0111110000000000);
		if (active[openmini::input::button::f2]) fillColor=(fillColor&0b1111110000011111)|(((fillColor&0b0000001111100000)+0b0000000000100000)&0b0000001111100000);
		if (active[openmini::input::button::f3]) fillColor=(fillColor&0b1111111111100000)|(((fillColor&0b0000000000011111)+0b0000000000000001)&0b0000000000011111);
		if (active[openmini::input::button::back]) fillColor=0b1000000000000000|grid[y*16+x];
		if (active[openmini::input::button::ok]) grid[y*16+x]=fillColor;
		if (active[openmini::input::button::quit]) break;
		if (x<0) x=0;
		if (x>=16) x=15;
		if (y<0) y=0;
		if (y>=16) y=15;
	}
	for (int i = 0; i < 16*16; i++) {
		std::string str = std::format("0x{:04x},",grid[i]);
		const char *buf = str.c_str();
		openmini::builtin::debug.send(buf, strlen(buf));
	}
	return 0;
}