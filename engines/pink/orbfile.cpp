#include "common/scummsys.h"
#include "common/array.h"
#include "common/file.h"
#include "common/str.h"
#include "common/stream.h"
#include "common/error.h"

#include "orbfile.h"
#include "objects/carchive.h"
#include "objects/cgame.h"
#include "objects/cruntimeclass.h"
#include "objects/cmoduleproxy.h"
#include "objects/cmodule.h"
#include "objects/cpage.h"

namespace Pink {
	using Common::String;

	OrbFile::OrbFile() {
	}

	OrbFile::~OrbFile() {
		delete _file;
	}

	Common::Error OrbFile::open(const char *filename) {
		_file = new Common::File();
		if (!_file->open(filename)) {
			// ERROR: could not open the file
			return Common::kPathNotFile;
		}

		if (_file->size() <  20) {
			// ERROR: not an ORB file - file too small
			delete _file;
			_file = NULL;
			return Common::kNoGameDataFoundError;
		}

		if (_file->readUint32BE() != 'ORB\0') {
			// ERROR: not an ORB file - wrong magic
			delete _file;
			_file = NULL;
			return Common::kNoGameDataFoundError;
		}

		_file->skip(4); // skip minor and major versions
		_file->skip(4); // skip timestamp

		uint32 index_offset = _file->readUint32LE();
		uint32 index_length = _file->readUint32LE();

		if (_file->size() < index_offset + index_length * sizeof(ObjectTableEntry)) {
			// ERROR: corrupted ORB file: unexpected end of file
			delete _file;
			_file = NULL;
			return Common::kNoGameDataFoundError;
		}

		_object_table_offset = index_offset;
		_object_table_length = index_length;

		return Common::kNoError;
	}

	CGame *OrbFile::loadGame(const char *name) {
		return (CGame *)_loadObject(name, new CGame());
	}

	CModule *OrbFile::loadModule(const char *name) {
		return (CModule *)_loadObject(name, new CModule());
	}

	CPage *OrbFile::loadPage(CModule *module, const char *name) {
		for (uint32 i = 0; CPage *page = (*module->pages)[i]; i++) {
			if (strcmp(page->name->c_str(), name) == 0) {
				return (CPage *)_loadObject(page->name, page);
			}
		}
		return NULL;
	}

	CObject *OrbFile::_loadObject(const char *name, CObject *obj) {
		ObjectTableEntry entry;
		_getObjectEntry(name, entry);
		if (!entry.name[0])
			return NULL;

		_file->seek(entry.object_offset);
		CArchive archive(_file);
		obj->readFromOrb(archive);
		return obj;
	}

	OrbFile::ObjectTableEntry &OrbFile::_getObjectEntry(const char *name, OrbFile::ObjectTableEntry &entry) {
		_file->seek(_object_table_offset);

		// XXX: should use binary search
		for (uint32 index = 0; index < _object_table_length; index++) {
			_file->read(&entry, sizeof(entry));
			if (scumm_stricmp(entry.name, name) == 0) {
				return entry;
			}
		}
		entry.name[0] = 0;
		return entry;
	}

	OrbFile::ResourceTableEntry &OrbFile::_getResourceEntry(const char *object, const char *name, OrbFile::ResourceTableEntry &entry) {
		ObjectTableEntry objectEntry;
		_getObjectEntry(object, objectEntry);

		_file->seek(objectEntry.resource_index_offset);

		// XXX: should use binary search
		for (uint32 index = 0; index < objectEntry.resource_index_length; index++) {
			_file->read(&entry, sizeof(entry));
			if (scumm_stricmp(entry.name, name) == 0) {
				return entry;
			}
		}
		entry.name[0] = 0;
		return entry;
	}

	Common::SeekableReadStream *OrbFile::getResource(const char *object, const char *name) {
		ResourceTableEntry entry;
		_getResourceEntry(object, name, entry);
		_file->seek(entry.resource_offset);
		return _file->readStream(entry.resource_size);
	}

};