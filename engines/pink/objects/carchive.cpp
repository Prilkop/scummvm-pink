#include "carchive.h"

#include "cobject.h"
#include "cruntimeclass.h"

#include "common/file.h"
#include "common/str.h"
#include "common/array.h"

#include "cgame.h"
#include "cnamedobject.h"
#include "cmoduleproxy.h"
#include "cobject.h"

namespace Pink {
	CArchive::CArchive(Common::File *file) : _known_items_length(1) {
		_file = file;
	}
	
	CArchive::~CArchive() {
	}

	void CArchive::mapObject(CObject *obj) {
		_known_objects[_known_items_length++] = obj;
	}

	void CArchive::mapClass(CRuntimeClass *runtimeclass) {
		_known_classes[_known_items_length++] = runtimeclass;
	}

	uint8 CArchive::readBYTE() {
		return _file->readByte();
	}

	uint16 CArchive::readWORD() {
		return _file->readUint16LE();
	}

	uint32 CArchive::readDWORD() {
		return _file->readUint32LE();
	}

	Common::String *CArchive::readCString() {
		uint32 length = readBYTE();
		if (length == 0xff)
			length = readWORD();
		if (length == 0xffff)
			length = readDWORD();

		char *tmpstr = new char[length];
		_file->read(tmpstr, length);
		Common::String *str = new Common::String(tmpstr, length);
		delete[] tmpstr;

		return str;
	}

	CObject *CArchive::readCObject() {
		uint16 wTag = _file->readUint16LE();
		uint32 tag;
		if (wTag == 0x7fff) // wide tag
			tag = _file->readUint32LE();
		else
			tag = ((wTag & 0x8000) << 16) | (wTag & 0x7fff);

		if (tag & 0x80000000) { // new object
			CRuntimeClass *runtimeclass;
			if (wTag == 0xffff) { // new class
				uint16 schemaNum = _file->readUint16LE();
				uint16 classnameLength = _file->readUint16LE();
				if (classnameLength > 64)
					return NULL;

				char *classname = new char[classnameLength + 1];
				_file->read(classname, classnameLength);
				classname[classnameLength] = 0;
				runtimeclass = CRuntimeClass::getRuntimeClassByName(classname);
				if (!runtimeclass) {
					warning("PINK: Could not find class named \"%s\"", classname);
					return NULL;
				}
				mapClass(runtimeclass);
			} else {
				uint32 index = tag & 0x7fffffff;
				if (_known_items_length > index)
					runtimeclass = _known_classes[index];
				else
					return NULL;
			}
			CObject *obj = runtimeclass->createObject();
			mapObject(obj);
			obj->deserialize(*this);
			return obj;
		} else {
			if (_known_items_length > tag)
				return _known_objects[tag];
			else
				return NULL;
		}
	}

	Common::Array<CObject *> *CArchive::readCObArray() {
		return readCObArray(NULL);
	}

	Common::Array<CObject *> *CArchive::readCObArray(CRuntimeClass *runtimeclass) {
		Common::Array<CObject *> *arr = new Common::Array<CObject *>();
		readCObArray(*arr);
		return arr;
	}

	Common::Array<CObject *> &CArchive::readCObArray(Common::Array<CObject *> &arr) {
		return readCObArray(arr, NULL);
	}

	Common::Array<CObject *> &CArchive::readCObArray(Common::Array<CObject *> &arr, CRuntimeClass *runtimeclass) {
		uint16 length = _file->readUint16LE();
		CObject **tmparray = (CObject **)calloc(length, sizeof(CObject *));
		for (uint16 i = 0; i < length; i++) {
			CObject *obj = readCObject();
			if (!obj || runtimeclass && !runtimeclass->isInstance(obj)) {
				if (obj)
					delete obj;

				for (uint16 j = 0; j < i; j++) {
					delete tmparray[j];
				}
				free(tmparray);
				return arr;
			} else {
				tmparray[i] = obj;
			}
		}
		arr = Common::Array<CObject *>(tmparray, length);
		free(tmparray);
		return arr;
	}

	Common::Array<Common::String *> *CArchive::readCStringArray() {
		uint16 length = _file->readUint16LE();
		Common::String **tmparray = (Common::String **)calloc(length, sizeof(Common::String *));
		for (uint16 i = 0; i < length; i++) {
			Common::String *obj = readCString();
			tmparray[i] = obj;
		}
		Common::Array<Common::String *> *arr = new Common::Array<Common::String *>(tmparray, length);
		free(tmparray);
		return arr;
	}

};
