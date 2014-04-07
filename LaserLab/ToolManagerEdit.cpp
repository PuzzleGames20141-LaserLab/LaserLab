#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <map>

#include "ToolManagerEdit.h"
//#include "GameScreen.h"

ToolManagerEdit::ToolManagerEdit()
{
	mouseBounds_.width = 1.f;
	mouseBounds_.height = 1.f;
	state = 0;
	state_right = 0;
	changeIdx = 0;
	// Load and put all equipment textures into vector
	sf::Texture mirrorDark;
	equipments_texture.push_back(mirrorDark);
	equipments_texture[0].loadFromFile("Equipments_Image/Mirror_Dark.png");
	sf::Texture mirrorLight;
	equipments_texture.push_back(mirrorLight);
	equipments_texture[1].loadFromFile("Equipments_Image/Mirror_Light.png");

	sf::Texture splitterDark;
	equipments_texture.push_back(splitterDark);
	equipments_texture[2].loadFromFile("Equipments_Image/Splitter_Dark.png");
	sf::Texture splitterLight;
	equipments_texture.push_back(splitterLight);
	equipments_texture[3].loadFromFile("Equipments_Image/Splitter_Light.png");

	sf::Texture filter_R_Dark;
	equipments_texture.push_back(filter_R_Dark);
	equipments_texture[4].loadFromFile("Equipments_Image/ColorChanger_red_Dark.png");
	sf::Texture filter_R_Light;
	equipments_texture.push_back(filter_R_Light);
	equipments_texture[5].loadFromFile("Equipments_Image/ColorChanger_red_Light.png");

	sf::Texture filter_B_Dark;
	equipments_texture.push_back(filter_B_Dark);
	equipments_texture[6].loadFromFile("Equipments_Image/ColorChanger_blue_Dark.png");
	sf::Texture filter_B_Light;
	equipments_texture.push_back(filter_B_Light);
	equipments_texture[7].loadFromFile("Equipments_Image/ColorChanger_blue_Light.png");

	// put all equipment into vector and map
	for(int i = 0; i != EQUIP_NUM; i++)
	{
		sf::Sprite equip_Button;
		equipments_use_.push_back(equip_Button);
		equipments_use_[i].setTexture(equipments_texture[2*i]);
		equipments_use_[i].setPosition((float)(MARGIN*(i+1)+BLOCK_SIZE*i), 530.0);
		equipAvalibility.insert(std::pair<int, int>(i,0));	
	}
	equipmentLabel.push_back('a');
	equipmentLabel.push_back('b');
	equipmentLabel.push_back('f');
	equipmentLabel.push_back('g');

}

void ToolManagerEdit::update(sf::RenderWindow& window)
{
	
	mouseBounds_.left = (float)sf::Mouse::getPosition(window).x;
	mouseBounds_.top = (float)sf::Mouse::getPosition(window).y;

	// Decide if drag from grid or toolbar
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(ToolManagerEdit::getState() == 0)
		{
			//check if the equipments on the toolbar is been selected
			std::map<std::string, std::shared_ptr<Equipment>>::iterator it = equipments_.begin();
			for(; it!= equipments_.end(); it++)
			{
				if((*it).second->getGlobalBounds().intersects(mouseBounds_))
				{
					std::shared_ptr<Equipment> new_equipment;
					((*it).second)->clone(new_equipment);
					ToolManagerEdit::setCopyEquipment(new_equipment);
					ToolManagerEdit::setState(1);
					break;
				}
			}

			//check if the equipment on the grid is selected
			std::map<int, std::shared_ptr<Equipment>>::iterator it_grid = equipments_on_grid_.begin();
			int flag_find = 0;
			for(; it_grid!= equipments_on_grid_.end(); it_grid++)
			{
				if(ToolManagerEdit::getState() == 1)
					break;

				if((*it_grid).second->getGlobalBounds().intersects(mouseBounds_))
				{
					ToolManagerEdit::setCopyEquipment((*it_grid).second);
					ToolManagerEdit::setState(2);
					flag_find = 1;
					break;
				}

			}
			if(flag_find == 1)
			{
				int key = (*it_grid).first;
//				currentScore += (*it_grid).second->cost;
				if((*it_grid).second->isLaserSource())
				{
					std::vector<LaserSource>::iterator it_Laser = my_lasers_.begin();
					for(;it_Laser!= my_lasers_.end(); it_Laser++)
					{
						if((*it_grid).second->getPosition() == (*it_Laser).getPosition())
						{
							my_lasers_.erase(it_Laser);
							break;
						}
					}
				}
				if((*it_grid).second->label == CAPACITOR_R)
				{
					std::vector<std::shared_ptr<Equipment>>::iterator it = my_capacitors_.begin();
					for(;it != my_capacitors_.end(); it++)
					{
						if((*it_grid).second->getPosition() == (*it)->getPosition())
						{
							my_capacitors_.erase(it);
							break;
						}
					}
				}
				equipments_on_grid_.erase(key);
				changeIdx  = key;
			}
		}

		if(ToolManagerEdit::getState() == 1 || ToolManagerEdit::getState() == 2)
		{
			ToolManagerEdit::getCopyEquipment()->setPosition((sf::Vector2f) sf::Mouse::getPosition(window) );
		}

	}

	// Decide if click on equipment availibility block
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(ToolManagerEdit::getState() == 0)
		{
			//check if the equipments on the availability is been selected
			for(int i = 0; i != equipments_use_.size(); i++)
			{
				if(equipments_use_[i].getGlobalBounds().intersects(mouseBounds_))
				{
					ToolManagerEdit::setState(3);
					break;
				}
			}
		}

	}


	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(ToolManagerEdit::state == 1 || ToolManagerEdit::state == 2)
		{
			unsigned int x = sf::Mouse::getPosition(window).x;
			unsigned int y = sf::Mouse::getPosition(window).y;
			if(x>20&&x<620&&y>20&&y<500)
			{

				int row = (y-MARGIN)/BLOCK_SIZE;
				int col = (x-MARGIN)/BLOCK_SIZE;
				std::shared_ptr<Equipment> new_equipment;
				(ToolManagerEdit::copy_equipment)->clone(new_equipment);
				ToolManagerEdit::equipments_on_grid_.insert(std::pair<int, std::shared_ptr<Equipment>>((row*GRID_WIDTH + col), new_equipment));
				if(ToolManagerEdit::copy_equipment->label == CAPACITOR_R)
				{
					my_capacitors_.push_back(equipments_on_grid_[row*GRID_WIDTH + col]);
					equipments_on_grid_[row*GRID_WIDTH + col]->setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
				}
				if(ToolManagerEdit::copy_equipment->isLaserSource())
				{
					LaserSource * newLaser = NULL;
					switch(ToolManagerEdit::copy_equipment->label)
					{
					case '1':
						{
							newLaser = new LaserSource('r');
							break;
						}
					case 'j':
						{
							newLaser = new LaserSource('b');
							break;
						}
					}
					newLaser->setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					newLaser->setRotation(ToolManagerEdit::copy_equipment->getRotation());
					my_lasers_.push_back(*newLaser);
				}
				/*
				if(ToolManagerEdit::copy_equipment->label == CAPACITOR_R  && ToolManagerEdit::state == 1)
				{
					my_capacitors_.push_back(equipments_on_grid_[row*GRID_WIDTH + col]);
				}
				*/
				changeIdx = row*GRID_WIDTH + col;
			}

		}
		if(ToolManagerEdit::state == 3)
		{
			for(int i = 0; i != equipments_use_.size(); i++)
			{
				if(equipments_use_[i].getGlobalBounds().intersects(mouseBounds_))
				{

					unsigned int x = sf::Mouse::getPosition(window).x;
					int idx = (x-1)/60;
					int prevState = equipAvalibility[idx];
					std::map<int, int>::iterator it = equipAvalibility.find(idx);
					if(it != equipAvalibility.end())
						it->second = 1 - prevState;
					equipments_use_[i].setTexture(equipments_texture[2*i+1-prevState]);	
					break;
				}
			}
	
		}
		ToolManagerEdit::setState(0);
					
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right) || ToolManagerEdit::getStateRight() == 1)
	{		
		ToolManagerEdit::setStateRight(1);
		if(!(sf::Mouse::isButtonPressed(sf::Mouse::Right)))
		{
			ToolManagerEdit::setStateRight(0);
		}
		
		if(ToolManagerEdit::getStateRight() == 0)
		{
			std::map<int, std::shared_ptr<Equipment>>::iterator it_on_grid = ToolManagerEdit::equipments_on_grid_.begin();
			for(; it_on_grid!=ToolManagerEdit::equipments_on_grid_.end(); it_on_grid ++)
			{
				if((*it_on_grid).second->getGlobalBounds().intersects(mouseBounds_))
				{	
					(*it_on_grid).second->myRotate_E();
					if((*it_on_grid).second->isLaserSource()) 
					{
						std::vector<LaserSource>::iterator it_Laser = my_lasers_.begin();
						for(;it_Laser!= my_lasers_.end(); it_Laser++)
						{
							if((*it_on_grid).second->getPosition() == (*it_Laser).getPosition())
							{
								(*it_Laser).myRotate_E();
								break;
							}
						}
					}
					changeIdx = (*it_on_grid).first;
				}
			}
		}
	}
}

// display the equipment, equipment itself can display
void ToolManagerEdit::render(sf::RenderWindow& window)
{

}

void ToolManagerEdit::addEquipment(const std::string& id, std::shared_ptr<Equipment>& equipment)
{
	equipments_[id] = equipment;
}

void ToolManagerEdit::removeEquipment(const std::string& id)
{
	equipments_.erase(id);
}

int ToolManagerEdit::getState()
{
	return ToolManagerEdit::state;
}

void ToolManagerEdit::setState(int val)
{
	ToolManagerEdit::state = val;
}

int ToolManagerEdit::getStateRight()
{
	return ToolManagerEdit::state_right;
}

void ToolManagerEdit::setStateRight(int val)
{
	ToolManagerEdit::state_right = val;
}

std::shared_ptr<Equipment> ToolManagerEdit::getCopyEquipment()
{
	return ToolManagerEdit::copy_equipment;
}

void ToolManagerEdit::setCopyEquipment(std::shared_ptr<Equipment>& new_copy)
{
	ToolManagerEdit::copy_equipment = new_copy;
}

