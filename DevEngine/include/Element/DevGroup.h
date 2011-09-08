#ifndef DEV_GROUP_H
#define DEV_GROUP_H

#include <Kernel/DevInclude.h>
#include <Element/DevElement.h>
#include <Shaders/DevShaderManager.h>

namespace dev
{
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
    
    inline unsigned int GetElementNum(Element* element) const
    {
      for (unsigned int i = 0; i < _elements.size(); ++i)
      {
        if (_elements[i] == element) 
          return i;
      }
      return static_cast<unsigned int>(_elements.size());
    }

    inline Element* GetElement(unsigned int num) const
    {
      if (num < _elements.size())
        return (*(_elements.begin() + num));
      return NULL;
    }

    virtual void Update();

    virtual inline Group* AsGroup() 
    {
      return this;
    }

  protected:
    virtual void updateMatrix();

    ElementList _elements;
  };
}

#endif