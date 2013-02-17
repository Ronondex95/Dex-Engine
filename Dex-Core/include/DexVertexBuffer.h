#pragma once

#include <DexPreCompletion.h>

namespace Dex
{
	enum VertexType
	{
		VT_POINT,
		VT_LINE,
		VT_PC,
		VT_PNT
	};

	class D_EXPORT IVertexBuffer
	{
	public:
		virtual void CreateBuffer( const VertexType& type ) = 0;

	protected:
		int						m_nVertex;
		size_t					m_SizeBuffer;
	};
}