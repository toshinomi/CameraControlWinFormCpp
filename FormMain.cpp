#include "FormMain.h"

using namespace CameraControlWindowsFormCpp;

/// <summary>
/// �^�C�g���o�[�}�E�X�_�E���̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
void FormMain::OnMouseDownLblTitle(Object^ sender, MouseEventArgs^ e)
{
	if ((e->Button & ::MouseButtons::Left) == ::MouseButtons::Left)
	{
		m_mousePoint = gcnew Point(e->X, e->Y);
	}

	return;
}

/// <summary>
/// �^�C�g���o�[�}�E�X���[�u�̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
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

/// <summary>
/// ����{�^���̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
void FormMain::OnClickBtnClose(Object^ sender, EventArgs^ e)
{
	auto result = MessageBox::Show("Close the application ?", "Question", MessageBoxButtons::OKCancel, MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button2);
	if (result == ::DialogResult::OK)
	{
		OnClickBtnStop(nullptr, nullptr);
		this->Close();
	}

	return;
}

/// <summary>
/// �ŏ����{�^���̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
void FormMain::OnClickBtnMinimizedIcon(Object^ sender, EventArgs^ e)
{
	this->WindowState = FormWindowState::Minimized;

	return;
}

/// <summary>
/// �J�������擾�̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
void FormMain::OnClickBtnGetCameraInfo(Object^ sender, EventArgs^ e)
{
	GetCameraInfo();

	return;
}

/// <summary>
/// �J�������擾
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
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

/// <summary>
/// �X�^�[�g�{�^���̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
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

/// <summary>
/// �X�g�b�v�{�^���̃N���b�N�C�x���g
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="e">�C�x���g�̃f�[�^</param>
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

/// <summary>
/// �r�f�I�`��
/// </summary>
/// <param name="sender">�I�u�W�F�N�g</param>
/// <param name="eventArgs">NewFrameEvent�̃f�[�^</param>
void FormMain::VideoRendering(Object^ sender, NewFrameEventArgs^ eventArgs)
{
	Bitmap^ bitmap = (Bitmap^)eventArgs->Frame->Clone();
	pictureBox->Image = bitmap;

	return;
}

/// <summary>
/// �r�f�I���\�[�X�̏I��
/// </summary>
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