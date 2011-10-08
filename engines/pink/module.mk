MODULE := engines/pink

MODULE_OBJS := \
	detection.o \
    orbfile.o \
    pink.o \
    runtimeregistry.o \
    objects/caction.o \
    objects/cactioncel.o \
    objects/cactionhide.o \
    objects/cactionplay.o \
    objects/cactionsound.o \
    objects/cactionstill.o \
    objects/cactor.o \
    objects/carchive.o \
    objects/ccursormgr.o \
    objects/cgame.o \
    objects/cgamepage.o \
    objects/chandler.o \
    objects/chandlermgr.o \
    objects/chandlerstartpage.o \
    objects/cleadactor.o \
    objects/cmodule.o \
    objects/cmoduleproxy.o \
    objects/cnamedobject.o \
    objects/cobject.o \
    objects/cpage.o \
    objects/cruntimeclass.o \
    objects/csequence.o \
    objects/csequenceitem.o \
    objects/csequenceitemdefaultaction.o \
    objects/csequenceitemleader.o \
    objects/csequenceitemleaderaudio.o \
    objects/csequencer.o \
    objects/csideeffect.o \
    objects/csideeffectexit.o \
    objects/cwalkmgr.o

# This module can be built as a plugin
ifeq ($(ENABLE_PINK), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
