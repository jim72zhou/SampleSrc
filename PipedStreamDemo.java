package file;

import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

class Sender implements Runnable{
	private PipedOutputStream pos = null;
	public Sender(){
		this.pos = new PipedOutputStream();
	}
	
	public void run(){
		String str = "Piped Stream Demo!";
		try {
			this.pos.write(str.getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		try {
			this.pos.close();
		} catch (IOException e) {
			e.printStackTrace();
		}			
	}
	
	public PipedOutputStream getPos(){
		return pos;
	}
}

class Receiver implements Runnable{
	private PipedInputStream pis = null;
	public Receiver(){
		this.pis = new PipedInputStream();
	}
	
	public void run(){
		byte b[] = new byte[100];
		int len = 0;
		try {
			len = this.pis.read(b);
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			this.pis.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		System.out.println("Received content:" + new String(b, 0, len));
	}
	
	public PipedInputStream getPis(){
		return pis;
	}
}

public class PipedStreamDemo {
	
	public static void main(String[] args) {
			Sender sender = new Sender();
			Receiver receiver = new Receiver();
			
			try {
				sender.getPos().connect(receiver.getPis());
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			new Thread(sender).start();
			new Thread(receiver).start();		
	}
}
