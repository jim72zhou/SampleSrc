package designpattern;

/**
 * Represents the product created by the builder.
 */
class Car {
    private int wheels;
    private String color;

    public Car() {
    }

    @Override
    public String toString() {
        return "Car [wheels = " + wheels + ", color = " + color + "]";
    }

    public int getWheels() {
        return wheels;
    }

    public void setWheels(final int wheels) {
        this.wheels = wheels;
    }

    public String getColor() {
        return color;
    }

    public void setColor(final String color) {
        this.color = color;
    }
}

/**
 * The builder abstraction.
 */
interface CarBuilder {
    CarBuilder setWheels(final int wheels);

    CarBuilder setColor(final String color);

    Car getResult();
}

class CarBuilderImpl implements CarBuilder {
    private Car car;

    public CarBuilderImpl() {
        car = new Car();
    }

    @Override
    public CarBuilder setWheels(final int wheels) {
        car.setWheels(wheels);
        return this;
    }

    @Override
    public CarBuilder setColor(final String color) {
        car.setColor(color);
        return this;
    }

    @Override
    public Car getResult() {
        return car;
    }
}

public class BuilderDemo {
    private CarBuilder builder;

    public BuilderDemo(final CarBuilder builder) {
        this.builder = builder;
    }

    public Car construct() {
        return builder.setWheels(4).setColor("Red").getResult();
    }

    public static void main(final String[] arguments) {
        CarBuilder builder = new CarBuilderImpl();
        BuilderDemo carBuildDirector = new BuilderDemo(builder);
        System.out.println(carBuildDirector.construct());
    }
}
