from CArchive import *

from CObject import *
from Environment import *
from CSequence import *
from CAction import *
from CHandler import *

class CActor(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        self.page = None
        self.actions = []

    def deserialize(self, archive):
        CNamedObject.deserialize(self, archive)
        self.page = archive.readObject()
        self.actions = archive.readCObArray()

    def _exportSubobjects(self):
        text = CNamedObject._exportSubobjects(self)
        for action in self.actions:
            text += action.exportText()
        return text

CArchive.register(CActor)

class CLeadActor(CActor):
    def __init__(self):
        CActor.__init__(self)
        self.cursorMgr = CCursorMgr()
        self.walkMgr = CWalkMgr()
        self.sequencer = CSequencer()
        
    def deserialize(self, archive):
        CActor.deserialize(self, archive)
        self.cursorMgr = archive.readObject(CCursorMgr)
        self.walkMgr = archive.readObject(CWalkMgr)
        self.sequencer = archive.readObject(CSequencer)

CArchive.register(CLeadActor)

class CSupportingActor(CActor):
    def __init__(self):
        CActor.__init__(self)
        self.location = ''
        self.pdaLink = ''
        self.cursor = ''
        self.handlerMgr = CHandlerMgr()
        
    def deserialize(self, archive):
        CActor.deserialize(self, archive)
        self.location = archive.readCString()
        self.pdaLink = archive.readCString()
        self.cursor = archive.readCString()
        self.handlerMgr.deserialize(archive)

    def _exportAttributes(self):
        text = CActor._exportAttributes(self)
        text += ['Location: %s' % self.location]
        text += ['PDALink: %s' % self.pdaLink]
        text += ['Cursor: %s' % self.cursor]
        return text

    def _exportSubobjects(self):
        text = CActor._exportSubobjects(self)
        text += self.handlerMgr.exportText()
        return text

CArchive.register(CSupportingActor)

class CCursorActor(CActor):
    pass

CArchive.register(CCursorActor)

class CInventoryActor(CActor):
    pass

CArchive.register(CInventoryActor)


__all__ = ["CActor", "CLeadActor", "CSupportingActor", "CCursorActor"]
