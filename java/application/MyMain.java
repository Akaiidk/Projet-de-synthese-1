package application;

public class MyMain {

	public static void main(String[] args) {
		new Intersections().runAllPairs("../data/input", "../data/output");
	}

	static {
		System.loadLibrary("intersections");
	}
}