#ifdef TARGET_GNW
#include "build/config.h"
#endif

#if !defined(TARGET_GNW) || (defined(TARGET_GNW) &&  defined(ENABLE_EMULATOR_NES) && FORCE_NOFRENDO == 0)
/* FCE Ultra - NES/Famicom Emulator
 *
 * Copyright notice for this file:
 *  Copyright (C) 2005 CaH4e3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "mapinc.h"

static uint8 latche;

static void Sync(void) {
	setprg16(0x8000, latche);
	setprg16(0xC000, 8);
}

static DECLFW(DREAMWrite) {
	latche = V & 7;
	Sync();
}

static void DREAMPower(void) {
	latche = 0;
	Sync();
	setchr8(0);
	SetReadHandler(0x8000, 0xFFFF, CartBR);
	SetWriteHandler(0x5020, 0x5020, DREAMWrite);
}

static void Restore(int version) {
	Sync();
}

void DreamTech01_Init(CartInfo *info) {
	GameStateRestore = Restore;
	info->Power = DREAMPower;
	AddExState(&latche, 1, 0, "LATC");
}
#endif
