# -*- coding: UTF-8 -*-

from Emitter import filename
from Emitter import headerDefine
from Emitter import friends
from Emitter import emitSimpleType
from CPPEmitter import emitArgument
from CPPEmitter import emitType
from CPPEmitter import attributeGetterSignature
from CPPEmitter import attributeSetterSignature
from CPPEmitter import operationSignature
from CPPEmitter import attributeSetterName
from CPPEmitter import renderDefinitionSourceFile

import pywidl

import os



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
  assert(not interface.callback)

  classDef = interface.name
  if interface.parent: classDef = "%s : public cssom::%s" % ( \
    classDef, interface.parent)

  print >>out, "class %s {" % classDef
  print >>out, "  public:"

  if not interface.parent:
    template = { 'name' : interface.name }
    print >>out, "    %(name)s(const cssom::%(name)s &copy);" % template
    print >>out, "    ~%(name)s();" % template
    print >>out
    print >>out, "    cssom::%(name)s& operator=(" % template
    print >>out, "     const cssom::%(name)s &rhs);" % template
    print >>out
    print >>out, "    void swap(cssom::%(name)s &rhs);" % template

  for member in interface.members:
    renderInterfaceMember(out, member)
  
  for declaration in friends.get(interface.name, []):
    renderFriend(out, declaration)

  if not interface.parent:
    print >>out
    print >>out, "  private:"
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
  if isinstance(definition, pywidl.Interface):
    if definition.parent:
      print >>out, "#include <cssompp/%s.hpp>" % definition.parent



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



def renderDefinitionHeaderFile(outputdir, definition):
  with open(os.path.join(outputdir, "%s.hpp" % definition.name), 'w') as out:
    define = headerDefine("cssompp", definition.name, "hpp")
    print >>out, "#ifndef %s" % define
    print >>out, "#define %s" % define

    renderInclude(out, definition)

    print >>out

    forwards = set()

    forwards.update(friends.get(definition.name, []))

    if isinstance(definition, pywidl.Interface):
      for member in definition.members:
        if isinstance(member, pywidl.Attribute):
          if isinstance(member.type, pywidl.InterfaceType) \
          and member.type.name != definition.name:
            forwards.add(member.type.name)

    renderForwardDeclarations(out, forwards)

    print >>out
    print >>out, """namespace cssom {"""

    renderDefinition(out, definition)

    print >>out
    print >>out
    print >>out
    print >>out, "} // cssom"
    print >>out
    print >>out, "#endif // %s""" % define  



def render(definitions=[], source=None, output=None, template=None,
  template_type=None, srcdir=None, includedir=None, **kwargs):

  assert(srcdir)
  assert(includedir)

  for definition in definitions:
    renderDefinitionHeaderFile(includedir, definition)

  for definition in definitions:
    renderDefinitionSourceFile(srcdir, definition)

  with open(output, 'w') as out:
    pass
