#ifndef SHOP_HPP
#define SHOP_HPP

// Forward declaration
class Player;

#include "inventory.hpp"
#include "building.hpp"
#include <iostream>

class Shop: public Building {
	private:
		Inventory shopInventory;
	public:
		Shop();
		virtual ~Shop();

		Inventory& getInventory();
		void buy(Player& player);
		void sell(Player& player);
};

#endif // SHOP_HPP
