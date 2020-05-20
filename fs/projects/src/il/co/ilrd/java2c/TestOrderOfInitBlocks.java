package il.co.ilrd.java2c;

class Super {
	static int superint;
	{
		System.out.println("Super instance block");
	}
	static {
		System.out.println("Super static block");
	}

	Super() {
		System.out.println("Super ctor");
	}
}

class Sub extends Super {
	static {
		System.out.println("Sub static block");
	}
	{
		System.out.println("Sub instance block");
	}
	Sub() {
		// super();
		System.out.println("Sub ctor");
	}
}

class SubSub extends Sub{
	static {
		System.out.println("SubSub static block");
	}
	
	SubSub() {
		System.out.println("SubSub ctor");
	}
	{
		System.out.println("SubSub instance block");
	}
}

public class TestOrderOfInitBlocks {
	public static void main(String[] args) {
		new SubSub();
	}
}