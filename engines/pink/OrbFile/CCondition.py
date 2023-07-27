from CArchive import *

from CObject import *

class CCondition(CObject):        
    def deserialize(self, archive):
        pass

CArchive.register(CCondition)

class CConditionVariable(CCondition):
    def __init__(self):
        CCondition.__init__(self)
        
        self.variable = ''
        self.value = ''
        
    def deserialize(self, archive):
        CCondition.deserialize(self, archive)
        
        self.variable = archive.readCString()
        self.value = archive.readCString()

    def __repr__(self):
        prefix = CObject.__repr__(self)[1:-1]
        return "<%s - %s == '%s'>" % (prefix, self.variable, self.value)
        
    def _exportAttributes(self):
        text = CCondition._exportAttributes(self)
        text += ["Variable: %s" % self.variable]
        text += ["Value: %s" % self.value]
        return text

CArchive.register(CConditionVariable)

class CConditionGameVariable(CConditionVariable):
    pass

CArchive.register(CConditionGameVariable)

class CConditionNotGameVariable(CConditionGameVariable):
    pass

CArchive.register(CConditionNotGameVariable)

class CConditionModuleVariable(CConditionVariable):
    pass

CArchive.register(CConditionModuleVariable)

class CConditionNotModuleVariable(CConditionModuleVariable):
    pass

CArchive.register(CConditionNotModuleVariable)

class CConditionPageVariable(CConditionVariable):
    pass

CArchive.register(CConditionPageVariable)

class CConditionNotPageVariable(CConditionPageVariable):
    pass

CArchive.register(CConditionNotPageVariable)


__all__ = ["CCondition", "CConditionVariable",
           "CConditionGameVariable", "CConditionNotGameVariable",
           "CConditionModuleVariable", "CConditionPageVariable"]
