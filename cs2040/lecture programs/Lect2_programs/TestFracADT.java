
public class TestFracADT {
	public static void main(String[] args) {
		FracADT frac1 = new Fraction(1,2);
		FracADT frac2 = new FractionArr(8,12);

		FracADT frac3 = frac1.add(frac2);

		System.out.println(frac3);
	}
}
