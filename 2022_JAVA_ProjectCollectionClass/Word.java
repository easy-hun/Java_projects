// *** Word.java ***
package task3;

public class Word {
	String eng;
	String kor;
	
	public Word(String eng, String kor) {
		super();
		this.eng = eng;
		this.kor = kor;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		Word tmp = (Word)obj;
		boolean result = this.eng.equals(tmp.eng)
				&& this.kor.equals(tmp.kor);
		return result;
	}

	@Override
	public int hashCode() {
		// TODO Auto-generated method stub
		return this.eng.hashCode() + this.kor.hashCode();
	}

	@Override
	public String toString() {
		// TODO Auto-generated method stub		
		return eng+" : "+kor;
	}
	
}
