#ifndef PINK_CARCHIVE_H
#define PINK_CARCHIVE_H

#include "common/scummsys.h"

namespace Common {
	class CObject;
	class File;
	class String;
	template<class T> class Array;
}

namespace Pink {
	class CObject;
	class CRuntimeClass;
};

namespace Pink {

	class CArchive {
	public:
		CArchive::CArchive(Common::File *file);
		virtual ~CArchive();

		void mapObject(CObject *obj);
		void mapClass(CRuntimeClass *runtimeclass);

		uint8 readBYTE();
		uint16 readWORD();
		uint32 readDWORD();
		Common::String *readCString();

		CObject *CArchive::readCObject();

		Common::Array<CObject *> *CArchive::readCObArray();
		Common::Array<CObject *> *CArchive::readCObArray(CRuntimeClass *runtimeclass);

		Common::Array<CObject *> &CArchive::readCObArray(Common::Array<CObject *> &arr);
		Common::Array<CObject *> &CArchive::readCObArray(Common::Array<CObject *> &arr, CRuntimeClass *runtimeclass);

		/*template<class T>
		Common::Array<T *> *CArchive::readCObArray() {
			return (Common::Array<T *>)readCObArray(T::RuntimeClass());
		}*/
		
	private:
		Common::File *_file;
		uint16 _known_items_length;
		CRuntimeClass *_known_classes[512];
		CObject *_known_objects[512];
	};

};
#endif //PINK_CARCHIVE_H

