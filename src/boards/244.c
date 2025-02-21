#ifdef TARGET_GNW
#include "build/config.h"
#endif

#if !defined(TARGET_GNW) || (defined(TARGET_GNW) &&  defined(ENABLE_EMULATOR_NES) && FORCE_NOFRENDO == 0)
/* FCE Ultra - NES/Famicom Emulator
 *
 * Copyright notice for this file:
 *  Copyright (C) 2012 CaH4e3
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

static uint8 preg, creg;
static SFORMAT StateRegs[] =
{
	{ &preg, 1, "PREG" },
	{ &creg, 1, "CREG" },
	{ 0 }
};

static uint8 prg_perm[4][4] = {
	{ 0, 1, 2, 3, },
	{ 3, 2, 1, 0, },
	{ 0, 2, 1, 3, },
	{ 3, 1, 2, 0, },
};

static uint8 chr_perm[8][8] = {
	{ 0, 1, 2, 3, 4, 5, 6, 7, },
	{ 0, 2, 1, 3, 4, 6, 5, 7, },
	{ 0, 1, 4, 5, 2, 3, 6, 7, },
	{ 0, 4, 1, 5, 2, 6, 3, 7, },
	{ 0, 4, 2, 6, 1, 5, 3, 7, },
	{ 0, 2, 4, 6, 1, 3, 5, 7, },
	{ 7, 6, 5, 4, 3, 2, 1, 0, },
	{ 7, 6, 5, 4, 3, 2, 1, 0, },
};

static void Sync(void) {
	setprg32(0x8000, preg);
	setchr8(creg);
}

static DECLFW(M244Write) {
	if (V & 8)
		creg = chr_perm[(V >> 4) & 7][V & 7];
	else
		preg = prg_perm[(V >> 4) & 3][V & 3];
	Sync();
}

static void M244Power(void) {
	preg = creg = 0;
	Sync();
	SetWriteHandler(0x8000, 0xFFFF, M244Write);
	SetReadHandler(0x8000, 0xFFFF, CartBR);
}

static void StateRestore(int version) {
	Sync();
}

void Mapper244_Init(CartInfo *info) {
	info->Power = M244Power;
	AddExState(&StateRegs, ~0, 0, 0);
	GameStateRestore = StateRestore;
}
#endif
