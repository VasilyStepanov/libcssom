# -*- coding: UTF-8 -*-

from Emitter import filename
from HPPEmitter import emitArgument
from HPPEmitter import emitType
from HPPEmitter import attributeGetterSignature
from HPPEmitter import attributeSetterSignature
from HPPEmitter import operationSignature
from HPPEmitter import attributeSetterName
from HEmitter import interfaceMemberName

import pywidl



def implArgument(interface):
  if not interface.parent: return "_impl"

  return "reinterpret_cast<CSSOM_%s*>(_impl)" % interface.name



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
    print >>out, "{}"

    print >>out
    print >>out
    print >>out
    print >>out, "%(name)s::%(name)s(const cssom::%(name)s &copy) :" % template
    print >>out, "  _impl(copy._impl)"
    print >>out, "{"
    print >>out, "  CSSOM_%(name)s__acquire(_impl);" % template
    print >>out, "}"

    print >>out
    print >>out
    print >>out
    print >>out, "%(name)s::~%(name)s() {" % template
    print >>out, "  CSSOM_%(name)s__release(_impl);" % template
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

  for member in interface.members:
    renderInterfaceMember(out, interface, member)



def renderDefinition(out, definition):
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition)
  else:
    raise RuntimeError("Unknown definition type: %s" % definition)



def renderInclude(out, definition):
  print >>out
  print >>out, "#include \"src/%s.h\"" % definition.name

  cppincludes = []
  if isinstance(definition, pywidl.Interface):
    if isinstance(definition, pywidl.Interface):
      for member in definition.members:
        if isinstance(member, pywidl.Attribute):
          if isinstance(member.type, pywidl.InterfaceType) \
          and member.type.name != definition.name:
            cppincludes.append(member.type.name)
        elif isinstance(member, pywidl.Operation):
          if isinstance(member.return_type, pywidl.InterfaceType) \
          and member.return_type.name != definition.name:
            cppincludes.append(member.return_type.name)

  if cppincludes: print >>out
  for include in cppincludes:
    print >>out, "#include <cssompp/%s.hpp>" % include



def render(definitions=[], source=None, output=None, template=None,
  template_type=None, **kwargs):

  with open(output, 'w') as out:
    print >>out, "#include <cssompp/%s.hpp>" % filename(source)

    for definition in definitions:
      renderInclude(out, definition)

    print >>out
    print >>out, "#include <utility>"
    print >>out
    print >>out, "namespace cssom {"

    for definition in definitions:
      renderDefinition(out, definition)

    print >>out
    print >>out
    print >>out
    print >>out, "} // cssom"
