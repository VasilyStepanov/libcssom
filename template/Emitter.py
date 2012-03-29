# -*- coding: UTF-8 -*-

import pywidl

import os.path



friends = { \
  'CSSStyleDeclaration' : ('CSSStyleRule', ),
  'CSSRule' : ('CSSRuleList', 'CSSStyleRule'),
}



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
      words.append(''.join(word))
      word = [pch]
    else:
      word.append(pch)

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



def filename(source):
  filename = os.path.basename(source)
  assert(filename.endswith(".idl"))
  return filename.rsplit('.', 1)[0]



def headerDefine(prefix, source, suffix):
  return "%s_%s_%s" % ( \
    capitalizeCamelCase(prefix),
    capitalizeCamelCase(filename(source)),
    capitalizeCamelCase(suffix))