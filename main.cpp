#include <iostream>
#include <string>
#include <fstream>
#include<stdlib.h>
using namespace std;
const int defaultSize = 100;
int length;

struct student//����ѧ����Ϣ
 {
    string num;
    string name;
    string sex;
    string birth;
    string exam;
};

template<class T>
class SeqList //˳�����
{
protected:
    T *data;
    int maxSize;
    int last;
public:
    
    SeqList(int sz) 
	{
        if (sz>0) {
            maxSize = defaultSize;
            last = sz - 1;
            data = new T[maxSize];
            if (data == NULL) {
                cerr << "�洢�������" << endl;
                exit(1);
            }
        }
    }
    
    void copy(SeqList<T>&L);
    ~SeqList() { delete[] data; };
    bool Insert(int i, T &x);
    bool Remove(int i);
    void output();
    int Search(string x);
    void read();
    void write();
};

template<class T>
void SeqList<T>::copy(SeqList<T>&L)//���ƺ���
{

    last = L.last-length+1;
    T value;
    data = new T[maxSize];
    for (int i = 0; i <= last; i++){
         data[i]=L.data[i];
    }
}

template <class T>
bool SeqList<T>::Insert(int i, T&x) {
    if (last == maxSize - 1) return false;
    if (i<0 || i>last + 1) return false;
    for (int j = last; j >= i; j--){
        data[j + 1] = data[j];

    }
    data[i] = x;
    last++;
    return true;
}

template <class T>
bool SeqList<T>::Remove(int i)//ɾ������ 
 {
    if (last == maxSize - 1) return false;
    if (i<0 || i>last + 1) return false;
    for (int j = i; j <= last; j++)
        data[j - 1] = data[j];
    last--;
    return true;
}

//�������
template <class T>
void SeqList<T>::output(){
    cout << "the last:" << last << endl;
    for (int i = 0; i < last-1; i++)
        cout << i + 1 << ":" << "ѧ��: " << data[i].num << " " << "����:" << data[i].name << " " << "�Ա�:" << data[i].sex << " "
        << "����:" << data[i].birth << " " << "����״��:" << data[i].exam << endl;
}

template <class T>
int SeqList<T>::Search(string x)//���Һ��� 
{
    for (int i = 0; i <= last; i++)
        {
        if (data[i].num==x)
            return i+1;
    }
	return 0;
}

template<class T>
void SeqList<T>::read()//��ȡ�ļ����� 
{
    int i = 0;
	bool flag;
    ifstream ifile("C:\\data.txt",ios::in);
    while (ifile.eof()==0)
    {
        ifile >> data[i].num >> data[i].name >> data[i].sex >>data[i].birth>> data[i].exam;
        
		if(!ifile)
    {
    	cerr<<"�򿪳���"<<endl;
		flag=1;
    	break;
    }
        i++;
        
    }
    if(flag!=1)
    cout<<"��ȡ���"<<endl;
    ifile.close();
}
//д���ļ�
template<class T>
void SeqList<T>::write(){
    ofstream ofile("C:\\data.txt");
    for (int i = 0; i < last; i++)
    {
        if (i == last - 1)
        {
            ofile << data[i].num << " " << data[i].name << " " << data[i].sex << " " << data[i].birth << " " << data[i].exam;
            break;
        }
        ofile << data[i].num << " " << data[i].name << " " << data[i].sex << " " << data[i].birth << " " << data[i].exam<<" ";
    }
    cout << "д��ɹ���\n";
    ofile.close();
}

void set()
 {  
    cout << "��ӭʹ��ѧ������ϵͳ\n";
    cout << "-------------------------\n";
    cout << "1.�½�ѧ��������\n";
    cout << "2.����ѧ����Ϣ\n";
    cout << "3.ɾ��ѧ����Ϣ\n";
    cout << "4.���ļ��ж�ȡ��������Ϣ\n";
    cout << "5.���ļ�д��ѧ����������Ϣ\n";
    cout << "6.�ڽ������в�ѯѧ����Ϣ����ѧ�������ң�" << endl;
    cout << "7.����Ļ�����ȫ��ѧ����Ϣ" << endl;
    cout << "8.�˳�" << endl;
    cout << "�������֣�\n";
}

int main(){
    int n;
    int i;
    SeqList<student>stu(2);
    string x;
    student s = { "110","Li","f","1998.12","����" };
    set();
    while (cin >> n&&n<8) {
        if (n == 1){
            cout << "�������ĳ��ȣ�\n"; 
			cin >> length; 
            SeqList <student> stu1(length); 
            student stu2[100];
            cout << "��������Ϣ��\n";
            
            for (int i = 0; i < length; i++)
			{
                cout << "ѧ��:"; cin >> stu2[i].num;
                cout << "����:"; cin >> stu2[i].name;
                cout << "�Ա�:"; cin >> stu2[i].sex;
                cout << "����:"; cin >> stu2[i].birth;
                cout << "����״����"; cin >> stu2[i].exam;
                stu1.Insert(i, stu2[i]);
            }
            stu.copy(stu1);

        }
        
        switch (n)
		{
        case 2: cout << "����������λ��:";
		 cin >> i; 
		 cout << "����������Ϣ:\n"; 
            cout << "ѧ��:"; cin >> s.num;
            cout << "����:"; cin >> s.name;
            cout << "�Ա�:"; cin >> s.sex;
            cout << "����:"; cin >> s.birth;
            cout << "����״����"; cin >> s.exam; 
            stu.Insert(i - 1, s); break;
        case 3:cout << "������ɾ����λ��:"; cin >> i; stu.Remove(i); break;
        case 4:stu.read(); break;
        case 5:stu.write(); break;
        case 6: cout << "������ѧ��ѧ�ţ�"; cin >> x; i = stu.Search(x); cout << i; break;//����ѧ������˳����λ��
        case 7:stu.output(); break;
        default:
            break;
        }
       system("pause"); 
        system("cls");
        set();
    }
    return 0;
}
