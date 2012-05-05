# -*- coding: UTF-8 -*-

import pywidl

import os.path



forwards = { \
  'CSSFontFaceRule' : ('CSSStyleDeclaration', ),
  'CSSMediaRule' : ('MediaList', ),
  'CSSImportRule' : ('MediaList', ),
  'CSSPageRule' : ('CSSStyleDeclaration', ),
  'CSSRule' : ('CSSStyleSheet', ),
  'CSSRuleList' : ('CSSRule', ),
  'CSSStyleDeclaration' : ('CSSRule', 'CSSStyleDeclarationValue', ),
  'CSSStyleDeclarationValue' : ('CSSPropertyValue', ),
  'CSSStyleRule' : ('CSSStyleDeclaration', ),
  'CSSStyleSheet' : ('CSSRule', ),
  'Selector' : ('CSSRule', ),
}



includes = { \
  'CSSFontFaceRule' : ('CSSRule', ),
  'CSSImportRule' : ('CSSRule', ),
  'CSSNamespaceRule' : ('CSSRule', ),
  'CSSMediaRule' : ('CSSRuleList', 'CSSRule', ),
  'CSSPageRule' : ('CSSRule', ),
  'CSSRuleList' : ('Sequence', ),
  'CSSStyleRule' : ('CSSRule', ),
  'CSSStyleSheet' : ('CSSRuleList', ),
}



shared = (
  'CSSStyleSheet',
)



def emitSimpleType(typedef):
  if typedef.type == typedef.DOMSTRING:
    return "const char *"
  elif typedef.type == typedef.VOID:
    assert(not typedef.nullable)
    return "void"
  elif typedef.type == typedef.SHORT:
    assert(not typedef.nullable)
    return "short"
  elif typedef.type == typedef.UNSIGNED_SHORT:
    assert(not typedef.nullable)
    return "unsigned short"
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



def splitCamelCase(ident):
  assert(' ' not in ident)

  if not ident: return ident

  words = []
  word = []


  pch = ''
  for ch in ident:
    if pch.isupper() and ch.islower():
      if word: words.append(''.join(word))
      word = [pch]
    else:
      if pch: word.append(pch)

    pch = ch

  word.append(ch)
  words.append(''.join(word))

  return words



def capitalizeCamelCase(ident):
  return "_".join([word.upper() for word in splitCamelCase(ident)])



def instanceName(className):
  words = splitCamelCase(className)
  words[0] = words[0].lower()

  return "".join(words)



def headerDefine(prefix, name, suffix):
  return "%s_%s_%s" % ( \
    capitalizeCamelCase(prefix),
    capitalizeCamelCase(name),
    capitalizeCamelCase(suffix))



def renderWarning(out, source):
    print >>out
    print >>out
    print >>out
    print >>out, "/**"
    print >>out, " * WARNING: DO NOT EDIT!!!"
    print >>out, " *"
    print >>out, " * Generated by PyWIdl from '%s'" % os.path.basename(source)
    print >>out, " */"
    print >>out
    print >>out



def _findDefinition(definitions, name):
  for definition in definitions:
    if definition.name == name: return definition
  return None



def _findMember(interface, name):
  for member in interface.members:
    if member.name == name: return member
  return None



def _forwardedAttribute(name, type, putforwards, definitions):
  assert not putforwards.arguments, "Unexpected PutForwards " \
    "extended attribute declaration"
  interface = _findDefinition(definitions, type.name)
  assert not interface is None and isinstance(interface, pywidl.Interface), \
    "Interface '%s' not found" % type.name
  attribute = _findMember(interface, putforwards.name)
  assert isinstance(attribute, pywidl.Attribute), \
    "Attribute '%s' not found" % extended_attribute.value.name
  return pywidl.Attribute(name=name, type=attribute.type)



def attributeExtendedAttributes(attribute, definitions):
  forwarded_attribute = None
  for extended_attribute in attribute.extended_attributes:
    if extended_attribute.name == "PutForwards":
      assert isinstance(attribute.type, pywidl.InterfaceType)
      assert forwarded_attribute is None, "Multiple PutForwards not allowed"
      assert attribute.readonly, \
        "PutForwards extended attribute not on readonly attribute"

      forwarded_attribute = _forwardedAttribute(attribute.name, attribute.type,
        extended_attribute.value, definitions)
    else:
      raise RuntimeError("Unknown extended attribute: %s" % \
        extended_attribute.name)
  return forwarded_attribute
