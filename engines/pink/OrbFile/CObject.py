class CObject(object):
    def __repr__(self):
        return "<%s>" % (self.__class__.__name__)

    def exportText(self):
        text = [self.__class__.__name__]
        text += [('   %s' % x) for x in self._exportAttributes()]
        text += [('   %s' % x) for x in self._exportSubobjects()]
        if (self._exportAttributes.im_func == CObject._exportAttributes.im_func \
                or self._exportAttributes.im_func == CNamedObject._exportAttributes.im_func) \
                and self._exportSubobjects.im_func == CObject._exportSubobjects.im_func:
            raise NotImplementedError("Export methods are not implemented for: %s" % self.__class__.__name__)
        #text += ['+']
        return text

    def _exportAttributes(self):
        return []

    def _exportSubobjects(self):
        return []

class CNamedObject(CObject):
    def __init__(self):
        self.name = ''

    def deserialize(self, archive):
        self.name = archive.readCString()

    def __repr__(self):
        return "<%s '%s'>" % (self.__class__.__name__, self.name)

    def _exportAttributes(self):
        text = ["Name: %s" % self.name]
        return text

__all__ = ["CObject", "CNamedObject"]
