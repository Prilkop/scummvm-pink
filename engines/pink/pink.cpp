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
#include "common/list.h"

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

		_page->init(this);

	
		while (!shouldQuit()) {
			Common::Event event;
			while (_eventMan->pollEvent(event)) {}
			execute();
		}
		return Common::kNoError;
	}

	Common::Error PinkEngine::init() {
		Common::Error res = _orb_file.open("pptp.orb");
		if (res.getCode() != Common::kNoError)
			return res;

		_game = _orb_file.loadGame("PinkGame");
		_module = _orb_file.loadModule(_game->modules->at(0)->name);
		_page = _orb_file.loadPage(_module, _module->pages->at(0)->name);
		initGraphics(640, 480, true);

		return Common::kNoError;
	}

	void PinkEngine::stageGfxAction(CActionCEL *action) {
		unstageActor(action->actor);
		_gfx_layer_actions[action->z].push_back(action);
	}

	void PinkEngine::unstageActor(CActor *actor) {
		for (uint i = 0; i < _layers_count; i++) {
			Common::List<CActionCEL *> *layer_actions = &_gfx_layer_actions[i];
			for (Common::List<CActionCEL *>::iterator iter = layer_actions->begin();
					 iter != layer_actions->end();
					 iter++) {
				CAction *action = (*iter);
				if (action->actor == actor) {
					layer_actions->erase(iter);
					return;
				}
			}	
		}
		
		askScreenUpdate();
	}

	void PinkEngine::copyToScreen(Video::FlicDecoder *decoder) {
		decoder->setSystemPalette();
		Graphics::Surface *frame = decoder->getDecodedFrame();
		_system->copyRectToScreen((byte *)frame->pixels, frame->pitch, decoder->getX(),
				decoder->getY(), decoder->getWidth(), decoder->getHeight());
	}

	Common::SeekableReadStream *PinkEngine::getPageResource(const Common::String *name) {
		return _orb_file.getResource(_page->name, name);
	}

	void PinkEngine::execute() {
		_page->execute(this);
		if (screen_update_needed) {
			screen_update_needed = false;
			draw();
		}
	}

	void PinkEngine::draw() {
		for (uint i = 0; i < _layers_count; i++) {
			Common::List<CActionCEL *> *layer_actions = &_gfx_layer_actions[i];

			for (Common::List<CActionCEL *>::iterator iter = layer_actions->begin();
				iter != layer_actions->end();
				iter++) {
					CActionCEL *action = (*iter);
					action->draw(this);
			}	
		}
		_system->updateScreen();
	}

	void PinkEngine::askScreenUpdate()	{
		screen_update_needed = true;
	}

	void PinkEngine::playMusic(Audio::SoundHandle *handle, Audio::AudioStream * stream, byte volume) {
		volume = (byte)((int)volume * 255 / 100);
		_system->getMixer()->playStream(Audio::Mixer::kMusicSoundType, handle, stream, -1, volume);
	}

} // namespace Pink
