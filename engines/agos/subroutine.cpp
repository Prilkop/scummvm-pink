/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2006 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "common/stdafx.h"

#include "agos/agos.h"
#include "agos/intern.h"

using Common::File;

namespace AGOS {

// Script opcodes to load into memory
static const char *const opcode_arg_table_elvira1[300] = {
	"I ", "I ", "I ", "I ", "I ", "I ", "I ", "I ",	 "II ",	"II ", "II ", "II ", "F ", "F ", "FN ",
	"FN ", "FN ", "FN ", "FF ", "FF ", "FF ", "FF ", "II ", "II ", "a ", "a ", "n ", "n ", "p ",
	"N ", "I ", "I ", "I ",	 "I ",	"IN ",	"IB ", "IB ", "II ", "IB ", "N ", " ", " ", " ", "I ",
	"I ","I ","I ", "I ","I ","I ",	"II ","II ","II ","II ","IBF ", "FIB ", "FF ", "N ", "NI ",
	"IF ", "F ", "F ", "IB ", "IB ", "FN ",	"FN ", "FN ", "FF ", "FF ", "FN ", "FN ", "FF ", "FF ",
	"FN ", "FF ", "FN ", "F ", "I ", "IN ", "IN ", "IB ", "IB ", "IB ", "IB ", "II ", "I ", "I ",
	"IN ", "T ", "F ", " ", "T ", "T ", "I ", "I ", " ", " ", "T ", " ", " ", " ", " ", " ", "T ",
	" ", "N ", "INN ", "II ", "II ", "ITN ", "ITIN ", "ITIN ", "I3 ", "IN ", "I ",	 "I ", "Ivnn ",
	"vnn ", "Ivnn ", "NN ",	"IT ", "INN ", " ", "N ", "N ", "N ", "T ", "v ", " ", " ", " ", " ",
	"FN ", "I ", "TN ", "IT ", "II ", "I ", " ", "N ", "I ", " ", "I ", "NI ", "I ", "I ", "T ",
	"I ", "I ", "N ", "N ", " ", "N ", "IF ", "IF ", "IF ", "IF ", "IF ", "IF ", "T ", "IB ",
	"IB ", "IB ", "I ", " ", "vnnN ", "Ivnn ", "T ", "T ", "T ", "IF ", " ", " ", " ", "Ivnn ",
	"IF ", "INI ", "INN ",  "IN ", "II ", "IFF ", "IIF ", "I ", "II ", "I ", "I ", "IN ", "IN ",
	"II ", "II ", "II ", "II ", "IIN ", "IIN ",  "IN ", "II ", "IN ", "IN ", "T ", "vanpan ",
	"vIpI ", "T ", "T ", " ", " ",	"IN ", "IN ", "IN ", "IN ", "N ", "INTTT ",  "ITTT ",
	"ITTT ", "I ", "I ", "IN ", "I ", " ", "F ", "NN ", "INN ", "INN ", "INNN ", "TF ", "NN ",
	"N ", "NNNNN ", "N ", " ", "NNNNNNN ", "N ", " ", "N ",	"NN ", "N ", "NNNNNIN ", "N ", "N ",
	"N ", "NNN ", "NNNN ", "INNN ", "IN ", "IN ", "TT ", "I ", "I ", "I ", "TTT ", "IN ", "IN ",
	"FN ", "FN ", "FN ", "N ", "N ", "N ", "NI ", " ", " ",	 "N ", "I ", "INN ", "NN ", "N ",
	"N ", "Nan ", "NN ", " ", " ", " ", " ", " ", " ", " ", "IF ", "N ", " ", " ",	 " ", "II ",
	" ", "NI ","N ",
};

static const char *const opcode_arg_table_waxworks[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "B ", "B ", "BN ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BB ", "BB ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBB ", "BIB ", "BB ", "B ", "BI ", "IB ", "B ", "B ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BN ", "BN ", "BB ", "BB ", "BN ", "BB ", "BN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "B ", "T ", "T ", "NNNNNB ", "BT ", "BT ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", "T ", "T ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NBNNN ", "N ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NN ", "N ", "N ", "Ban ", "BB ", " ", " ", " ", " ", "IB ", "B ", " ", "II ", " ", "BI ", "N ",
	"I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "B ", "B ", "B ",	"B ",
	"IBB ", "IBN ", "IB ", "B ", " ", "TB ", "TB ", "I ", "N ", "B ", "INB ", "INB ", "INB ", "INB ",
	"INB ", "INB ", "INB ", "N ", " ", "INBB ", "B ", "B ", "Ian ", "B ", "B ", "B ", "B ", "T ",
	"T ", "B ", " ", "I ", " ", " "
};

static const char *const opcode_arg_table_simon1win[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "B ", "B ", "BN ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BB ", "BB ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBB ", "BIB ", "BB ", "B ", "BI ", "IB ", "B ", "B ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BN ", "BN ", "BB ", "BB ", "BN ", "BB ", "BN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "B ", "T ", "T ", "NNNNNB ", "BT ", "BTS ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", " ", " ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NBNNN ", "N ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NN ", "N ", "N ", "Ban ", "BB ", " ", " ", " ", " ", "IB ", "B ", " ", "II ", " ", "BI ", "N ",
	"I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "B ", "B ", "B ", "B ",
	"IBB ", "IBN ", "IB ", "B ", "BNBN ", "BBTS ", "N ", " ", "Ian ", "B ", "B ", "B ", "B ", "T ",
	"T ", "B ", " ", "I ", " ", " ", "BBI ", "NNBB ", "BBB ", " ", " ", " ", " ", "N ", "N ", " ",
	" ",
};

static const char *const opcode_arg_table_simon1dos[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "B ", "B ", "BN ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BB ", "BB ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBB ", "BIB ", "BB ", "B ", "BI ", "IB ", "B ", "B ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BN ", "BN ", "BB ", "BB ", "BN ", "BB ", "BN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "B ", "T ", "T ", "NNNNNB ", "BT ", "BT ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", " ", " ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NBNNN ", "N ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NN ", "N ", "N ", "Ban ", "BB ", " ", " ", " ", " ", "IB ", "B ", " ", "II ", " ", "BI ", "N ",
	"I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "B ", "B ", "B ", "B ",
	"IBB ", "IBN ", "IB ", "B ", "BNBN ", "BBT ", "N ", " ", "Ian ", "B ", "B ", "B ", "B ", "T ",
	"T ", "B ", " ", "I ", " ", " ", "BBI ", "NNBB ", "BBB ", " ", " ", " ", " ", "N ", "N ", " ",
	" ",
};

static const char *const opcode_arg_table_simon2win[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "B ", "B ", "BN ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BB ", "BB ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBB ", "BIB ", "BB ", "B ", "BI ", "IB ", "B ", "B ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BN ", "BN ", "BB ", "BB ", "BN ", "BB ", "BN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "B ", "T ", "T ", "NNNNNB ", "BT ", "BTS ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", " ", " ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NNBNNN ", "NN ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NNB ", "N ", "N ", "Ban ", "BB ", " ", " ", " ", " ", "IB ", "B ", " ", "II ", " ", "BI ",
	"N ", "I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "B ", "B ", "B ",
	"B ", "IBB ", "IBN ", "IB ", "B ", "BNBN ", "BBTS ", "N ", " ", "Ian ", "B ", "B ", "B ", "B ",
	"T ", "T ", "B ", " ", "I ", " ", " ", "BBI ", "NNBB ", "BBB ", " ", " ", " ", " ", "N ", "N ",
	" ", " ", "BT ", " ", "B "
};

static const char *const opcode_arg_table_simon2dos[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "B ", "B ", "BN ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BB ", "BB ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBB ", "BIB ", "BB ", "B ", "BI ", "IB ", "B ", "B ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BN ", "BN ", "BB ", "BB ", "BN ", "BB ", "BN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "B ", "T ", "T ", "NNNNNB ", "BT ", "BT ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", " ", " ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NNBNNN ", "NN ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NNB ", "N ", "N ", "Ban ", "BB ", " ", " ", " ", " ", "IB ", "B ", " ", "II ", " ", "BI ",
	"N ", "I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "B ", "B ", "B ",
	"B ", "IBB ", "IBN ", "IB ", "B ", "BNBN ", "BBT ", "N ", " ", "Ian ", "B ", "B ", "B ", "B ",
	"T ", "T ", "B ", " ", "I ", " ", " ", "BBI ", "NNBB ", "BBB ", " ", " ", " ", " ", "N ", "N ",
	" ", " ", "BT ", " ", "B "
};

static const char *const opcode_arg_table_feeblefiles[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "B ", "B ", "BN ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BB ", "BB ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBB ", "BIB ", "BB ", "B ", "BI ", "IB ", "B ", "B ", "BN ",
	"BN ", "BN ", "BB ", "BB ", "BN ", "BN ", "BB ", "BB ", "BN ", "BB ", "BN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "B ", "T ", "T ", "NNNNNB ", "BT ", "BTS ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", " ", " ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NNBNNN ", "NN ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NNB ", "N ", "N ", "Ban ", " ", " ", " ", " ", " ", "IB ", "B ", " ", "II ", " ", "BI ",
	"N ", "I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "B ", "B ", "B ",
	"B ", "IBB ", "IBN ", "IB ", "B ", "BNNN ", "BBTS ", "N ", " ", "Ian ", "B ", "B ", "B ", "B ",
	"T ", "N ", " ", " ", "I ", " ", " ", "BBI ", "NNBB ", "BBB ", " ", " ", "T ", " ", "N ", "N ",
	" ", " ", "BT ", " ", "B ", " ", "BBBB ", " ", " ", "BBBB ", "B ", "B ", "B ", "B "
};

static const char *const opcode_arg_table_puzzlepack[256] = {
	" ", "I ", "I ", "I ", "I ", "I ", "I ", "II ", "II ", "II ", "II ", "N ", "N ", "NN ", "NN ",
	"NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "II ", "II ", "N ", "I ", "I ", "I ", "IN ", "IB ",
	"II ", "I ", "I ", "II ", "II ", "IBN ", "NIB ", "NN ", "B ", "BI ", "IN ", "N ", "N ", "NN ",
	"NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "NN ", "B ", "I ", "IB ",
	"IB ", "II ", "I ", "I ", "IN ", "N ", "T ", "T ", "NNNNNB ", "BTNN ", "BTS ", "T ", " ", "B ",
	"N ", "IBN ", "I ", "I ", "I ", "NN ", " ", " ", "IT ", "II ", "I ", "B ", " ", "IB ", "IBB ",
	"IIB ", "T ", " ", " ", "IB ", "IB ", "IB ", "B ", "BB ", "IBB ", "NB ", "N ", "NNBNNN ", "NN ",
	" ", "BNNNNNN ", "B ", " ", "B ", "B ", "BB ", "NNNNNIN ", "N ", "N ", "N ", "NNN ", "NBNN ",
	"IBNN ", "IB ", "IB ", "IB ", "IB ", "N ", "N ", "N ", "BI ", " ", " ", "N ", "I ", "IBB ",
	"NNB ", "N ", "N ", "Ban ", " ", " ", " ", " ", " ", "IN ", "B ", " ", "II ", " ", "BI ",
	"N ", "I ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "IB ", "BI ", "BB ", "N ", "N ", "N ",
	"N ", "IBN ", "IBN ", "IN ", "B ", "BNNN ", "BBTS ", "N ", " ", "Ian ", "B ", "B ", "B ", "B ",
	"T ", "N ", " ", " ", "I ", " ", " ", "BBI ", "NNBB ", "BBB ", " ", " ", "T ", " ", "N ", "N ",
	" ", " ", "BT ", " ", "B ", " ", "BBBB ", " ", " ", "BBBB ", "B ", "B ", "B ", "B "
};

Subroutine *AGOSEngine::getSubroutineByID(uint subroutine_id) {
	Subroutine *cur;

	_subroutine = subroutine_id;

	for (cur = _subroutineList; cur; cur = cur->next) {
		if (cur->id == subroutine_id)
			return cur;
	}

	if (loadXTablesIntoMem(subroutine_id)) {
		for (cur = _subroutineList; cur; cur = cur->next) {
			if (cur->id == subroutine_id)
				return cur;
		}
	}

	if (loadTablesIntoMem(subroutine_id)) {
		for (cur = _subroutineList; cur; cur = cur->next) {
			if (cur->id == subroutine_id)
				return cur;
		}
	}

	if (subroutine_id != 160)
		debug(0,"getSubroutineByID: subroutine %d not found", subroutine_id);
	return NULL;
}

void AGOSEngine::alignTableMem() {
	if ((unsigned long)_tablesHeapPtr & 3) {
		_tablesHeapPtr += 2;
		_tablesHeapCurPos += 2;
	}
}

byte *AGOSEngine::allocateTable(uint size) {
	byte *org = _tablesHeapPtr;

	size = (size + 1) & ~1;

	_tablesHeapPtr += size;
	_tablesHeapCurPos += size;

	if (_tablesHeapCurPos > _tablesHeapSize)
		error("Tablesheap overflow");

	return org;
}

File *AGOSEngine::openTablesFile(const char *filename) {
	if (getFeatures() & GF_OLD_BUNDLE)
		return openTablesFile_simon1(filename);
	else
		return openTablesFile_gme(filename);
}

File *AGOSEngine::openTablesFile_simon1(const char *filename) {
	File *fo = new File();
	fo->open(filename);
	if (fo->isOpen() == false)
		error("openTablesFile: Can't open '%s'", filename);
	return fo;
}

File *AGOSEngine::openTablesFile_gme(const char *filename) {
	uint res;
	uint32 offs;

	res = atoi(filename + 6) + _tableIndexBase - 1;
	offs = _gameOffsetsPtr[res];

	_gameFile->seek(offs, SEEK_SET);
	return _gameFile;
}

bool AGOSEngine::loadTablesIntoMem(uint subr_id) {
	if (getGameType() == GType_ELVIRA || getGameType() == GType_ELVIRA2)
		return loadTablesOldIntoMem(subr_id);
	else
		return loadTablesNewIntoMem(subr_id);
}


bool AGOSEngine::loadTablesOldIntoMem(uint subr_id) {
	byte *p;
	uint16 min_num, max_num, file_num;
	File *in;
	char filename[30];

	if (_tblList == NULL)
		return 0;

	p = _tblList + 32;

	min_num = READ_BE_UINT16(p);
	max_num = READ_BE_UINT16(p + 2);
	file_num = *(p + 4);
	p += 6;

	while (min_num) {
		if ((subr_id >= min_num) && (subr_id <= max_num)) {
			_subroutineList = _subroutineListOrg;
			_tablesHeapPtr = _tablesHeapPtrOrg;
			_tablesHeapCurPos = _tablesHeapCurPosOrg;
			_stringIdLocalMin = 1;
			_stringIdLocalMax = 0;

			sprintf(filename, "TABLES%.2d", file_num);
			in = openTablesFile(filename);
			readSubroutineBlock(in);
			closeTablesFile(in);

			alignTableMem();

			_tablesheapPtrNew = _tablesHeapPtr;
			_tablesHeapCurPosNew = _tablesHeapCurPos;

			if (_tablesHeapCurPos > _tablesHeapSize)
				error("loadTablesOldIntoMem: Out of table memory");
			return 1;
		}

		min_num = READ_BE_UINT16(p);
		max_num = READ_BE_UINT16(p + 2);
		file_num = *(p + 4);
		p += 6;
	}

	debug(1,"loadTablesOldIntoMem: didn't find %d", subr_id);
	return 0;
}

bool AGOSEngine::loadTablesNewIntoMem(uint subr_id) {
	byte *p;
	int i;
	uint min_num, max_num;
	char filename[30];
	File *in;

	p = _tblList;
	if (p == NULL)
		return 0;

	while (*p) {
		for (i = 0; *p; p++, i++)
			filename[i] = *p;
		filename[i] = 0;
		p++;

		for (;;) {
			min_num = READ_BE_UINT16(p); p += 2;
			if (min_num == 0)
				break;

			max_num = READ_BE_UINT16(p); p += 2;

			if (subr_id >= min_num && subr_id <= max_num) {
				_subroutineList = _subroutineListOrg;
				_tablesHeapPtr = _tablesHeapPtrOrg;
				_tablesHeapCurPos = _tablesHeapCurPosOrg;
				_stringIdLocalMin = 1;
				_stringIdLocalMax = 0;

				in = openTablesFile(filename);
				readSubroutineBlock(in);
				closeTablesFile(in);
				if (getGameType() == GType_SIMON2) {
					_sound->loadSfxTable(_gameFile, _gameOffsetsPtr[atoi(filename + 6) - 1 + _soundIndexBase]);
				} else if (getGameType() == GType_SIMON1 && getPlatform() == Common::kPlatformWindows) {
					memcpy(filename, "SFXXXX", 6);
					if (atoi(filename + 6) != 1 && atoi(filename + 6) != 30)
						_sound->readSfxFile(filename);
				}

				alignTableMem();

				_tablesheapPtrNew = _tablesHeapPtr;
				_tablesHeapCurPosNew = _tablesHeapCurPos;

				if (_tablesHeapCurPos > _tablesHeapSize)
					error("loadTablesNewIntoMem: Out of table memory");
				return 1;
			}
		}
	}

	debug(1,"loadTablesNewIntoMem: didn't find %d", subr_id);
	return 0;
}

bool AGOSEngine::loadXTablesIntoMem(uint subr_id) {
	byte *p;
	int i;
	uint min_num, max_num;
	char filename[30];
	File *in;

	p = _xtblList;
	if (p == NULL)
		return 0;

	while (*p) {
		for (i = 0; *p; p++, i++)
			filename[i] = *p;
		filename[i] = 0;
		p++;

		for (;;) {
			min_num = READ_BE_UINT16(p);
			p += 2;

			if (min_num == 0)
				break;

			max_num = READ_BE_UINT16(p);
			p += 2;

			if (subr_id >= min_num && subr_id <= max_num) {
				_subroutineList = _xsubroutineListOrg;
				_tablesHeapPtr = _xtablesHeapPtrOrg;
				_tablesHeapCurPos = _xtablesHeapCurPosOrg;
				_stringIdLocalMin = 1;
				_stringIdLocalMax = 0;

				in = openTablesFile(filename);
				readSubroutineBlock(in);
				closeTablesFile(in);

				alignTableMem();

				_subroutineListOrg = _subroutineList;
				_tablesHeapPtrOrg = _tablesHeapPtr;
				_tablesHeapCurPosOrg = _tablesHeapCurPos;
				_tablesheapPtrNew = _tablesHeapPtr;
				_tablesHeapCurPosNew = _tablesHeapCurPos;

				return 1;
			}
		}
	}

	debug(1,"loadXTablesIntoMem: didn't find %d", subr_id);
	return 0;
}

void AGOSEngine::closeTablesFile(File *in) {
	if (getFeatures() & GF_OLD_BUNDLE) {
		in->close();
		delete in;
	}
}

Subroutine *AGOSEngine::createSubroutine(uint id) {
	Subroutine *sub;

	alignTableMem();

	sub = (Subroutine *)allocateTable(sizeof(Subroutine));
	sub->id = id;
	sub->first = 0;
	sub->next = _subroutineList;
	_subroutineList = sub;
	return sub;
}

SubroutineLine *AGOSEngine::createSubroutineLine(Subroutine *sub, int where) {
	SubroutineLine *sl, *cur_sl = NULL, *last_sl = NULL;

	if (sub->id == 0)
		sl = (SubroutineLine *)allocateTable(SUBROUTINE_LINE_BIG_SIZE);
	else
		sl = (SubroutineLine *)allocateTable(SUBROUTINE_LINE_SMALL_SIZE);

	// where is what offset to insert the line at, locate the proper beginning line
	if (sub->first != 0) {
		cur_sl = (SubroutineLine *)((byte *)sub + sub->first);
		while (where) {
			last_sl = cur_sl;
			cur_sl = (SubroutineLine *)((byte *)sub + cur_sl->next);
			if ((byte *)cur_sl == (byte *)sub)
				break;
			where--;
		}
	}

	if (last_sl != NULL) {
		// Insert the subroutine line in the middle of the link
		last_sl->next = (byte *)sl - (byte *)sub;
		sl->next = (byte *)cur_sl - (byte *)sub;
	} else {
		// Insert the subroutine line at the head of the link
		sl->next = sub->first;
		sub->first = (byte *)sl - (byte *)sub;
	}

	return sl;
}

void AGOSEngine::runSubroutine101() {
	Subroutine *sub;

	if (getGameType() == GType_ELVIRA) {
		// HACK
		sub = getSubroutineByID(1);
	} else {
		sub = getSubroutineByID(101);
	}

	if (sub != NULL)
		startSubroutineEx(sub);

	permitInput();
}

int AGOSEngine::startSubroutine(Subroutine *sub) {
	int result = -1;
	SubroutineLine *sl;
	const byte *old_code_ptr;

	if (_startMainScript)
		dumpSubroutine(sub);

	old_code_ptr = _codePtr;

	if (++_recursionDepth > 40)
		error("Recursion error");

	// WORKAROUND: Bit Flag 171 isn't set when Simon rides the lion to the
	// goblin camp in non-English versions. Bit Flag 171 is required to display 
	// the red trail between locations on the map, during the ride.
	if (getGameType() == GType_SIMON2) {
		if (sub->id == 13020)
			setBitFlag(171, true);
		if (sub->id == 13021)
			setBitFlag(171, false);
	}

	sl = (SubroutineLine *)((byte *)sub + sub->first);

	while ((byte *)sl != (byte *)sub) {
		if (checkIfToRunSubroutineLine(sl, sub)) {
			result = 0;
			_codePtr = (byte *)sl;
			if (sub->id)
				_codePtr += 2;
			else
				_codePtr += 8;

			if (_continousMainScript)
				printf("; %d\n", sub->id);
			result = runScript();
			if (result != 0) {
				/* result -10 means restart subroutine */
				if (result == -10) {
					delay(0);							/* maybe leave control to the VGA */
					sl = (SubroutineLine *)((byte *)sub + sub->first);
					continue;
				}
				break;
			}
		}
		sl = (SubroutineLine *)((byte *)sub + sl->next);
	}

	_codePtr = old_code_ptr;

	_recursionDepth--;
	return result;
}

int AGOSEngine::startSubroutineEx(Subroutine *sub) {
	return startSubroutine(sub);
}

bool AGOSEngine::checkIfToRunSubroutineLine(SubroutineLine *sl, Subroutine *sub) {
	if (sub->id)
		return true;

	if (sl->verb != -1 && sl->verb != _scriptVerb &&
			(sl->verb != -2 || _scriptVerb != -1))
		return false;

	if (sl->noun1 != -1 && sl->noun1 != _scriptNoun1 &&
			(sl->noun1 != -2 || _scriptNoun1 != -1))
		return false;

	if (sl->noun2 != -1 && sl->noun2 != _scriptNoun2 &&
			(sl->noun2 != -2 || _scriptNoun2 != -1))
		return false;

	return true;
}

void AGOSEngine::readSubroutineBlock(File *in) {
	while (in->readUint16BE() == 0) {
		readSubroutine(in, createSubroutine(in->readUint16BE()));
	}
}
void AGOSEngine::readSubroutine(File *in, Subroutine *sub) {
	while (in->readUint16BE() == 0) {
		readSubroutineLine(in, createSubroutineLine(sub, 0xFFFF), sub);
	}
}

void AGOSEngine::readSubroutineLine(File *in, SubroutineLine *sl, Subroutine *sub) {
	byte line_buffer[2048], *q = line_buffer;
	int size;

	if (sub->id == 0) {
		sl->verb = in->readUint16BE();
		sl->noun1 = in->readUint16BE();
		sl->noun2 = in->readUint16BE();
	} else if (getGameType() == GType_ELVIRA) {
		in->readUint16BE();
		in->readUint16BE();
		in->readUint16BE();
	}

	if (getGameType() == GType_ELVIRA) {
		int16 tmp = in->readUint16BE();
		WRITE_BE_UINT16(q, tmp);
		while (tmp != 10000) {
			if (READ_BE_UINT16(q) == 0xC6) {
				in->readUint16BE();
			} else {
				q = readSingleOpcode(in, q);
			}

			tmp = in->readUint16BE();
			WRITE_BE_UINT16(q, tmp);
		}

		size = (q - line_buffer + 1) * 2;
		memcpy(allocateTable(size), line_buffer, size);
	} else {
		while ((*q = in->readByte()) != 0xFF) {
			if (*q == 87) {
				in->readUint16BE();
			} else {
				q = readSingleOpcode(in, q);
			}
		}

		size = (q - line_buffer + 1);
		memcpy(allocateTable(size), line_buffer, size);
	}
}

byte *AGOSEngine::readSingleOpcode(Common::File *in, byte *ptr) {
	int i, l;
	const char *string_ptr;
	uint opcode, val;

	const char *const *table;

	if (getGameType() == GType_PP)
		table = opcode_arg_table_puzzlepack;
	else if (getGameType() == GType_FF)
		table = opcode_arg_table_feeblefiles;
	else if (getGameType() == GType_SIMON2 && (getFeatures() & GF_TALKIE))
		table = opcode_arg_table_simon2win;
	else if (getGameType() == GType_SIMON2)
		table = opcode_arg_table_simon2dos;
	else if (getGameType() == GType_SIMON1 && (getFeatures() & GF_TALKIE))
		table = opcode_arg_table_simon1win;
	else if (getGameType() == GType_SIMON1)
		table = opcode_arg_table_simon1dos;
	else if (getGameType() == GType_WW || getGameType() == GType_ELVIRA2)
		table = opcode_arg_table_waxworks;
	else
		table = opcode_arg_table_elvira1;

	i = 0;
	if (getGameType() == GType_ELVIRA) {
		opcode = READ_BE_UINT16(ptr);
		ptr += 2;
	} else {
		opcode = *ptr++;
	}

	string_ptr = table[opcode];
	if (!string_ptr)
		error("Unable to locate opcode table. Perhaps you are using the wrong game target?");

	for (;;) {
		if (string_ptr[i] == ' ')
			return ptr;

		l = string_ptr[i++];

		switch (l) {
		case 'F':
		case 'N':
		case 'S':
		case 'a':
		case 'n':
		case 'p':
		case 'v':
		case '3':
			val = in->readUint16BE();
			WRITE_BE_UINT16(ptr, val); ptr += 2;
			break;

		case 'B':
			if (getGameType() == GType_ELVIRA) {
				val = in->readUint16BE();
				WRITE_BE_UINT16(ptr, val); ptr += 2;
			} else {
				*ptr++ = in->readByte();
				if (ptr[-1] == 0xFF) {
					*ptr++ = in->readByte();
				}
			}
			break;

		case 'I':
			val = in->readUint16BE();
			switch (val) {
			case 1:
				val = 0xFFFF;
				break;
			case 3:
				val = 0xFFFD;
				break;
			case 5:
				val = 0xFFFB;
				break;
			case 7:
				val = 0xFFF9;
				break;
			case 9:
				val = 0xFFF7;
				break;
			default:
				val = fileReadItemID(in);;
			}
			WRITE_BE_UINT16(ptr, val); ptr += 2;
			break;

		case 'T':
			val = in->readUint16BE();
			switch (val) {
			case 0:
				val = 0xFFFF;
				break;
			case 3:
				val = 0xFFFD;
				break;
			default:
				val = (uint16)in->readUint32BE();
				break;
			}
			WRITE_BE_UINT16(ptr, val); ptr += 2;
			break;
		default:
			error("readSingleOpcode: Bad cmd table entry %c", l);
		}
	}
}

} // End of namespace AGOS
