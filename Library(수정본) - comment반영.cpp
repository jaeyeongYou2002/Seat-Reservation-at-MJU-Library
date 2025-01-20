/*	
	프로그램 : 명지대학교 도서관 회원가입, 자리예약,취소,조회하기 시스템 
	작성자 : 유재영 24 - 05 - 01
	
	 04-30 수정 내용 
	 RoomInfo 클래스추가 - 148행 
	 숫자대신 상수사용 - #define 사용 
	 회원가입시 재귀함수가 아닌 while문 돌리기 - 86행의 join메소드 
	 사용자의 편의를 위해 좌석에 저장되는 배열의 인덱스 값 수정 - 170행	
	 
	 05-20 수정 내용 
	 roomInfo class name변수 추가, 복사 생성자 추가 - 38행
	 동적 할당 메모리 해제를 위한 소멸자 추가, 복사 생성자 연습용 class추가 -  411행
	 
	 static 변수 count 추가 , static 함수 getCount 추가 - 340행
	 static 함수를 이용하여 현재까지 인원수 조회하기 메뉴, 기능 추가 - 377행 
	 
	 
	 
	 --------14주차 과제 수정 내용--------- 
	 06- 04 수정 내용
	 355행 - group reserve class 추가
	 알고리즘 빈틈 - main_id를 +1하면서 저장하게 될경우 main_id뒤에 id가 이미 있으면 결함이 발생한다.
	 대안 -> userdata를 개인, 단체를 따로 만들어 저장한다. 
	 
	  
*/
#include<iostream>
#include<string.h>
#define NUM_OF_ROW 10
#define NUM_OF_COLUMN 10
#define MAX_USER 3 * NUM_OF_ROW * NUM_OF_COLUMN

using namespace std;

class RoomInfo //RoomInfo클래스 추가 
{
	int roomNumber; // 방번호 
	int roomRow;	// 좌석의 행 
	int roomColumn;	 //좌석의 열 
	char* name; //복사생성자 연습을 위한 char* 변수 추가 
	
	public:
	RoomInfo(){}
	RoomInfo(int n):roomNumber(n){}
	RoomInfo(int n,int r,int c, char* na):roomNumber(n),roomRow(r),roomColumn(c)
	{
		name = new char[50];
		strcpy(this->name,na);
	}
	
	RoomInfo(RoomInfo& rhs) // 복사 생성자 추가 
	{
		this->roomNumber = 	rhs.roomNumber;
		this->roomRow = rhs.roomRow;
		this->roomColumn = rhs.roomColumn;
		
		
		this->name = new char[50]; // 깊은 복사 
		strcpy(this->name,rhs.name);  

		cout << "복사 생성자가 생성되었습니다." << endl;	
	} 
	
	~RoomInfo() // 메모리 해제 
	{
		delete [] name;
	}
	
	void setroomNumber(int n) {roomNumber = n;}
	void setroomRow(int r){roomRow = r;}	
	void setroomColumn(int c){roomColumn = c;}	
	void setName(char* na)
	{
		 this->name = new char[50];
		strcpy(this->name,na);
	}	
	int getroomNuber(){return roomNumber;}
	int getroomRow(){return roomRow;}
	int getroomColumn(){return roomColumn;}
	char* getName(){return this -> name;}
	void show()
	{
		 
		cout << "이름 : " << name << endl;
		cout << "방 번호 : " << roomNumber << endl;
		cout << "좌석 : ("<< roomRow << "," << roomColumn << ")" <<  endl;
	}
};
	
	
class UserData
{		
	int id;
	RoomInfo roomData;
	
	public:
		UserData(){}
		UserData(int i,int num, int row,int column) {setdata(i,0,0,0,NULL);}
		void setdata(int id,int roomNumber,int row, int column, char* name)
		{
			this->id = id;
			
			roomData.setroomNumber(roomNumber);
			roomData.setroomRow(row);
			roomData.setroomColumn(column);
			roomData.setName(name);
		}
		int get_id(){return id;}
		RoomInfo& getroomInfo(){return roomData;}
		
		void set_id(int i){id = i;}
		void show()
		{
			cout << "id : " << id << endl;
			cout << "방 번호 : " << roomData.getroomNuber() << endl;
			cout << "좌석 : ("<< roomData.getroomRow() << "," << roomData.getroomColumn() << ")" <<  endl;
		}
		
};


class Library{
	
	protected:
	UserData* user = new UserData[MAX_USER]; //최대 600명의 데이터 저장 가능 
	char studyGarden[NUM_OF_ROW][NUM_OF_COLUMN]; //파생클래스인 groupreserve와 같이 사용해야하므로 static선언 
	char noteBookZoon[NUM_OF_ROW][NUM_OF_COLUMN];
	char cafeZoon[NUM_OF_ROW][NUM_OF_COLUMN];
	
	public:
		static int count;
		Library()
		{
			count = 0;
			for(int i=0; i<NUM_OF_ROW; i++)//좌석은 모두 0으로 초기화 
			{	
			for(int j=0; j<NUM_OF_COLUMN; j++)
				{
					studyGarden[i][j] = '0'; 
					noteBookZoon[i][j] = '0';
					cafeZoon[i][j] = '0';
				}	
			}
				
		}
		
		void join()
		{
			int num;
			
			while(true)
			{
				cout <<"회원 가입할 id를 입력하세요.(뒤로가기 : -1)"<<endl;	
				cin >> num;
				
				if(num==-1)
				return ;
			
				if(search_id(num)==-1)
					break;
				else
					cout << "이미 존재하는 id입니다." <<endl; 
			}	
				
			user[count++].set_id(num);
			
			cout <<"회원 가입되었습니다."<<endl<<endl;
		}
		void print_seat(char seat[][10])
		{
			cout << "- : 빈자리, @ - 예약된 자리" << endl;
			for(int i=0; i<NUM_OF_ROW; i++)
			{
				for(int j =0; j<NUM_OF_COLUMN; j++)
				{
					if(seat[i][j]=='0') //자리가 비어있는 경우 
					 	cout << "-";
					else          // 자리가 예약되어 있는 경우 
					 	cout << "@";
				}
				cout << endl;
			}
		}
		
		int search_id(int id) // id를 받아서 회원가입을 이미 했는지 확인 
		{
			for(int i=0; i<MAX_USER; i++)
			{
				if(user[i].get_id() == id)
					return i;	//user의 인덱스 반환 
				
			}
			return -1;
		}
		
		void copy_array(char lib[][NUM_OF_COLUMN], char study[][NUM_OF_COLUMN])
		{
			for(int i=0; i<NUM_OF_ROW; i++)
			{
				for(int j=0; j<NUM_OF_COLUMN; j++)
				lib[i][j] = study[i][j];
			}
		}
		
		void reserve()//예약하기 프로그램 
		{
			int num;
			int id,r,c;
			char lib[NUM_OF_ROW][NUM_OF_COLUMN];
			cout << "id를 입력 하세요: ";
			cin >> id;
			if(search_id(id)!=-1) // 회원 가입이 되어있을 경우 
				{
					cout << "선호하는 도서관을 입력하세요."<<endl;
					cout << "1.스터디 가든 2.노트북 룸 3.카페 존"<<endl;
					cin >> num;
					
					switch (num)
					{
						case 1: print_seat(studyGarden); copy_array(lib,studyGarden); break;
						case 2: print_seat(noteBookZoon); copy_array(lib,noteBookZoon); break;
						case 3: print_seat(cafeZoon);  copy_array(lib,cafeZoon); break;
						default: cout <<"다시 입력 하세요."; return; 
					}
					
					cout << "좌석을 입력 하세요. (ex 2행,3열 -> 2 3)"<<endl; 
					cin >> r >> c;
					
					//배열 인데스는 0부터 시작이므로 사용자의 편의를 위해 내부적으로는 r-1,c-1을 저장
					int row_index = r-1;  
					int column_index = c-1; 
					
					if(row_index>=NUM_OF_ROW || column_index>=NUM_OF_COLUMN) 
					{
						cout<<"해당 자리는 없습니다." <<endl;
						return;
					}
					
					if(lib[row_index][column_index]=='1') 
					{
						cout<<"해당 자리는 이미 예약되어있습니다."<<endl; 
						return;
					}	
					
					
					user[search_id(id)].setdata(id,num,row_index,column_index,"사람"); // 임의의 이름 대입 

					
					
					
					switch (num)//예약한 좌석 표시
					{
						case 1:  studyGarden[row_index][column_index] = '1'; break;
						case 2: noteBookZoon[row_index][column_index] = '1'; break;
						case 3: cafeZoon[row_index][column_index] = '1'; break;
					}
					
					cout << "("<<r <<","<<c<<")" << "로 예약되었습니다"<<endl<<endl;
				}
				else 
				{
					cout << "해당 id는 회원가입이 안되어 있습니다." <<endl;
					join(); //회원 가입이 안되어있으면 회원가입으로 이동 
				}
		}
		
		void watch_seat()
		{
			int num; 
			cout << "자리를 조회할  도서관을  선택하세요"<<endl;
			cout << "1.스터디 가든 2.노트북 룸 3.카페 존"<<endl;
			cin >> num;
				switch (num)
					{
						case 1: print_seat(studyGarden); break;
						case 2: print_seat(noteBookZoon); break;
						case 3: print_seat(cafeZoon); break;
					}
		}
		
		void cancel()
		{
			int id;
			cout <<"-------자리 취소------" <<endl;
			cout <<"id를 입력 하세요."<<endl;
			cin >> id;
			int index = search_id(id);
			
		
			if(index!=-1)
			{
				RoomInfo roominfo = user[index].getroomInfo();
				int roomnum = roominfo.getroomNuber();
				int roomrow = roominfo.getroomRow();
				int roomcolumn = roominfo.getroomColumn();
				
				cout << "("<<roomrow+1<<","<< roomcolumn+1<<") 가 취소되었습니다."<<endl;
				switch (roomnum) // 예약한 좌석 표시 
					{
						case 1: studyGarden[roomrow][roomcolumn] = '0'; break; 
						case 2: noteBookZoon[roomrow][roomcolumn] = '0'; break;
						case 3: cafeZoon[roomrow][roomcolumn] = '0'; break;
					}	
					
				user[index].set_id(-1); //id를 -1로 초기화 함
				count--; //인원수 -1 
				
			}
			
			else{
				cout << "해당 id의 정보가  없습니다." << endl;
				}
		}
		
		void my_data()
		{
			int id;
			cout <<  "id 입력: ";
			cin >> id;
			int index = search_id(id);
			if(index==-1) //아이디가 없는 경우 
			{
				cout << "아이디 조회 불가" <<endl;
				return;
			}
			RoomInfo roominfo = user[index].getroomInfo();
			int roomnum = roominfo.getroomNuber();
			int roomrow = roominfo.getroomRow();
			int roomcolumn = roominfo.getroomColumn();
			
			switch (roomnum)
					{
						case 1: cout<<"현위치 : 스터디 가든" <<endl;  break;
						case 2: cout<<"현위치 : 노트북 존" <<endl; break;
						case 3: cout<<"현위치 : 카페 존" <<endl; break;
					}
					//실제 유저의 자리는 인덱스에서  +1을 해줘야함
					cout <<"좌석 : (" << roomrow+1 << "," << roomcolumn+1 << ")"  <<endl; 
					 
					
		}
		
		void showCount()
		{
			cout << "현재까지 인원수는 " << getcount() << "명 입니다." << endl;
		}
		
		static int getcount(){
			return count;
		}
		
		~Library()
		{
			delete[] user;
		}
};


int Library::count = 0; //static 변수 초기화


class GroupReserve : public Library{
	int number;
	int main_id;
	
	public:
		GroupReserve(){}
		GroupReserve(int number, int main_id)
		{
			this->number = number;
			this->main_id = main_id;
		}
		void group_reserve()
		{
			char lib[NUM_OF_ROW][NUM_OF_COLUMN];	
			cout << "대표자의 아이디를 입력하세요. - (단체 예약은 스터디 가든만 가능합니다.)" <<endl;
			cin >> this->main_id;
			int row;
			int column;		
			if(search_id(main_id)!=-1)
			{	
				cout << "총 인원수를 입력하세요."<<endl;
				cin >> this->number;
				cout << this->number <<"번 자리를 선택하세요.ex) 2 3"<<endl;
				for(int i=0; i<this->number; i++)
				{
					copy_array(lib,studyGarden);
					print_seat(lib);
					cout << number-i << "번남았습니다. " << endl;
					 
					cin >> row >> column;
					row--;
					column--;
					
					if(row>=NUM_OF_ROW || column>=NUM_OF_COLUMN) 
					{
						cout<<"해당 자리는 없습니다." <<endl;
						cout << "다시 입력 하세요." <<endl;
						i--;
						continue;
					}
					
					if(studyGarden[row][column]=='1') 
					{
						cout<<"해당 자리는 이미 예약되어있습니다."<<endl; 
						cout << "다시 입력 하세요." <<endl;
						i--;
						continue;
					}	
					
					studyGarden[row][column] = '1';
					
					//id는 하나만 받았지만 모든 인원수 관리(단체석 취소시, 총인원수 조회시 등등 )를 해야하므로 main_id에서 1씩 더한값으로 사람들의 정보 저장  
					
					user[search_id(main_id++)].setdata(main_id++,1,row,column,"사람"); //스터디 가든 고정이므로 방번호가 1로 고정 
					user[count++].set_id(main_id);
				}
				
				cout << "예약 완료 되었습니다." <<endl;
				
//				for(int i=0; i<100; i++)
//				cout << user[i].get_id() << endl;
				
			}	
			else
			{
				cout << "아이디 회원가입이 안되어 있습니다." <<endl;
				join();
			}
			 
		}
		void group_cancel()
		{
			int id;
			int num=0;
			cout <<"-------자리 취소------" <<endl;
			cout << "취소할 인원수를 입력 하세요. " <<endl;
			cin >> num;
		
			cout <<"id를 입력 하세요."<<endl;
			cin >> id;
			
			for(int i=0; i<num; i++)
			{
				int index = search_id(id++);
			
		
				if(index!=-1)
				{
					RoomInfo roominfo = user[index].getroomInfo();
					int roomnum = roominfo.getroomNuber();
					int roomrow = roominfo.getroomRow();
					int roomcolumn = roominfo.getroomColumn();
				
					cout << "("<<roomrow+1<<","<< roomcolumn+1<<") 가 취소되었습니다."<<endl;
					studyGarden[roomrow][roomcolumn] = '0';
					user[index].set_id(-1); //id를 -1로 초기화 함
					count--; //인원수 -1 
				}
				
				else{
				cout << "해당 id의 정보가  없습니다." << endl;
				}
			}
			
			cout << "취소 완료 되었습니다." <<endl;
			
			
		}
}; 

 
class Run{	
	GroupReserve* lib = new GroupReserve();
	public:
	Run(){}
	int manu()
	{
		int num;
		cout << "-----명지대학교 도서관 예약 프로그램-------" <<endl;
		cout << "1. 회원가입" <<endl;
		cout << "2. 예약하기" <<endl;
		cout << "3. 비어었는 자리조회" <<endl;
		cout << "4. 자리취소" <<endl;
		cout << "5. 내 자리 조회" <<endl;
		cout << "6. 인원수 조회" <<endl;
		cout << "7. 단체 예약" <<endl;
		cout << "8. 단체 취소" <<endl;
		cout << "9. 종료" <<endl;
		cout << "------------------------------------------" <<endl;
	
		cin >> num;
		return num;
	}
	
	void run()
	{
		int num;
		while((num=manu())!=9)
		{
			switch (num)
			{
				case 1: lib->join(); break;
				case 2: lib->reserve(); break;
				case 3: lib->watch_seat(); break;
				case 4: lib->cancel(); break;
				case 5: lib->my_data(); break;
				case 6: lib->showCount();
				case 7: lib->group_reserve(); break;
				case 8: lib->group_cancel(); break;
				case 9: break;
			}
		}
	}
};



int main()
{
	
	//library 프로그램 실행 
    Run run;
    run.run();
	
	
	//객체 배열 실습  
//	UserData user[5];
//	
//	for(int i=0; i<5; i++)
//		user[i].set_id(i);
//			
//	for(int i=0; i<5; i++)
//	cout << "user id : "<< user[i].get_id() << endl;
//	
//	
//	cout << endl;
//	UserData* ptr;
//	ptr = user;
//	
//	int i=0;
//	while(i<5)
//	{
//		cout << "user id : "<< (ptr)->get_id()<<endl;
//		ptr++;
//		i++;
//	}
//	
//	cout << endl;
//	
//	//복사 생성자 실습
//	 RoomInfo person1(1,2,3,"유재영");
//	 RoomInfo person2(person1); 
//	 person2.show();
//	 
//	 Circle pizza(1);
//	 Circle donut(pizza);
//	 donut.show();
}
 
 
 class Circle //복사 생성자 연습용 class 
{
	int radius;
	public:
		Circle(){}
		Circle(int r):radius(r){}
		void setCircle(int r)
		{
			radius = r;
		}
		int getRadius(){return radius;}
		void show()
		{
			cout << "반지름의 길이 : " << radius << endl;
		}
};

