import os
import sys
import struct

from CArchive import *
from CObject import *
from CGame import *
from CModule import *
from CPage import *

class OrbFile(object):
    __slots__ = ["_file", "_file_size", "_index_offset", "_index_length", "_index"]

    RECORD_SIZE = 32
    RESOURCE_RECORD_SIZE = 26
    
    def __init__(self, filename):
        file_size = os.stat(filename).st_size
        
        if file_size < 20:
            raise TypeError("Not an ORB file")
        
        self._file = file(filename, 'rb')
        (magic, minorVersion, majorVersion, timestamp, index_offset, index_length) = \
             struct.unpack('4sHHIII', self._file.read(20))

        if magic != "ORB\x00":
            raise TypeError("Not an ORB file")

        if file_size < index_offset + index_length * OrbFile.RECORD_SIZE:
            raise TypeError("File is too short")

        self._file_size = file_size
    
        self._index = self._read_index(index_offset, index_length)
        

    def _read_index(self, index_offset, index_length):
        self._index_offset = index_offset
        self._index_length = index_length

        index = {}
        prevname = ''
        for i in xrange(index_length):
            self._file.seek(index_offset + i * OrbFile.RECORD_SIZE, 0)
            (name, objpos, objsize, indexpos, indexlen) = struct.unpack('16sIIII', self._file.read(OrbFile.RECORD_SIZE))
            name = name[:name.index('\x00')]
            assert prevname.lower() < name.lower(), '%s < %s' % (repr(prevname), repr(name))
            prevname = name
            index[name] = {
                              'Object': (objpos, objsize),
                              'FilesIndex': (indexpos, indexlen),
                          }

        return index

    def _read_subindex(self, index_offset, index_length):
        index = {}
        prevname = ''
        for i in xrange(index_length):
            self._file.seek(index_offset + i * OrbFile.RESOURCE_RECORD_SIZE, 0)
            (name, respos, ressize, restype) = struct.unpack('16sIIH', self._file.read(OrbFile.RESOURCE_RECORD_SIZE))
            name = name[:name.index('\x00')]
            assert prevname.lower() < name.lower(), '%s < %s' % (repr(prevname), repr(name))
            prevname = name
            index[name] = (respos, ressize, restype)
        return index

    def _load_object(self, name, obj):
        if self._index.has_key(name):
            indexRecord = self._index[name]
            self._file.seek(indexRecord['Object'][0])
            archive = CArchive(self._file)
            try:
                obj.readFromOrb(archive)
            except:
                import traceback
##                (type_, vaule, tb) = sys.exc_info()
##                while tb.tb_next:
##                    tb = tb.tb_next
##                    
##                filename = tb.tb_frame.f_code.co_filename
##                lineno = tb.tb_frame.f_lineno               
##                print >> sys.stderr, '%s(%d):\n\t%s: %s' % (filename, lineno, type_.__name__, vaule.message)
                traceback.print_exc()
                pass
            readen = self._file.tell() - indexRecord['Object'][0]
            if readen != indexRecord['Object'][1]:
                #raise Exception("Wrong object size. %d/%d!" % (readen, indexRecord['Object'][1]))
                print >> sys.stderr, "Wrong object size. %d/%d!" % (readen, indexRecord['Object'][1])
                return
            obj.resources = self._read_subindex(*indexRecord['FilesIndex'])
            return obj

    def loadGame(self, name):
        return self._load_object(name, CGame())

    def loadModule(self, name):
        return self._load_object(name, CModule())

    def loadPage(self, name):
        return self._load_object(name, CGamePage())

    def readChunk(self, offset, size):
        self._file.seek(offset)
        return self._file.read(size)
            
    @property
    def index(self):
        return self._index

class PinkGame(object):
    def __init__(self, path):
        self.orbFile = self._openOrbFile(path)
        self.broFile = self._openBroFile(path)

    def _openOrbFile(self, path):
        try:
            orb = os.path.join(path, 'pptp.orb')
            os.stat(orb)
        except:
            try:
                orb = os.path.join(path, 'Orb', 'pptp.orb')
                os.stat(orb)
            except:
                raise
        return OrbFile(orb)

    def _openBroFile(self, path):
        try:
            bro = os.path.join(path, 'pptp.bro')
            os.stat(bro)
        except:
            try:
                bro = os.path.join(path, 'INSTALL', 'pptp.bro')
                os.stat(bro)
            except:
                raise
        return file(bro, 'rb')

    def loadModule(self, name):
        module = self.orbFile.loadModule(name)
        for index, page in enumerate(module.pages):
            page = self.orbFile.loadPage(page.name)
            page.module = module
            module.pages[index] = page
        return module
        
    def exportPage(self, name, module, path):
        page = self.orbFile.loadPage(name)
        file(os.path.join(path, 'Def', '%sPage.txt' % page.name), 'w').write('\n'.join(page.exportText()))
        for res, rng in page.resources.items():
            offset, size, restype = rng
                
            ext = res.split('.')[-1].upper()
            if ext == 'CEL':
                folder = 'gfx'
            elif ext == 'WAV' or ext == 'VOX':
                folder = 'audio'
            else:
                raise Exception("Unknown extension %s" % ext)

            try: os.makedirs(os.path.join(path, module.directory, page.directory, folder))
            except: pass
            
            if restype == 1:
                self.broFile.seek(offset)
                data = self.broFile.read(size)
            elif restype == 0:
                data = self.orbFile.readChunk(offset, size)
            else:
                raise Exception("Unknown resource type: %d" % data)
                
            file(os.path.join(path, module.directory, page.directory, folder, res), 'wb').write(data)

    def exportModule(self, name, path):
        module = self.orbFile.loadModule(name)
        if module is None:
            return
        lines = ['CModule'] + module._exportAttributes()
        file(os.path.join(path, 'Def', '%sModule.txt' % module.name), 'w').write('\n'.join(lines))
        for page in module.pages:
            print "  - Exporting \"%s\" page..." % page.name
            self.exportPage(page.name, module, path)

def main():
    import sys
    import os
    if len(sys.argv) <= 1:
        print "Usage: %s <Module Name> [<Module Name> ...]" % os.path.basename(sys.argv[0])
        return

    pinkGame = PinkGame(r'D:\games\PERIL')
    for module in sys.argv[1:]:
        print "\n* Exporting \"%s\" module..." % module
        pinkGame.exportModule(module, r'D:\games\PERIL')
            
if __name__ == "__main__":
    main()
