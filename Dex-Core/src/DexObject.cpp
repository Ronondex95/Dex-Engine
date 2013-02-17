#include <DexObject.h>

namespace Dex
{
	Object::Object( const String& name, int id )
	{
		m_Name = name;
		m_Id = id;

		m_Position = Point3( 0.0f, 0.0f, 0.0f );
		m_Rotation = Point3( 0.0f, 0.0f, 0.0f );
		m_Scale = Point3( 1.0f, 1.0f, 1.0f );
	}

	// Name and Id
	int Object::GetId( void )
	{
		return m_Id;
	}
	const String& Object::GetName( void )
	{
		return m_Name;
	}

	// Position
	void Object::Move( const Point3& position )
	{
		m_Position = m_Position + position;
	}
	void Object::MoveX( const Point& move )
	{
		m_Position = m_Position + Point3( move, 0.0f, 0.0f );
	}
	void Object::MoveY( const Point& move )
	{
		m_Position = m_Position + Point3( 0.0f, move, 0.0f );
	}
	void Object::MoveZ( const Point& move )
	{
		m_Position = m_Position + Point3( 0.0f, 0.0f, move );
	}
	void Object::MoveTo( const Point3& position )
	{
		m_Position = position;
	}
	const Point3& Object::GetPosition( void )
	{
		return m_Position;
	}

	// Rotation
	void Object::Rotation( const Point3& rotation )
	{
		m_Rotation = m_Rotation + rotation;
	}
	void Object::RotationX( const Point& angle )
	{
		m_Rotation = m_Rotation + Point3( angle, 0.0f, 0.0f );
	}
	void Object::RotationY( const Point& angle )
	{
		m_Rotation = m_Rotation + Point3( 0.0f, angle, 0.0f );
	}
	void Object::RotationZ( const Point& angle )
	{
		m_Rotation = m_Rotation + Point3( 0.0f, 0.0f, angle );
	}
	void Object::RotationTo( const Point3& rotation )
	{
		m_Rotation = rotation;
	}
	const Point3& Object::GetRotation( void )
	{
		return m_Rotation;
	}

	// Scale
	void Object::Scale( const Point3& scale )
	{
		m_Scale = m_Scale + scale;
	}
	void Object::ScaleX( const Point& size )
	{
		m_Scale = m_Scale + Point3( size, 0.0f, 0.0f );
	}
	void Object::ScaleY( const Point& size )
	{
		m_Scale = m_Scale + Point3( 0.0f, size, 0.0f );
	}
	void Object::ScaleZ( const Point& size )
	{
		m_Scale = m_Scale + Point3( 0.0f, 0.0f, size );
	}
	void Object::ScaleTo( const Point3& scale )
	{
		m_Scale = scale;
	}
	const Point3& Object::GetScale( void )
	{
		return m_Scale;
	}
}