#ifndef DEV_SINGLETON_H
#define DEV_SINGLETON_H

namespace dev
{
  template<class T>
  class Singleton
  {
  public:
    static T* Get()
    {
      static T* element = new T();
      return element;
    }
  };
}

#endif