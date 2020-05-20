package il.co.ilrd.vendingmachine;

public class Product {
	private String name;
	private int price;

	public Product(String name, int price) {
		this.name = name;
		this.price = price;
	}

	public int getPrice() {
		return price;
	}

	public String getName() {
		return name;
	}

	@Override
	public boolean equals(Object other) {
		if (!(other instanceof Product)) {
			return false;
		}

		return ((Product) other).getName().equals(name) 
				&& ((Product) other).getPrice() == price;
	}

	@Override
	public int hashCode() {
		return (name.hashCode() + ((Integer) price).hashCode()) / 2;
	}

	@Override
	public final void finalize() {
	}
}// class Product
