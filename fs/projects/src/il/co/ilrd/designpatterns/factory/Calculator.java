package il.co.ilrd.designpatterns.factory;

import java.util.function.Function;

public class Calculator {
	private Factory<String, Args, Integer> calcFactory = new Factory<>();
	private Factory<String, Calculator, Calculator> voidCalcFac = new Factory<>();

	static private Function<Args, ? extends Integer> addition = new Function<Calculator.Args, Integer>() {
		@Override
		public Integer apply(Args operands) {
			checkOperands(operands);
			return Integer.valueOf(operands.operand1() + operands.operand2());
		}
	};
	// private Function<Args, ? extends Integer> power = Calculator::power;

	private Calculator() {
		calcFactory.add("addition", addition);
		calcFactory.add("subtraction", (Args operands) -> operands.operand1() - operands.operand2);
		calcFactory.add("division", Calculator::division);
		calcFactory.add("multiplication", this::multiplication);
		voidCalcFac.add("nothing", Calculator::Zero);

	}

	public Calculator Zero() {
		Calculator myCalc = new Calculator();

		myCalc.calcFactory.add("nothing", (Args arg) -> (arg.operand1()));
		System.out.println(calcFactory.create("nothing", new Args(1,2)));
		System.out.println("Created Zero method;");

		return myCalc;
	}

	public int operate(String key, int operand1, int operand2) {
		return calcFactory.create(key, new Args(operand1, operand2));
	}

	private static void checkOperands(Args operands) {
		if (null == operands) {
			throw new IllegalArgumentException("Please pass operands!");
		}
	}

	private static Integer division(Args operands) {
		checkOperands(operands);
		if (0 == operands.operand2) {
			throw new ArithmeticException("Mustn't divide by Zero!");
		}

		return operands.operand1() / operands.operand2();
	}

	private Integer multiplication(Args operands) {
		checkOperands(operands);

		return operands.operand1() * operands.operand2();
	}

	public Integer power(Args operands) {
		checkOperands(operands);
		if (operands.operand1() == 0 && operands.operand2() <= 0) {
			throw new ArithmeticException("Non-positive power of Zero - illegal division by Zero!");
		}

		return (int) Math.pow(operands.operand1(), operands.operand2());
	}

	private class Args {
		private int operand1;
		private int operand2;

		public Args(int operand1, int operand2) {
			this.operand1 = operand1;
			this.operand2 = operand2;
		}

		public int operand1() {
			return operand1;
		}

		public int operand2() {
			return operand2;
		}
	}// class Args

	public static void main(String[] args) {
		Calculator myCalc = new Calculator();

		Calculator zeroCalc =  myCalc.Zero();
		System.out.println(zeroCalc.operate("nothing", 1, 2));
		System.out.println(myCalc.operate("multiplication", 3, 2));
		System.out.println(myCalc.operate("subtraction", 3, 2));

		System.out.println(myCalc.operate("division", 3, 2));

		System.out.println(myCalc.operate("addition", 3, 2));

	}
}
