from CArchive import *

from CObject import *

class CGame(CObject):
    def __init__(self):
        self.path = ''
        self.ini = ''
        self.modules = []

    def readFromOrb(self, archive):
        archive.mapObject(self)
        self.path = archive.readCString()
        self.ini = archive.readCString()
        self.modules = archive.readCObArray()

    def __repr__(self):
        return "<CGame - %d objects in '%s' in '%s'>" % (len(self.modules), self.ini, self.path)

CArchive.register(CGame)

__all__ = ["CGame"]
