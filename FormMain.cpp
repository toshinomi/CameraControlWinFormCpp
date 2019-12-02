#include "FormMain.h"

using namespace CameraControlWindowsFormCpp;

void FormMain::OnMouseDownLblTitle(Object^ sender, MouseEventArgs^ e)
{
	if ((e->Button & ::MouseButtons::Left) == ::MouseButtons::Left)
	{
		m_mousePoint = gcnew Point(e->X, e->Y);
	}

	return;
}

void FormMain::OnMouseMoveLblTitle(Object^ sender, MouseEventArgs^ e)
{
	if ((e->Button & ::MouseButtons::Left) == ::MouseButtons::Left)
	{
		this->Left += e->X - m_mousePoint->X;
		this->Top += e->Y - m_mousePoint->Y;
		delete m_mousePoint;
	}

	return;
}

void FormMain::OnClickBtnClose(Object^ sender, EventArgs^ e)
{
	auto result = MessageBox::Show("Close the application ?", "Question", MessageBoxButtons::OKCancel, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button2);
	if (result == ::DialogResult::OK)
	{
		this->Close();
	}

	return;
}

void FormMain::OnClickBtnMinimizedIcon(Object^ sender, EventArgs^ e)
{
	this->WindowState = FormWindowState::Minimized;

	return;
}

void FormMain::OnClickBtnGetCameraInfo(Object^ sender, EventArgs^ e)
{
	GetCameraInfo();

	return;
}

void FormMain::GetCameraInfo(void)
{
	try
	{
		delete m_videoDevices;
		m_videoDevices = gcnew FilterInfoCollection(FilterCategory::VideoInputDevice);
		cmbCamera->Items->Clear();

		if (m_videoDevices->Count <= 0)
		{
			throw gcnew ApplicationException();
		}

		for each(FilterInfo^ device in m_videoDevices)
		{
			cmbCamera->Items->Add(device->Name);
			cmbCamera->SelectedIndex = 0;
			m_isDeviceExist = true;
		}
	}
	catch (ApplicationException^)
	{
		cmbCamera->Items->Add("Device does not exist");
		m_isDeviceExist = false;
	}

	return;
}

void FormMain::OnClickBtnStart(Object^ sender, EventArgs^ e)
{
	if (m_isDeviceExist)
	{
		delete m_videoSource;
		m_videoSource = gcnew VideoCaptureDevice(m_videoDevices[cmbCamera->SelectedIndex]->MonikerString);
		m_videoSource->NewFrame += gcnew NewFrameEventHandler(this, &FormMain::VideoRendering);
		CloseVideoSource();

		m_videoSource->Start();
	}

	return;
}

void FormMain::OnClickBtnStop(Object^ sender, EventArgs^ e)
{
	if (m_videoSource != nullptr)
	{
		if (m_videoSource->IsRunning)
		{
			CloseVideoSource();
		}
	}

	return;
}

void FormMain::VideoRendering(Object^ sender, NewFrameEventArgs^ eventArgs)
{
	Bitmap^ bitmap = (Bitmap^)eventArgs->Frame->Clone();
	pictureBox->Image = bitmap;

	return;
}

void FormMain::CloseVideoSource(void)
{
	if (m_videoSource != nullptr)
	{
		if (m_videoSource->IsRunning)
		{
			m_videoSource->SignalToStop();
			m_videoSource = nullptr;
		}
	}

	return;
}