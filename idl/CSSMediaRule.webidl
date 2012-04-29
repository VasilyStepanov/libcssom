interface MediaList {
  stringifier attribute DOMString mediaText;
  // readonly attribute unsigned long length;
  // getter DOMString item(unsigned long index);
  // void appendMedium(DOMString medium);
  // void deleteMedium(DOMString medium);
};



interface CSSMediaRule : CSSRule {
  [PutForwards=mediaText] readonly attribute MediaList media;
  readonly attribute CSSRuleList cssRules;
  unsigned long insertRule(DOMString rule, in unsigned long index);
  void deleteRule(unsigned long index);
};
