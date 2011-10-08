#ifndef PINK_COBJECT_H
#define PINK_COBJECT_H

namespace Pink {
	class CArchive;
	class CRuntimeClass;
};

namespace Pink {

	class CObject {
	public:
		CObject();
		virtual ~CObject();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);
		virtual void readFromOrb(CArchive &archive);
	};

};

#endif //PINK_COBJECT_H
