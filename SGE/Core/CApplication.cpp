//====================================================================================================
// Filename:	CApplication.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Core/CApplication.h"

#include "Core/CLog.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CApplication::CApplication(void)
	: mWindow(0)
	, mWinWidth(0)
	, mWinHeight(0)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CApplication::~CApplication(void)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CApplication::Initialize(const char* pAppName, HINSTANCE hInstance, int iWinWidth, int iWinHeight)
{
	// Initialize error log
	CLog::Create();
	CLog::Get()->Initialize();

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Application] Initializing: %s...", pAppName);

	// Create a new window class
	WNDCLASSEXA wc;

	// Fill the window class structure
	wc.cbSize		   = sizeof(WNDCLASSEXA);
	wc.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	  = DefWindowProcA;
	wc.cbClsExtra	   = 0;
	wc.cbWndExtra	   = 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor		  = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	 = nullptr;
	wc.lpszClassName	= pAppName;
	wc.hIconSm		  = LoadIcon(nullptr, IDI_APPLICATION);

	// Register the window class
	RegisterClassExA(&wc);

	// Cache the windows dimension
	mWinWidth = iWinWidth;
	mWinHeight = iWinHeight;

	// Create a new window
	mWindow = CreateWindowExA
	(
		0,					   // Extended style
		pAppName,				   // Class name
		pAppName,				   // Window name
		WS_OVERLAPPEDWINDOW,			  // Style
		0, 0,					   // Position
		mWinWidth, mWinHeight,	// Dimensions
		nullptr,					   // Handle to parent window
		nullptr,					   // Handle to menu
		hInstance,				  // Handle to instance
		nullptr						// Param
	);

	// Hide the cursor
	//SetCursor(nullptr);

	// Show the window
	UpdateWindow(mWindow);
	ShowWindow(mWindow, SW_SHOWNORMAL);

	// Do any additional initialization here
	OnInitialize();

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Application] %s initialized", pAppName);
}

//----------------------------------------------------------------------------------------------------

void CApplication::Terminate(void)
{
	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Application] Terminating...");

	// Do any additional termination tasks here
	OnTerminate();

	// Destroy the window
	DestroyWindow(mWindow);

	// Write to log
	CLog::Get()->Write(ELogMessageType_MESSAGE, "[Application] Application terminated.");

	// Shutdown error log
	CLog::Get()->Terminate();
	CLog::Destroy();
}

//----------------------------------------------------------------------------------------------------

void CApplication::Run(void)
{
	MSG msg;
	memset(&msg, 0, sizeof(MSG));

	// Start the message loop
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Run main loop
			OnMainLoop();
		}
	}
}

//----------------------------------------------------------------------------------------------------

void CApplication::Quit(void)
{
	PostQuitMessage(0);
}

//----------------------------------------------------------------------------------------------------

void CApplication::OnInitialize(void)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CApplication::OnTerminate(void)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CApplication::OnMainLoop(void)
{
	if (KEYDOWN(VK_ESCAPE))
	{
		Quit();
	}
}