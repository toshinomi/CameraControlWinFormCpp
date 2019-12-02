#pragma once

namespace CameraControlWindowsFormCpp {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace AForge::Video;
	using namespace AForge::Video::DirectShow;

	/// <summary>
	/// FormMain の概要
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//

			lblTitle->MouseDown += gcnew MouseEventHandler(this, &FormMain::OnMouseDownLblTitle);
			lblTitle->MouseMove += gcnew MouseEventHandler(this, &FormMain::OnMouseMoveLblTitle);

			GetCameraInfo();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~FormMain()
		{
			delete m_videoDevices;
			delete m_videoSource;

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnStop;
	protected:
	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::Button^ btnGetCameraInfo;
	private: System::Windows::Forms::Label^ lblCameraList;
	private: System::Windows::Forms::ComboBox^ cmbCamera;
	private: System::Windows::Forms::Button^ btnMinimizedIcon;
	private: System::Windows::Forms::Button^ btnClose;
	private: System::Windows::Forms::Label^ lblTitle;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->btnGetCameraInfo = (gcnew System::Windows::Forms::Button());
			this->lblCameraList = (gcnew System::Windows::Forms::Label());
			this->cmbCamera = (gcnew System::Windows::Forms::ComboBox());
			this->btnMinimizedIcon = (gcnew System::Windows::Forms::Button());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// btnStop
			// 
			this->btnStop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnStop->Location = System::Drawing::Point(713, 64);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(75, 37);
			this->btnStop->TabIndex = 10;
			this->btnStop->Text = L"Stop";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &FormMain::OnClickBtnStop);
			// 
			// btnStart
			// 
			this->btnStart->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnStart->Location = System::Drawing::Point(632, 64);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 37);
			this->btnStart->TabIndex = 8;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &FormMain::OnClickBtnStart);
			// 
			// pictureBox
			// 
			this->pictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox->Location = System::Drawing::Point(12, 112);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(776, 476);
			this->pictureBox->TabIndex = 15;
			this->pictureBox->TabStop = false;
			// 
			// btnGetCameraInfo
			// 
			this->btnGetCameraInfo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnGetCameraInfo->Location = System::Drawing::Point(332, 64);
			this->btnGetCameraInfo->Name = L"btnGetCameraInfo";
			this->btnGetCameraInfo->Size = System::Drawing::Size(72, 37);
			this->btnGetCameraInfo->TabIndex = 13;
			this->btnGetCameraInfo->Text = L"Get";
			this->btnGetCameraInfo->UseVisualStyleBackColor = true;
			this->btnGetCameraInfo->Click += gcnew System::EventHandler(this, &FormMain::OnClickBtnGetCameraInfo);
			// 
			// lblCameraList
			// 
			this->lblCameraList->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->lblCameraList->Location = System::Drawing::Point(12, 39);
			this->lblCameraList->Name = L"lblCameraList";
			this->lblCameraList->Size = System::Drawing::Size(174, 27);
			this->lblCameraList->TabIndex = 14;
			this->lblCameraList->Text = L"Camera List";
			// 
			// cmbCamera
			// 
			this->cmbCamera->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCamera->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cmbCamera->FormattingEnabled = true;
			this->cmbCamera->Location = System::Drawing::Point(12, 69);
			this->cmbCamera->Name = L"cmbCamera";
			this->cmbCamera->Size = System::Drawing::Size(314, 28);
			this->cmbCamera->TabIndex = 12;
			// 
			// btnMinimizedIcon
			// 
			this->btnMinimizedIcon->BackColor = System::Drawing::Color::Black;
			this->btnMinimizedIcon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnMinimizedIcon->ForeColor = System::Drawing::Color::White;
			this->btnMinimizedIcon->Location = System::Drawing::Point(739, 0);
			this->btnMinimizedIcon->Name = L"btnMinimizedIcon";
			this->btnMinimizedIcon->Size = System::Drawing::Size(30, 30);
			this->btnMinimizedIcon->TabIndex = 11;
			this->btnMinimizedIcon->TabStop = false;
			this->btnMinimizedIcon->Text = L"-";
			this->btnMinimizedIcon->UseVisualStyleBackColor = false;
			this->btnMinimizedIcon->Click += gcnew System::EventHandler(this, &FormMain::OnClickBtnMinimizedIcon);
			// 
			// btnClose
			// 
			this->btnClose->BackColor = System::Drawing::Color::Black;
			this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnClose->ForeColor = System::Drawing::Color::White;
			this->btnClose->Location = System::Drawing::Point(770, 0);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(30, 30);
			this->btnClose->TabIndex = 9;
			this->btnClose->TabStop = false;
			this->btnClose->Text = L"×";
			this->btnClose->UseCompatibleTextRendering = true;
			this->btnClose->UseVisualStyleBackColor = false;
			this->btnClose->Click += gcnew System::EventHandler(this, &FormMain::OnClickBtnClose);
			// 
			// lblTitle
			// 
			this->lblTitle->BackColor = System::Drawing::Color::Black;
			this->lblTitle->Location = System::Drawing::Point(0, 0);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(800, 30);
			this->lblTitle->TabIndex = 7;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ClientSize = System::Drawing::Size(800, 600);
			this->Controls->Add(this->btnStop);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->btnGetCameraInfo);
			this->Controls->Add(this->lblCameraList);
			this->Controls->Add(this->cmbCamera);
			this->Controls->Add(this->btnMinimizedIcon);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->lblTitle);
			this->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		private:
			Point^ m_mousePoint;
			bool m_isDeviceExist = false;
			FilterInfoCollection^ m_videoDevices;
			VideoCaptureDevice^ m_videoSource = nullptr;
		private:
			void OnMouseDownLblTitle(Object^ sender, MouseEventArgs^ e);
			void OnMouseMoveLblTitle(Object^ sender, MouseEventArgs^ e);
			void OnClickBtnClose(Object^ sender, EventArgs^ e);
			void OnClickBtnMinimizedIcon(Object^ sender, EventArgs^ e);
			void OnClickBtnGetCameraInfo(Object^ sender, EventArgs^ e);
			void GetCameraInfo(void);
			void OnClickBtnStart(Object^ sender, EventArgs^ e);
			void OnClickBtnStop(Object^ sender, EventArgs^ e);
			void VideoRendering(Object^ sender, NewFrameEventArgs^ eventArgs);
			void CloseVideoSource(void);
	};
}
