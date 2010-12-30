#include <Element/DevGroup.h>

using namespace dev;

Group::Group(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale) :
  Element(position, rotation, scale)
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
}

void Group::SetElement(unsigned int num, Element* element)
{
  if (num < _elements.size())
    _elements[num] = element;
}

void Group::ReplaceElement(Element* element, Element* newElement)
{
  unsigned int num = GetElementNum(element);
  if (num != _elements.size())
    _elements[num] = newElement;
}

void Group::RemoveElement(Element* element)
{
  unsigned int num = GetElementNum(element);
  if (num != _elements.size())
    _elements.erase(_elements.begin() + num);
}

void Group::RemoveElement(unsigned int num)
{
  if (num < _elements.size())
    _elements.erase(_elements.begin() + num);
}

unsigned int Group::GetElementNum(Element* element)
{
  for (unsigned int i = 0; i < _elements.size(); ++i)
  {
    if (_elements[i] == element) 
      return i;
  }
  return static_cast<unsigned int>(_elements.size());
}

Element* Group::GetElement(unsigned int num)
{
  if (num < _elements.size())
    return (*(_elements.begin() + num));
  return NULL;
}

void Group::Update()
{
  for (unsigned int i = 0; i < _elements.size(); ++i)
    _elements[i]->Update();

  Element::Update();
}
