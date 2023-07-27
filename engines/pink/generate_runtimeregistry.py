import os
import re

def readClasses(path):
	l = [('CObject', None)]
	for f in os.listdir(path):
		if f.endswith('.h'):
			try:
				l.append(re.findall('class\s+(\w+)\s*:[^{]+\s+(\w+)\s*\{', file(os.path.join(path,f)).read())[0])
			except: pass
	return l

l = readClasses(os.path.join(os.path.dirname(__file__),'objects'))
f = file(os.path.join(os.path.dirname(__file__),'runtimeregistry.cpp'), 'w');

print>>f, '#include "runtimeregistry.h"'
print>>f
print>>f, '#include "common/scummsys.h"'
print>>f

classes = {}
for i, (cls, base) in enumerate(l):
    classes[cls] = i

for cls, base in l:
    print>>f, ('#include "objects/%s.h"' % cls.lower())

print>>f
print>>f, 'namespace Pink {'
print>>f
print>>f, '\tuint32 CRuntimeClass::runtimeclassesCount = %d;' % len(l)
print>>f
print>>f, '\tCRuntimeClass CRuntimeClass::runtimeclasses[] = {'
for cls, base in l:
    if base is None:
        print>>f, ('\t\tREGISTER_RUNTIME_CLASS(%s, NULL),' % (cls,))
    else:
        print>>f, ('\t\tREGISTER_RUNTIME_CLASS(%s, &runtimeclasses[%s]),' % (cls, classes[base]))
print>>f, '\t};'
print>>f
for cls, base in l:
    print>>f, ('\tIMPLEMENT_RUNTIME_CLASS(%d, %s);' % (classes[cls], cls))
print>>f
print>>f, '}'