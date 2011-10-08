/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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
 *
 */

#include "engines/advancedDetector.h"

#include "pink/pink.h"

static const PlainGameDescriptor pinkGames[] = {
	{ "peril", "Pink Panther: Passport to Peril" },
	{ "hokus", "Pink Panther: Hokus Pokus" },
	{ 0, 0 }
};

static const ADGameDescription gameDescriptions[] = {
	{
		"peril",
		"",
		{
			{ "pptp.orb", 0, "3567b5edb6ef1b7f56c0ce1d0ed14c30",  616292424 },
			{ NULL, 0, NULL, 0 }
		},
		Common::HE_ISR,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS
	},
	{
		"peril",
		"",
		{
			{ "pptp.orb", 0, "40553999b02818049427faf0dae9c46d",  618203600 },
			{ NULL, 0, NULL, 0 }
		},
		Common::EN_ANY,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS
	},
	{
		"peril",
		"",
		{
			{ "pptp.orb", 0, "73d8693b29fb85e28814cd3de13d2e0a",  644839372 },
			{ NULL, 0, NULL, 0 }
		},
		Common::PL_POL,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS
	},
	AD_TABLE_END_MARKER
};

class PinkMetaEngine : public AdvancedMetaEngine {
public:
	PinkMetaEngine() : AdvancedMetaEngine(gameDescriptions, sizeof(ADGameDescription), pinkGames) {
		_md5Bytes = 1024;
	}

	virtual const char *getName() const {
		return "Pink Panther Games Engine";
	}

	virtual const char *getOriginalCopyright() const {
		return "Copyright (C) Wanderlust Interactive";
	}

	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
		const ADGameDescription *gd = (const ADGameDescription *)desc;
		if (gd) {
			*engine = new Pink::PinkEngine(syst);
		}
		return gd != 0;
	}
};

#if PLUGIN_ENABLED_DYNAMIC(PINK)
	REGISTER_PLUGIN_DYNAMIC(PINK, PLUGIN_TYPE_ENGINE, PinkMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(PINK, PLUGIN_TYPE_ENGINE, PinkMetaEngine);
#endif
