package designpattern;

import java.util.Observable;
import java.util.Observer;

class Car extends Observable{
	private int model;
	public Car(int model){
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
		return "Car's model is: MODEL-" + this.model;
	}	
}

class CarFan implements Observer{
	private String name;
	public CarFan(String name){
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
		Car car = new Car(1);
		CarFan fan1 = new CarFan("Jim");
		CarFan fan2 = new CarFan("Tom");
		CarFan fan3 = new CarFan("Jobs");
		CarFan fan4 = new CarFan("Winnie");

		car.addObserver(fan1);
		car.addObserver(fan2);
		car.addObserver(fan3);
		car.addObserver(fan4);
		
		System.out.println(car);
		
		car.setModel(2);
		
		System.out.println(car);
		
	}
}
