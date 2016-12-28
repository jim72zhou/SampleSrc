package designpattern;

import java.util.Observable;
import java.util.Observer;

class Bike extends Observable{
	private int model;
	public Bike(int model){
		this.model = model;
	}
	public int getModel() {
		return model;
	}
	public void setModel(int model) {
		super.setChanged();
		super.notifyObservers(model);
		this.model = model;
	}
	@Override
	public String toString(){
		return "Bike's model is: MODEL-" + this.model;
	}	
}

class BikeFan implements Observer{
	private String name;
	public BikeFan(String name){
		this.name = name;
	}
	public void update(Observable obj, Object arg){
		if(arg instanceof Integer){
			System.out.print(this.name + " knows the model was changed to: MODEL-");
			System.out.println(((Integer) arg).intValue());
		}
	}
}

public class ObserverDemo {
	public static void main(String[] args) {
		Bike Bike = new Bike(1);
		BikeFan fan1 = new BikeFan("Jim");
		BikeFan fan2 = new BikeFan("Tom");
		BikeFan fan3 = new BikeFan("Jobs");
		BikeFan fan4 = new BikeFan("Winnie");

		Bike.addObserver(fan1);
		Bike.addObserver(fan2);
		Bike.addObserver(fan3);
		Bike.addObserver(fan4);
		
		System.out.println(Bike);
		
		Bike.setModel(2);
		
		System.out.println(Bike);
		
	}
}
