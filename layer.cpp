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

struct pin : openmini::bus::pin {
	int id;
	mode mode;
	pin(int id, enum mode mode) : id(id), mode(mode) {}
};
pin debug_uart_rx {0, openmini::bus::pin::INPUT};
pin debug_uart_tx {1, openmini::bus::pin::OUTPUT};
pin debug_i2c_rx {2, openmini::bus::pin::INPUT};
pin debug_i2c_tx {3, openmini::bus::pin::OUTPUT};
pin module_rx {4, openmini::bus::pin::INPUT};
pin module_tx {4, openmini::bus::pin::OUTPUT};
static openmini::bus::uart module_uart {module_tx,module_rx};

openmini::modules::protocol openmini::modules::protocol::bus {&module_uart};
openmini::