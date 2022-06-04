#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)

wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Minesweaper", wxPoint(30,30), wxSize(500, 500))
{
	buttons = new wxButton* [width * height];
	wxGridSizer* grid = new wxGridSizer(width, height, 0, 0);

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	field = new int[width + height];
	for (size_t x = 0; x < width; x++)
	{
		for (size_t y = 0; y < height; y++)
		{
			buttons[y * width + x] = new wxButton(this, 10000 + (y * width + x));
			buttons[y * width + x]->SetFont(font);
			grid->Add(buttons[y * width + x], 1, wxEXPAND | wxALL);

			buttons[y * width + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClicked, this);
			field[width * y + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}
Main::~Main()
{
	delete[] buttons;
}

void Main::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % width;
	int y = (evt.GetId() - 10000) / width;

	if (isFirstClick)
	{
		int mines = 30;
		while (mines)
		{
			int rx = rand() % width;
			int ry = rand() % height;

			if (field[ry * width * +rx] == 0 && rx != x && ry != y)
			{
				field[ry * width + rx] = -1;
				mines--;
			}
		}
		isFirstClick = false;
	}

	buttons[y * width + x]->Enable(false);

	if (field[y * width + x] == -1)
	{
		wxMessageBox("x_x");

		isFirstClick = true;
		for (size_t x = 0; x < width; x++)
		{
			for (size_t y = 0; y < height; y++)
			{
				field[y * width + x] = 0;
				buttons[y * width + x]->SetLabel("");
				buttons[y * width + x]->Enable(true);
			}
		}
	}
	else
	{
		int mineAmount = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height)
				{
					if (field[(y + j) * width + (x + i)] == -1)
						mineAmount++;
				}
			}
		}
		if (mineAmount > 0)
		{
			buttons[y * width + x]->SetLabel(std::to_string(mineAmount));
		}
	}

	evt.Skip();
}