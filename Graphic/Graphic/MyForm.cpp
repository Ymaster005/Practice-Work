#include "MyForm.h"
#include "math.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Graphic::MyForm form;
	Application::Run(% form);
}

//код який виконується при натисканні на кнопку "побудувати індивідуальний варіант"
System::Void Graphic::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (graph1show == false) {
		if (textBox_a->Text == "" || textBox_b->Text == "" || textBox_h->Text == "") {
			MessageBox::Show("Введіть усі параметри побудови!", "Увага!");
		}
		else {
			a = Convert::ToDouble(textBox_a->Text);
			b = Convert::ToDouble(textBox_b->Text);
			h = Convert::ToDouble(textBox_h->Text);
			x = a;

			this->chart->Series[0]->Points->Clear();
			while (x <= b) {
				if (x > -5 && x <= -2) {
					y = x - 2;
				}
				else if (x > 1 && x < 7) {
					y = (sqrt(pow(cos(x / 8), 3)) + cbrt(pow(exp(1), 2.3 * x) + pow(exp(1), -2.3 * x))) * (4 / fabs(x + (7.0 / 9.0)));
				}
				else {
					y = 1.0 / pow(x, 4);
					if (x == 0) {
						y = 1;
					}
				}
				this->chart->Series[0]->Points->AddXY(x, y);
				x = round((x + h) * 100) / 100;
			}
			graph1show = true;
		}
		}

	return System::Void();
}

//код який виконується при натисканні на кнопку "відкрити файл"
System::Void Graphic::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Stream^ myStream;
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = "c:\\";
	openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{

		if ((myStream = openFileDialog1->OpenFile()) != nullptr)
		{
			std::string filepath = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);
			std::string s;

			std::ifstream fin;
			fin.open(filepath);
			if (graph2show == false) {
				this->chart->Series[1]->Points->Clear();

				for (int i = 0; i < 200; i++) {
					getline(fin, s);
					x = atof(s.c_str());
					getline(fin, s);
					y = atof(s.c_str());
					this->chart->Series[1]->Points->AddXY(x, y);
				}
				graph2show = true;
			}
			else {
				this->chart->Series[2]->Points->Clear();

				for (int i = 0; i < 200; i++) {
					getline(fin, s);
					x = atof(s.c_str());
					getline(fin, s);
					y = atof(s.c_str());
					this->chart->Series[2]->Points->AddXY(x, y);
				}
				graph3show = true;
			}
			
			myStream->Close();
		}
	}	
	return System::Void();
}

//код який виконується при натисканні на кнопку "видалити графік"
System::Void Graphic::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (graph3show == true) {
		this->chart->Series[2]->Points->Clear();
		graph3show = false;
	}
	else if (graph2show == true) {
		this->chart->Series[1]->Points->Clear();
		graph2show = false;
	}
	else if (graph1show == true) {
		this->chart->Series[0]->Points->Clear();
		graph1show = false;
	}
	return System::Void();
}
