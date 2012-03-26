# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import friends
from Emitter import attributeGetterName
from Emitter import attributeSetterName

import pywidl



def renderFriend(out, declaration):
  print >>out
  print >>out, "    friend class %s;" % declaration;



def emitSimpleType(typedef):
  if typedef.type == typedef.DOMSTRING:
    return "const char *"
  elif typedef.type == typedef.VOID:
    assert(not typedef.nullable)
    return "void"
  elif typedef.type == typedef.LONG:
    assert(not typedef.nullable)
    return "long"
  elif typedef.type == typedef.UNSIGNED_LONG:
    assert(not typedef.nullable)
    return "unsigned long"
  elif typedef.type == typedef.LONG_LONG:
    assert(not typedef.nullable)
    return "long long"
  elif typedef.type == typedef.UNSIGNED_LONG_LONG:
    assert(not typedef.nullable)
    return "unsigned long long"
  else:
    raise RuntimeError("Unknown simple type: %s" % typedef.type)



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



def renderOperation(out, operation):
  assert(not operation.extended_attributes)
  assert(not operation.stringifier)
  assert(not operation.static)
  assert(not operation.getter)
  assert(not operation.setter)
  assert(not operation.creator)
  assert(not operation.deleter)
  assert(not operation.legacycaller)

  print >>out, "    %s %s(%s);" % ( \
    emitType(operation.return_type),
    operation.name,
    ", ".join([emitArgument(arg) for arg in operation.arguments]))



def renderAttribute(out, attribute):
  assert(not attribute.stringifier)
  assert(not attribute.inherit)
  assert(not attribute.extended_attributes)

  print >>out, "    %(type)s %(name)s() const;" % { \
      "type" : emitType(attribute.type),
      "name" : attributeGetterName(attribute.name),
    }
  if not attribute.readonly:
    print >>out, "    void %(name)s(%(type)s %(attr)s);" % { \
        "type" : emitType(attribute.type),
        "name" : attributeSetterName(attribute.name),
        "attr" : attribute.name,
      }



def renderInterfaceMember(out, member):
  print >>out

  if isinstance(member, pywidl.Operation):
    renderOperation(out, member)
  elif isinstance(member, pywidl.Attribute):
    renderAttribute(out, member)
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
  print >>out, "    CSSOM_%(name)s *_impl;" % template
  print >>out
  print >>out, "    explicit %(name)s(CSSOM_%(name)s *impl);" % template
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
            if isinstance(member.type, pywidl.InterfaceType):
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
