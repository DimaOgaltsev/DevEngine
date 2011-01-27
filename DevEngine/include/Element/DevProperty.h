#ifndef DEV_PROPERTY_H
#define DEV_PROPERTY_H

#include <Kernel/DevInclude.h>
#include <Math/DevMatrix.h>

namespace dev
{
  namespace Properties
  {
    class Property
    {
    public:
      Property() {}
      virtual ~Property() {}

      virtual void Save();
      virtual void Load();
    };

    //Bool
    class Bool:
      public Property
    {
    public:
      Bool() : Property(), _value(FALSE) {}
      virtual ~Bool() {}

      void operator = (const bool& value);
      inline const bool& operator () () const
      {
        return _value;
      }

    protected:
      bool _value;
    };

    //Float
    class Float:
      public Property
    {
    public:
      Float() : Property(), _value(0) {}
      virtual ~Float() {}

      void operator = (const float& value);
      void operator += (const float& value);
      inline const float& operator () () const
      {
        return _value;
      }

    protected:
      float _value;
    };

    //Vector2
    class Vector2: 
      public Property
    {
    public:
      Vector2() : Property(), _value(0, 0) {}
      virtual ~Vector2() {}

      void operator = (const Vec2& value);
      void operator += (const Vec2& value);
      inline const Vec2& operator () () const
      {
        return _value;
      }

    protected:
      Vec2 _value;
    };

    //Vector3
    class Vector3: 
      public Property
    {
    public:
      Vector3() : Property(), _value(0, 0, 0) {}
      virtual ~Vector3() {}

      void operator = (const Vec3& value);
      void operator += (const Vec3& value);
      inline const Vec3& operator () () const
      {
        return _value;
      }

    protected:
      Vec3 _value;
    };

    //Vector4
    class Vector4: 
      public Property
    {
    public:
      Vector4() : Property(), _value(0, 0, 0, 0) {}
      virtual ~Vector4() {}

      void operator = (const Vec4& value);
      void operator += (const Vec4& value);
      inline const Vec4& operator () () const
      {
        return _value;
      }
    protected:
      Vec4 _value;
    };

    //path
    class Path: 
      public Property
    {
    public:
      Path() : Property() {}
      virtual ~Path() {}

      void operator = (const char* value);
      inline const char* operator () () const
      {
        return _value.c_str();
      }

    protected:
      std::string _value;
    };
  }
}

#endif