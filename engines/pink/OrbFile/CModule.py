from CArchive import *

from CObject import *
from Inventory import *

class CModule(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        self.directory = ''
        self.num = 0
        self.inv = CInventoryMgr()
        self.pages = []

    def readFromOrb(self, archive):
        archive.mapObject(self)
        CNamedObject.deserialize(self, archive)
        self.directory = archive.readCString()
        self.inv.deserialize(archive)
        self.pages = archive.readCObArray()

    def __repr__(self):
        return CNamedObject.__repr__(self)
        
    def _exportAttributes(self):
        text = CNamedObject._exportAttributes(self)
        text += ["Directory: %s" % self.directory]
        return text

    def _exportSubobjects(self):
        text = CNamedObject._exportSubobjects(self)
        text += self.inv.exportText()
        for page in self.pages:
            text += page.exportText()
        return text

CArchive.register(CModule)

class CModuleProxy(CObject):
    def __init__(self):
        self.name = ''

    def deserialize(self, archive):
        self.name = archive.readCString()

    def __repr__(self):
        return "<%s - '%s'>" % (self.__class__.__name__, self.name)

CArchive.register(CModuleProxy)

__all__ = ["CModule", "CModuleProxy"]
