package m9.d24.q2;

public class Q2 {

	public static void main(String[] args) {
		System.out.println(func());
	//	static int x = 10;
	}
	
	static int x = 5;
	
	static int func() {
		return Q2.x--;
	}
}
