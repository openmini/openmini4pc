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
#include "api/everything.hpp"
#include "api/main.hpp"
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <cstdint>
using namespace SDL2pp;
openmini::screen::screen() {}
void openmini::screen::draw(uint16_t *buf, uint16_t x, uint16_t y, uint8_t width, uint8_t height) {}
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
		if (x>=height) return;
		state[y*width+x]=z;
		if (autoSync) sync();
	}
	void draw(uint16_t *buf, uint16_t x0, uint16_t y0, uint8_t width, uint8_t height) override {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				write(x0+x,y0+y,*buf);
				++buf;
			}
		}
	}
};
screen builtin_screen;
openmini::screen &openmini::builtin::screen = builtin_screen;