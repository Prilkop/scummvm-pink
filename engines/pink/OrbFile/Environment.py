from CArchive import *

from CObject import *

class CWalkMgr(CObject):
    def __init__(self):
        self.leadActor = None
        self.locations = []
        
    def deserialize(self, archive):
        self.leadActor = archive.readObject()
        self.locations = archive.readCObArray()

    def _exportSubobjects(self):
        text = CObject._exportSubobjects(self)
        for location in self.locations:
            text += location.exportText()#.split('\n')
        return text

CArchive.register(CWalkMgr)

class CWalkLocation(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        self.neighbors = []
        
    def deserialize(self, archive):
        CNamedObject.deserialize(self, archive)
        self.neighbors = archive.readCStringArray()

    def _exportSubobjects(self):
        text = CNamedObject._exportSubobjects(self)
        text += ['Neighbors: %s' % (' '.join(self.neighbors))]
        return text

CArchive.register(CWalkLocation)

class CCursorMgr(CObject):
    def deserialize(self, archive):
        pass

CArchive.register(CCursorMgr)

__all__ = ["CWalkMgr", "CCursorMgr"]
