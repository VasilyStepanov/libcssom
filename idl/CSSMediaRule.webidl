interface CSSMediaRule : CSSRule {
  [PutForwards=mediaText] readonly attribute MediaList media;
  readonly attribute CSSRuleList cssRules;
  unsigned long insertRule(DOMString rule, in unsigned long index);
  void deleteRule(unsigned long index);
};