#ifndef PINK_ORBFILE_H
#define PINK_ORBFILE_H

#include "common/scummsys.h"
#include "common/error.h"

namespace Common {
	class String;
	class File;
	class SeekableReadStream;
}

namespace Pink {
	class CObject;
	class CNamedObject;
	class CArchive;
	class CGame;
	class CModule;
	class CPage;
};

namespace Pink {

	class OrbFile {
	public:
		OrbFile();
		virtual ~OrbFile();

		Common::Error open(const char *filename);
		inline Common::Error open(const Common::String *filename) { return open(filename->c_str()); };

		CGame *loadGame(const char *name);
		inline CGame *loadGame(const Common::String *name) { return loadGame(name->c_str()); };

		CModule *loadModule(const char *name);
		inline CModule *loadModule(const Common::String *name) { return loadModule(name->c_str()); };

		CPage *loadPage(CModule *module, const char *name);
		inline CPage *loadPage(CModule *module, const Common::String *name) { return loadPage(module, name->c_str()); };

		Common::SeekableReadStream *getResource(const char *object, const char *name);
		Common::SeekableReadStream *getResource(const char *object, const Common::String *name) { return getResource(object, name->c_str()); };
		Common::SeekableReadStream *getResource(const Common::String *object, const char *name) { return getResource(object->c_str(), name); };
		Common::SeekableReadStream *getResource(const Common::String *object, const Common::String *name) { return getResource(object->c_str(), name->c_str()); };

	private:
#include "common/pack-start.h"

		struct ObjectTableEntry {
			char name[16];
			uint32 object_offset;
			uint32 object_size;
			uint32 resource_index_offset;
			uint32 resource_index_length;
		};

		struct ResourceTableEntry {
			char name[16];
			uint32 resource_offset;
			uint32 resource_size;
			uint16 bro_resource;
		};

#include "common/pack-end.h"

		Common::File *_file;
		CArchive *_archive;

		uint32 _object_table_offset;
		uint32 _object_table_length;

		CObject *_loadObject(const char *name, CObject *obj);
		inline CObject *_loadObject(const Common::String *name, CObject *obj) { return _loadObject(name->c_str(), obj); };

		ObjectTableEntry &_getObjectEntry(const char *name, ObjectTableEntry &entry);
		inline ObjectTableEntry &_getObjectEntry(const Common::String *name, ObjectTableEntry &entry) { return _getObjectEntry(name->c_str(), entry); };

		ResourceTableEntry &_getResourceEntry(const char *object, const char *name, ResourceTableEntry &entry);
		inline ResourceTableEntry &_getResourceEntry(const char *object, const Common::String *name, ResourceTableEntry &entry) { return _getResourceEntry(object, name->c_str(), entry); };
		inline ResourceTableEntry &_getResourceEntry(const Common::String *object, const char *name, ResourceTableEntry &entry) { return _getResourceEntry(object->c_str(), name, entry); };
		inline ResourceTableEntry &_getResourceEntry(const Common::String *object, const Common::String *name, ResourceTableEntry &entry) { return _getResourceEntry(object->c_str(), name->c_str(), entry); };

	};

};

#endif //PINK_ORBFILE_H
