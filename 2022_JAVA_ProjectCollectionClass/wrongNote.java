// *** wrongNote.java ***
package task3;

public class wrongNote {

	static int index = 0;
	
	// # 각 문제 별 출제 횟수 및 오답 횟수
	int counted = 0;
	int failed = 0;
	
	int myIndex;
	
	public wrongNote() {
		this.counted = 0;
		this.failed = 0;
		this.myIndex = index++;
	}

	void addCount() {
		this.counted++;
	}
	
	void addFailed() {
		this.failed++;
	}

	public int getCounted() {
		return counted;
	}

	public int getFailed() {
		return failed;
	}

}
