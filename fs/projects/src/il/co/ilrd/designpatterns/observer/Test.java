package il.co.ilrd.designpatterns.observer;

public class Test {

	public static void main(String[] args) {
		Newspaper<Integer> haaretz= new Newspaper<>();
		Reader<Integer> yossi = new Reader<>();
		Reader<Integer> ami = new Reader<>();
		Reader<Integer> shmil = new Reader<>();
		
		yossi.subscribe(haaretz); 
		ami.subscribe(haaretz);
		shmil.subscribe(haaretz);

		haaretz.getDispatcher().notify(null);
		
//		haaretz.unsubscribe(yossi.getCallback());
		haaretz.closeNewspaper();

	}

}
