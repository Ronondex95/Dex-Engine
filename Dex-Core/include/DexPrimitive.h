#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	enum PrimitiveType
	{
		PT_POINT_LIST,
		PT_LINE_LIST,
		PT_LINE_STRIP,
		PT_TRIANGLE_LIST,
		PT_TRIANGLE_STRIP,
		PT_TRIANGLE_FAN
	};

	class D_EXPORT Primitive
	{
	public:
		void SetPrimitiveType( const PrimitiveType& type )
		{
			m_Type = type;
		}

		const PrimitiveType& GetPrimitiveType( void )
		{
			return m_Type;
		}

		IVertexBuffer* GetVertexBuffer( void );

	private:
		PrimitiveType			m_Type;

		IVertexBuffer*			m_VercexBuffer;
	};
}