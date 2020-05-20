class Overflow {
	private int x = 0;
	private final int MAX = 60;
	
	void overflow() {
		
		if (this.MAX <= this.x)
			return ;

		System.out.println(this.x);
		++this.x;

		overflow();

		//System.out.println(this.x);
	}

	public static void main(String[] args) {
		Overflow overflow = new Overflow();
		
		overflow.overflow();
	}
}