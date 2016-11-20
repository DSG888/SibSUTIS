#pragma once

#include <string.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0400
#include "windows.h"
#include <stdio.h>
#include <iostream>

namespace lab9 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void) {InitializeComponent();}
	protected:
		~Form1(){if (components) delete components;	}
	private: System::Windows::Forms::Button^  ButtonBuilder;
	private: System::Windows::Forms::Button^  ButtonHelp;
	private: System::Windows::Forms::Button^  ButtonColor;
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private:
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
			 Color oldColor; // для запоминания старого цвета

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)	{
			this->ButtonBuilder = (gcnew System::Windows::Forms::Button());
			this->ButtonHelp = (gcnew System::Windows::Forms::Button());
			this->ButtonColor = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// ButtonBuilder
			// 
			this->ButtonBuilder->Location = System::Drawing::Point(12, 38);
			this->ButtonBuilder->Name = L"ButtonBuilder";
			this->ButtonBuilder->Size = System::Drawing::Size(75, 23);
			this->ButtonBuilder->TabIndex = 0;
			this->ButtonBuilder->Text = L"ButtonBuilder";
			this->ButtonBuilder->UseVisualStyleBackColor = true;
			this->ButtonBuilder->Click += gcnew System::EventHandler(this, &Form1::ButtonBuilder_Click);
			this->ButtonBuilder->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::ButtonBuilder_KeyPress);
			// 
			// ButtonHelp
			// 
			this->ButtonHelp->Location = System::Drawing::Point(12, 67);
			this->ButtonHelp->Name = L"ButtonHelp";
			this->ButtonHelp->Size = System::Drawing::Size(75, 23);
			this->ButtonHelp->TabIndex = 1;
			this->ButtonHelp->Text = L"ButtonHelp";
			this->ButtonHelp->UseVisualStyleBackColor = true;
			this->ButtonHelp->Click += gcnew System::EventHandler(this, &Form1::ButtonHelp_Click);
			// 
			// ButtonColor
			// 
			this->ButtonColor->Location = System::Drawing::Point(12, 96);
			this->ButtonColor->Name = L"ButtonColor";
			this->ButtonColor->Size = System::Drawing::Size(75, 23);
			this->ButtonColor->TabIndex = 2;
			this->ButtonColor->Text = L"ButtonColor";
			this->ButtonColor->UseVisualStyleBackColor = true;
			this->ButtonColor->Click += gcnew System::EventHandler(this, &Form1::ButtonColor_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 125);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Exit\?";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 4;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(100, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(163, 20);
			this->textBox1->TabIndex = 5;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 166);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->ButtonColor);
			this->Controls->Add(this->ButtonHelp);
			this->Controls->Add(this->ButtonBuilder);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDoubleClick);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseClick);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		char* SystemStringToChar(System::String^ string) 
		{
            return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
        }
		System::String^ CharToSystemString(char* ch) 
		{
			return gcnew String(ch);
		}
#pragma endregion

//

	private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) { // обработчик закрытия формы
				FILE *file; // файл
				String ^ filename = System::Diagnostics::Process::GetCurrentProcess()->ProcessName+".ini"; // имя текущего процесса, для созания файла
				file = fopen(SystemStringToChar(filename),"w"); // окрываем файл с именем filename для записи
				fputs(SystemStringToChar(""+this->Top),file); // выводим верхнюю координату формы
				fputc('\n',file); // переход на новую строку
				fputs(SystemStringToChar(""+this->Left),file); // левую границу
				fputc('\n',file);
				fputs(SystemStringToChar(""+this->Width),file); // ширину
				fputc('\n',file);
				fputs(SystemStringToChar(""+this->Height),file); // высоту
				if(textBox1->Text != "") // если текстбокс не пустой
				{
					fputc('\n',file); // на новой строке
					fputs(SystemStringToChar(this->textBox1->Text),file); // воводим этот текст
				}
				fclose(file); // закрываем файл

			 }
	private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) { // обработчик открытия формы
				char buff[100];
				String ^ filename = System::Diagnostics::Process::GetCurrentProcess()->ProcessName+".ini"; // узнаем имя файла
				{
					FILE *file;
					file = fopen(SystemStringToChar(filename),"r"); // открываем файл для чтения
					if(file != NULL) // если он существует
					{
						int a;

						fscanf(file,"%d",&a); // считываем первое число
						this->Top = a; // задаем верхнюю координату формы
							
						fscanf(file,"%d",&a); // второе число
						this->Left = a; // левая координата
							
						fscanf(file,"%d",&a);
						this->Width = a; // ширина формы
							
						fscanf(file,"%d",&a);
						this->Height = a; // высота
						int i = 0;
						while(!feof(file)) // пока не конец файла
						{
							buff[i++] = fgetc(file); // считываем строки в файл
						}
						buff[i > 0 ? --i:i] = '\0';// ограничиваем строку нулевым символом (обозначим конец строки)
						this->textBox1->Text = CharToSystemString(buff); // задаем этот текст текстбоксу
						fclose(file); // закрываем файл
					}
				}
			 }
	private: System::Void ButtonBuilder_Click(System::Object^  sender, System::EventArgs^  e) { // buttonBuilde
				System::Windows::Forms::DialogResult res; // создаем обхект типа DialogResult
				res=MessageBox::Show("message!", "Form NEVER Closing", MessageBoxButtons::YesNo,MessageBoxIcon::Question); // выдаем окно спрашивающее да или нет.

				if (res == System::Windows::Forms::DialogResult::No) // если выбрали нет
				{
					label1->Text=L"You chose No"; // выводим что выбрали нет
				}
				else
				{
					label1->Text=L"You chose Yes"; // иначе выбрали да
				}
			 }
	private: System::Void ButtonBuilder_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) { // слушаем кнопки
				if (e->KeyChar == (wchar_t)Keys::Escape) // если нажали эскейп
				 {
					 label1->Text = ""; // очищаем лейбл
				 }
			 }
private: System::Void Form1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) { // клик мышки по форме
			 this->Text = L"Еще раз"; // меняем заголовок формы
		 }
private: System::Void Form1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) { // двойной клик по форме
			  this->Text = L"Я вас слушаю"; // меняем заголовок формы
		 }
private: System::Void ButtonHelp_Click(System::Object^  sender, System::EventArgs^  e) { // buttonHelp
			 MessageBox::Show(this,"Ничего не знаю!","Help",MessageBoxButtons::OK,MessageBoxIcon::Question); // вывод сообщения
		 }
private: System::Void ButtonColor_Click(System::Object^  sender, System::EventArgs^  e) { // buttonColor
			 System::Windows::Forms::DialogResult res;
				res=MessageBox::Show("Покрасить в зеленый цвет?", "Покраска", MessageBoxButtons::YesNo,MessageBoxIcon::Question); // спрашиваем перекрасить или нет?

				if (res == System::Windows::Forms::DialogResult::No) // если нет
				{
					this->BackColor = oldColor; // перекрасить в родной цвет
				}
				else
				{
					this->BackColor = Color::Green; // иначе в зеленый
				}
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) { // закрытие формы
			 	System::Windows::Forms::DialogResult res;
				res=MessageBox::Show("Закрыть?", "Form Closing", MessageBoxButtons::YesNo,MessageBoxIcon::Question); // закрыть ли форму?

				if (res == System::Windows::Forms::DialogResult::No) // если нет
				{
					label1->Text = e->CloseReason.ToString(); // выводим  в лейбл причину незакрытия
					e->Cancel = true; // отменяем закрытие
					
				}
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) { // там где написано Exit?
			 this->Close(); // выход
		 }
	};
}

