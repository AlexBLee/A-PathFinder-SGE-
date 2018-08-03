//====================================================================================================
// Filename:	CSpriteRenderer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Graphics/CSpriteRenderer.h"

#include <assert.h>

#include "Core/CLog.h"
#include "Graphics/CSprite.h"
#include "Graphics/CDXGraphics.h"

//====================================================================================================
// Statics
//====================================================================================================

CSpriteRenderer* CSpriteRenderer::s_pInstance = nullptr;

//====================================================================================================
// Class Definitions
//====================================================================================================

void CSpriteRenderer::Create()
{
	assert(s_pInstance == nullptr);
	s_pInstance = new CSpriteRenderer();
}

//----------------------------------------------------------------------------------------------------

void CSpriteRenderer::Destroy()
{
	assert(s_pInstance != nullptr);
	delete s_pInstance;
	s_pInstance = nullptr;
}

//----------------------------------------------------------------------------------------------------

CSpriteRenderer* CSpriteRenderer::Get(void)
{
	assert(s_pInstance != nullptr);
	return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

CSpriteRenderer::CSpriteRenderer(void) :
	mpD3DXSprite(nullptr),
	mInitialized(false)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CSpriteRenderer::~CSpriteRenderer(void)
{
	// Terminate the sprite renderer
	Terminate();
}

//----------------------------------------------------------------------------------------------------

void CSpriteRenderer::Initialize(void)
{
	// Check if we have already initialized the renderer
	if (mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[SpriteRenderer] Renderer already initialized.");
		return;
	}

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[SpriteRenderer] Initializing...");

	// Create a D3DX sprite for rendering
	if (FAILED(D3DXCreateSprite(CDXGraphics::Get()->D3DDevice(), &mpD3DXSprite)))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[SpriteRenderer] Failed to create D3DX sprite.");
		return;
	}

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[SpriteRenderer] Renderer initialized.");

	// Set flag
	mInitialized = true;
}

//----------------------------------------------------------------------------------------------------

void CSpriteRenderer::Terminate(void)
{
	// Check if we have already terminated the renderer
	if (!mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[SpriteRenderer] Renderer already terminated.");
		return;
	}

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[SpriteRenderer] Terminating...");

	// Release D3DX sprite
	if (nullptr != mpD3DXSprite)
	{
		mpD3DXSprite->Release();
		mpD3DXSprite = nullptr;
	}

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[SpriteRenderer] Renderer terminated.");

	// Set flag
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void CSpriteRenderer::BeginRender(void)
{
	// Check if renderer is initialized
	if (!mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[SpriteRenderer] Failed to render sprites. Renderer not initialized.");
		return;
	}

	// Start sprite rendering
	mpD3DXSprite->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
}

//----------------------------------------------------------------------------------------------------

void CSpriteRenderer::EndRender(void)
{
	// Check if renderer is initialized
	if (!mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[SpriteRenderer] Failed to render sprites. Renderer not initialized.");
		return;
	}

	// Commit sprite rendering
	mpD3DXSprite->End();
}

//----------------------------------------------------------------------------------------------------

ID3DXSprite* CSpriteRenderer::D3DXSprite(void) const
{
	// Check if renderer is initialized
	if (!mInitialized)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_ERROR, "[SpriteRenderer] Failed to get D3DX sprite. Renderer not initialized.");
		return nullptr;
	}

	return mpD3DXSprite;
}