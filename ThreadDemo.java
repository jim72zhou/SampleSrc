package demo;

class Info{
	private String name = "Jim";
	private String title = "Manager";
	
	private boolean canSet = true;
	
	public String getName(){
		return name;
	}
	
	public void setName(String name){
		this.name = name;
	}
	
	public String getTitle(){
		return title;
	}
	
	public void setTitle(String title){
		this.title = title;
	}
	
	public synchronized void set(String name, String title){
		if(!canSet){
			try{
				super.wait();
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
		}
		
		this.setName(name);
		this.setTitle(title);
		
		try{
			Thread.sleep(100);
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
		canSet = false;
		super.notify();
	}
	
	public synchronized void get(){
		if(canSet){
			try{
				super.wait();
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
		}

		try{
			Thread.sleep(100);
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
				
		System.out.println(this.getName() + " --> " + this.getTitle());
		canSet = true;
		super.notify();
	}
}

class Producer implements Runnable{
	private Info info = null;
	private static boolean flag = false;
	
	public Producer(Info info){
		this.info = info;
	}
	
	public void run(){		
		for(int i = 0; i < 10; i++){
			if(flag){
				this.info.set("Jim", "Manager");
				flag = false;
			}
			else{
				this.info.set("Winnie", "CEO");
				flag = true;
			}
		}
	}	
}

class Consumer implements Runnable{
	private Info info = null;
	
	public Consumer(Info info){
		this.info = info;
	}
	
	public void run(){
		boolean flag = false;
		
		for(int i = 0; i < 10; i++){
			try{
				Thread.sleep(90);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
			
			this.info.get();
		}
	}	
}

public class ThreadDemo {	
	public static void main(String[] args){
		Info info = new Info();
		
		Producer producer = new Producer(info);
		Consumer consumer = new Consumer(info);
		
		Thread t1 = new Thread(producer);
		Thread t2 = new Thread(consumer);
			
		t1.start();
		t2.start();
	}
}
