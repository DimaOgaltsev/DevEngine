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
      if(!_element)
        _element = new T();
      return _element;
    }

    static void Release()
    { 
      if(_element)
      {
        delete _element;
        _element = 0;
      }
    }
  private:
    static T* _element;
  };
  
  template<class T>
  T* Singleton<T>::_element = 0;
}

#endif