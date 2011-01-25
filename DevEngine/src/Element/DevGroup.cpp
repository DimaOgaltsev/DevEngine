#include <Element/DevGroup.h>

using namespace dev;

Group::Group(Vec3 position, Vec3 rotation, Vec3 scale) :
  Element(position, rotation, scale)
{
}

Group::Group() :
  Element()
{

}

Group::~Group()
{
}

void Group::ClearList()
{
  _elements.clear();
}

void Group::AddElement(Element* element)
{
  InsertElement(_elements.size(), element);
}

void Group::InsertElement(unsigned int num, Element* element)
{
  if (!element)
    return;

  if (GetElementNum(element) != _elements.size())
    return;

  if (num >= _elements.size())
  {
    _elements.push_back(element);
  }
  else
  {
    _elements.insert(_elements.begin() + num, element);
  }
  element->SetParent(this);
}

void Group::SetElement(unsigned int num, Element* element)
{
  if (num < _elements.size())
  {
    _elements[num] = element;
    element->SetParent(this);
  }
}

void Group::ReplaceElement(Element* element, Element* newElement)
{
  unsigned int num = GetElementNum(element);
  
  if (num != _elements.size())
  {
    _elements[num] = newElement;
    element->ClearParent();
    newElement->SetParent(this);
  }
}

void Group::RemoveElement(Element* element)
{
  unsigned int num = GetElementNum(element);
  if (num != _elements.size())
  {
    _elements.erase(_elements.begin() + num);
    element->ClearParent();
  }
}

void Group::RemoveElement(unsigned int num)
{
  if (num < _elements.size())
  {
    GetElement(num)->ClearParent();
    _elements.erase(_elements.begin() + num);
  }
}

void Group::Update()
{
  for (unsigned int i = 0; i < _elements.size(); ++i)
    _elements[i]->Update();

  Element::Update();
}
