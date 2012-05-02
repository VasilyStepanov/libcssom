interface CSSPropertyValue {
           attribute DOMString cssText;
};



[NoInterfaceObject] interface CSSMapValue {
  getter CSSValue (DOMString name);
};



[NoInterfaceObject] interface CSSPropertyValueList {
  readonly attribute CSSValue[] list;
};



[NoInterfaceObject] interface CSSComponentValue {
  readonly attribute DOMString type;
           attribute any value;
};



[NoInterfaceObject] interface CSSStringComponentValue {
           attribute DOMString string;
};



[NoInterfaceObject] interface CSSKeywordComponentValue {
           attribute DOMString keyword;
};



[NoInterfaceObject] interface CSSIdentifierComponentValue {
           attribute DOMString identifier;
};



[NoInterfaceObject] interface CSSColorComponentValue {
           attribute short red;
           attribute short green;
           attribute short blue;
           attribute float alpha;
};



[NoInterfaceObject] interface CSSLengthComponentValue {
           attribute float em;
           attribute float ex;
           attribute float px;
           // figure out what to do with absolute lengths
};



[NoInterfaceObject] interface CSSPercentageComponentValue {
           attribute float percent;
};



[NoInterfaceObject] interface CSSURLComponentValue {
           attribute DOMString? url;
};
