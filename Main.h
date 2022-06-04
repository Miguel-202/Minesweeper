#pragma once
#include "wx/wx.h"

class Main : public wxFrame
{
public:
	Main();
	~Main();

public:
	int width = 10;
	int height = 10;
	wxButton **buttons;
	int* field = nullptr;
	bool isFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

