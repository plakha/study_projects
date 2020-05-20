package m9.d26.q3;

public class CalculatorTest {
    public static void main(String[] args) {
	Calculator calc = new Calculator();

	System.out.println(calc.operate("+", 1, 2));
	System.out.println(calc.operate("-", 1, 2));
	System.out.println(calc.operate("/", 1, 0));
	System.out.println(calc.operate("*", 1, 2));

    }

}
