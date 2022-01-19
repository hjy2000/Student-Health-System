#include <iostream>
#include <string>
#include <fstream>
#include<stdlib.h>
using namespace std;
const int defaultSize = 100;
int length;

struct student//声明学生信息
 {
    string num;
    string name;
    string sex;
    string birth;
    string exam;
};

template<class T>
class SeqList //顺序表类
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
                cerr << "存储分配错误！" << endl;
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
void SeqList<T>::copy(SeqList<T>&L)//复制函数
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
bool SeqList<T>::Remove(int i)//删除函数 
 {
    if (last == maxSize - 1) return false;
    if (i<0 || i>last + 1) return false;
    for (int j = i; j <= last; j++)
        data[j - 1] = data[j];
    last--;
    return true;
}

//输出函数
template <class T>
void SeqList<T>::output(){
    cout << "the last:" << last << endl;
    for (int i = 0; i < last-1; i++)
        cout << i + 1 << ":" << "学号: " << data[i].num << " " << "姓名:" << data[i].name << " " << "性别:" << data[i].sex << " "
        << "生日:" << data[i].birth << " " << "健康状况:" << data[i].exam << endl;
}

template <class T>
int SeqList<T>::Search(string x)//查找函数 
{
    for (int i = 0; i <= last; i++)
        {
        if (data[i].num==x)
            return i+1;
    }
	return 0;
}

template<class T>
void SeqList<T>::read()//读取文件函数 
{
    int i = 0;
	bool flag;
    ifstream ifile("C:\\data.txt",ios::in);
    while (ifile.eof()==0)
    {
        ifile >> data[i].num >> data[i].name >> data[i].sex >>data[i].birth>> data[i].exam;
        
		if(!ifile)
    {
    	cerr<<"打开出错"<<endl;
		flag=1;
    	break;
    }
        i++;
        
    }
    if(flag!=1)
    cout<<"读取完成"<<endl;
    ifile.close();
}
//写入文件
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
    cout << "写入成功！\n";
    ofile.close();
}

void set()
 {  
    cout << "欢迎使用学生健康系统\n";
    cout << "-------------------------\n";
    cout << "1.新建学生健康表\n";
    cout << "2.插入学生信息\n";
    cout << "3.删除学生信息\n";
    cout << "4.从文件中读取健康表信息\n";
    cout << "5.向文件写入学生健康表信息\n";
    cout << "6.在健康表中查询学生信息（按学号来查找）" << endl;
    cout << "7.在屏幕中输出全部学生信息" << endl;
    cout << "8.退出" << endl;
    cout << "输入数字：\n";
}

int main(){
    int n;
    int i;
    SeqList<student>stu(2);
    string x;
    student s = { "110","Li","f","1998.12","良好" };
    set();
    while (cin >> n&&n<8) {
        if (n == 1){
            cout << "请输入表的长度：\n"; 
			cin >> length; 
            SeqList <student> stu1(length); 
            student stu2[100];
            cout << "输入表的信息：\n";
            
            for (int i = 0; i < length; i++)
			{
                cout << "学号:"; cin >> stu2[i].num;
                cout << "姓名:"; cin >> stu2[i].name;
                cout << "性别:"; cin >> stu2[i].sex;
                cout << "生日:"; cin >> stu2[i].birth;
                cout << "健康状况："; cin >> stu2[i].exam;
                stu1.Insert(i, stu2[i]);
            }
            stu.copy(stu1);

        }
        
        switch (n)
		{
        case 2: cout << "请输入插入的位置:";
		 cin >> i; 
		 cout << "输入插入的信息:\n"; 
            cout << "学号:"; cin >> s.num;
            cout << "姓名:"; cin >> s.name;
            cout << "性别:"; cin >> s.sex;
            cout << "生日:"; cin >> s.birth;
            cout << "健康状况："; cin >> s.exam; 
            stu.Insert(i - 1, s); break;
        case 3:cout << "请输入删除的位置:"; cin >> i; stu.Remove(i); break;
        case 4:stu.read(); break;
        case 5:stu.write(); break;
        case 6: cout << "请输入学生学号："; cin >> x; i = stu.Search(x); cout << i; break;//返回学生所在顺序表的位置
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
