package designpattern;

import java.util.List;
import java.util.Map;
import java.util.Vector;
import java.util.concurrent.ConcurrentHashMap;

// Instances of CoffeeFlavour will be the Flyweights
class CoffeeFlavour {
	private final String name;

	CoffeeFlavour(final String newFlavor) {
		this.name = newFlavor;
	}

	@Override
	public String toString() {
		return name;
	}
}

// Menu acts as a factory and cache for CoffeeFlavour flyweight objects
class Menu {
	private Map<String, CoffeeFlavour> flavours = new ConcurrentHashMap<String, CoffeeFlavour>();

	CoffeeFlavour lookup(final String flavorName) {
		if (!flavours.containsKey(flavorName))
			flavours.put(flavorName, new CoffeeFlavour(flavorName));
		return flavours.get(flavorName);
	}

	int totalCoffeeFlavoursMade() {
		return flavours.size();
	}
}

// Order is the context of the CoffeeFlavour flyweight.
class Order {
	private final int tableNumber;
	private final CoffeeFlavour flavour;

	Order(final int tableNumber, final CoffeeFlavour flavor) {
		this.tableNumber = tableNumber;
		this.flavour = flavor;
	}

	void serve() {
		System.out.println("Serving " + flavour + " to table " + tableNumber);
	}
}

public class FlyweightDemo {
	private final List<Order> orders = new Vector<Order>();
	private final Menu menu = new Menu();

	void takeOrder(final String flavourName, final int table) {
		CoffeeFlavour flavour = menu.lookup(flavourName);
		Order order = new Order(table, flavour);
		orders.add(order);
	}

	void service() {
		for (Order order : orders)
			order.serve();
	}

	String report() {
		return "\ntotal CoffeeFlavour objects made: " + menu.totalCoffeeFlavoursMade();
	}

	public static void main(final String[] args) {
		FlyweightDemo shop = new FlyweightDemo();

		shop.takeOrder("Cappuccino", 2);
		shop.takeOrder("Frappe", 1);
		shop.takeOrder("Espresso", 1);
		shop.takeOrder("Frappe", 897);
		shop.takeOrder("Cappuccino", 97);
		shop.takeOrder("Frappe", 3);
		shop.takeOrder("Espresso", 3);
		shop.takeOrder("Cappuccino", 3);
		shop.takeOrder("Espresso", 96);
		shop.takeOrder("Frappe", 552);
		shop.takeOrder("Cappuccino", 121);
		shop.takeOrder("Espresso", 121);

		shop.service();
		System.out.println(shop.report());
	}
}
