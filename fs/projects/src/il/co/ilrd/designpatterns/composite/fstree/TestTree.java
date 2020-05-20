package il.co.ilrd.designpatterns.composite.fstree;

import java.io.FileNotFoundException;

public class TestTree {
	public static void main(String[] args) throws FileNotFoundException {
		FSTree tree = new FSTree("/home/student/git/c/ws8");
		tree.print();
	}
}
