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
    Group(Vec3 position, Vec3 rotation, Vec3 scale);
    Group();
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