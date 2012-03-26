# -*- coding: UTF-8 -*-

from Emitter import headerDefine
from Emitter import friends

import pywidl



def renderFriend(out, declaration):
  print >>out
  print >>out, "    friend class %s;" % declaration;



def renderInterface(out, interface):
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

    for definition in definitions:
      definition_friends = friends.get(definition.name, None)
      if definition_friends:
        renderForwardDeclarations(out, definition_friends)

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
