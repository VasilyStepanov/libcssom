interface CSSRule {
  // Types
  const unsigned short STYLE_RULE = 1;
  const unsigned short IMPORT_RULE = 3;
  const unsigned short MEDIA_RULE = 4;
  const unsigned short FONT_FACE_RULE = 5;
  const unsigned short PAGE_RULE = 6;
  const unsigned short NAMESPACE_RULE = 10;
  readonly attribute unsigned short type;

  // Parsing and serialization
           attribute DOMString cssText;

  // Context
  readonly attribute CSSRule parentRule;
  readonly attribute CSSStyleSheet parentStyleSheet;
};



interface CSSFontFaceRule : CSSRule {
  readonly attribute CSSStyleDeclaration style;
};



interface MediaList {
  stringifier attribute DOMString mediaText;
  readonly attribute unsigned long length;
  getter DOMString item(unsigned long index);
  void appendMedium(DOMString medium);
  void deleteMedium(DOMString medium);
};



interface CSSImportRule : CSSRule {
  readonly attribute DOMString href;
  [PutForwards=mediaText] readonly attribute MediaList media;
  readonly attribute CSSStyleSheet styleSheet;
};



interface CSSMediaRule : CSSRule {
  [PutForwards=mediaText] readonly attribute MediaList media;
  readonly attribute CSSRuleList cssRules;
  unsigned long insertRule(DOMString rule, in unsigned long index);
  void deleteRule(unsigned long index);
};



interface CSSNamespaceRule : CSSRule {
  readonly attribute DOMString namespaceURI;
  readonly attribute DOMString? prefix;
};



interface CSSPageRule : CSSRule {
           attribute DOMString selectorText;
  readonly attribute CSSStyleDeclaration style;
};



interface CSSStyleRule : CSSRule {
           attribute DOMString selectorText;
  readonly attribute CSSStyleDeclaration style;
};
