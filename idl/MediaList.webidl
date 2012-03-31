interface MediaList {
  stringifier attribute DOMString mediaText;
  readonly attribute unsigned long length;
  getter DOMString item(unsigned long index);
  void appendMedium(DOMString medium);
  void deleteMedium(DOMString medium);
};
