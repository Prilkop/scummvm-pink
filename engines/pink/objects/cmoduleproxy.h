#ifndef PINK_CMODULEPROXY_H
#define PINK_CMODULEPROXY_H

#include "common/scummsys.h"
#include "cnamedobject.h"

namespace Pink {

	class CModuleProxy : public CNamedObject {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	};

};

#endif //PINK_CMODULEPROXY_H
