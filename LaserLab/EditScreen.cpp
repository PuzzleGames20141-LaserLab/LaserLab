#include <SFML\Graphics.hpp>

#include <memory>
#include<fstream>
#include<iostream>
#include <algorithm> 

#include "EditScreen.h"
#include "Game.h"
#include "Grid.h"
#include "Macro.h"
#include "Mirror.h"
#include "Equipment.h"
#include "Target.h"
#include "LevelSelectScreen.h"
#include "MenuScreen.h"
#include "Splitter.h"
#include "Wall.h"
#include "Bomb.h"
#include "Filter_Red.h"
#include "Filter_Blue.h"
#include "Capacitor.h"
#include "LaserSource.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <shobjidl.h> 
#include <cmath>

HINSTANCE hInstance;
HANDLE save_button;
HWND file_name;
HWND initial_score;
HWND two_star;
HWND three_star;

char buffer1[20];
char buffer2[20];
char buffer3[20];
char buffer4[20];


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

	case WM_CREATE:
		file_name = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,WS_CHILD | WS_VISIBLE, 110, 20, 140,20, hwnd, NULL, NULL, NULL);
	
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Static"), TEXT("File Name"),WS_CHILD | WS_VISIBLE, 10, 20, 100,20, hwnd, NULL, NULL, NULL);

		initial_score = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE, 110, 70, 140,20, hwnd, NULL, NULL, NULL);

		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Static"), TEXT("Initial Money"), WS_CHILD | WS_VISIBLE, 10, 70, 100,20, hwnd, NULL, NULL, NULL);

		two_star = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,WS_CHILD | WS_VISIBLE, 110, 120, 140,20, hwnd, NULL, NULL, NULL);

		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Static"), TEXT("Two Stars Scores"),WS_CHILD | WS_VISIBLE, 10, 120, 100,20, hwnd, NULL, NULL, NULL);

		three_star = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,WS_CHILD | WS_VISIBLE, 110, 170, 140,20, hwnd, NULL, NULL, NULL);

		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Static"), TEXT("Three Stars Scores"),WS_CHILD | WS_VISIBLE, 10, 170, 100,20, hwnd, NULL, NULL, NULL);

		save_button = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Button"), TEXT("OK"),WS_CHILD | WS_VISIBLE, 100, 220, 50,20, hwnd, NULL, NULL, NULL);
		
		break;
	


	case WM_COMMAND:
		switch(wParam)
		{
		case BN_CLICKED:
			if(save_button = (HWND)lParam)
			{
				SendMessage(file_name, WM_GETTEXT, 20, reinterpret_cast<LPARAM>(buffer1));
				SendMessage(initial_score, WM_GETTEXT, 20, reinterpret_cast<LPARAM>(buffer2));
				SendMessage(two_star, WM_GETTEXT, 20, reinterpret_cast<LPARAM>(buffer3));
				SendMessage(three_star, WM_GETTEXT, 20, reinterpret_cast<LPARAM>(buffer4));
				DestroyWindow(hwnd);
				break;
			}
		}
		break;


    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void my_callBack_clear_edit()
{
	Game::Screen = std::make_shared<EditScreen>();
}

void my_callBack_save()
{
	
}

void my_callBack_goBack_edit()
{
	Game::Screen = std::make_shared<MenuScreen>();
}

EditScreen::EditScreen()
	:clearButton_edit("Images/clear_button.png"), saveButton_edit("Images/save_button.png"),goBackButton_edit("Images/go_back.png")
{
	clearButton_edit.callBack = &my_callBack_clear_edit;
	saveButton_edit.callBack = &my_callBack_save;
	goBackButton_edit.callBack = &my_callBack_goBack_edit;

	saveButton_edit.setPosition(400, 520);
	clearButton_edit.setPosition(500,520);
	goBackButton_edit.setPosition(600,520);

	buttonManager_edit.addButton("clear", std::make_shared<UserButton>(clearButton_edit));
	buttonManager_edit.addButton("save", std::make_shared<UserButton>(saveButton_edit));
	buttonManager_edit.addButton("edit", std::make_shared<UserButton>(goBackButton_edit));

	Capacitor::loadTexture();
	Pit::loadTexture();
	Wall::loadTexture();
	Mirror::loadTexture();
	Splitter::loadTexture();
	LaserSource::loadTexture();
	Target::loadTexture();
	Photon::loadTexture();
	Bomb::loadTexture();
	Filter_Blue::loadTexture();
	Filter_Red::loadTexture();

	loadGridEdit_();
	loadEquipmentEdit();
	if(!background.loadFromFile("Background/GameScreen.jpg"))
	{
		std::cout<< "load game screen background fail!"	<<std::endl;
	}
	backgroundSp.setTexture(background);
}

void EditScreen::handleInput(sf::RenderWindow& window)
{
	EditScreen::tool_manager_edit.update(window);
	EditScreen::handleLaserEdit();
	buttonManager_edit.update(window);


}

void EditScreen::render(sf::RenderWindow& window)
{
	window.draw(backgroundSp);
	buttonManager_edit.render(window);
	drawGridEdit(window);
	drawEquitmentEdit(window);
	if(EditScreen::tool_manager_edit.getState() == 1 || EditScreen::tool_manager_edit.getState() == 2)
	{
		window.draw(*(EditScreen::tool_manager_edit.getCopyEquipment()));
	}
	//std::cout<<"laser num "<<tool_manager_edit.my_lasers_.size()<<std::endl;
	drawLaserEdit(window);
	if(buttonManager_edit.isSaveButton == 1)
	{
	    save(window);
	}
}

void EditScreen::update(sf::Time delta)
{

}

void EditScreen::handleLaserEdit()
{
	/*
	if(tool_manager_edit.changeIdx >= 0)
	{
		//lightPaths_edit
		for(int i=0; i!=lightPaths_edit.size(); i++)
		{
			std::vector<Photon>::iterator lightPaths_it = lightPaths_edit[i].begin();
			for(; lightPaths_it != lightPaths_edit[i].end(); lightPaths_it++)
			{
				if((*lightPaths_it).getIndex() == tool_manager_edit.changeIdx)
				{
					lightPaths_edit[i].erase(lightPaths_it, lightPaths_edit[i].end());
					break;
				}
			}
		
		}
		calculatePathEdit();
		tool_manager_edit.changeIdx = -1;

	}
	*/
	calculatePathEdit();
}

void EditScreen::loadGridEdit_()
{
	EditScreen::myGrid_edit.loadGridEdit();
}

void EditScreen::drawGridEdit(sf::RenderWindow& window)
{
	std::vector<std::vector<sf::Sprite>> gridImage = myGrid_edit.getSprites();
	
	for (int i = 0; i < GRID_HEIGHT; i++) 
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			window.draw(gridImage[i][j]);
		}
	}
}


void EditScreen::loadEquipmentEdit()
{

	std::string* text_equipment;
	text_equipment = loadEquipmentTXT_edit("LevelEdit/level_equipment_all.txt");
	int i=0;
	while(!text_equipment[i].empty())
	{
		switch(text_equipment[i][0])
		{
		case LASER_SOURCE_U_RED:
			{
				if(tool_manager_edit.equipments_.count("laser_source_u_red")==0)
				{
					LaserSource lasersource('r');
					lasersource.setPosition(650,100);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("laser_source_u_red", std::make_shared<LaserSource>(lasersource)));
					tool_manager_edit.equipments_.at("laser_source_u_red")->setTexture(LaserSource::redTexture);
					i++;
				}
				break;
			}
		case DOOR_U_RED:
			{
				if(tool_manager_edit.equipments_.count("target_u_red")==0)
				{
					Target target(sf::Color::Red);
					target.setPosition(650,150);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("target_u_red", std::make_shared<Target>(target)));
					tool_manager_edit.equipments_.at("target_u_red")->setTexture(Target::redTexture);
					i++;
				}
				break;
			}
		case LASER_SOURCE_U_BLUE:
			{
				if(tool_manager_edit.equipments_.count("laser_source_u_blue")==0)
				{
					LaserSource lasersource('b');
					lasersource.setPosition(650,200);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("laser_source_u_blue", std::make_shared<LaserSource>(lasersource)));
					tool_manager_edit.equipments_.at("laser_source_u_blue")->setTexture(LaserSource::blueTexture);
					i++;
				}
				break;
			}
		case DOOR_U_BLUE:
			{
				if(tool_manager_edit.equipments_.count("target_u_blue")==0)
				{
					Target target(sf::Color::Blue);
					target.setPosition(650,250);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("target_u_blue", std::make_shared<Target>(target)));
					tool_manager_edit.equipments_.at("target_u_blue")->setTexture(Target::blueTexture);
					i++;
				}
				break;
			}
		case MIRROR:
			{
				if(tool_manager_edit.equipments_.count("mirror")==0)
				{
					Mirror mirror;
					mirror.setPosition(650,300);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("mirror", std::make_shared<Mirror>(mirror)));
					tool_manager_edit.equipments_.at("mirror")->setTexture(Mirror::mTexture);
					i++;
				}
				break;
			}
		case SPLITTER :
			{

				if(tool_manager_edit.equipments_.count("splitter")==0)
				{
					Splitter splitter;
					splitter.setPosition(650,350);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("splitter", std::make_shared<Splitter>(splitter)));
					tool_manager_edit.equipments_.at("splitter")->setTexture(Splitter::sTexture);
					i++;
				}
				break;
			}
		case WALL:
			{
				if(tool_manager_edit.equipments_.count("wall")==0)
				{
					Wall wall;
					wall.setPosition(650,400);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("wall", std::make_shared<Wall>(wall)));
					tool_manager_edit.equipments_.at("wall")->setTexture(Wall::wTexture);
					i++;
				}
				break;
			}
		case PIT:
			{
				if(tool_manager_edit.equipments_.count("pit")==0)
				{
					Pit pit;
					pit.setPosition(720,100);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("pit", std::make_shared<Pit>(pit)));
					tool_manager_edit.equipments_.at("pit")->setTexture(Pit::pTexture);
					i++;
				}
				break;
			}
		case BOMB:
			{
				if(tool_manager_edit.equipments_.count("bomb")==0)
				{
					Bomb bomb;
					bomb.setPosition(720,150);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("bomb", std::make_shared<Bomb>(bomb)));
					tool_manager_edit.equipments_.at("bomb")->setTexture(Bomb::bTexture);
					i++;
				}
				break;
			}
		case FILTER_R:
			{
				if(tool_manager_edit.equipments_.count("filter_red")==0)
				{
					Filter_Red filter_red;
					filter_red.setPosition(720,200);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("filter_red", std::make_shared<Filter_Red>(filter_red)));
					tool_manager_edit.equipments_.at("filter_red")->setTexture(Filter_Red::fTexture);
					i++;
				}
				break;
			}
		case FILTER_B:
			{
				if(tool_manager_edit.equipments_.count("filter_blue")==0)
				{
					Filter_Blue filter_blue;
					filter_blue.setPosition(720,250);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("filter_blue", std::make_shared<Filter_Blue>(filter_blue)));
					tool_manager_edit.equipments_.at("filter_blue")->setTexture(Filter_Blue::fTexture);
					i++;
				}
				break;
			}
		case CAPACITOR_R:
			{
				if(tool_manager_edit.equipments_.count("capacitor")==0)
				{
					Capacitor capacitor;
					capacitor.setPosition(720,300);
					tool_manager_edit.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("capacitor", std::make_shared<Capacitor>(capacitor)));
					tool_manager_edit.equipments_.at("capacitor")->setTexture(Capacitor::idle_Texture);
					i++;
				}
				break;
			}
		case SWITCH:
			{
				break;
			}
		case GATE:
			{
				break;
			}
		case POWERED:
			{
				break;
			}
		default:
			break;

		}
	
	}
		
}


void EditScreen::drawEquitmentEdit(sf::RenderWindow& window)
{
	std::map<std::string, std::shared_ptr<Equipment>>::iterator it = tool_manager_edit.equipments_.begin();
	for(; it!= tool_manager_edit.equipments_.end(); it++)
	{
		window.draw(*((*it).second));
	}

	std::map<int, std::shared_ptr<Equipment>>::iterator it_on_grid = tool_manager_edit.equipments_on_grid_.begin();
	for(; it_on_grid!=tool_manager_edit.equipments_on_grid_.end(); it_on_grid ++)
	{
		int x = (*it_on_grid).first/GRID_WIDTH;
		int y = (*it_on_grid).first - GRID_WIDTH*x;
		((*it_on_grid).second)->setPosition((float)(2*MARGIN+y*(BLOCK_SIZE)), (float)(2*MARGIN+x*(BLOCK_SIZE)));
		window.draw(*((*it_on_grid).second));
	}

	for(int i=0; i<tool_manager_edit.equipments_use_.size(); i++)
	{
		window.draw(tool_manager_edit.equipments_use_[i]);
	}

}

std::string* loadEquipmentTXT_edit(const char* fileName)
{
	std::string* text;
	text = new std::string[100];
	std::ifstream myfile(fileName);
	int lineNum = 0;
	while(std::getline(myfile, text[lineNum]))
	{
		lineNum++;
	}
	return text;
}

void EditScreen::calculatePathEdit()
{
	//std::cout<<"laser dir: "<<tool_manager_edit.my_lasers_[0].<<
	sf::FloatRect windowRect(MARGIN, MARGIN, GRID_WIDTH*(BLOCK_SIZE), GRID_HEIGHT*(BLOCK_SIZE));
	lightPaths_edit.clear();
	for(int i = 0; i != EditScreen::tool_manager_edit.my_capacitors_.size(); i++)
	{
		EditScreen::tool_manager_edit.my_capacitors_[i]->lightOff();
	}
	if(lightPaths_edit.size() == 0)
	{
		for(int i = 0; i != tool_manager_edit.my_lasers_.size(); i++)
		{
			std::vector<Photon> lightPath;
			lightPath.push_back(tool_manager_edit.my_lasers_[i].getPhoton());
			lightPaths_edit.push_back(lightPath);
		}
		for(int i = 0; i != capLightPaths.size(); i++)
		{
			lightPaths_edit.push_back(capLightPaths[i]);
		}
	}

	for(int i = 0; i != lightPaths_edit.size(); i++)
	{
		Photon current = lightPaths_edit[i].back();
		while(current.getVelocity() != 0.0 && windowRect.contains(current.getPosition()))
		{
			Photon nextPhoton = current;
			int idx = nextPhoton.getIndex();
			if(tool_manager_edit.equipments_on_grid_.count(idx) > 0)
			{
				if(tool_manager_edit.equipments_on_grid_[idx]->label == BOMB)
				{
					int row = idx/GRID_WIDTH;
					int col = idx%GRID_WIDTH;
					if(row > 0)
					{
						if(tool_manager_edit.equipments_on_grid_.count(idx-GRID_WIDTH) > 0)
						{
							char lab = tool_manager_edit.equipments_on_grid_[idx-GRID_WIDTH]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager_edit.equipments_on_grid_.erase(idx-GRID_WIDTH);
						}
					}
					if(row < GRID_HEIGHT-1)
					{
						if(tool_manager_edit.equipments_on_grid_.count(idx+GRID_WIDTH) > 0)
						{
							char lab = tool_manager_edit.equipments_on_grid_[idx+GRID_WIDTH]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager_edit.equipments_on_grid_.erase(idx+GRID_WIDTH);
						}
					}
					if(col > 0)
					{
						if(tool_manager_edit.equipments_on_grid_.count(idx-1) > 0)
						{
							char lab = tool_manager_edit.equipments_on_grid_[idx-1]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager_edit.equipments_on_grid_.erase(idx-1);
						}
					}
					if(col < GRID_WIDTH-1)
					{
						if(tool_manager_edit.equipments_on_grid_.count(idx+1) > 0)
						{
							char lab = tool_manager_edit.equipments_on_grid_[idx+1]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager_edit.equipments_on_grid_.erase(idx+1);
						}
					}
					tool_manager_edit.equipments_on_grid_.erase(idx);
					nextPhoton.myMove();
				}
				else
				{
					tool_manager_edit.equipments_on_grid_[idx]->reaction(nextPhoton, lightPaths_edit);
				}
				lightPaths_edit[i].push_back(nextPhoton);
			}
			else
			{
				nextPhoton.myMove();
				lightPaths_edit[i].push_back(nextPhoton);
			}
			current = nextPhoton;
		}
	}
	
	for(int i = 0; i != lightPaths_edit.size(); i++)
	{
		Photon tail = lightPaths_edit[i].back();
		int tailIdx = tail.getIndex();
		if(tool_manager_edit.equipments_on_grid_.count(tailIdx) > 0)
		{
			tool_manager_edit.equipments_on_grid_[tailIdx]->reaction(tail, lightPaths_edit);
		}
	}
	for(int i = 0; i != EditScreen::tool_manager_edit.my_capacitors_.size(); i++)
	{
		if(!EditScreen::tool_manager_edit.my_capacitors_[i]->isHit() && (EditScreen::tool_manager_edit.my_capacitors_[i]->curState())/10 == 2)
		{
			int colorNum = (EditScreen::tool_manager_edit.my_capacitors_[i]->curState())%10;
			sf::Color color;
			if(colorNum == 1)
			{
				color =  sf::Color::Red;
			}
			else
			{
				color = sf::Color::Blue;
			}
			float angle = tool_manager_edit.my_capacitors_[i]->getRotation();
			/*
			if(angle > 0)
			{
				angle = 360 - angle;
			}
			*/
			int direction = (int)(angle/45)+1;
			float x = EditScreen::tool_manager_edit.my_capacitors_[i]->getPosition().x;
			float y = EditScreen::tool_manager_edit.my_capacitors_[i]->getPosition().y;
			int row = (y-MARGIN)/BLOCK_SIZE;
			int col = (x-MARGIN)/BLOCK_SIZE;
			tool_manager_edit.equipments_on_grid_.erase(row*GRID_WIDTH + col);
			LaserSource laser(color == sf::Color::Red ? 'r' : 'b');
			laser.setRotation(angle);
			laser.setTexture(Capacitor::charged_Texture);
			laser.setPosition(x,y);
			tool_manager_edit.equipments_on_grid_.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(laser)));
			tool_manager_edit.my_lasers_.push_back(laser);
			/*
			Photon newPhoton(direction, color);
			float deltaX = 0;
			float deltaY = 0;
			if(direction == 1 || direction == 5)
			{
				deltaX = (float)(BLOCK_SIZE*(3-direction)/4);
			}
			else if(direction == 3 || direction == 7)
			{
				deltaY = (float)(BLOCK_SIZE*(direction-5)/4);
			}
			sf::Vector2f delta(deltaX, deltaY);
			newPhoton.setPosition(EditScreen::tool_manager_edit.my_capacitors_[i]->getPosition() + delta);
			std::vector<Photon> lightPath;
			lightPath.push_back(newPhoton);
			capLightPaths.push_back(lightPath);
			//GameScreen::tool_manager.my_capacitors_[i]->curState();
			*/
		}
	}
	
}


void EditScreen::drawLaserEdit(sf::RenderWindow& window)
{
	for(int i = 0; i != lightPaths_edit.size(); i++)
	{
		for(int j = 0; j != lightPaths_edit[i].size(); j++)
		{
			window.draw(lightPaths_edit[i][j]);
		}
	}
}




void EditScreen::save(sf::RenderWindow& window)
{
	
	hInstance = NULL;

	 const wchar_t CLASS_NAME[]  = L"save information";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

	

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                    // Optional window styles.
        CLASS_NAME,                         // Window class
        L"Learn to Program for Windows",    // Window text
        WS_OVERLAPPEDWINDOW,                // Window style

        // Size and position
        (int)100, (int)200, (int)300, (int)400,

		NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );
	
    if(hwnd == NULL)
    {
        return;
    }


	EnableWindow(window.getSystemHandle(),false);
	SetActiveWindow(hwnd);

    ShowWindow(hwnd, 1);

	
    // Run the message loop.a3e

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	SetActiveWindow(window.getSystemHandle());
	EnableWindow(window.getSystemHandle(),true);
	buttonManager_edit.isSaveButton = 0;
	//std::cout<<buffer1[1]<<std::endl;
	//std::cout<<buffer1[2]<<std::endl;
	//std::cout<<buffer1[3]<<std::endl;
	saveToFile(buffer1, buffer2, buffer3, buffer4);

}

void EditScreen::saveToFile(char * levelName_arr, char * initMoney_arr, char * twoStarScore_arr, char * threeStarScore_arr)
{
	// create filename for the user designed level
	std::string levelName(levelName_arr, 20);
	std::string initMoney(initMoney_arr, 20);
	std::string twoStarScore(twoStarScore_arr, 20);
	std::string threeStarScore(threeStarScore_arr, 20);
	levelName.erase(std::remove(levelName.begin(), levelName.end(), (char)0), levelName.end());
	initMoney.erase(std::remove(initMoney.begin(), initMoney.end(), (char)0), initMoney.end());
	twoStarScore.erase(std::remove(twoStarScore.begin(), twoStarScore.end(), (char)0), twoStarScore.end());
	threeStarScore.erase(std::remove(threeStarScore.begin(), threeStarScore.end(), (char)0), threeStarScore.end());

	std::string path = "UserLevel/";
	std::string layout = path + levelName + ".txt";
	std::string info = path + levelName + "_info.txt";
	std::string equip = path + levelName + "_equipment.txt";

	const char * layoutFileName = layout.c_str();
	const char * infoFileName = info.c_str();
	const char * equipFileName = equip.c_str();

	// save layout into txt
	std::ofstream layoutFile;
	layoutFile.open(layoutFileName);
	for(int i = 0; i != 12; i++)
	{
		for(int j = 0; j != 15; j++)
		{
			int idx = i*GRID_WIDTH+j;
			char sign = '0';
			if(tool_manager_edit.equipments_on_grid_.count(idx) > 0)
			{
				if(tool_manager_edit.equipments_on_grid_[idx]->label != MIRROR &&
					tool_manager_edit.equipments_on_grid_[idx]->label != SPLITTER &&
					tool_manager_edit.equipments_on_grid_[idx]->label != FILTER_R &&
					tool_manager_edit.equipments_on_grid_[idx]->label != FILTER_B)
				{
					switch(tool_manager_edit.equipments_on_grid_[idx]->label)
					{
					case LASER_SOURCE_U_RED:
						{
							int angle = (int)(tool_manager_edit.equipments_on_grid_[idx]->getRotation());
							if(angle > 180)
							{
								angle = angle - 360;
							}
							sign = (char)((int)'0' + (angle/90 + 2));
							break;
						}
					case DOOR_U_RED:
						{
							int angle = (int)(tool_manager_edit.equipments_on_grid_[idx]->getRotation());
							if(angle == 0)
							{
								angle = 360;
							}
							sign = (char)((int)'0' + (angle/90 + 4));
							break;
						}
					case LASER_SOURCE_U_BLUE:
						{
							int angle = (int)(tool_manager_edit.equipments_on_grid_[idx]->getRotation());
							if(angle > 180)
							{
								angle = angle - 360;
							}
							sign = (char)((int)'i' + (angle/90 + 2));
							break;
						}
					case DOOR_U_BLUE:
						{
							int angle = (int)(tool_manager_edit.equipments_on_grid_[idx]->getRotation());
							if(angle == 0)
							{
								angle = 360;
							}
							sign = (char)((int)'i' + (angle/90 + 4));
							break;
						}
					case WALL:
						{
							sign = WALL;
							break;
						}
					case PIT:
						{
							sign = PIT;
							break;
						}
					case BOMB:
						{
							sign = BOMB;
							break;
						}
					case CAPACITOR_R:
						{
							int angle = (int)(tool_manager_edit.equipments_on_grid_[idx]->getRotation());
							if(angle == 270)
							{
								angle = -90;
							}
							sign = (char)((int)'s' + (angle/90 + 1));
							break;
						}
					default :
						{
							break;
						}
					}
				}
			}
			layoutFile << sign;
			if(j != 14)
			{
				layoutFile << ',';
			}
		}
		if(i != 11)
		{
			layoutFile << '\n';
		}
	}
	layoutFile.close();
	// save level_info into txt
	std::ofstream infoFile;
	infoFile.open(infoFileName);
	infoFile << 0 << "\n"; // dummy level label
	infoFile << 0 << "\n"; // dummy islock info
	infoFile << 0 << "\n"; // initial best score;
	infoFile << twoStarScore << "\n"; // 2 stars threshold
	infoFile << threeStarScore << "\n"; // 3 stars threshold
	infoFile << initMoney; // initial money
	infoFile.close();
	
	// save level available equipments into txt
	std::ofstream equipFile;
	equipFile.open(equipFileName);
	std::map<int, int>::iterator equipIt = tool_manager_edit.equipAvalibility.begin();
	for(; equipIt != tool_manager_edit.equipAvalibility.end(); equipIt++)
	{
		if(equipIt->second == 1)
		{
			equipFile << tool_manager_edit.equipmentLabel[equipIt->first] << "\n";
		}
	}
	equipFile.close();
	
	std::ofstream level_name;
	level_name.open("UserLevel/level_names.txt", std::ios::app);
	level_name << levelName << std::endl;
	level_name.close();
}