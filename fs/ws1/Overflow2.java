class Overflow2 {

	static void overflow(int n) {
		System.out.println(n);
		overflow(++n);
	}

	public static void main (String[] args) {
		Overflow2.overflow(1);
	}
}