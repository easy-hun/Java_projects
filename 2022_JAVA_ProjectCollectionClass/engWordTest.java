// *** engWordTest.java ***
package task3;

import java.util.*;
import java.util.Map.Entry;
import java.io.*;

public class engWordTest {

	// # 사용자명, 파일명
	String userName, fileName;
	
	// # count 변수들...
	final int SIZE_OF_WORDS = 59;
	final int SIZE_OF_QUIZES = 10;
	int number = 0;
	int collected = 0;
		
	// # 단어장 hashmap , 오답노트 배열
	HashMap<Integer, Word> wordMap = new HashMap<>();
	wrongNote[] noteMap = new wrongNote[SIZE_OF_WORDS];
	
	static Scanner scan = new Scanner(System.in);
	
	
	// @ 생성자 : user의 이름 받아 초기화
	public engWordTest(String userName) {
		super();
		this.userName = userName;
	}

	// @ addWord 함수
	void addWord(Word word) {
		if(number < SIZE_OF_WORDS) {
			wordMap.put(number, new Word(word.eng, word.kor));
			noteMap[number] = new wrongNote();
			number++;
		}
		else
			System.out.println("단어장에 더 이상의 단어를 등록할 수 없습니다.");
	}
	
	// @ 단어장 만들기
	void makeVoc(String filename) {
		
		try(Scanner scan = new Scanner(new File(filename));){
			while(scan.hasNextLine()) {
				String str = scan.nextLine();
				String[] temp = str.split("\t");
				this.addWord(new Word(temp[0].trim(), temp[1].trim()));
			}
			System.out.println(userName+"의 단어장이 생성되었습니다.");
			this.menu();
		}
		catch(FileNotFoundException e) {
			System.out.println(userName +"의 단어장이 생성되지 않았습니다. 파일명을 확인하세요.");
		}
	}
	
	// @ 메뉴 출력 및 함수 별 실행
	void menu() {
		int sel = 0;
		boolean i = true;
		
		while(sel != 5) {
			i = true;
			try {
				System.out.println("\n============  " + userName + "의 단어장  ============");
				System.out.println("1) 주관식 퀴즈  2) 객관식 퀴즈  3) 오답노트  4) 단어 검색  5) 종료");
				System.out.print("메뉴를 선택하세요 : ");
				sel = scan.nextInt();
				
				// Out of range 값 들어올 시 throw함
				if(!(sel>0 && sel<6))
					throw new InputMismatchException();
			}
			// menu 선택 시 그릇된 값을 입력하면 예외 발생
			catch(InputMismatchException e) {
				System.out.println("숫자 1~5 사이의 값을 다시 입력해주세요.");
				i = false;
			}
			catch(Exception e) {
				System.out.println("잘못된 입력입니다. 다시 입력해주세요.");
				i = false;
			}
			finally {
				scan.nextLine();
			}
			
			if(i) {
				switch (sel) {
				case 1:	// => 주관식 단어 Quiz
					quiz1();
					break;
				case 2: // => 객관식 단어 Quiz
					quiz2();
					break;
				case 3:	// => 오답노트
					showWrongnote();
					break;
				case 4:	// => 단어검색
					searchWord();
					break;
				case 5:	// => 종료
					System.out.println(userName + "의 단어장 프로그램을 종료합니다.");
					break;
				}
			}
		}
	}

	// @ 1) 주관식 퀴즈 CODE
	private void quiz1() {
		// TODO Auto-generated method stub
		System.out.println();
		Random r = new Random();
		int count = 0, num = 0, isRight = 0;
		boolean isOK = true;
		int[] isUsed = new int[SIZE_OF_QUIZES];
		long start, end;
		
		start= System.nanoTime();	// 시작 시각 check
		
		while(count<SIZE_OF_QUIZES) {
			// 랜덤 번호 생성, 중복 x
			isOK = true;
			num = r.nextInt(59);
			if (count > 0) {
				for (int a : isUsed) {
					if (a == num)
						isOK = false;
				}
			}
			if (isOK)
				isUsed[count] = num;
			else
				continue;

			// 주관식 퀴즈 UI 및 정답 판별
			System.out.println("------ 주관식 퀴즈 " + (count+1) +"번 ------");
			System.out.println("\"" + this.wordMap.get(num).kor + "\"의 뜻을 가진 영어 단어는 무엇일까요?");
			//System.out.println("정답 Index : " + (num+1));
			System.out.print("답을 입력하세요 : ");
			String str = scan.nextLine();
			str = str.trim();	// 앞뒤 공백은 정답 인정
			if(isRightAnswer(this.wordMap.get(num).kor, str, num))
				isRight++;
			count++;
		}
		
		end = System.nanoTime();	// 끝난 시각 check
		
		System.out.println("\n" + this.userName + "님 10문제 중 " + isRight 
				+ "개 맞추셨고, 총 " + (end-start)/1000000000 + "초 소요되었습니다.");
	}

	// @ 2) 객관식 퀴즈 CODE
	private void quiz2() {
		// TODO Auto-generated method stub
		System.out.println();
		Random r = new Random();
		final int NUM_OF_QUIZ = 4;
		int count = 0, ans = 0, isRight = 0;
		boolean isOK = true;
		int[] isUsed = new int[SIZE_OF_QUIZES];
		
		// 4지선다에 들어갈 Words' Index 저장 배열
		Integer[] quiz = new Integer[NUM_OF_QUIZ];
		long start, end;
		
		start = System.nanoTime();	// 시작 시각 check
		
		// 문제 및 정답 만들기
		while(count<SIZE_OF_QUIZES) {
			isOK = true;
			
			// 정답 Index 만들기, 중복 제외
			ans = r.nextInt(59);
			if (count > 0) {
				for (int a : isUsed) {
					if (a == ans)
						isOK = false;
				}
			}
			if (isOK)
				isUsed[count] = ans;
			else
				continue;
			
			// 4지선다 만들기, 중복 제거
			quiz[0] = ans;
			for(int i=1;i<NUM_OF_QUIZ;i++) {
				quiz[i] = r.nextInt(59);
				for(int j=0;j<i;j++) {
					// Index of Word가 같은 경우 중복 제거
					if(quiz[i] == quiz[j]) {
						i--;
						break;
					}
					// Kor 뜻 of Word가 같은 경우 중복 제거
					else if(this.wordMap.get(quiz[i]).kor.equals(this.wordMap.get(quiz[j]).kor)) {
						i--;
						break;
					}
				}
			}
			
			// 4지선다 Shuffle For 정답 위치 무작위화
			Collections.shuffle(Arrays.asList(quiz));
			
			// Shuffle된 배열에서 정답 Index 찾아 ANS에 저장
			int ANS = 0;
			for(int i=0;i<NUM_OF_QUIZ;i++) {
				if(this.wordMap.get(ans).eng.equals(this.wordMap.get(quiz[i]).eng))
					ANS = i;
			}
			
			// 객관식 퀴즈 UI 및 정답 판별 구현하기
			try {
				System.out.println("------ 객관식 퀴즈 " + (count + 1) + "번 ------");
				System.out.println("\"" + this.wordMap.get(ans).eng + "\"의 뜻은 무엇일까요?");
				for (int i = 0; i < NUM_OF_QUIZ; i++) {
					System.out.println((i + 1) + ") " + this.wordMap.get(quiz[i]).kor);
				}
				System.out.print("답을 입력하세요 : ");
				int sel = scan.nextInt();
				
				// Out of range 값 입력 시 예외 throw
				if(!(sel>0 && sel<5))
					throw new InputMismatchException();
				
				// Index를 이용해 정답 판별
				if(quiz[sel-1] == ans) {
					System.out.println("정답입니다.");
					isRight++;
				}
				else {
					System.out.println("틀렸습니다. 정답은 " + (ANS+1) + "번 입니다.");
					this.noteMap[ans].addFailed();
				}
			}
			// 잘못된 값 입력 시 예외처리
			catch(InputMismatchException e) {
				System.out.println("잘못된 입력입니다. 정답은 " + (ANS+1) +"번 입니다.");
				this.noteMap[ans].addFailed();
			}
			catch(Exception e) {
				System.out.println("잘못된 입력입니다. 정답은 " + (ANS+1) +"번 입니다.");
				this.noteMap[ans].addFailed();
			}
			finally {
				scan.nextLine();
				this.noteMap[ans].addCount();
				count++;
			}
		}

		end = System.nanoTime();	// 종료 시각 check
		
		System.out.println("\n" + this.userName + "님 10문제 중 " + isRight 
				+ "개 맞추셨고, 총 " + (end-start)/1000000000 + "초 소요되었습니다.");
	}

	// @ 3) 오답노트 CODE
	private void showWrongnote() {
		// TODO Auto-generated method stub
		
		System.out.println("\n--------- 오답 노트 ---------");
		
		// 원본 Data인 noteMap을 변경하지 않고 얕은 복사하여 정렬 후 출력하기 위한 Data들
		wrongNote[] note = new wrongNote[SIZE_OF_WORDS]; 
		ArrayList<wrongNote> arr = new ArrayList<>();
		
		int index = 0;
		
		// noteMap에서 틀린 문제만 note에 순차적으로 저장
		for(int i=0;i<SIZE_OF_WORDS;i++) {
			if(noteMap[i].getFailed() > 0) {
				note[index] = new wrongNote();
				note[index++] = noteMap[i];
			}
		}
		
		// 틀린 문제가 없을 시 Return
		if(index==0) {
			System.out.println("틀린 문제가 없습니다.");
			return;
		}
		
		// Collections.sort() 함수 쓰기 위한 list에 note값 대입
		for(int i=0;i<index;i++) {
			arr.add(note[i]);
		}
		
		// Failed 기준 내림차순 정렬
		if(note!=null) {
			Collections.sort(arr, new Comparator<wrongNote>() {
				@Override
				public int compare(wrongNote o1, wrongNote o2) {
					return (-1) * (o1.failed - o2.failed);
				}
			});
		}
		
		// 출력코드 편리성을 위해 다시 wrongNote[] 타입으로 변환
		int k = 0;
		Iterator<wrongNote> it = arr.iterator();
		while(it.hasNext()) {
			note[k++] = it.next();
		}
		
		for(int i=0;i<k;i++) {
			if(note[i]!=null) {
				System.out.println(this.wordMap.get(note[i].myIndex).eng 
						+ " 뜻 : " + this.wordMap.get(note[i].myIndex).kor
						+ "\n출제회수 : " + note[i].counted 
						+ "     오답회수 : " + note[i].failed
						+ "\n--------------------------");
			}
		}
	}
	
	// @ 4) 단어검색 CODE
	private void searchWord() {
		// TODO Auto-generated method stub
		String sWord;
		boolean find = false;
		
		System.out.println("\n------- 단어 검색 -------");
		System.out.print("검색할 단어를 입력하세요 : ");
		
		sWord = scan.nextLine();
		sWord = sWord.trim();	// 앞뒤 공백 제거 후 단어 검색
		
		for(int i=0;i<SIZE_OF_WORDS;i++) {
			if(this.wordMap.get(i).eng.equals(sWord)) {
				find = true;
				System.out.println(sWord + " 뜻 : " + this.wordMap.get(i).kor);
				System.out.println("출제회수 : " + noteMap[i].counted 
						+ "     오답회수 : " + noteMap[i].failed);
			}
		}
		
		if(!find)
			System.out.println("단어장에 등록된 단어가 아닙니다.");
		
		System.out.println("----------------------");
	}
	
	// +) 정답 판별 메소드
	private boolean isRightAnswer(String sKor, String sEng, int num) {
		// 한글의 영단어 입력, 한글 같고 영어 달라도 정답처리
		// sKor : 단어장에서 나온 한국어 뜻
		// sEng : 사용자가 입력한 영어 String
		boolean isRight = false;
		Set<Entry<Integer, Word>> eset = wordMap.entrySet();
		Iterator<Entry<Integer, Word>> eit = eset.iterator();
		
		// User가 입력한 Eng가 wordMap의 Kor와 같으면 wordMap.Eng가 달라도 정답처리 (Index 순차 탐색)
		while(eit.hasNext()) {
			Entry<Integer, Word> entry = eit.next();
			Word value = entry.getValue();
			if(value.kor.equals(sKor) && value.eng.equals(sEng))
				isRight = true;
		}
		
		// 틀린 경우, 오답노트에 출제회수 및 오답회수 추가
		if(!isRight) {
			System.out.println("틀렸습니다. 정답은 " + this.wordMap.get(num).eng + "입니다.");
			this.noteMap[num].addCount();
			this.noteMap[num].addFailed();
		}
		// 맞은 경우, 오답노트에 출제회수 추가
		else {
			System.out.println("정답입니다.");
			this.noteMap[num].addCount();
		}
		return isRight;
	}
	
}
