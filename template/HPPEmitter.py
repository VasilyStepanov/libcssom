# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import friends
from Emitter import emitSimpleType

import pywidl



def operationSignature(operation):
  return "%s(%s)" % ( \
    operation.name,
    ", ".join([emitArgument(arg) for arg in operation.arguments]))



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



def emitInterfaceType(typedef):
  return "%s*" % typedef.name



def emitType(typedef):
  if isinstance(typedef, pywidl.SimpleType):
    return emitSimpleType(typedef)
  elif isinstance(typedef, pywidl.InterfaceType):
    return emitInterfaceType(typedef)
  else:
    raise RuntimeError("Unknown type: %s" % typedef)



def emitArgument(argument):
  assert(not argument.optional)
  assert(not argument.default)
  assert(not argument.ellipsis)
  assert(not argument.extended_attributes)

  return "%s %s" % (emitType(argument.type), argument.name)



def renderFriend(out, declaration):
  print >>out
  print >>out, "    friend class %s;" % declaration;



def renderOperation(out, operation):
  assert(not operation.extended_attributes)
  assert(not operation.stringifier)
  assert(not operation.static)
  assert(not operation.getter)
  assert(not operation.setter)
  assert(not operation.creator)
  assert(not operation.deleter)
  assert(not operation.legacycaller)

  print >>out, "    %s %s;" % ( \
    emitType(operation.return_type),
    operationSignature(operation))



def renderAttribute(out, attribute):
  assert(not attribute.stringifier)
  assert(not attribute.inherit)
  assert(not attribute.extended_attributes)

  print >>out, "    %s %s;" % ( \
    emitType(attribute.type),
    attributeGetterSignature(attribute))
  if not attribute.readonly:
    print >>out, "    void %s;" % attributeSetterSignature(attribute)



def renderConst(out, const):
  assert(not const.extended_attributes)

  print >>out, "    static %s %s;" % ( \
    emitType(const.type),
    const.name)



def renderInterfaceMember(out, member):
  print >>out

  if isinstance(member, pywidl.Operation):
    renderOperation(out, member)
  elif isinstance(member, pywidl.Attribute):
    renderAttribute(out, member)
  elif isinstance(member, pywidl.Const):
    renderConst(out, member)
  else:
    raise RuntimeError("Unknown member type %s" % member)



def renderInterface(out, interface):
  assert(not interface.extended_attributes)
  assert(not interface.parent)
  assert(not interface.callback)

  template = { 'name' : interface.name }
  print >>out, "class %(name)s {" % template
  print >>out, "  public:"
  print >>out, "    %(name)s(const cssom::%(name)s &copy);" % template
  print >>out, "    ~%(name)s();" % template
  print >>out
  print >>out, "    cssom::%(name)s& operator=(" % template
  print >>out, "     const cssom::%(name)s &rhs);" % template
  print >>out
  print >>out, "    void swap(cssom::%(name)s &rhs);" % template

  for member in interface.members:
    renderInterfaceMember(out, member)
  
  print >>out
  print >>out, "  private:"

  for declaration in friends.get(interface.name, []):
    renderFriend(out, declaration)

  print >>out
  print >>out, "    CSSOM_%(name)s * _impl;" % template
  print >>out
  print >>out, "    explicit %(name)s(CSSOM_%(name)s * impl);" % template
  print >>out, "};"



def renderDefinition(out, definition):
  print >>out
  print >>out
  print >>out
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition)
  else:
    print >>out, "/* unknown definition type %s */" % definition



def renderInclude(out, definition):
  print >>out
  print >>out, "#include <cssom/%s.h>" % definition.name



def renderForwardDeclaration(out, declaration):
  print >>out
  print >>out
  print >>out
  print >>out, "class %s;" % declaration



def renderForwardDeclarations(out, declarations):
  print >>out, "namespace cssom {"

  for declaration in declarations:
    renderForwardDeclaration(out, declaration)

  print >>out
  print >>out
  print >>out
  print >>out, "} // cssom"



def render(definitions=[], source=None, output=None, template=None,
  template_type=None, **kwargs):

  with open(output, 'w') as out:
    define = headerDefine("cssompp", source, "hpp")
    print >>out, "#ifndef %s" % define
    print >>out, "#define %s" % define

    for definition in definitions:
      renderInclude(out, definition)

    print >>out

    forwards = set()

    for definition in definitions:
      forwards.update(friends.get(definition.name, []))

    for definition in definitions:
      if isinstance(definition, pywidl.Interface):
        for member in definition.members:
          if isinstance(member, pywidl.Attribute):
            if isinstance(member.type, pywidl.InterfaceType) \
            and member.type.name != definition.name:
              forwards.add(member.type.name)

    renderForwardDeclarations(out, forwards)

    print >>out
    print >>out, """namespace cssom {"""

    for definition in definitions:
      renderDefinition(out, definition)

    print >>out
    print >>out
    print >>out
    print >>out, "} // cssom"
    print >>out
    print >>out, "#endif // %s""" % define
