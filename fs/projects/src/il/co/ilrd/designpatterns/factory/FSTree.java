package il.co.ilrd.designpatterns.factory;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Map;
import java.util.TreeMap;

import il.co.ilrd.designpatterns.factory.Factory;

/**
 * Reimplementation of File System Tree to use Factory design Pattern. It is
 * both Composie and Factory.
 * 
 * @author Andrei
 * @version 6/10/2019
 * 
 *          design implements GoF Composite design pattern
 *          &
 *          GoF Factory Design Pattern
 *
 */
public class FSTree {
	private Node fileTree;

	public FSTree(String path) throws FileNotFoundException {
		File file = new File(path);
		if (null == file.listFiles()) {
			throw new FileNotFoundException("Bad directory path");
		}
		fileTree = NodeFactory.manufacture(file);
	}

	public void print() {
		fileTree.print(0);
	}

	private static abstract class Node {
		private File root;

		abstract public void print(int indentation);

		protected File getRoot() {
			return root;
		}

		protected void setRoot(File root) {
			this.root = root;
		}
	}// abstract class Node

	private static class Branch extends Node {
		private Map<String, Node> fileTree = new TreeMap<>();

		public Branch(File path) {
			setRoot(path);

			for (File file : getRoot().listFiles()) {
				fileTree.put(file.getName(), NodeFactory.manufacture(file));
			}
		}

		@Override
		public void print(int indentation) {
			for (int i = 0; i < indentation; ++i) {
				System.out.print(" ");
			}

			System.out.println(getRoot().getName());

			for (Node node : fileTree.values()) {
				node.print(indentation + 1);
			}
		}
	}// class Branch

	private static class Leaf extends Node {
		public Leaf(File path) {
			setRoot(path);
		}

		@Override
		public void print(int indentation) {
			for (int i = 0; i < indentation; ++i) {
				System.out.print(" ");
			}

			System.out.println("|--" + getRoot().getName());
		}
	}// class Leaf

	private enum FileType {
		FILE, DIRECTORY;
	}// enum FileType

	private static class NodeFactory {
		private static Factory<FileType, File, Node> nodeFactory = new Factory<>();

		static {
			nodeFactory.add(FileType.FILE, Leaf::new);
			nodeFactory.add(FileType.DIRECTORY, Branch::new);
		}

		public static Node manufacture(File path) {
			return nodeFactory.create(FSTree.getFileType(path), path);
		}
	}// class NodeFactory

	private static FileType getFileType(File file) {
		if (file.isFile()) {
			return FileType.FILE;
		} else if (file.isDirectory()) {
			return FileType.DIRECTORY;
		}

		throw new IllegalArgumentException("The file argument is nor File nor Directory");
	}
}// class Tree