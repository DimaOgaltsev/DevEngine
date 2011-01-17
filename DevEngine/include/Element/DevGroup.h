#ifndef DEV_GROUP_H
#define DEV_GROUP_H

#include <Kernel/DevInclude.h>
#include <Element/DevElement.h>

namespace dev
{
  typedef std::vector<Element*> ElementList;
  
  class Group : 
    public Element
  {
  public:
    Group(D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 scale = D3DXVECTOR3(1, 1, 1));
    virtual ~Group();

    void ClearList();
    void AddElement(Element* element);
    void InsertElement(unsigned int num, Element* element);
    void SetElement(unsigned int num, Element* element);
    void ReplaceElement(Element* element, Element* newElement);
    void RemoveElement(Element* element);
    void RemoveElement(unsigned int num);
    unsigned int GetElementNum(Element* element);
    Element* GetElement(unsigned int num);

    virtual void Update();

  protected:
    ElementList _elements;
  };
}

#endif