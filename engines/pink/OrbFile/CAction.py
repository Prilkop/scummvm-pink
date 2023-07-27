from CArchive import *

from CObject import *

class CAction(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        self.actor = None
    
    def deserialize(self, archive):
        CNamedObject.deserialize(self, archive)
        self.actor = archive.readObject()

    def __repr__(self):
        prefix = CNamedObject.__repr__(self)[1:-1]
        return "<%s of '%s'>" % (prefix , self.actor.name)
        

CArchive.register(CAction)

class CActionHide(CAction):
    def _exportAttributes(self):
        return CAction._exportAttributes(self)

CArchive.register(CActionHide)

class CActionCEL(CAction):
    def __init__(self):
        CAction.__init__(self)
        self.filename = ''
        self.z = 0
    
    def deserialize(self, archive):
        CAction.deserialize(self, archive)
        self.filename = archive.readCString()
        self.z = archive.readUInt()

    def __repr__(self):
        prefix = CAction.__repr__(self)[1:-1]
        return "<%s - '%s'(%d)>" % (prefix , self.filename, self.z)

    def _exportAttributes(self):
        text = CAction._exportAttributes(self)
        text += ['CEL: %s' % self.filename]
        text += ['Z: %d' % self.z]
        return text

CArchive.register(CActionCEL)

class CActionStill(CActionCEL):
    def __init__(self):
        CActionCEL.__init__(self)
        self.startFrame = 0
    
    def deserialize(self, archive):
        CActionCEL.deserialize(self, archive)
        self.startFrame = archive.readInt()
        
    def __repr__(self):
        prefix = CActionCEL.__repr__(self)[1:-1]
        return "<%s - startFrame(%d)>" % (prefix, self.startFrame)

    def _exportAttributes(self):
        text = CActionCEL._exportAttributes(self)
        text += ['StartFrame: %d' % (self.startFrame + 1)]
        return text

CArchive.register(CActionStill)

class CActionPlay(CActionStill):
    def __init__(self):
        CActionStill.__init__(self)
        self.stopFrame = 0
    
    def deserialize(self, archive):
        CActionStill.deserialize(self, archive)
        self.stopFrame = archive.readInt()
        
    def __repr__(self):
        prefix = CActionStill.__repr__(self)[1:-1]
        return "<%s, stopFrame(%d)>" % (prefix, self.stopFrame)

    def _exportAttributes(self):
        text = CActionStill._exportAttributes(self)
        text += ['StopFrame: %d' % (self.stopFrame + 1)]
        return text

CArchive.register(CActionPlay)

class CActionPlayWithSfx(CActionPlay):
    def __init__(self):
        CActionPlay.__init__(self)
        self.loop = 0
        self.sfx = []
    
    def deserialize(self, archive):
        CActionPlay.deserialize(self, archive)
        self.loop = archive.readUInt()
        self.sfx = archive.readCObArray()
        
    def __repr__(self):
        prefix = CActionPlay.__repr__(self)[1:-1]
        return "<%s, loop(%d)>" % (prefix, self.loop)

    def _exportAttributes(self):
        text = CActionPlay._exportAttributes(self)
        text += ['Loop: %d' % self.loop]
        return text
        
    def _exportSubobjects(self):
        text = CActionPlay._exportSubobjects(self)
        for action in self.sfx:
            text += action.exportText()
        return text

CArchive.register(CActionPlayWithSfx)

class CActionLoop(CActionPlay):
    styleIndices = {
        1: "Forward",
        2: "Ping-Pong",
        3: "Random",
        }
    styleNames = {
        "Forward": 1,
        "Ping-Pong": 2,
        "Random": 3,
        }
    def __init__(self):
        CActionPlay.__init__(self)
        self.intro = False
        self.style = "Forward"
    
    def deserialize(self, archive):
        CActionPlay.deserialize(self, archive)
        self.intro = bool(archive.readUInt())
        self.style = CActionLoop.styleNames.get(archive.readUShort(), "Forward")
        
    def __repr__(self):
        prefix = CActionPlay.__repr__(self)[1:-1]
        intro = ''
        if self.intro:
            intro = ' Intro'
        return "<%s - %s%s>" % (prefix, self.style, intro)

    def _exportAttributes(self):
        text = CActionPlay._exportAttributes(self)
        text += ['Intro: %s' % str(bool(self.intro)).upper()]
        text += ['Style: %s' % self.style]
        return text

CArchive.register(CActionLoop)

class CActionTalk(CActionLoop):
    def __init__(self):
        CActionLoop.__init__(self)
        self.vox = ''
    
    def deserialize(self, archive):
        CActionLoop.deserialize(self, archive)
        self.vox = archive.readCString()

    def _exportAttributes(self):
        text = CActionLoop._exportAttributes(self)
        text += ['VOX: %s' % self.vox]
        return text

CArchive.register(CActionTalk)

class CActionSound(CAction):
    def __init__(self):
        CAction.__init__(self)
        self.sound = ''
        self.volume = 0
        self.loop = False
        self.background = False
    
    def deserialize(self, archive):
        CAction.deserialize(self, archive)
        self.sound = archive.readCString()
        self.volume = archive.readUInt()
        if self.volume > 100:
            self.volume = 100
        self.loop = bool(archive.readUInt())
        self.background = bool(archive.readUInt())

    def _exportAttributes(self):
        text = CAction._exportAttributes(self)
        text += ['Sound: %s' % self.sound]
        text += ['Volume: %d' % self.volume]
        text += ['Loop: %s' % str(bool(self.loop)).upper()]
        text += ['Background: %s' % str(bool(self.background)).upper()]
        return text

CArchive.register(CActionSound)

class CActionSfx(CObject):
    def __init__(self):
        self.frame = 0
        self.volume = 0
        self.sfx = ''
        self.action = None
    
    def deserialize(self, archive):
        self.frame = archive.readUInt()
        self.volume = archive.readUInt()
        if self.volume > 100:
            self.volume = 100
        self.sfx = archive.readCString()
        self.action = archive.readObject()

    def _exportAttributes(self):
        text = CObject._exportAttributes(self)
        text += ['Frame: %d' % self.frame]
        text += ['Volume: %d' % self.volume]
        text += ['Sfx: %s' % self.sfx]
        return text
    
CArchive.register(CActionSfx)

class CWalkAction(CActionCEL):
    def __init__(self):
        CActionCEL.__init__(self)
        self.calcFramePositions = False
    
    def deserialize(self, archive):
        CActionCEL.deserialize(self, archive)
        self.calcFramePositions = bool(archive.readInt())
        
    def __repr__(self):
        prefix = CActionCEL.__repr__(self)[1:-1]
        return "<%s - calcFramePositions(%s)>" % (prefix, str(self.calcFramePositions))

    def _exportAttributes(self):
        text = CActionCEL._exportAttributes(self)
        text += ['CalcFramePositions: %s' % str(self.calcFramePositions)]
        return text

CArchive.register(CWalkAction)

__all__ = ["CAction", "CActionHide", "CActionCEL", "CActionStill",
           "CActionStill", "CActionPlay", "CActionSound", "CActionSfx",
           "CWalkAction"]
