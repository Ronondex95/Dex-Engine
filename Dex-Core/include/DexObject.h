#pragma once

#include <DexPreCompletion.h>
#include <DexMath.h>

namespace Dex
{
	class D_EXPORT Object
	{
	public:
		Object( const String& name, int id );

		// Name and Id
		int GetId( void );
		const String& GetName( void );

		// Position
		void Move( const Point3& position );
		void MoveX( const Point& move );
		void MoveY( const Point& move );
		void MoveZ( const Point& move );
		void MoveTo( const Point3& position );
		const Point3& GetPosition( void );

		// Rotation
		void Rotation( const Point3& rotation );
		void RotationX( const Point& angle );
		void RotationY( const Point& angle );
		void RotationZ( const Point& angle );
		void RotationTo( const Point3& rotation );
		const Point3& GetRotation( void );

		// Scale
		void Scale( const Point3& scale );
		void ScaleX( const Point& size );
		void ScaleY( const Point& size );
		void ScaleZ( const Point& size );
		void ScaleTo( const Point3& scale );
		const Point3& GetScale( void );

	private:
		int					m_Id;
		String				m_Name;

		Point3				m_Position;
		Point3				m_Rotation;
		Point3				m_Scale;
	};
}