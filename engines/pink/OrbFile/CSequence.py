from CArchive import *

from CObject import *

class CSequencer(CObject):
    def __init__(self):
        self.sequences = []
        self.timers = []
        
    def deserialize(self, archive):
        self.sequences = archive.readCObArray()
        self.timers = archive.readCObArray()

    def _exportSubobjects(self):
        text = CObject._exportSubobjects(self)
        for sequence in self.sequences:
            text += sequence.exportText()
        for timer in self.timers:
            text += timer.exportText()
        return text

CArchive.register(CSequencer)

class CSequence(CNamedObject):
    def __init__(self):
        CNamedObject.__init__(self)
        
        self.sequencer = None
        self.items = []
        
    def deserialize(self, archive):
        CNamedObject.deserialize(self, archive)
        
        self.sequencer = archive.readObject(CSequencer)
        self.items = archive.readCObArray()

    def _exportSubobjects(self):
        text = CNamedObject._exportSubobjects(self)
        for item in self.items:
            text += item.exportText()
        return text

CArchive.register(CSequence)

class CSequenceAudio(CSequence):
    def __init__(self):
        CSequence.__init__(self)

        self.sound = ''
        
    def deserialize(self, archive):
        CSequence.deserialize(self, archive)

        self.sound = archive.readCString()

    def __repr__(self):
        prefix = CSequence.__repr__(self)[1:-1]
        return "<%s - %s>" % (prefix, self.sound)

    def _exportAttributes(self):
        text = CSequence._exportAttributes(self)
        text += ['Sound: %s' % self.sound]
        return text

CArchive.register(CSequenceAudio)

class CSequenceItem(CObject):
    def __init__(self):
        self.actor = ''
        self.action = ''
        
    def deserialize(self, archive):
        self.actor = archive.readCString()
        self.action = archive.readCString()

    def __repr__(self):
        prefix = CObject.__repr__(self)[1:-1]
        return "<%s - %s / %s>" % (prefix, self.actor, self.action)

    def _exportAttributes(self):
        text = CObject._exportAttributes(self)
        text += ['Actor: %s' % self.actor]
        text += ['Action: %s' % self.action]
        return text

CArchive.register(CSequenceItem)

class CSequenceItemDefaultAction(CSequenceItem):
    pass

CArchive.register(CSequenceItemDefaultAction)

class CSequenceItemLeader(CSequenceItem):
    pass

CArchive.register(CSequenceItemLeader)

class CSequenceItemLeaderAudio(CSequenceItemLeader):
    def __init__(self):
        CSequenceItemLeader.__init__(self)

        self.sample = 0
        
    def deserialize(self, archive):
        CSequenceItemLeader.deserialize(self, archive)

        self.sample = archive.readUInt()

    def _exportAttributes(self):
        text = CSequenceItemLeader._exportAttributes(self)
        text += ['Sample: %s' % self.sample]
        return text

CArchive.register(CSequenceItemLeaderAudio)

class CSeqTimer(CObject):
    def __init__(self):
        self.actor = ''
        self.period = 0
        self.range = 0
        
    def deserialize(self, archive):
        self.actor = archive.readCString()
        self.period = archive.readUInt()
        self.range = archive.readUInt()
        self.sequencer = archive.readObject()

    def _exportAttributes(self):
        text = CObject._exportAttributes(self)
        text += ['Actor: %s' % self.actor]
        text += ['Period: %d' % self.period]
        text += ['Range: %d' % self.range]
        return text

CArchive.register(CSeqTimer)

__all__ = ["CSequencer", "CSequence", "CSequenceAudio", "CSequenceItem",
           "CSequenceItemDefaultAction", "CSequenceItemLeader",
           "CSequenceItemLeader", "CSequenceItemLeaderAudio"]
