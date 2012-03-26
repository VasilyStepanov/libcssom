# -*- coding: UTF-8 -*-

import os.path



friends = { \
  'CSSStyleDeclaration' : ('CSSStyleRule', )
}



def attributeGetterName(name):
  return name



def attributeSetterName(name):
  assert(name)
  return "set%s%s" % (name[0].upper(), name[1:])



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



def headerDefine(prefix, source, suffix):
  filename = os.path.basename(source)
  assert(filename.endswith(".idl"))
  return "%s_%s_%s" % ( \
    capitalizeCamelCase(prefix),
    capitalizeCamelCase(filename.rsplit('.', 1)[0]),
    capitalizeCamelCase(suffix))
