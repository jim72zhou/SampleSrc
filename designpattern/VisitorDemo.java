package designpattern;

interface CarElementVisitor {
    void visit(Wheel wheel);
    void visit(Engine engine);
    void visit(Body body);
    void visit(Truck truck);
}

interface CarElement {
    void accept(CarElementVisitor visitor);
}

class Wheel implements CarElement {
    private String name;

    public Wheel(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void accept(CarElementVisitor visitor) {
        /*
         * accept(CarElementVisitor) in Wheel implements
         * accept(CarElementVisitor) in CarElement, so the call
         * to accept is bound at run time. This can be considered
         * the first dispatch. However, the decision to call
         * visit(Wheel) (as opposed to visit(Engine) etc.) can be
         * made during compile time since 'this' is known at compile
         * time to be a Wheel. Moreover, each implementation of
         * CarElementVisitor implements the visit(Wheel), which is
         * another decision that is made at run time. This can be
         * considered the second dispatch.
         */
        visitor.visit(this);
    }
}

class Engine implements CarElement {
    public void accept(CarElementVisitor visitor) {
        visitor.visit(this);
    }
}

class Body implements CarElement {
    public void accept(CarElementVisitor visitor) {
        visitor.visit(this);
    }
}

class Truck implements CarElement {
    CarElement[] elements;

    public Truck() {
        this.elements = new CarElement[] { 
        	new Wheel("front left"),
            new Wheel("front right"), 
            new Wheel("back left"),
            new Wheel("back right"), 
            new Body(), 
            new Engine() 
         };
    }

    public void accept(CarElementVisitor visitor) {    
        for(CarElement elem : elements) {
            elem.accept(visitor);
        }
        visitor.visit(this);    
    }
}

class CarElementPrintVisitor implements CarElementVisitor {
    public void visit(Wheel wheel) {      
        System.out.println("Visiting " + wheel.getName() + " wheel");
    }

    public void visit(Engine engine) {
        System.out.println("Visiting engine");
    }

    public void visit(Body body) {
        System.out.println("Visiting body");
    }
 
    public void visit(Truck truck) {      
        System.out.println("Visiting truck");
    }
}

class CarElementDoVisitor implements CarElementVisitor {
    public void visit(Wheel wheel) {
        System.out.println("Kicking my " + wheel.getName() + " wheel");
    }

    public void visit(Engine engine) {
        System.out.println("Starting my engine");
    }

    public void visit(Body body) {
        System.out.println("Moving my body");
    }

    public void visit(Truck truck) {
        System.out.println("Starting my truck");
    }
}

public class VisitorDemo {
    public static void main(String[] args) {
        CarElement truck = new Truck();
        truck.accept(new CarElementPrintVisitor());
        truck.accept(new CarElementDoVisitor());
    }
}
