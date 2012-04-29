# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import forwards
from Emitter import includes
from Emitter import emitSimpleType
from Emitter import renderWarning
from Emitter import instanceName
from Emitter import attributeExtendedAttributes
from CPPEmitter import emitArgument
from CPPEmitter import emitType
from CPPEmitter import attributeGetterSignature
from CPPEmitter import attributeSetterSignature
from CPPEmitter import operationSignature
from CPPEmitter import getterOperationSignature
from CPPEmitter import attributeSetterName
from CPPEmitter import renderDefinitionSourceFile

import pywidl

import os.path



def renderOperation(out, operation):
  assert(not operation.extended_attributes)
  assert(not operation.stringifier)
  assert(not operation.static)
  assert(not operation.setter)
  assert(not operation.creator)
  assert(not operation.deleter)
  assert(not operation.legacycaller)

  print >>out, "    %s %s;" % ( \
    emitType(operation.return_type),
    operationSignature(operation))



def renderAttribute(out, interface, attribute, definitions):
  assert(not attribute.inherit)

  print >>out, "    %s %s;" % ( \
    emitType(attribute.type),
    attributeGetterSignature(attribute))
  if not attribute.readonly:
    print >>out, "    void %s;" % attributeSetterSignature(attribute)

  forwarded_attribute = attributeExtendedAttributes(attribute, definitions)
  if forwarded_attribute:
    print >>out
    print >>out
    print >>out
    print >>out, "    void %s;" % attributeSetterSignature(forwarded_attribute)



def renderConst(out, const):
  assert(not const.extended_attributes)

  print >>out, "    static %s %s;" % ( \
    emitType(const.type),
    const.name)



def renderInterfaceMember(out, interface, member, definitions):
  print >>out

  if isinstance(member, pywidl.Operation):
    renderOperation(out, member)
  elif isinstance(member, pywidl.Attribute):
    renderAttribute(out, interface, member, definitions)
  elif isinstance(member, pywidl.Const):
    renderConst(out, member)
  else:
    raise RuntimeError("Unknown member type %s" % member)



def renderSpecialOperations(out, members):
  stringifier = None
  getter_operations = []

  for member in members:
    if isinstance(member, pywidl.Attribute) and member.stringifier:
      assert(not stringifier)
      stringifier = member

    if isinstance(member, pywidl.Operation):
      assert(not member.setter)
      assert(not member.creator)
      assert(not member.deleter)
      assert(not member.legacycaller)
      assert(not member.stringifier)

      if member.getter: getter_operations.append(member)

  if stringifier:
    print >>out
    print >>out, "    operator const char *();"

  if getter_operations:
    print >>out
    for operation in getter_operations:
      assert(len(operation.arguments) == 1)
      print >>out, "    %s %s;" % ( \
        emitType(operation.return_type),
        getterOperationSignature(operation))





def renderInterface(out, interface, definitions):
  assert(not interface.extended_attributes)
  assert(not interface.callback)

  classDef = interface.name
  if interface.parent: classDef = "%s : public cssom::%s" % ( \
    classDef, interface.parent)

  template = { 'name' : interface.name }
  print >>out, "class %s {" % classDef
  print >>out, "  public:"
  print >>out, "    typedef CSSOM_%(name)s * C;" % template;
  print >>out

  if interface.parent:
    template.update({
      'inst' : instanceName(interface.parent),
      'parent' : interface.parent})
    print >>out, "    static cssom::%(name)s cast(" \
      "const cssom::%(parent)s & %(inst)s);" % template
    print >>out, "    static cssom::%(name)s & cast(" \
      "cssom::%(parent)s & %(inst)s);" % template
    print >>out

  print >>out, "    %(name)s();" % template
  print >>out, "    explicit %(name)s(CSSOM_%(name)s * impl);" % template
  if not interface.parent:
    print >>out, "    %(name)s(const cssom::%(name)s &copy);" % template
    print >>out, "    ~%(name)s();" % template
    print >>out
    print >>out, "    cssom::%(name)s& operator=(" \
      "const cssom::%(name)s &rhs);" % template
    print >>out
    print >>out, "    bool operator==(" \
      "const cssom::%(name)s &rhs) const;" % template
    print >>out
    print >>out, "    bool isNull() const;"
    print >>out
    print >>out, "    void swap(cssom::%(name)s &rhs);" % template

  renderSpecialOperations(out, interface.members)

  for member in interface.members:
    renderInterfaceMember(out, interface, member, definitions)
  
  if not interface.parent:
    print >>out
    print >>out, "  protected:"
    print >>out, "    CSSOM_%(name)s * _impl;" % template
  print >>out, "};"



def renderTypedef(out, typedef):
  assert(not typedef.extended_attributes)
  assert(not typedef.type_extended_attributes)

  print >>out, "typedef %s %s;" % (emitType(typedef.type), typedef.name)



def renderDefinition(out, definition, definitions):
  print >>out
  print >>out
  print >>out
  if isinstance(definition, pywidl.Interface):
    renderInterface(out, definition, definitions)
  elif isinstance(definition, pywidl.Typedef):
    renderTypedef(out, definition)
  else:
    raise RuntimeError("Unknown definition type %s" % definition)



def renderInclude(out, definition):
  hppincludes = includes.get(definition.name, [])
  if hppincludes: print >>out

  for include in hppincludes:
    print >>out, "#include <cssompp/%s.hpp>" % include

  print >>out
  print >>out, "#include <cssom/typedefs.h>"




def renderForwardDeclarations(out, declarations):
  if not declarations: return

  print >>out, "namespace cssom {"

  for declaration in declarations:
    print >>out
    print >>out
    print >>out
    print >>out, "class %s;" % declaration

  print >>out
  print >>out
  print >>out
  print >>out, "} // cssom"



def renderDefinitionHeaderFile(outputdir, source, definition, definitions):
  with open(os.path.join(outputdir, "%s.hpp" % definition.name), 'w') as out:
    define = headerDefine("cssompp", definition.name, "hpp")
    print >>out, "#ifndef %s" % define
    print >>out, "#define %s" % define

    renderWarning(out, source)

    renderInclude(out, definition)

    print >>out

    renderForwardDeclarations(out, forwards.get(definition.name, []))

    print >>out
    print >>out, """namespace cssom {"""

    renderDefinition(out, definition, definitions)

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
    renderDefinitionHeaderFile(includedir, source, definition, definitions)

  for definition in definitions:
    renderDefinitionSourceFile(srcdir, source, definition, definitions)

  with open(output, 'w') as out:
    pass
