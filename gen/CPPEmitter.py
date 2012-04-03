# -*- coding: UTF-8 -*-

from Emitter import emitSimpleType
from Emitter import forwards
from Emitter import renderWarning
from HEmitter import interfaceMemberName

import pywidl

import os.path



def implArgument(interface):
  if not interface.parent: return "_impl"

  return "reinterpret_cast<CSSOM_%s*>(_impl)" % interface.name



def attributeSetterName(name):
  assert(name)
  return "set%s%s" % (name[0].upper(), name[1:])



def attributeGetterSignature(attribute):
  return "%s() const" % attribute.name



def attributeSetterSignature(attribute):
  return "%s(%s %s)" % ( \
        attributeSetterName(attribute.name),
        emitType(attribute.type),
        attribute.name,
      )



def operationSignature(operation):
  return "%s(%s)" % ( \
    operation.name,
    ", ".join([emitArgument(arg) for arg in operation.arguments]))



def emitType(typedef):
  if isinstance(typedef, pywidl.SimpleType):
    return emitSimpleType(typedef)
  elif isinstance(typedef, pywidl.InterfaceType):
    return emitInterfaceType(typedef)
  elif isinstance(typedef, pywidl.Sequence):
    return emitSequenceType(typedef)
  else:
    raise RuntimeError("Unknown type: %s" % typedef)



def emitInterfaceType(interface):
  assert(not interface.nullable)

  return "cssom::%s" % interface.name



def emitSequenceType(sequence):
  assert(not sequence.nullable)

  return "cssom::Sequence<%s>" % emitType(sequence.t)



def emitArgument(argument):
  assert(not argument.optional)
  assert(not argument.default)
  assert(not argument.ellipsis)
  assert(not argument.extended_attributes)

  return "%s %s" % (emitType(argument.type), argument.name)



def renderOperation(out, interface, operation):
  assert(not operation.extended_attributes)
  assert(not operation.stringifier)
  assert(not operation.static)
  assert(not operation.getter)
  assert(not operation.setter)
  assert(not operation.creator)
  assert(not operation.deleter)
  assert(not operation.legacycaller)

  impl = implArgument(interface)

  print >>out, "%s %s::%s {" % ( \
    emitType(operation.return_type),
    interface.name,
    operationSignature(operation))

  print >>out, "  return CSSOM_%s_%s(%s%s);" % (
    interface.name,
    interfaceMemberName(interface, operation),
    impl,
    "".join([", %s" % arg.name for arg in operation.arguments]))

  print >>out, "}"



def renderAttribute(out, interface, attribute):
  assert(not attribute.stringifier)
  assert(not attribute.inherit)
  assert(not attribute.extended_attributes)

  impl = implArgument(interface)

  print >>out, "%s %s::%s {" % ( \
    emitType(attribute.type),
    interface.name,
    attributeGetterSignature(attribute))

  if not isinstance(attribute.type, pywidl.InterfaceType):
    print >>out, "  return CSSOM_%s_%s(%s);" % ( \
      interface.name,
      interfaceMemberName(interface, attribute),
      impl)
  else:
    print >>out, "  return %s(CSSOM_%s_%s(%s));" % ( \
      emitType(attribute.type),
      interface.name,
      interfaceMemberName(interface, attribute),
      impl)

  print >>out, "}"

  if attribute.readonly: return

  print >>out
  print >>out
  print >>out
  print >>out, "void %s::%s {" % ( \
    interface.name,
    attributeSetterSignature(attribute))

  print >>out, "  CSSOM_%s_%s(%s, %s);" % ( \
    interface.name,
    attributeSetterName(interfaceMemberName(interface, attribute)),
    impl,
    attribute.name)

  print >>out, "}"



def renderConst(out, interface, const):
  assert(not const.extended_attributes)
  
  print >>out, "%(type)s %(iface)s::%(name)s = CSSOM_%(iface)s_%(name)s;" % { \
    "type" : emitType(const.type),
    "iface" : interface.name,
    "name" : const.name }



def renderInterfaceMember(out, interface, member):
  print >>out
  print >>out
  print >>out

  if isinstance(member, pywidl.Operation):
    renderOperation(out, interface, member)
  elif isinstance(member, pywidl.Attribute):
    renderAttribute(out, interface, member)
  elif isinstance(member, pywidl.Const):
    renderConst(out, interface, member)
  else:
    raise RuntimeError("Unknown member type %s" % member)



def renderInterface(out, interface):
  template = { "name" : interface.name }

  if not interface.parent:
    print >>out
    print >>out
    print >>out
    print >>out, "%(name)s::%(name)s(CSSOM_%(name)s * impl) :" % template
    print >>out, "  _impl(impl)"
    print >>out, "{"
    print >>out, "  CSSOM_%(name)s_acquire(_impl);" % template
    print >>out, "}"

    print >>out
    print >>out
    print >>out
    print >>out, "%(name)s::%(name)s(const cssom::%(name)s &copy) :" % template
    print >>out, "  _impl(copy._impl)"
    print >>out, "{"
    print >>out, "  CSSOM_%(name)s_acquire(_impl);" % template
    print >>out, "}"

    print >>out
    print >>out
    print >>out
    print >>out, "%(name)s::~%(name)s() {" % template
    print >>out, "  CSSOM_%(name)s_release(_impl);" % template
    print >>out, "}"

    print >>out
    print >>out
    print >>out
    print >>out, "cssom::%(name)s& %(name)s::operator=(" % template
    print >>out, "  const cssom::%(name)s &rhs)" % template
    print >>out, "{"
    print >>out, "  if (&rhs == this) return *this;"
    print >>out
    print >>out, "  cssom::%(name)s(rhs).swap(*this);" % template
    print >>out
    print >>out, "  return *this;"
    print >>out, "}"

    print >>out
    print >>out
    print >>out
    print >>out, "void %(name)s::swap(cssom::%(name)s &rhs) {" % template
    print >>out, "  std::swap(_impl, rhs._impl);"
    print >>out, "}"
  else:
    template['parent'] = interface.parent
    print >>out
    print >>out
    print >>out
    print >>out, "%(name)s::%(name)s(CSSOM_%(name)s * impl) :" % template
    print >>out, "  %(parent)s((CSSOM_%(parent)s *)impl)" % template
    print >>out, "{}"

  for member in interface.members:
    renderInterfaceMember(out, interface, member)



def renderDefinition(out, definition):
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition)
  else:
    raise RuntimeError("Unknown definition type: %s" % definition)



def renderInclude(out, definition):
  print >>out
  print >>out, "#include <cssom/%s.h>" % definition.name

  hppincludes = forwards.get(definition.name, [])

  if hppincludes: print >>out
  for include in hppincludes:
    print >>out, "#include <cssompp/%s.hpp>" % include



def renderDefinitionSourceFile(outputdir, source, definition):
  if isinstance(definition, pywidl.Typedef): return

  with open(os.path.join(outputdir, "%s.cpp" % definition.name), 'w') as out:
    print >>out, "#include <cssompp/%s.hpp>" % definition.name

    renderWarning(out, source)

    renderInclude(out, definition)

    print >>out
    print >>out, "#include <utility>"
    print >>out
    print >>out, "namespace cssom {"

    renderDefinition(out, definition)

    print >>out
    print >>out
    print >>out
    print >>out, "} // cssom"
