
class Q23 {
	public static void main(String[] args) {
		short s1 = 3;
		short s2 = 1;
		

		/* s1, s2 are implicitly casted to int to make calculations */
		short s3 = (short)(s1 & s2);/* with no explicit conversion, won't compile */
	}
}