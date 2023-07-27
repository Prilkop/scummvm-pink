from CArchive import *

from CObject import *

class CInventoryMgr(CObject):
    def __init__(self):
        self.items = []
        
    def deserialize(self, archive):
        self.items = archive.readCObArray()

    def _exportSubobjects(self):
        for item in self.item:
            text += item.exportText()#.split('\n')
        return text

CArchive.register(CInventoryMgr)

class CInventoryItem(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        self.initialOwner = None
    
    def deserialize(self, archive):
        CNamedObject.deserialize(self, archive)
        self.initialOwner = archive.readCString()
        self.value = ''

    def __repr__(self):
        prefix = CNamedObject.__repr__(self)[1:-1]
        return "<%s of '%s'>" % (prefix , self.initialOwner)

    def _exportAttributes(self):
        text = CAction._exportAttributes(self)
        text += ['InitialOwner: %s %s' % (self.initialOwner, self.value)]
        return text

CArchive.register(CInventoryItem)

__all__ = ["CInventoryMgr", "CInventoryItem"]