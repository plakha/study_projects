package il.co.ilrd.designpatterns.factory;

import java.io.FileNotFoundException;

public class TestTree {
	public static void main(String[] args) throws FileNotFoundException {
		FSTree tree = new FSTree("/home/student/git/c");
		tree.print();
	}
}
