from CArchive import *

from CObject import *
from Environment import *
from CSequence import *
from CActor import *
from CHandler import *
from CSideEffect import *

class CPage(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        self.directory = ''
        self.actors = []
        self.leadActor = None

    def readFromOrb(self, archive):
        archive.mapObject(self)
        CNamedObject.deserialize(self, archive)
        self.directory = archive.readCString()
        self.actors = archive.readCObArray()
        for actor in self.actors:
            if isinstance(actor, CLeadActor):
                self.leadActor = actor
                break
        
    def _exportAttributes(self):
        text = CNamedObject._exportAttributes(self)
        text += ["Directory: %s" % self.directory]
        return text

    def _exportSubobjects(self):
        text = CNamedObject._exportSubobjects(self)
        for actor in self.actors:
            text += actor.exportText()
        return text
        

CArchive.register(CPage)

class CGamePage(CPage):
    def __init__(self):
        CPage.__init__(self)
        self.cursorMgr = CCursorMgr()
        self.walkMgr = CWalkMgr()
        self.sequencer = CSequencer()
        self.handlers = []

    def readFromOrb(self, archive):
        archive.mapObject(self.cursorMgr)
        archive.mapObject(self.walkMgr)
        archive.mapObject(self.sequencer)
        
        CPage.readFromOrb(self, archive)

        self.leadActor = archive.readObject(CLeadActor)
        self.cursorMgr.deserialize(archive)
        self.walkMgr.deserialize(archive)
        self.sequencer.deserialize(archive)
        self.handlers = archive.readCObArray()

    def deserialize(self, archive):
        CNamedObject.deserialize(self, archive)
        self.module = archive.readObject()

    def _exportSubobjects(self):
        text = CPage._exportSubobjects(self)
        for handler in self.handlers:
            text += handler.exportText()
        text += self.walkMgr.exportText()
        text += self.sequencer.exportText()
        return text

CArchive.register(CGamePage)

__all__ = ["CPage", "CGamePage"]
