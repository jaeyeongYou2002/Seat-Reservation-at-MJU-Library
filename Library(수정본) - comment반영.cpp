/*	
	���α׷� : �������б� ������ ȸ������, �ڸ�����,���,��ȸ�ϱ� �ý��� 
	�ۼ��� : ���翵 24 - 05 - 01
	
	 04-30 ���� ���� 
	 RoomInfo Ŭ�����߰� - 148�� 
	 ���ڴ�� ������ - #define ��� 
	 ȸ�����Խ� ����Լ��� �ƴ� while�� ������ - 86���� join�޼ҵ� 
	 ������� ���Ǹ� ���� �¼��� ����Ǵ� �迭�� �ε��� �� ���� - 170��	
	 
	 05-20 ���� ���� 
	 roomInfo class name���� �߰�, ���� ������ �߰� - 38��
	 ���� �Ҵ� �޸� ������ ���� �Ҹ��� �߰�, ���� ������ ������ class�߰� -  411��
	 
	 static ���� count �߰� , static �Լ� getCount �߰� - 340��
	 static �Լ��� �̿��Ͽ� ������� �ο��� ��ȸ�ϱ� �޴�, ��� �߰� - 377�� 
	 
	 
	 
	 --------14���� ���� ���� ����--------- 
	 06- 04 ���� ����
	 355�� - group reserve class �߰�
	 �˰��� ��ƴ - main_id�� +1�ϸ鼭 �����ϰ� �ɰ�� main_id�ڿ� id�� �̹� ������ ������ �߻��Ѵ�.
	 ��� -> userdata�� ����, ��ü�� ���� ����� �����Ѵ�. 
	 
	  
*/
#include<iostream>
#include<string.h>
#define NUM_OF_ROW 10
#define NUM_OF_COLUMN 10
#define MAX_USER 3 * NUM_OF_ROW * NUM_OF_COLUMN

using namespace std;

class RoomInfo //RoomInfoŬ���� �߰� 
{
	int roomNumber; // ���ȣ 
	int roomRow;	// �¼��� �� 
	int roomColumn;	 //�¼��� �� 
	char* name; //��������� ������ ���� char* ���� �߰� 
	
	public:
	RoomInfo(){}
	RoomInfo(int n):roomNumber(n){}
	RoomInfo(int n,int r,int c, char* na):roomNumber(n),roomRow(r),roomColumn(c)
	{
		name = new char[50];
		strcpy(this->name,na);
	}
	
	RoomInfo(RoomInfo& rhs) // ���� ������ �߰� 
	{
		this->roomNumber = 	rhs.roomNumber;
		this->roomRow = rhs.roomRow;
		this->roomColumn = rhs.roomColumn;
		
		
		this->name = new char[50]; // ���� ���� 
		strcpy(this->name,rhs.name);  

		cout << "���� �����ڰ� �����Ǿ����ϴ�." << endl;	
	} 
	
	~RoomInfo() // �޸� ���� 
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
		 
		cout << "�̸� : " << name << endl;
		cout << "�� ��ȣ : " << roomNumber << endl;
		cout << "�¼� : ("<< roomRow << "," << roomColumn << ")" <<  endl;
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
			cout << "�� ��ȣ : " << roomData.getroomNuber() << endl;
			cout << "�¼� : ("<< roomData.getroomRow() << "," << roomData.getroomColumn() << ")" <<  endl;
		}
		
};


class Library{
	
	protected:
	UserData* user = new UserData[MAX_USER]; //�ִ� 600���� ������ ���� ���� 
	char studyGarden[NUM_OF_ROW][NUM_OF_COLUMN]; //�Ļ�Ŭ������ groupreserve�� ���� ����ؾ��ϹǷ� static���� 
	char noteBookZoon[NUM_OF_ROW][NUM_OF_COLUMN];
	char cafeZoon[NUM_OF_ROW][NUM_OF_COLUMN];
	
	public:
		static int count;
		Library()
		{
			count = 0;
			for(int i=0; i<NUM_OF_ROW; i++)//�¼��� ��� 0���� �ʱ�ȭ 
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
				cout <<"ȸ�� ������ id�� �Է��ϼ���.(�ڷΰ��� : -1)"<<endl;	
				cin >> num;
				
				if(num==-1)
				return ;
			
				if(search_id(num)==-1)
					break;
				else
					cout << "�̹� �����ϴ� id�Դϴ�." <<endl; 
			}	
				
			user[count++].set_id(num);
			
			cout <<"ȸ�� ���ԵǾ����ϴ�."<<endl<<endl;
		}
		void print_seat(char seat[][10])
		{
			cout << "- : ���ڸ�, @ - ����� �ڸ�" << endl;
			for(int i=0; i<NUM_OF_ROW; i++)
			{
				for(int j =0; j<NUM_OF_COLUMN; j++)
				{
					if(seat[i][j]=='0') //�ڸ��� ����ִ� ��� 
					 	cout << "-";
					else          // �ڸ��� ����Ǿ� �ִ� ��� 
					 	cout << "@";
				}
				cout << endl;
			}
		}
		
		int search_id(int id) // id�� �޾Ƽ� ȸ�������� �̹� �ߴ��� Ȯ�� 
		{
			for(int i=0; i<MAX_USER; i++)
			{
				if(user[i].get_id() == id)
					return i;	//user�� �ε��� ��ȯ 
				
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
		
		void reserve()//�����ϱ� ���α׷� 
		{
			int num;
			int id,r,c;
			char lib[NUM_OF_ROW][NUM_OF_COLUMN];
			cout << "id�� �Է� �ϼ���: ";
			cin >> id;
			if(search_id(id)!=-1) // ȸ�� ������ �Ǿ����� ��� 
				{
					cout << "��ȣ�ϴ� �������� �Է��ϼ���."<<endl;
					cout << "1.���͵� ���� 2.��Ʈ�� �� 3.ī�� ��"<<endl;
					cin >> num;
					
					switch (num)
					{
						case 1: print_seat(studyGarden); copy_array(lib,studyGarden); break;
						case 2: print_seat(noteBookZoon); copy_array(lib,noteBookZoon); break;
						case 3: print_seat(cafeZoon);  copy_array(lib,cafeZoon); break;
						default: cout <<"�ٽ� �Է� �ϼ���."; return; 
					}
					
					cout << "�¼��� �Է� �ϼ���. (ex 2��,3�� -> 2 3)"<<endl; 
					cin >> r >> c;
					
					//�迭 �ε����� 0���� �����̹Ƿ� ������� ���Ǹ� ���� ���������δ� r-1,c-1�� ����
					int row_index = r-1;  
					int column_index = c-1; 
					
					if(row_index>=NUM_OF_ROW || column_index>=NUM_OF_COLUMN) 
					{
						cout<<"�ش� �ڸ��� �����ϴ�." <<endl;
						return;
					}
					
					if(lib[row_index][column_index]=='1') 
					{
						cout<<"�ش� �ڸ��� �̹� ����Ǿ��ֽ��ϴ�."<<endl; 
						return;
					}	
					
					
					user[search_id(id)].setdata(id,num,row_index,column_index,"���"); // ������ �̸� ���� 

					
					
					
					switch (num)//������ �¼� ǥ��
					{
						case 1:  studyGarden[row_index][column_index] = '1'; break;
						case 2: noteBookZoon[row_index][column_index] = '1'; break;
						case 3: cafeZoon[row_index][column_index] = '1'; break;
					}
					
					cout << "("<<r <<","<<c<<")" << "�� ����Ǿ����ϴ�"<<endl<<endl;
				}
				else 
				{
					cout << "�ش� id�� ȸ�������� �ȵǾ� �ֽ��ϴ�." <<endl;
					join(); //ȸ�� ������ �ȵǾ������� ȸ���������� �̵� 
				}
		}
		
		void watch_seat()
		{
			int num; 
			cout << "�ڸ��� ��ȸ��  ��������  �����ϼ���"<<endl;
			cout << "1.���͵� ���� 2.��Ʈ�� �� 3.ī�� ��"<<endl;
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
			cout <<"-------�ڸ� ���------" <<endl;
			cout <<"id�� �Է� �ϼ���."<<endl;
			cin >> id;
			int index = search_id(id);
			
		
			if(index!=-1)
			{
				RoomInfo roominfo = user[index].getroomInfo();
				int roomnum = roominfo.getroomNuber();
				int roomrow = roominfo.getroomRow();
				int roomcolumn = roominfo.getroomColumn();
				
				cout << "("<<roomrow+1<<","<< roomcolumn+1<<") �� ��ҵǾ����ϴ�."<<endl;
				switch (roomnum) // ������ �¼� ǥ�� 
					{
						case 1: studyGarden[roomrow][roomcolumn] = '0'; break; 
						case 2: noteBookZoon[roomrow][roomcolumn] = '0'; break;
						case 3: cafeZoon[roomrow][roomcolumn] = '0'; break;
					}	
					
				user[index].set_id(-1); //id�� -1�� �ʱ�ȭ ��
				count--; //�ο��� -1 
				
			}
			
			else{
				cout << "�ش� id�� ������  �����ϴ�." << endl;
				}
		}
		
		void my_data()
		{
			int id;
			cout <<  "id �Է�: ";
			cin >> id;
			int index = search_id(id);
			if(index==-1) //���̵� ���� ��� 
			{
				cout << "���̵� ��ȸ �Ұ�" <<endl;
				return;
			}
			RoomInfo roominfo = user[index].getroomInfo();
			int roomnum = roominfo.getroomNuber();
			int roomrow = roominfo.getroomRow();
			int roomcolumn = roominfo.getroomColumn();
			
			switch (roomnum)
					{
						case 1: cout<<"����ġ : ���͵� ����" <<endl;  break;
						case 2: cout<<"����ġ : ��Ʈ�� ��" <<endl; break;
						case 3: cout<<"����ġ : ī�� ��" <<endl; break;
					}
					//���� ������ �ڸ��� �ε�������  +1�� �������
					cout <<"�¼� : (" << roomrow+1 << "," << roomcolumn+1 << ")"  <<endl; 
					 
					
		}
		
		void showCount()
		{
			cout << "������� �ο����� " << getcount() << "�� �Դϴ�." << endl;
		}
		
		static int getcount(){
			return count;
		}
		
		~Library()
		{
			delete[] user;
		}
};


int Library::count = 0; //static ���� �ʱ�ȭ


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
			cout << "��ǥ���� ���̵� �Է��ϼ���. - (��ü ������ ���͵� ���縸 �����մϴ�.)" <<endl;
			cin >> this->main_id;
			int row;
			int column;		
			if(search_id(main_id)!=-1)
			{	
				cout << "�� �ο����� �Է��ϼ���."<<endl;
				cin >> this->number;
				cout << this->number <<"�� �ڸ��� �����ϼ���.ex) 2 3"<<endl;
				for(int i=0; i<this->number; i++)
				{
					copy_array(lib,studyGarden);
					print_seat(lib);
					cout << number-i << "�����ҽ��ϴ�. " << endl;
					 
					cin >> row >> column;
					row--;
					column--;
					
					if(row>=NUM_OF_ROW || column>=NUM_OF_COLUMN) 
					{
						cout<<"�ش� �ڸ��� �����ϴ�." <<endl;
						cout << "�ٽ� �Է� �ϼ���." <<endl;
						i--;
						continue;
					}
					
					if(studyGarden[row][column]=='1') 
					{
						cout<<"�ش� �ڸ��� �̹� ����Ǿ��ֽ��ϴ�."<<endl; 
						cout << "�ٽ� �Է� �ϼ���." <<endl;
						i--;
						continue;
					}	
					
					studyGarden[row][column] = '1';
					
					//id�� �ϳ��� �޾����� ��� �ο��� ����(��ü�� ��ҽ�, ���ο��� ��ȸ�� ��� )�� �ؾ��ϹǷ� main_id���� 1�� ���Ѱ����� ������� ���� ����  
					
					user[search_id(main_id++)].setdata(main_id++,1,row,column,"���"); //���͵� ���� �����̹Ƿ� ���ȣ�� 1�� ���� 
					user[count++].set_id(main_id);
				}
				
				cout << "���� �Ϸ� �Ǿ����ϴ�." <<endl;
				
//				for(int i=0; i<100; i++)
//				cout << user[i].get_id() << endl;
				
			}	
			else
			{
				cout << "���̵� ȸ�������� �ȵǾ� �ֽ��ϴ�." <<endl;
				join();
			}
			 
		}
		void group_cancel()
		{
			int id;
			int num=0;
			cout <<"-------�ڸ� ���------" <<endl;
			cout << "����� �ο����� �Է� �ϼ���. " <<endl;
			cin >> num;
		
			cout <<"id�� �Է� �ϼ���."<<endl;
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
				
					cout << "("<<roomrow+1<<","<< roomcolumn+1<<") �� ��ҵǾ����ϴ�."<<endl;
					studyGarden[roomrow][roomcolumn] = '0';
					user[index].set_id(-1); //id�� -1�� �ʱ�ȭ ��
					count--; //�ο��� -1 
				}
				
				else{
				cout << "�ش� id�� ������  �����ϴ�." << endl;
				}
			}
			
			cout << "��� �Ϸ� �Ǿ����ϴ�." <<endl;
			
			
		}
}; 

 
class Run{	
	GroupReserve* lib = new GroupReserve();
	public:
	Run(){}
	int manu()
	{
		int num;
		cout << "-----�������б� ������ ���� ���α׷�-------" <<endl;
		cout << "1. ȸ������" <<endl;
		cout << "2. �����ϱ�" <<endl;
		cout << "3. ������ �ڸ���ȸ" <<endl;
		cout << "4. �ڸ����" <<endl;
		cout << "5. �� �ڸ� ��ȸ" <<endl;
		cout << "6. �ο��� ��ȸ" <<endl;
		cout << "7. ��ü ����" <<endl;
		cout << "8. ��ü ���" <<endl;
		cout << "9. ����" <<endl;
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
	
	//library ���α׷� ���� 
    Run run;
    run.run();
	
	
	//��ü �迭 �ǽ�  
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
//	//���� ������ �ǽ�
//	 RoomInfo person1(1,2,3,"���翵");
//	 RoomInfo person2(person1); 
//	 person2.show();
//	 
//	 Circle pizza(1);
//	 Circle donut(pizza);
//	 donut.show();
}
 
 
 class Circle //���� ������ ������ class 
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
			cout << "�������� ���� : " << radius << endl;
		}
};

