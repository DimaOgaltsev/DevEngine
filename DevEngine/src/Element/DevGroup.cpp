#include <Element/DevGroup.h>

using namespace dev;

Group::Group(Vec3 position, Vec3 rotation, Vec3 scale) :
  Element(position, rotation, scale)
{
  ClearList();
}

Group::Group() :
  Element()
{
  ClearList();
}

Group::~Group()
{
  for (ElementList::iterator i = _elements.begin(); i < _elements.end(); ++i)
    delete (*i);
  ClearList();
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

  DevShaderManager::Get()->AddMesh(element->AsMesh());
}

void Group::SetElement(unsigned int num, Element* element)
{
  if (!element)
    return;

  if (num < _elements.size())
  {
    Element* oldElement = _elements[num];
    _elements[num] = element;
    element->SetParent(this);

    DevShaderManager::Get()->RemoveMesh(oldElement->AsMesh());
    DevShaderManager::Get()->AddMesh(element->AsMesh());
  }
}

void Group::ReplaceElement(Element* element, Element* newElement)
{
  if (!element || !newElement)
    return;

  unsigned int num = GetElementNum(element);
  
  if (num != _elements.size())
  {
    _elements[num] = newElement;
    element->ClearParent();
    newElement->SetParent(this);

    DevShaderManager::Get()->RemoveMesh(element->AsMesh());
    DevShaderManager::Get()->AddMesh(newElement->AsMesh());
  }
}

void Group::RemoveElement(Element* element)
{
  if (!element)
    return;

  unsigned int num = GetElementNum(element);
  if (num != _elements.size())
  {
    _elements.erase(_elements.begin() + num);
    element->ClearParent();
    DevShaderManager::Get()->RemoveMesh(element->AsMesh());
  }
}

void Group::RemoveElement(unsigned int num)
{
  if (num < _elements.size())
  {
    Element* element = GetElement(num);
    element->ClearParent();
    _elements.erase(_elements.begin() + num);
    DevShaderManager::Get()->RemoveMesh(element->AsMesh());
  }
}

void Group::Update()
{
  if (!_visible())
    return;

  if (_updateMatrix)
  {
    updateMatrix();
    _updateMatrix = false;
  }

  for (unsigned int i = 0; i < _elements.size(); ++i)
    _elements[i]->Update();
}

void Group::updateMatrix()
{
  Element::updateMatrix();
  for (unsigned int i = 0; i < _elements.size(); ++i)
    _elements[i]->UpdateWorldMatrix();
}
