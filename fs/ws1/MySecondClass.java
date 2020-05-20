class MySecondClass {
	/* A static method doesn't interact with instance variables.
	No need to instantiate an object */
	static void foo1()
	{
		System.out.println("This is static method foo1()");
	}

	/* To use this method, there's a need to intantiate an object */
	void foo2()
	{
		System.out.println("This is method foo2");
	}
}