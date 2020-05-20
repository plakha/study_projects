package ws4.ex;

public enum EWeekDay {
	SUNDAY(1), 
	MONDAY(2), 
	TUESDAY(3), 
	WEDNESDAY(4), 
	THURSDAY(5), 
	FRIDAY(6), 
	SATURDAY(7);
	
	private final int nthDay;
	
	private static final EWeekDay[] EWeekDayArr = EWeekDay.values();//why Enum<EWeekDay> also works?
	private EWeekDay(int nthDay) {
		this.nthDay = nthDay;
	}
	
	public int getNthDay() {return nthDay;}
	
	public static EWeekDay fromValue(int nthDay) {		
		return EWeekDayArr[nthDay - 1];
	}
	
	public static void printAllValues() {
		for (EWeekDay day: EWeekDayArr) {
			System.out.println(day);
		}
	}
	
	@Override
	public String toString() {
		return super.toString() + getNthDay();
	}
	
	public static void main(String[] args) {
		//System.out.println(fromValue(1));
		
		printAllValues();
	}

}
