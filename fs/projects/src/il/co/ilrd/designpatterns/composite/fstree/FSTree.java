package il.co.ilrd.designpatterns.composite.fstree;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * 
 * @author Andrei
 * @version 18/9/2019
 * 
 *          Class holds and can print info about the Files and Directories. The
 *          design implements GoF Composite design pattern
 *
 */
public class FSTree {
	private Node fileTree;

	private interface Node {
		public void print();
	}

	public FSTree(String path) {
		fileTree = new Branch(path, 0);
	}

	public void print() {
		fileTree.print();
	}

	private class Branch implements Node {
		private List<Node> fileTree = new ArrayList<Node>();
		private File root;
		private int indent;

		public Branch(String path, int indent) {
			root = new File(path);
			this.indent = indent;

			File[] listFiles = root.listFiles();

			for (File file : listFiles) {
				if (file.isFile()) {
					fileTree.add(new Leaf(file.getPath(), indent + 1));
				} else if (file.isDirectory()) {
					fileTree.add(new Branch(file.getPath(), indent + 1));
				}
			}
		}

		@Override
		public void print() {
			for (int i = 0; i < indent; ++i) {
				System.out.print(" ");
			}

			System.out.println(root.getName());

			for (Node node : fileTree) {
				node.print();
			}
		}
	}// class Branch

	private class Leaf implements Node {
		private File node;
		private int indent;

		public Leaf(String path, int indent) {
			node = new File(path);
			this.indent = indent;
		}

		@Override
		public void print() {
			for (int i = 0; i < indent; ++i) {
				System.out.print(" ");
			}

			System.out.println("|--" + node.getName());
		}
	}// class Leaf

}// class Tree