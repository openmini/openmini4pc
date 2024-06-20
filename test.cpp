#include "api/main.hpp"
#include "api/screen.hpp"
#include "api/builtin.hpp"
#include "api/input.hpp"
#include <chrono>
#include <thread>

int main(void) {
	uint16_t testimg[8*8] = {
		0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
		0x8000,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x8000,
		0x8000,0xffff,0x8000,0x8000,0x8000,0x8000,0xffff,0x8000,
		0x8000,0xffff,0x8000,0xffff,0xffff,0x8000,0xffff,0x8000,
		0x8000,0xffff,0x8000,0xffff,0xffff,0x8000,0xffff,0x8000,
		0x8000,0xffff,0x8000,0x8000,0x8000,0x8000,0xffff,0x8000,
		0x8000,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x8000,
		0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000
	};
	int x = 0, y = 0;
	while (true) {
		openmini::builtin::screen.draw(testimg, x, y, 8, 8);
		openmini::builtin::screen.sync();
		openmini::builtin::input.poll();
		if (openmini::builtin::input.active[openmini::input::button::up]) y--;
		if (openmini::builtin::input.active[openmini::input::button::down]) y++;
		if (openmini::builtin::input.active[openmini::input::button::left]) x--;
		if (openmini::builtin::input.active[openmini::input::button::right]) x++;
		if (openmini::builtin::input.active[openmini::input::button::quit]) break;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return 0;
}