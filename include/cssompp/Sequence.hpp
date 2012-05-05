#ifndef CSSOMPP_SEQUENCE_HPP
#define CSSOMPP_SEQUENCE_HPP

#include <cssom/Sequence.h>

#include <utility>

namespace cssom {



template <typename T>
class Sequence {
  public:
    Sequence();
    explicit Sequence(CSSOM_Sequence * impl);
    Sequence(const cssom::Sequence<T> &copy);
    ~Sequence();

    cssom::Sequence<T>& operator=(const cssom::Sequence<T> &rhs);

    bool operator==(const cssom::Sequence<T> &rhs) const;

    bool isNull() const;

    void swap(cssom::Sequence<T> &rhs);

    size_t length() const;
    T operator[](size_t index) const;

  protected:
    CSSOM_Sequence * _impl;
};



template <typename T>
Sequence<T>::Sequence() :
  _impl(NULL)
{}



template <typename T>
Sequence<T>::Sequence(CSSOM_Sequence * impl) :
  _impl(impl)
{
  CSSOM_Sequence_acquire(_impl);
}



template <typename T>
Sequence<T>::Sequence(const cssom::Sequence<T> &copy) :
  _impl(copy._impl)
{
  CSSOM_Sequence_acquire(_impl);
}



template <typename T>
Sequence<T>::~Sequence<T>() {
  CSSOM_Sequence_release(_impl);
}



template <typename T>
cssom::Sequence<T>& Sequence<T>::operator=(const cssom::Sequence<T> &rhs) {
  if (&rhs == this) return *this;

  cssom::Sequence<T>(rhs).swap(*this);

  return *this;
}



template <typename T>
bool Sequence<T>::operator==(const cssom::Sequence<T> &rhs) const {
  return _impl == rhs._impl;
}



template <typename T>
bool Sequence<T>::isNull() const {
  return _impl == NULL;
}



template <typename T>
void Sequence<T>::swap(cssom::Sequence<T> &rhs) {
  std::swap(_impl, rhs._impl);
}



template <typename T>
size_t Sequence<T>::length() const {
  return CSSOM_Sequence_length(_impl);
}



template <typename T>
T Sequence<T>::operator[](size_t index) const {
   return T((typename T::C)CSSOM_Sequence_at(_impl, index));
}



} // cssom

#endif // CSSOMPP_SEQUENCE_HPP
