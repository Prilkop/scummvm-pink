from CArchive import *

from CObject import *
from CCondition import *

class CHandlerMgr(CObject):
    def __init__(self):
        self.leftClickHandlers = []
        self.useClickHandlers = []
        self.timerHandlers = []
        
    def deserialize(self, archive):
        self.leftClickHandlers = archive.readCObArray()
        self.useClickHandlers = archive.readCObArray()
        self.timerHandlers = archive.readCObArray()

    def _exportSubobjects(self):
        text = CObject._exportSubobjects(self)
        for handler in self.leftClickHandlers:
            text += handler.exportText()
        for handler in self.useClickHandlers:
            text += handler.exportText()
        for handler in self.timerHandlers:
            text += handler.exportText()
        return text

CArchive.register(CHandlerMgr)

class CHandler(CObject):
    def __init__(self):
        self.conditions = []
        self.sideEffects = []
        
    def deserialize(self, archive):
        self.conditions = archive.readCObArray()
        self.sideEffects = archive.readCObArray()

    def _exportSubobjects(self):
        text = CObject._exportSubobjects(self)
        for condition in self.conditions:
            text += condition.exportText()
        for sideEffect in self.sideEffects:
            text += sideEffect.exportText()
        return text

CArchive.register(CHandler)

class CHandlerSequences(CHandler):
    def __init__(self):
        CHandler.__init__(self)
        
        self.sequences = []
        
    def deserialize(self, archive):
        CHandler.deserialize(self, archive)
        
        self.sequences = archive.readCStringArray()

    def _exportAttributes(self):
        text = CHandler._exportAttributes(self)
        text += ['Sequences: %s' % (' '.join(self.sequences))]
        return text

CArchive.register(CHandlerSequences)

class CHandlerStartPage(CHandlerSequences):
    pass

CArchive.register(CHandlerStartPage)

class CHandlerUseClick(CHandlerSequences):
    def __init__(self):
        CHandlerSequences.__init__(self)
        
        self.recipient = ''
        self.inventoryItem = ''
        
    def deserialize(self, archive):
        CHandlerSequences.deserialize(self, archive)
        
        self.recipient = archive.readCString()
        self.inventoryItem = archive.readCString()

    def _exportAttributes(self):
        text = CHandlerSequences._exportAttributes(self)
        text += ['Recipient: %s' % self.recipient]
        text += ['InventoryItem: %s' % self.inventoryItem]
        return text

CArchive.register(CHandlerUseClick)

class CHandlerLeftClick(CHandlerSequences):
    pass

CArchive.register(CHandlerLeftClick)

class CHandlerTimer(CHandler):
    def __init__(self):
        CHandler.__init__(self)
        
        self.actions = []
        
    def deserialize(self, archive):
        CHandler.deserialize(self, archive)
        
        self.actions = archive.readCStringArray()

    def _exportAttributes(self):
        text = CHandler._exportAttributes(self)
        text += ['Actions: %s' % (' '.join(self.actions))]
        return text

CArchive.register(CHandlerTimer)

__all__ = ["CHandlerMgr", "CHandler", "CHandlerSequences",
           "CHandlerStartPage", "CHandlerTimer", "CHandlerUseClick",
           "CHandlerLeftClick"]
