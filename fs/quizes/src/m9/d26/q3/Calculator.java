package m9.d26.q3;

import java.util.HashMap;

public class Calculator {
	private HashMap<String, Operator> mapOperator = new HashMap<>();

	public Calculator() {
		addOperator("*", new Multiplication());
		addOperator("+", (int a, int b) -> {// lambda expression
			return a + b;
		});
		addOperator("-", new Operator() {// anonymous class

			@Override
			public int operate(int a, int b) {
				return a - b;
			}
		});

		// Local class
		class Division implements Operator {

			@Override
			public int operate(int a, int b) {
				if (0 == b) {
					throw new ArithmeticException();
				}

				return a / b;
			}
		}// class Division

		addOperator("/", new Division());
	}

	public void addOperator(String key, Operator o) {
		mapOperator.put(key, o);

	}

	public int operate(String key, int a, int b) {
		return mapOperator.get(key).operate(a, b);
	}

	// Inner class
	private class Multiplication implements Operator {
		@Override
		public int operate(int a, int b) {
			return a * b;
		}
	}// class Multiplication

	private interface Operator {
		public int operate(int a, int b);
	}// interface Operator
}// class Calculator
