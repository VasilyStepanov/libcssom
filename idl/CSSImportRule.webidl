interface CSSImportRule : CSSRule {
  readonly attribute DOMString href;
  [PutForwards=mediaText] readonly attribute MediaList media;
  readonly attribute CSSStyleSheet styleSheet;
};