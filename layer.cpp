/*******************************************************************************

Copyright 2024 openmini (copyright@openmini.org)

This file is part of openmini.

openmini is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

openmini is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
openmini. If not, see <https://www.gnu.org/licenses/>.

*******************************************************************************/
#include "api/bus/pin.hpp"
#include "api/everything.hpp"
#include "api/main.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <vector>
using namespace SDL2pp;
openmini::screen::screen() {}
void openmini::screen::draw(uint16_t *buf, int16_t x, int16_t y, uint8_t width, uint8_t height) {}
void openmini::screen::fill(int16_t x, int16_t y, uint8_t width, uint8_t height, uint16_t color) {}
void openmini::screen::sync() {}
void openmini::screen::setSync(bool) {}
struct screen : openmini::screen {
	uint16_t width = 320,
			 height = 240;
	bool canSync = true;
	uint16_t state[320*240];
	SDL sdl {SDL_INIT_VIDEO};
	Window win {"openmini4pc",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,0};
	Renderer render {win,-1,SDL_RENDERER_ACCELERATED};
	Texture tex {render,SDL_PIXELFORMAT_ARGB1555,SDL_TEXTUREACCESS_STATIC,320,240};
	bool autoSync = false;
	void sync() override {
		tex.Update(Rect(0,0,320,240),state,320*2);
		render.Copy(tex,Rect(0,0,320,240),Rect(0,0,640,480));
		render.Present();
	}
	void setSync(bool value) override {autoSync=!value;}
	screen() {}
	~screen() {}
	void write(int x, int y, uint16_t z) {
		if (x<0) return;
		if (y<0) return;
		if (x>=width) return;
		if (y>=height) return;
		state[y*width+x]=z;
		if (autoSync) sync();
	}
	void draw(uint16_t *buf, int16_t x0, int16_t y0, uint8_t width, uint8_t height) override {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				write(x0+x,y0+y,*buf);
				++buf;
			}
		}
	}
	void fill(int16_t x0, int16_t y0, uint8_t width, uint8_t height, uint16_t color) override {
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
				write(x0+x,y0+y,color);
	}
};
screen builtin_screen;

openmini::bus::uart::uart(pin &tx, pin &rx) : tx(tx),rx(rx) {}
int openmini::bus::uart::send(const void *buf, int length) {
	std::cerr.write(static_cast<const char*>(buf),length);
	return length;
}
int openmini::bus::uart::recv(void *buf, int length) {
	std::cin.read(static_cast<char*>(buf),length);
	return length;
}
struct sdl2input : openmini::input {
	bool poll() override {
		for (int i = 0; i < 16; i++) changed[i]=false;
		SDL_Event event;
		bool flag = false;
		while (SDL_PollEvent(&event)) {
			if (event.type==SDL_QUIT) {
				std::exit(0);
			} else if ((event.type==SDL_KEYDOWN)||(event.type==SDL_KEYUP)) {
				bool ka = event.type==SDL_KEYDOWN;
				switch (event.key.keysym.sym) {
					case SDLK_RETURN: // OK
						active[button::ok]=ka;
						changed[button::ok]=true;
						flag=true;
						break;
					case SDLK_UP: // up
						active[button::up]=ka;
						changed[button::up]=true;
						flag=true;
						break;
					case SDLK_DOWN: // down
						active[button::down]=ka;
						changed[button::down]=true;
						flag=true;
						break;
					case SDLK_LEFT: // left
						active[button::left]=ka;
						changed[button::left]=true;
						flag=true;
						break;
					case SDLK_RIGHT: // right
						active[button::right]=ka;
						changed[button::right]=true;
						flag=true;
						break;
					case SDLK_BACKSPACE: // back
						active[button::back]=ka;
						changed[button::back]=true;
						flag=true;
						break;
					case SDLK_h: // home
						active[button::home]=ka;
						changed[button::home]=true;
						flag=true;
						break;
					case SDLK_m: // menu
						active[button::menu]=ka;
						changed[button::menu]=true;
						flag=true;
						break;
					case SDLK_ESCAPE: // quit
						active[button::quit]=ka;
						changed[button::quit]=true;
						flag=true;
						break;
					case SDLK_1: // f1
						active[button::f1]=ka;
						changed[button::f1]=true;
						flag=true;
						break;
					case SDLK_2: // f2
						active[button::f2]=ka;
						changed[button::f2]=true;
						flag=true;
						break;
					case SDLK_3: // f3
						active[button::f3]=ka;
						changed[button::f3]=true;
						flag=true;
						break;
				}
			}
		}
		return flag;
	}
};
std::vector<std::string> openmini::storage::filesystem::ls(std::string) {return {};}
std::unique_ptr<openmini::storage::file> openmini::storage::filesystem::open(std::string,bool) {return nullptr;}
void openmini::storage::device::read(uint64_t, void *, uint32_t) {}
void openmini::storage::device::write(uint64_t, void *, uint32_t) {}
void openmini::storage::device::sync() {}
void openmini::storage::file::read(uint64_t, void *, uint32_t) {}
void openmini::storage::file::write(uint64_t, void *, uint32_t) {}
void openmini::storage::file::resize(uint64_t) {}
void openmini::storage::file::close() {}
bool openmini::input::poll() {return false;}
struct builtinfs : openmini::storage::filesystem {
	struct file : openmini::storage::file {
		const bool readonly;
		std::fstream f;
		std::string name;
		file(std::string name, bool readonly) : name(name),readonly(readonly),f(name,std::ios_base::in|std::ios_base::openmode(readonly?0:std::ios_base::out)|std::ios_base::binary) {}
		void write(uint64_t pos, void *buf, uint32_t size) override {
			f.seekp(pos,f.beg);
			f.write(static_cast<const char*>(buf),size);
		}
		void read(uint64_t pos, void *buf, uint32_t size) override {
			f.seekg(pos,f.beg);
			f.read(static_cast<char*>(buf),size);
		}
		void resize(uint64_t size) override {
			f.close();
			std::error_code ec;
			std::filesystem::resize_file(std::filesystem::path(name), size, ec);
			f=std::fstream(name,std::ios_base::in|std::ios_base::openmode(readonly?0:std::ios_base::out)|std::ios_base::binary);
		}
		void close() override {
			f.close();
		}
	};
	std::unique_ptr<openmini::storage::file> open(std::string path, bool ro = true) override {
		file *f = new file{path,ro};
		return std::unique_ptr<openmini::storage::file>(static_cast<openmini::storage::file*>(f));
	}
	std::vector<std::string> ls(std::string path) override {
		std::vector<std::string> files;
		auto iter = std::filesystem::directory_iterator(path);
		for (auto x : iter)
			files.emplace_back(x.path().filename().string());
		return files;
	}
};
void openmini::bus::pin::set(bool) {}
bool openmini::bus::pin::get() {return false;}
openmini::bus::pin::mode openmini::bus::pin::setMode(openmini::bus::pin::mode) {return INPUT;}
openmini::bus::pin::mode openmini::bus::pin::getMode() {return INPUT;}
void openmini::bus::pin::analog::set(float) {}
float openmini::bus::pin::analog::get() {return 0.0;}
openmini::bus::pin::mode openmini::bus::pin::analog::setMode(openmini::bus::pin::mode) {return INPUT;}
openmini::bus::pin::mode openmini::bus::pin::analog::getMode() {return INPUT;}
sdl2input builtin_input;
openmini::bus::pin nil_pin;
openmini::bus::uart builtin_debug_uart{nil_pin,nil_pin};
openmini::screen &openmini::builtin::screen = builtin_screen;
openmini::bus::uart &openmini::builtin::debug = builtin_debug_uart;
openmini::input &openmini::builtin::input = builtin_input;
builtinfs builtin_fs;
openmini::storage::filesystem &openmini::builtin::fs = builtin_fs;