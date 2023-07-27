import struct
import new

from CObject import *

def logged(func):
    return func

    import functools

    @functools.wraps(func)
    def a(*args, **kwargs):
        ret = func(*args, **kwargs)
        print ret
        return ret
    return a

class CArchive(object):
    _serializable = {}

    @classmethod
    def register(cls, clsObj):
        cls._serializable[clsObj.__name__] = clsObj
        #print len(cls._serializable), clsObj.__name__
    
    def __init__(self, f):
        self._f = f
        self._map = []
        self._objTypes = []
        self.mapObject(None)

    def mapObject(self, obj):
        self._insertObj(obj)

    def _insertObj(self, obj):
        self._map.append(obj)
        self._objTypes.append(2)

    def _insertClass(self, cls):
        self._map.append(cls)
        self._objTypes.append(1)

    def readUInt(self):
        (num,) = struct.unpack('I', self._f.read(4))
        return num

    def readInt(self):
        (num,) = struct.unpack('i', self._f.read(4))
        return num

    def readUShort(self):
        (num,) = struct.unpack('H', self._f.read(2))
        return num

    def readShort(self):
        (num,) = struct.unpack('h', self._f.read(2))
        return num

    def readUByte(self):
        (num,) = struct.unpack('B', self._f.read(1))
        return num

    def readByte(self):
        (num,) = struct.unpack('b', self._f.read(1))
        return num

    def readCString(self):
        size = self.readUByte()
        if size == 0xff:
            raise TypeError('size is -1')
        text = self._f.read(size)
        return text

    def readCount(self):
        count = self.readUShort()
        if count == 0xff:
            raise TypeError('count is -1')
        return count

    def readCStringArray(self):
        length = self.readCount()
        if length == 0xff:
            raise TypeError('length is -1')
        arr = []
        for i in xrange(length):
            s = self.readCString()
            arr.append(s)
        return arr

    def readCObArray(self):
        length = self.readCount()
        arr = []
        for i in xrange(length):
            obj = self.readObject()
            if obj is None:
                arr += [None] * (length - i)
                break
            arr.append(obj)
        return arr

    @logged
    def readObject(self, baseClass = CObject):
        wTag = self.readUShort()
        if wTag == 0x7fff: # big object tag
            tag = self.readUInt()
        else:
            tag = ((wTag & 0x8000) << 16) | (wTag & 0x7fff)

        if (tag & 0x80000000) == 0:
            try:
                obj = self._map[tag]
            except IndexError:
                raise IndexError("Undefined tag %d" % tag)
            if isinstance(obj, baseClass):
                return obj
            raise Exception("Not the right object!")
        
        if wTag == 0xffff: # new class tag
            schemaNum = self.readUShort()
            classname_length = self.readUShort()
            if classname_length > 64:
                return None
            
            classname = self._f.read(classname_length)
            try:
                cls = CArchive._serializable[classname]
            except:
                raise TypeError("Unknown class %s" % classname) 

            self._insertClass(cls)
        else:
            index = tag & 0x7fffffff
            if len(self._map) > index:
                cls = self._map[index]
            else:
                return None

        if not issubclass(cls, baseClass):
            raise TypeError("Expected a %s object, got %s" % (baseClass.__name__, cls.__name__))
        
        obj = cls()
        self._insertObj(obj)
        obj.deserialize(self)
        return obj

__all__ = ["CArchive"]
