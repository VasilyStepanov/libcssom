#ifndef CSSOMPP__MEDIA_LIST_HPP
#define CSSOMPP__MEDIA_LIST_HPP



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'MediaList.idl'
 */



#include <cssom/typedefs.h>


namespace cssom {



class MediaList {
  public:
    typedef CSSOM_MediaList * C;

    MediaList();
    explicit MediaList(CSSOM_MediaList * impl);
    MediaList(const cssom::MediaList &copy);
    ~MediaList();

    cssom::MediaList& operator=(const cssom::MediaList &rhs);

    bool operator==(const cssom::MediaList &rhs) const;

    bool isNull() const;

    void swap(cssom::MediaList &rhs);

  protected:
    CSSOM_MediaList * _impl;
};



} // cssom

#endif // CSSOMPP__MEDIA_LIST_HPP
