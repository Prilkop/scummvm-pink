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

#include "pink/pink.h"

#include "common/array.h"
#include "common/system.h"
#include "common/hashmap.h"
#include "common/types.h"
#include "common/error.h"
#include "common/events.h"

#include "engines/util.h"
#include "video/flic_decoder.h"
#include "audio/audiostream.h"
#include "audio/decoders/wave.h"
#include "audio/mixer.h"

#include "objects/cruntimeclass.h"
#include "objects/cgame.h"
#include "objects/cmodule.h"
#include "objects/cmoduleproxy.h"
#include "objects/cgamepage.h"
#include "objects/cactor.h"
#include "objects/caction.h"
#include "objects/cactioncel.h"
#include "objects/cactionsound.h"


namespace Pink {

	using Common::String;

	PinkEngine::PinkEngine(OSystem *system) : Engine(system) {
	}

	PinkEngine::~PinkEngine() {
	}

	Common::Error PinkEngine::run() {
		Common::Error res = init();
		if (res.getCode() != Common::kNoError) {
			return res;
		}

		Common::Array<Video::FlicDecoder *> *layers[100] = {NULL};
		const Common::Array<CActor *> *actors = _page->actors;

		for (uint32 i = 0; i < actors->size(); i++) {
			CActor *actor = (*actors)[i];
			const Common::Array<CAction *> *actions = actor->actions;
			for (uint32 j = 0; j < actions->size(); j++) {
				CAction *action = (*actions)[j];
				if (CActionCEL::RuntimeClass()->isInstance((CObject *)action)) {
					CActionCEL *actionCEL = (CActionCEL *)action;
					if (!layers[actionCEL->z])
						layers[actionCEL->z] = new Common::Array<Video::FlicDecoder *>();
					Video::FlicDecoder *decoder = new Video::FlicDecoder();
					decoder->loadStream(_orbFile.getResource(_page->name, actionCEL->cel));
					layers[actionCEL->z]->push_back(decoder);
				} else if (CActionSound::RuntimeClass()->isInstance((CObject *)action)) {
					CActionSound *actionSound = (CActionSound *)action;
					Audio::RewindableAudioStream *as = Audio::makeWAVStream(_orbFile.getResource(_page->name, actionSound->sound), DisposeAfterUse::YES);
					Audio::SoundHandle handle;
					_system->getMixer()->playStream(Audio::Mixer::kMusicSoundType, &handle, as);
				}
			}
		}
	
		while (!shouldQuit()) {
			Common::Event event;
			while (_eventMan->pollEvent(event)) {}
			draw(layers, sizeof(layers) / sizeof(*layers));
		}
		return Common::kNoError;
	}

	Common::Error PinkEngine::init() {
		Common::Error res = _orbFile.open("pptp.orb");
		if (res.getCode() != Common::kNoError)
			return res;

		_game = _orbFile.loadGame("PinkGame");
		_module = _orbFile.loadModule(_game->modules->at(0)->name);
		_page = _orbFile.loadPage(_module, _module->pages->at(0)->name);
		initGraphics(640, 480, true);

		return Common::kNoError;
	}

	void PinkEngine::draw(Common::Array<Video::FlicDecoder *> **layers, size_t layerscount) {
		bool update_needed = false;
		for (Common::Array<Video::FlicDecoder *> **layerdecoders = layers;
				layerdecoders < layers + layerscount;
				layerdecoders++) {
			if (*layerdecoders == NULL)
				continue;
			for (uint32 i = 0; i < (*layerdecoders)->size(); i++) {
				Video::FlicDecoder *decoder = (**layerdecoders)[i];
				if (!decoder->getTimeToNextFrame() && !decoder->endOfVideo()) {
					decoder->decodeNextFrame();
					update_needed = true;
				}
			}
		}
		if (update_needed) {
			for (Common::Array<Video::FlicDecoder *> **layerdecoders = layers;
					layerdecoders < layers + layerscount;
					layerdecoders++) {
				if (*layerdecoders == NULL)
					continue;
				for (uint32 i = 0; i < (*layerdecoders)->size(); i++) {
					Video::FlicDecoder *decoder = (**layerdecoders)[i];
					decoder->setSystemPalette();
					Graphics::Surface *frame = decoder->getDecodedFrame();
					_system->copyRectToScreen((byte *)frame->pixels, frame->pitch, decoder->getX(),
							decoder->getY(), decoder->getWidth(), decoder->getHeight());
				}
			}
			_system->updateScreen();
		}
	}

} // namespace Pink
