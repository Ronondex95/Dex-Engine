#include <DexScene.h>
#include <DexCore.h>
#include <DexCamera.h>
#include <DexMash.h>
#include <DexLight.h>
#include <DexGroup.h>
#include <DexRootGroup.h>
#include <DexRenderConnect.h>

namespace Dex
{
	Scene::Scene( const String& name, const String& render_window )
	{
		m_Name = name;
		m_ActiveCamera = 0;
		m_IdCounter = 0;

		m_pConnect = Core::GetRenderSystem()->GetConnect( render_window );

		m_RootGroup = new RootGroup( this, "Root", m_IdCounter++ );
	}

	Scene::~Scene( void )
	{
	}

	int Scene::GetNewId( void )
	{
		return m_IdCounter++;
	}

	Group* Scene::GetRootGroup( void )
	{
		return m_RootGroup;
	}

	Camera* Scene::CreateCamera( const String& name, bool active )
	{
		m_CameraList::iterator it_find_camera = m_Camera.find( name );

		if ( it_find_camera == m_Camera.end() )
		{
			Camera* camera = new Camera( name, m_IdCounter++ );

			m_Camera[name] = camera;

			if ( active )
			{
				m_ActiveCamera = camera;
			}

			return camera;
		}
		else
		{
			Core::GetLog()->DrawLine("Scene:CreateCamera Камера " + name + " уже существует", MT_WARNING );

			return m_Camera[name];
		}
	}

	Camera* Scene::GetCamera( const String& name )
	{
		return m_Camera[name];
	}

	Mash* Scene::CreateDMashFromFile( const String& file, const String& name )
	{
		m_MashList::iterator it_find_mash = m_Mash.find( name );

		if ( it_find_mash == m_Mash.end() )
		{
			if ( m_pConnect->LoadMash( file ) )
			{
				Mash* obj = new Mash( name, m_IdCounter++ );

				IVertexBuffer* vertex = m_pConnect->CreateVertexBuffer();

				m_pConnect->LoadMash( file, &vertex );

				m_Mash[name] = obj;

				return obj;
			}

			return NULL;
		}
		else
		{
			Core::GetLog()->DrawLine("Scene:CreateDMashFromFile Камера " + name + " уже существует", MT_WARNING );

			return m_Mash[name];
		}
	}

	Mash* Scene::GetMash( const String& name )
	{
		return m_Mash[name];
	}

	Light* Scene::CreateLight( const String& name, const Point4& color )
	{
		m_LightList::iterator it_find_light = m_Light.find( name );

		if ( it_find_light == m_Light.end() )
		{
			Light* light = new Light( name, m_IdCounter++, color );

			m_Light[name] = light;

			return light;
		}
		else
		{
			Core::GetLog()->DrawLine("Scene:CreateDMashFromFile Камера " + name + " уже существует", MT_WARNING );

			return m_Light[name];
		}
	}

	Light* Scene::GetLight( const String& name )
	{
		return m_Light[name];
	}

	void Scene::RenderScene( void )
	{
		if ( m_pConnect->IsLostControl() )
			return;

		m_pConnect->Clear();
		m_pConnect->PreRender();
		m_pConnect->SetMatrixIdentity();

		// Camera
		m_pConnect->SetViewMatrix( m_ActiveCamera->GetPosition(), m_ActiveCamera->GetTarget(), m_ActiveCamera->GetUp() );

		// Light
		m_LightList::iterator it_light;
		for ( it_light = m_Light.begin(); it_light != m_Light.end(); ++it_light )
		{
			m_pConnect->AddLight( it_light->second->GetPosition(), it_light->second->GetColor() );
		}

		// Motor
		m_MashList::iterator it_mash;
		for ( it_mash = m_Mash.begin(); it_mash != m_Mash.end(); ++it_mash )
		{
			Mash* obj = it_mash->second;

			m_pConnect->SetWorldMatrix( obj->GetPosition(), obj->GetRotation(), obj->GetScale() );
			obj->
			m_pConnect->Render( obj->GetPrimitiveType() );
		}

		m_pConnect->PostRender();
		m_pConnect->Present();
	}
}