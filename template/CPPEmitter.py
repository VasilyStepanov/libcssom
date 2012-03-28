# -*- coding: UTF-8 -*-

from Emitter import filename
from Emitter import emitType
from Emitter import emitArgument
from HPPEmitter import attributeGetterSignature
from HPPEmitter import attributeSetterSignature
from HPPEmitter import operationSignature
from HPPEmitter import attributeSetterName
from HEmitter import interfaceMemberName

import pywidl



def renderOperation(out, interface, operation):
  assert(not operation.extended_attributes)
  assert(not operation.stringifier)
  assert(not operation.static)
  assert(not operation.getter)
  assert(not operation.setter)
  assert(not operation.creator)
  assert(not operation.deleter)
  assert(not operation.legacycaller)

  print >>out, "%s %s::%s {" % ( \
    emitType(operation.return_type),
    interface.name,
    operationSignature(operation))

  print >>out, "  return CSSOM_%s_%s(_impl%s);" % (
    interface.name,
    interfaceMemberName(interface, operation),
    "".join([", %s" % arg.name for arg in operation.arguments]))

  print >>out, "}"



def renderAttribute(out, interface, attribute):
  assert(not attribute.stringifier)
  assert(not attribute.inherit)
  assert(not attribute.extended_attributes)

  print >>out, "%s %s::%s {" % ( \
    emitType(attribute.type),
    interface.name,
    attributeGetterSignature(attribute))

  print >>out, "  return CSSOM_%s_%s(_impl);" % ( \
    interface.name,
    interfaceMemberName(interface, attribute))

  print >>out, "}"

  if attribute.readonly: return

  print >>out
  print >>out
  print >>out
  print >>out, "void %s::%s {" % ( \
    interface.name,
    attributeSetterSignature(attribute))

  print >>out, "  CSSOM_%s_%s(_impl, %s);" % ( \
    interface.name,
    attributeSetterName(interfaceMemberName(interface, attribute)),
    attribute.name)

  print >>out, "}"



def renderInterfaceMember(out, interface, member):
  print >>out
  print >>out
  print >>out

  if isinstance(member, pywidl.Operation):
    renderOperation(out, interface, member)
  elif isinstance(member, pywidl.Attribute):
    renderAttribute(out, interface, member)
  else:
    raise RuntimeError("Unknown member type %s" % member)



def renderInterface(out, interface):
  template = { "name" : interface.name }

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



def render(definitions=[], source=None, output=None, template=None,
  template_type=None, **kwargs):

  with open(output, 'w') as out:
    print >>out, "#include <cssompp/%s.hpp>" % filename(source)
    print >>out
    print >>out, "#include \"src/%s.h\"" % filename(source)
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
