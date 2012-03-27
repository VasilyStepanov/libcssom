# -*- coding: UTF-8 -*-

import pywidl

import os.path



friends = { \
  'CSSStyleDeclaration' : ('CSSStyleRule', )
}



def emitArgument(argument):
  assert(not argument.optional)
  assert(not argument.default)
  assert(not argument.ellipsis)
  assert(not argument.extended_attributes)

  return "%s %s" % (emitType(argument.type), argument.name)



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



def capitalizeCamelCase(ident):
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

  return "_".join([word.upper() for word in words])



def filename(source):
  filename = os.path.basename(source)
  assert(filename.endswith(".idl"))
  return filename.rsplit('.', 1)[0]



def headerDefine(prefix, source, suffix):
  return "%s_%s_%s" % ( \
    capitalizeCamelCase(prefix),
    capitalizeCamelCase(filename(source)),
    capitalizeCamelCase(suffix))
