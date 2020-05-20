package ws4.q4;

import static java.lang.System.out;

enum Superhero {
	BATMAN (1) {
		@Override
		public void superpower() {
			out.println("RICH!");
		}
		
	}, 
	SUPERMAN (2) {
		@Override
		public void superpower() {
			out.println("IMMORTAL! AIRBOURNE!");
		}		
	}, 
	CATWOMAN (1) {
		@Override
		public void superpower() {
			out.println("SCRATCH!");
		}		
	};

	private int numOfSuperpowers;

	Superhero(int numOfSuperpowers) {
		this.numOfSuperpowers = numOfSuperpowers;
	}
	
	public int getNumOfSuperpowers() {return numOfSuperpowers;}
	
	public void setNumOfSuperpowers(int numOfSuperpowers) {
		this.numOfSuperpowers = numOfSuperpowers;
	}
	abstract public void superpower();
}
