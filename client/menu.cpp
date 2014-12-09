#include "menu.h"

using namespace std;

int Menu::selectMenuVoice()
{
	int choice = -1;

	cout<<"Choice: ";
	cin>>choice;

	return choice;
}


void Menu::menuChoice()
{
	int choice = -1;
	bool menu_is_on = true;
	
	while (menu_is_on)
	{
		cout<<"Select:\n";
		cout<<"1 - Insert and Send data to server\n";
		cout<<"2 - Query all tables into DB\n";
		cout<<"3 - Exit Tool\n";
		choice = selectMenuVoice();
		if (choice>3 || choice<1)
		{
			cerr<<"ERROR Wrong menu choice. Please Select again.\n";
			choice = selectMenuVoice();
		}
		if (choice==3) menu_is_on = false;
	}
}

