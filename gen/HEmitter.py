# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import emitSimpleType
from Emitter import splitCamelCase
from Emitter import instanceName

import pywidl

import os



def interfaceMemberName(interface, member):
  i = 0
  for m in interface.members:
    if m == member:
      if i == 0: return member.name
      if i == 1: return "%sEx" % member.name
      return "%sEx%d" % (member.name, i)
    if m.name == member.name: i += 1

  return member.name



def attributeSetterName(name):
  assert(name)
  return "set%s%s" % (name[0].upper(), name[1:])



def attributeGetterSignature(interface, attribute):
  return "CSSOM_%(iface)s_%(attr)s(const CSSOM_%(iface)s * %(inst)s)" % { \
    "attr" : interfaceMemberName(interface, attribute),
    "inst" : instanceName(interface.name),
    "iface" : interface.name }



def attributeSetterSignature(interface, attribute):
  return "CSSOM_%(iface)s_%(setter)s" \
    "(CSSOM_%(iface)s * %(inst)s, %(type)s %(attr)s)" % { \
    "iface" : interface.name,
    "inst" : instanceName(interface.name),
    "setter" : attributeSetterName(interfaceMemberName(interface, attribute)),
    "type" : emitType(attribute.type),
    "attr" : attribute.name }



def isGetterOperation(operation):
  return splitCamelCase(operation.name)[0] == "get"



def operationSignature(interface, operation):
  inst = "CSSOM_%(iface)s * %(inst)s" % {
    "iface" : interface.name,
    "inst" : instanceName(interface.name)}

  if isGetterOperation(operation): inst = "const %s" % inst

  return "CSSOM_%(iface)s_%(op)s(%(inst)s, %(args)s)" % { \
    "iface" : interface.name,
    "inst" : inst,
    "op" : interfaceMemberName(interface, operation),
    "args" : ", ".join([emitArgument(arg) for arg in operation.arguments])}



def emitArgument(argument):
  assert(not argument.optional)
  assert(not argument.default)
  assert(not argument.ellipsis)
  assert(not argument.extended_attributes)

  return "%s %s" % (emitType(argument.type), argument.name)



def emitInterfaceType(typedef):
  return "CSSOM_%s*" % typedef.name



def emitType(typedef):
  if isinstance(typedef, pywidl.SimpleType):
    return emitSimpleType(typedef)
  elif isinstance(typedef, pywidl.InterfaceType):
    return emitInterfaceType(typedef)
  else:
    raise RuntimeError("Unknown type: %s" % typedef)



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



def renderConst(out, interface, const):
  assert(not const.extended_attributes)

  print >>out, "extern %s CSSOM_%s_%s;" % ( \
    emitType(const.type),
    interface.name,
    const.name)



def renderInterfaceMember(out, interface, member):
  print >>out
  print >>out
  print >>out
  if isinstance(member, pywidl.Attribute):
    renderAttribute(out, interface, member)
  elif isinstance(member, pywidl.Operation):
    renderOperation(out, interface, member)
  elif isinstance(member, pywidl.Const):
    renderConst(out, interface, member)
  else:
    raise RuntimeError("Unknown interface member %s" % member)



def renderInterface(out, interface):
  assert(not interface.extended_attributes)
  assert(not interface.callback)

  print >>out, "typedef struct _CSSOM_%(name)s CSSOM_%(name)s;" % { \
    "name" : interface.name }

  for member in interface.members:
    renderInterfaceMember(out, interface, member)




def renderInclude(out, definition):
  types = []
  if isinstance(definition, pywidl.Interface):
    if isinstance(definition, pywidl.Interface):
      for member in definition.members:
        if isinstance(member, pywidl.Attribute):
          types.append(member.type)
        elif isinstance(member, pywidl.Operation):
          types.append(member.return_type)

  hppincludes = set()
  for type in types:
    if isinstance(type, pywidl.InterfaceType) \
    and type.name != definition.name:
      hppincludes.add(type.name)

  if hppincludes: print >>out
  for include in hppincludes:
    print >>out, "#include <cssom/%s.h>" % include



def renderDefinition(out, definition):
  print >>out
  print >>out
  print >>out
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition)
  else:
    raise RuntimeError("Unknown definition type %s" % definition)



def renderDefinitionFile(outputdir, definition):
  with open(os.path.join(outputdir, "%s.h" % definition.name), 'w') as out:
    define = headerDefine("cssom", definition.name, "h")
    print >>out, "#ifndef %s" % define
    print >>out, "#define %s" % define

    renderInclude(out, definition)

    print >>out
    print >>out, "#ifdef __cplusplus"
    print >>out, "extern \"C\" {"
    print >>out, "#endif"

    renderDefinition(out, definition)

    print >>out
    print >>out
    print >>out
    print >>out, "#ifdef __cplusplus"
    print >>out, "}"
    print >>out, "#endif"
    print >>out
    print >>out, "#endif"


def render(definitions=[], source=None, output=None, template=None,
  template_type=None, includedir=None, **kwargs):

  assert(includedir)

  for definition in definitions:
    renderDefinitionFile(includedir, definition)

  with open(output, 'w') as out:
    pass
