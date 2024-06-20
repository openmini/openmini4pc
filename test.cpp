#include "api/main.hpp"
#include "api/screen.hpp"
#include "api/builtin.hpp"
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
	openmini::builtin::screen.draw(testimg, 0, 0, 8, 8);
	openmini::builtin::screen.sync();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}