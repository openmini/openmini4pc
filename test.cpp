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
	
	int x = 0, y = 0;
	while (true) {
		openmini::builtin::screen.fill(x*8, y*8, 8, 8, 0x8000);
		openmini::builtin::screen.fill(x*8+1, y*8+1, 6, 6, fillColor);
		openmini::builtin::screen.fill(x*8+2, y*8+2, 4, 4, 0x8000);
		openmini::builtin::screen.fill(x*8+3, y*8+3, 2, 2, grid[y*16+x]);
		openmini::builtin::screen.sync();
		openmini::builtin::screen.fill(x*8, y*8, 8, 8, grid[y*16+x]);
		openmini::builtin::input.poll();
		if (openmini::builtin::input.active[openmini::input::button::up]&&openmini::builtin::input.changed[openmini::input::button::up]) y--;
		if (openmini::builtin::input.active[openmini::input::button::down]&&openmini::builtin::input.changed[openmini::input::button::down]) y++;
		if (openmini::builtin::input.active[openmini::input::button::left]&&openmini::builtin::input.changed[openmini::input::button::left]) x--;
		if (openmini::builtin::input.active[openmini::input::button::right]&&openmini::builtin::input.changed[openmini::input::button::right]) x++;
		if (openmini::builtin::input.active[openmini::input::button::f1]&&openmini::builtin::input.changed[openmini::input::button::f1]) fillColor=(fillColor&0b1000001111111111)|(((fillColor&0b0111110000000000)+0b0000010000000000)&0b0111110000000000);
		if (openmini::builtin::input.active[openmini::input::button::f2]&&openmini::builtin::input.changed[openmini::input::button::f2]) fillColor=(fillColor&0b1111110000011111)|(((fillColor&0b0000001111100000)+0b0000000000100000)&0b0000001111100000);
		if (openmini::builtin::input.active[openmini::input::button::f3]&&openmini::builtin::input.changed[openmini::input::button::f3]) fillColor=(fillColor&0b1111111111100000)|(((fillColor&0b0000000000011111)+0b0000000000000001)&0b0000000000011111);
		if (openmini::builtin::input.active[openmini::input::button::back]&&openmini::builtin::input.changed[openmini::input::button::back]) fillColor=grid[y*16+x];
		if (openmini::builtin::input.active[openmini::input::button::ok]) grid[y*16+x]=fillColor;
		if (openmini::builtin::input.active[openmini::input::button::quit]) break;
		if (x<0) x=0;
		if (x>=16) x=15;
		if (y<0) y=0;
		if (y>=16) y=15;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	for (int i = 0; i < 16*16; i++) {
		std::string str = std::format("{:04x},",grid[i]);
		const char *buf = str.c_str();
		openmini::builtin::debug.send(buf, strlen(buf));
	}
	return 0;
}