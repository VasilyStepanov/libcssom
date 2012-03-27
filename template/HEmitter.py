# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import emitType
from Emitter import emitArgument

import pywidl



def attributeSetterName(name):
  assert(name)
  return "set%s%s" % (name[0].upper(), name[1:])



def attributeGetterSignature(interface, attribute):
  return "CSSOM_%(iface)s_%(attr)s(const CSSOM_%(iface)s *)" % { \
    "attr" : attribute.name,
    "iface" : interface.name }



def attributeSetterSignature(interface, attribute):
  return "CSSOM_%(iface)s_%(setter)s" \
    "(CSSOM_%(iface)s *, %(type)s %(attr)s)" % { \
    "iface" : interface.name,
    "setter" : attributeSetterName(attribute.name),
    "type" : emitType(attribute.type),
    "attr" : attribute.name }



def operationSignature(interface, operation):
  return "CSSOM_%(iface)s_%(op)s(CSSOM_%(iface)s *, %(args)s)" % { \
    "iface" : interface.name,
    "op" : operation.name,
    "args" : ", ".join([emitArgument(arg) for arg in operation.arguments])}



def renderAttribute(out, interface, attribute):
  assert(not attribute.extended_attributes)
  assert(not attribute.stringifier)
  assert(not attribute.inherit)

  print >>out, "%s %s;" % ( \
    emitType(attribute.type),
    attributeGetterSignature(interface, attribute))

  if attribute.readonly: return

  print >>out
  print >>out
  print >>out
  print >>out, "void %s;" % attributeSetterSignature(interface, attribute)



def renderOperation(out, interface, operation):
  assert(not operation.extended_attributes)
  assert(not operation.stringifier)
  assert(not operation.static)
  assert(not operation.getter)
  assert(not operation.setter)
  assert(not operation.creator)
  assert(not operation.deleter)
  assert(not operation.legacycaller)

  print >>out, "%s %s;" % ( \
    emitType(operation.return_type),
    operationSignature(interface, operation))



def renderInterfaceMember(out, interface, member):
  print >>out
  print >>out
  print >>out
  if isinstance(member, pywidl.Attribute):
    renderAttribute(out, interface, member)
  elif isinstance(member, pywidl.Operation):
    renderOperation(out, interface, member)
  else:
    raise RuntimeError("Unknown interface member %s" % member)



def renderInterface(out, interface):
  assert(not interface.extended_attributes)
  assert(not interface.callback)

  print >>out, "typedef struct _CSSOM_%(name)s CSSOM_%(name)s;" % { \
    "name" : interface.name }

  for member in interface.members:
    renderInterfaceMember(out, interface, member)




def renderDefinition(out, definition):
  print >>out
  print >>out
  print >>out
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition)
  else:
    raise RuntimeError("Unknown definition type %s" % definition)



def render(definitions=[], source=None, output=None, template=None,
  template_type=None, **kwargs):

  with open(output, 'w') as out:
    define = headerDefine("cssom", source, "h")
    print >>out, "#ifndef %s" % define
    print >>out, "#define %s" % define
    print >>out
    print >>out, "#ifdef __cplusplus"
    print >>out, "extern \"C\" {"
    print >>out, "#endif"

    for definition in definitions:
      renderDefinition(out, definition)

    print >>out
    print >>out
    print >>out
    print >>out, "#ifdef __cplusplus"
    print >>out, "}"
    print >>out, "#endif"
    print >>out
    print >>out, "#endif"
