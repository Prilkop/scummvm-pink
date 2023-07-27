from CArchive import *

from CObject import *

class CSideEffect(CObject):        
    def deserialize(self, archive):
        pass

CArchive.register(CSideEffect)

class CSideEffectLocation(CSideEffect):
    def __init__(self):
        CSideEffect.__init__(self)
        
        self.location = ''
        
    def deserialize(self, archive):
        CSideEffect.deserialize(self, archive)
        
        self.location = archive.readCString()

    def __repr__(self):
        prefix = CObject.__repr__(self)[1:-1]
        return "<%s - %s>" % (prefix, self.location)
        
    def _exportAttributes(self):
        text = CSideEffect._exportAttributes(self)
        text += ["Location: %s" % self.location]
        return text

CArchive.register(CSideEffectLocation)

class CSideEffectInventoryItemOwner(CSideEffect):
    def __init__(self):
        CSideEffect.__init__(self)
        
        self.owner = ''
        self.item = ''
        
    def deserialize(self, archive):
        CSideEffect.deserialize(self, archive)
        
        self.owner = archive.readCString()
        self.item = archive.readCString()

    def __repr__(self):
        prefix = CObject.__repr__(self)[1:-1]
        return "<%s - '%s', '%s'>" % (prefix, self.owner, self.item)
        
    def _exportAttributes(self):
        text = CSideEffect._exportAttributes(self)
        text += ["Owner: %s" % self.owner]
        text += ["Item  : %s" % self.item]
        return text

CArchive.register(CSideEffectInventoryItemOwner)

class CSideEffectExit(CSideEffect):
    def __init__(self):
        CSideEffect.__init__(self)
        
        self.nextModule = ''
        self.nextPage = ''
        
    def deserialize(self, archive):
        CSideEffect.deserialize(self, archive)
        
        self.nextModule = archive.readCString()
        self.nextPage = archive.readCString()

    def __repr__(self):
        prefix = CObject.__repr__(self)[1:-1]
        return "<%s - '%s', '%s'>" % (prefix, self.nextModule, self.nextPage)
        
    def _exportAttributes(self):
        text = CSideEffect._exportAttributes(self)
        text += ["NextModule: %s" % self.nextModule]
        text += ["NextPage: %s" % self.nextPage]
        return text

CArchive.register(CSideEffectExit)

class CSideEffectVariable(CSideEffect):
    def __init__(self):
        CSideEffect.__init__(self)
        
        self.variable = ''
        self.value = ''
        
    def deserialize(self, archive):
        CSideEffect.deserialize(self, archive)
        
        self.variable = archive.readCString()
        self.value = archive.readCString()

    def __repr__(self):
        prefix = CObject.__repr__(self)[1:-1]
        return "<%s - %s = '%s'>" % (prefix, self.variable, self.value)
        
    def _exportAttributes(self):
        text = CSideEffect._exportAttributes(self)
        text += ["Variable: %s" % self.variable]
        text += ["Value: %s" % self.value]
        return text

CArchive.register(CSideEffectVariable)

class CSideEffectGameVariable(CSideEffectVariable):
    pass

CArchive.register(CSideEffectGameVariable)

class CSideEffectModuleVariable(CSideEffectVariable):
    pass

CArchive.register(CSideEffectModuleVariable)

class CSideEffectPageVariable(CSideEffectVariable):
    pass

CArchive.register(CSideEffectPageVariable)


__all__ = ["CSideEffect", "CSideEffectExit", "CSideEffectVariable",
           "CSideEffectGameVariable", "CSideEffectModuleVariable",
           "CSideEffectPageVariable"]
