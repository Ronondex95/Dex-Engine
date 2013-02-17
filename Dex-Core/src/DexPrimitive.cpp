#include <DexPrimitive.h>
#include <DexIndexBuffer.h>
#include <DexVertexBuffer.h>

namespace Dex
{
	void Primitive::SetPrimitiveType( const PrimitiveType& type )
	{
		m_Type = type;
	}

	const PrimitiveType& Primitive::GetPrimitiveType( void )
	{
		return m_Type;
	}

	IVertexBuffer* Primitive::GetVertexBuffer( void )
	{
		return m_VercexBuffer;
	}
}