# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import emitSimpleType
from Emitter import splitCamelCase
from Emitter import instanceName
from Emitter import includes
from Emitter import forwards
from Emitter import renderWarning

import pywidl

import os.path



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

  template = { \
    'iface' : interface.name,
    'inst' : instanceName(interface.name) }

  print >>out, "typedef struct _CSSOM_%(iface)s CSSOM_%(iface)s;" % template

  if not interface.parent:
    print >>out
    print >>out
    print >>out
    print >>out, "void CSSOM_%(iface)s_acquire(" % template
    print >>out, "  CSSOM_%(iface)s * %(inst)s);" % template

    print >>out
    print >>out
    print >>out
    print >>out, "void CSSOM_%(iface)s_release(" % template
    print >>out, "  CSSOM_%(iface)s * %(inst)s);" % template
  else:
    template['parent'] = interface.parent

    print >>out
    print >>out
    print >>out
    print >>out, "#define CSSOM_%(iface)s_acquire(%(inst)s) \\" % template
    print >>out, "  CSSOM_%(parent)s_acquire((CSSOM_%(parent)s*)(%(inst)s))" % \
      template

    print >>out
    print >>out
    print >>out
    print >>out, "#define CSSOM_%(iface)s_release(%(inst)s) \\" % template
    print >>out, "  CSSOM_%(parent)s_release((CSSOM_%(parent)s*)(%(inst)s))" % \
      template

  for member in interface.members:
    renderInterfaceMember(out, interface, member)




def renderTypedef(out, typedef):
  if isinstance(typedef.type, pywidl.Sequence):
    renderTypedefSequence(out, typedef)
  else:
    raise RuntimeError("Unknown type %s" % typedef.type)




def renderTypedefSequence(out, typedef):
  assert(not typedef.extended_attributes)
  assert(not typedef.type_extended_attributes)

  template = { \
    'type' : typedef.name,
    'name' : instanceName(typedef.name),
    't' : emitType(typedef.type.t)}

  print >>out, "typedef CSSOM_Sequence CSSOM_%(type)s;" % template;
  print >>out
  print >>out
  print >>out
  print >>out, "#define CSSOM_%(type)s_acquire(%(name)s) \\" % template
  print >>out, "  (CSSOM_Sequence_acquire((%(name)s)))" % template
  print >>out
  print >>out
  print >>out
  print >>out, "#define CSSOM_%(type)s_release(%(name)s, index) \\" % template
  print >>out, "  (CSSOM_Sequence_release((%(name)s)))" % template
  print >>out
  print >>out
  print >>out
  print >>out, "#define CSSOM_%(type)s_size(%(name)s) \\" % template
  print >>out, "  (CSSOM_Sequence_size((%(name)s)))" % template
  print >>out
  print >>out
  print >>out
  print >>out, "#define CSSOM_%(type)s_at(%(name)s, index) \\" % template
  print >>out, "  ((%(t)s)CSSOM_Sequence_at((%(name)s), (index)))" % template



def renderInclude(out, definition):
  hppincludes = set()
  hppincludes.update(includes.get(definition.name, []))
  hppincludes.update(forwards.get(definition.name, []))

  if hppincludes: print >>out
  for include in hppincludes:
    print >>out, "#include <cssom/%s.h>" % include



def renderDefinition(out, definition):
  print >>out
  print >>out
  print >>out
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition)
  elif isinstance(definition, pywidl.Typedef):
    renderTypedef(out, definition)
  else:
    raise RuntimeError("Unknown definition type %s" % definition)



def renderDefinitionFile(outputdir, source, definition):
  with open(os.path.join(outputdir, "%s.h" % definition.name), 'w') as out:
    define = headerDefine("cssom", definition.name, "h")
    print >>out, "#ifndef %s" % define
    print >>out, "#define %s" % define

    renderWarning(out, source)

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
    renderDefinitionFile(includedir, source, definition)

  with open(output, 'w') as out:
    pass
