#ifndef PINK_CSEQUENCEITEMLEADERAUDIO_H
#define PINK_CSEQUENCEITEMLEADERAUDIO_H

#include "common/scummsys.h"
#include "csequenceitemleader.h"

namespace Pink {

	class CSequenceItemLeaderAudio : public CSequenceItemLeader {
	public:
		CSequenceItemLeaderAudio();
		virtual ~CSequenceItemLeaderAudio();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		uint32 sample;
	};

};

#endif //PINK_CSEQUENCEITEMLEADERAUDIO_H
