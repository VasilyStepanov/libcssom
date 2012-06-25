#include <cssompp/CSSStyleDeclaration.hpp>



/**
 * WARNING: DO NOT EDIT!!!
 *
 * Generated by PyWIdl from 'CSSStyleDeclaration.idl'
 */



#include <cssom/CSSStyleDeclaration.h>

#include <cssompp/CSSRule.hpp>
#include <cssompp/CSSStyleDeclarationValue.hpp>

#include "checks.hpp"

#include <utility>

namespace cssom {



CSSStyleDeclaration::CSSStyleDeclaration() :
  _impl(NULL)
{}



CSSStyleDeclaration::CSSStyleDeclaration(cssom::CSSStyleDeclaration::Impl impl) :
  _impl(impl)
{
  CSSOM_CSSStyleDeclaration_acquire(_impl);
}



CSSStyleDeclaration::CSSStyleDeclaration(const cssom::CSSStyleDeclaration &copy) :
  _impl(copy._impl)
{
  CSSOM_CSSStyleDeclaration_acquire(_impl);
}



CSSStyleDeclaration::~CSSStyleDeclaration() {
  CSSOM_CSSStyleDeclaration_release(_impl);
}



cssom::CSSStyleDeclaration& CSSStyleDeclaration::operator=(
  const cssom::CSSStyleDeclaration &rhs)
{
  if (&rhs == this) return *this;

  cssom::CSSStyleDeclaration(rhs).swap(*this);

  return *this;
}



bool CSSStyleDeclaration::operator==(
  const cssom::CSSStyleDeclaration &rhs) const
{
  return _impl == rhs._impl;
}



bool CSSStyleDeclaration::isNull() const {
  return _impl == NULL;
}



void CSSStyleDeclaration::swap(cssom::CSSStyleDeclaration &rhs) {
  std::swap(_impl, rhs._impl);
}



const char * CSSStyleDeclaration::cssText() const {
  return CSSOM_CSSStyleDeclaration_cssText(_impl);
}



void CSSStyleDeclaration::setCSSText(const char * cssText) {
  CSSOM_CSSStyleDeclaration_setCSSText(_impl, cssText);
}



unsigned long CSSStyleDeclaration::length() const {
  return CSSOM_CSSStyleDeclaration_length(_impl);
}



const char * CSSStyleDeclaration::item(unsigned long index) {
  return CSSOM_CSSStyleDeclaration_item(_impl, index);
}



const char * CSSStyleDeclaration::getPropertyValue(const char * property) {
  return CSSOM_CSSStyleDeclaration_getPropertyValue(_impl, property);
}



const char * CSSStyleDeclaration::getPropertyPriority(const char * property) {
  return CSSOM_CSSStyleDeclaration_getPropertyPriority(_impl, property);
}



void CSSStyleDeclaration::setProperty(const char * property, const char * value) {
  return CSSOM_CSSStyleDeclaration_setProperty(_impl, property, value);
}



void CSSStyleDeclaration::setProperty(const char * property, const char * value, const char * priority) {
  return CSSOM_CSSStyleDeclaration_setPropertyEx(_impl, property, value, priority);
}



const char * CSSStyleDeclaration::removeProperty(const char * property) {
  return CSSOM_CSSStyleDeclaration_removeProperty(_impl, property);
}



cssom::CSSStyleDeclarationValue CSSStyleDeclaration::values() const {
  return cssom::CSSStyleDeclarationValue(CSSOM_CSSStyleDeclaration_values(_impl));
}



cssom::CSSRule CSSStyleDeclaration::parentRule() const {
  return cssom::CSSRule(CSSOM_CSSStyleDeclaration_parentRule(_impl));
}



const char * CSSStyleDeclaration::azimuth() const {
  return CSSOM_CSSStyleDeclaration_azimuth(_impl);
}



void CSSStyleDeclaration::setAzimuth(const char * azimuth) {
  CSSOM_CSSStyleDeclaration_setAzimuth(_impl, azimuth);
}



const char * CSSStyleDeclaration::background() const {
  return CSSOM_CSSStyleDeclaration_background(_impl);
}



void CSSStyleDeclaration::setBackground(const char * background) {
  CSSOM_CSSStyleDeclaration_setBackground(_impl, background);
}



const char * CSSStyleDeclaration::backgroundAttachment() const {
  return CSSOM_CSSStyleDeclaration_backgroundAttachment(_impl);
}



void CSSStyleDeclaration::setBackgroundAttachment(const char * backgroundAttachment) {
  CSSOM_CSSStyleDeclaration_setBackgroundAttachment(_impl, backgroundAttachment);
}



const char * CSSStyleDeclaration::backgroundColor() const {
  return CSSOM_CSSStyleDeclaration_backgroundColor(_impl);
}



void CSSStyleDeclaration::setBackgroundColor(const char * backgroundColor) {
  CSSOM_CSSStyleDeclaration_setBackgroundColor(_impl, backgroundColor);
}



const char * CSSStyleDeclaration::backgroundImage() const {
  return CSSOM_CSSStyleDeclaration_backgroundImage(_impl);
}



void CSSStyleDeclaration::setBackgroundImage(const char * backgroundImage) {
  CSSOM_CSSStyleDeclaration_setBackgroundImage(_impl, backgroundImage);
}



const char * CSSStyleDeclaration::backgroundPosition() const {
  return CSSOM_CSSStyleDeclaration_backgroundPosition(_impl);
}



void CSSStyleDeclaration::setBackgroundPosition(const char * backgroundPosition) {
  CSSOM_CSSStyleDeclaration_setBackgroundPosition(_impl, backgroundPosition);
}



const char * CSSStyleDeclaration::backgroundRepeat() const {
  return CSSOM_CSSStyleDeclaration_backgroundRepeat(_impl);
}



void CSSStyleDeclaration::setBackgroundRepeat(const char * backgroundRepeat) {
  CSSOM_CSSStyleDeclaration_setBackgroundRepeat(_impl, backgroundRepeat);
}



const char * CSSStyleDeclaration::border() const {
  return CSSOM_CSSStyleDeclaration_border(_impl);
}



void CSSStyleDeclaration::setBorder(const char * border) {
  CSSOM_CSSStyleDeclaration_setBorder(_impl, border);
}



const char * CSSStyleDeclaration::borderCollapse() const {
  return CSSOM_CSSStyleDeclaration_borderCollapse(_impl);
}



void CSSStyleDeclaration::setBorderCollapse(const char * borderCollapse) {
  CSSOM_CSSStyleDeclaration_setBorderCollapse(_impl, borderCollapse);
}



const char * CSSStyleDeclaration::borderColor() const {
  return CSSOM_CSSStyleDeclaration_borderColor(_impl);
}



void CSSStyleDeclaration::setBorderColor(const char * borderColor) {
  CSSOM_CSSStyleDeclaration_setBorderColor(_impl, borderColor);
}



const char * CSSStyleDeclaration::borderSpacing() const {
  return CSSOM_CSSStyleDeclaration_borderSpacing(_impl);
}



void CSSStyleDeclaration::setBorderSpacing(const char * borderSpacing) {
  CSSOM_CSSStyleDeclaration_setBorderSpacing(_impl, borderSpacing);
}



const char * CSSStyleDeclaration::borderStyle() const {
  return CSSOM_CSSStyleDeclaration_borderStyle(_impl);
}



void CSSStyleDeclaration::setBorderStyle(const char * borderStyle) {
  CSSOM_CSSStyleDeclaration_setBorderStyle(_impl, borderStyle);
}



const char * CSSStyleDeclaration::borderTop() const {
  return CSSOM_CSSStyleDeclaration_borderTop(_impl);
}



void CSSStyleDeclaration::setBorderTop(const char * borderTop) {
  CSSOM_CSSStyleDeclaration_setBorderTop(_impl, borderTop);
}



const char * CSSStyleDeclaration::borderRight() const {
  return CSSOM_CSSStyleDeclaration_borderRight(_impl);
}



void CSSStyleDeclaration::setBorderRight(const char * borderRight) {
  CSSOM_CSSStyleDeclaration_setBorderRight(_impl, borderRight);
}



const char * CSSStyleDeclaration::borderBottom() const {
  return CSSOM_CSSStyleDeclaration_borderBottom(_impl);
}



void CSSStyleDeclaration::setBorderBottom(const char * borderBottom) {
  CSSOM_CSSStyleDeclaration_setBorderBottom(_impl, borderBottom);
}



const char * CSSStyleDeclaration::borderLeft() const {
  return CSSOM_CSSStyleDeclaration_borderLeft(_impl);
}



void CSSStyleDeclaration::setBorderLeft(const char * borderLeft) {
  CSSOM_CSSStyleDeclaration_setBorderLeft(_impl, borderLeft);
}



const char * CSSStyleDeclaration::borderTopColor() const {
  return CSSOM_CSSStyleDeclaration_borderTopColor(_impl);
}



void CSSStyleDeclaration::setBorderTopColor(const char * borderTopColor) {
  CSSOM_CSSStyleDeclaration_setBorderTopColor(_impl, borderTopColor);
}



const char * CSSStyleDeclaration::borderRightColor() const {
  return CSSOM_CSSStyleDeclaration_borderRightColor(_impl);
}



void CSSStyleDeclaration::setBorderRightColor(const char * borderRightColor) {
  CSSOM_CSSStyleDeclaration_setBorderRightColor(_impl, borderRightColor);
}



const char * CSSStyleDeclaration::borderBottomColor() const {
  return CSSOM_CSSStyleDeclaration_borderBottomColor(_impl);
}



void CSSStyleDeclaration::setBorderBottomColor(const char * borderBottomColor) {
  CSSOM_CSSStyleDeclaration_setBorderBottomColor(_impl, borderBottomColor);
}



const char * CSSStyleDeclaration::borderLeftColor() const {
  return CSSOM_CSSStyleDeclaration_borderLeftColor(_impl);
}



void CSSStyleDeclaration::setBorderLeftColor(const char * borderLeftColor) {
  CSSOM_CSSStyleDeclaration_setBorderLeftColor(_impl, borderLeftColor);
}



const char * CSSStyleDeclaration::borderTopStyle() const {
  return CSSOM_CSSStyleDeclaration_borderTopStyle(_impl);
}



void CSSStyleDeclaration::setBorderTopStyle(const char * borderTopStyle) {
  CSSOM_CSSStyleDeclaration_setBorderTopStyle(_impl, borderTopStyle);
}



const char * CSSStyleDeclaration::borderRightStyle() const {
  return CSSOM_CSSStyleDeclaration_borderRightStyle(_impl);
}



void CSSStyleDeclaration::setBorderRightStyle(const char * borderRightStyle) {
  CSSOM_CSSStyleDeclaration_setBorderRightStyle(_impl, borderRightStyle);
}



const char * CSSStyleDeclaration::borderBottomStyle() const {
  return CSSOM_CSSStyleDeclaration_borderBottomStyle(_impl);
}



void CSSStyleDeclaration::setBorderBottomStyle(const char * borderBottomStyle) {
  CSSOM_CSSStyleDeclaration_setBorderBottomStyle(_impl, borderBottomStyle);
}



const char * CSSStyleDeclaration::borderLeftStyle() const {
  return CSSOM_CSSStyleDeclaration_borderLeftStyle(_impl);
}



void CSSStyleDeclaration::setBorderLeftStyle(const char * borderLeftStyle) {
  CSSOM_CSSStyleDeclaration_setBorderLeftStyle(_impl, borderLeftStyle);
}



const char * CSSStyleDeclaration::borderTopWidth() const {
  return CSSOM_CSSStyleDeclaration_borderTopWidth(_impl);
}



void CSSStyleDeclaration::setBorderTopWidth(const char * borderTopWidth) {
  CSSOM_CSSStyleDeclaration_setBorderTopWidth(_impl, borderTopWidth);
}



const char * CSSStyleDeclaration::borderRightWidth() const {
  return CSSOM_CSSStyleDeclaration_borderRightWidth(_impl);
}



void CSSStyleDeclaration::setBorderRightWidth(const char * borderRightWidth) {
  CSSOM_CSSStyleDeclaration_setBorderRightWidth(_impl, borderRightWidth);
}



const char * CSSStyleDeclaration::borderBottomWidth() const {
  return CSSOM_CSSStyleDeclaration_borderBottomWidth(_impl);
}



void CSSStyleDeclaration::setBorderBottomWidth(const char * borderBottomWidth) {
  CSSOM_CSSStyleDeclaration_setBorderBottomWidth(_impl, borderBottomWidth);
}



const char * CSSStyleDeclaration::borderLeftWidth() const {
  return CSSOM_CSSStyleDeclaration_borderLeftWidth(_impl);
}



void CSSStyleDeclaration::setBorderLeftWidth(const char * borderLeftWidth) {
  CSSOM_CSSStyleDeclaration_setBorderLeftWidth(_impl, borderLeftWidth);
}



const char * CSSStyleDeclaration::borderWidth() const {
  return CSSOM_CSSStyleDeclaration_borderWidth(_impl);
}



void CSSStyleDeclaration::setBorderWidth(const char * borderWidth) {
  CSSOM_CSSStyleDeclaration_setBorderWidth(_impl, borderWidth);
}



} // cssom
