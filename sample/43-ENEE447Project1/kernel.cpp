//
// kernel.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2015-2018  R. Stange <rsta2@o2online.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"
#include "screentask.h"
#include "primetask.h"
#include "ledtask.h"
#include <circle/string.h>
#include <assert.h>

static const char FromKernel[] = "kernel";

CKernel::CKernel (void)
:	m_Screen (m_Options.GetWidth (), m_Options.GetHeight ()),
	m_Timer (&m_Interrupt),
	m_Logger (m_Options.GetLogLevel (), &m_Timer)
{
	m_ActLED.Blink (5);	// show we are alive
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	boolean bOK = TRUE;

	if (bOK)
	{
		bOK = m_Screen.Initialize ();
	}

	if (bOK)
	{
		bOK = m_Serial.Initialize (115200);
	}

	if (bOK)
	{
		CDevice *pTarget = m_DeviceNameService.GetDevice (m_Options.GetLogDevice (), FALSE);
		if (pTarget == 0)
		{
			pTarget = &m_Screen;
		}

		bOK = m_Logger.Initialize (pTarget);
	}

	if (bOK)
	{
		bOK = m_Interrupt.Initialize ();
	}

	if (bOK)
	{
		bOK = m_Timer.Initialize ();
	}

	return bOK;
}

TShutdownMode CKernel::Run (void)
{
	m_Logger.Write (FromKernel, LogNotice, "Compile time: " __DATE__ " " __TIME__);

	// start tasks
	for (unsigned nTaskID = 1; nTaskID <= 4; nTaskID++)
	{
		auto t = new CScreenTask (nTaskID, &m_Screen);
		t->SetName("ScreenTask");
		t->SetTaskPriority(30); //30
	}

	auto t = new CPrimeTask (&m_Screen);
	t->SetName("PrimeTask");
	t->SetTaskPriority(20); //20

	auto t2 = new CLEDTask (&m_ActLED);
	t2->SetName("LEDTask");
	t2->SetTaskPriority(10); //10

	// the main task
	while (1)
	{
		static const char Message[] = "Main ****\n";
		m_Screen.Write (Message, sizeof Message-1);

		m_Event.Clear ();
		m_Timer.StartKernelTimer (5 * HZ, TimerHandler, this);

		m_Event.Wait ();
	}

	return ShutdownHalt;
}

void CKernel::TimerHandler (TKernelTimerHandle hTimer, void *pParam, void *pContext)
{
	CKernel *pThis = (CKernel *) pParam;
	assert (pThis != 0);

	pThis->m_Event.Set ();
}
