#include <iostream>
#include <fstream>
#include <stack>
#include <string>
 
using namespace std;
 
class ChessNode {
public:
	ChessNode(int x, int y, int id) {
		location_x = x;
		location_y = y;
		player_id = id;
	}
public:
	int location_x;
	int location_y;
	int player_id;
};
 
class CheckerBoard {
public:
	void AddStep(ChessNode c) {
		route.push(c);
	}
public:
	stack<ChessNode> route;
	stack<ChessNode> route2;
};
 
int main(void)
{
	CheckerBoard* b = new CheckerBoard;
 
	ChessNode n1(1, 1, 1);
	b->AddStep(n1);
	ChessNode n2(1, 2, 2);
	b->AddStep(n2);
	ChessNode n3(1, 3, 1);
	b->AddStep(n3);
 
	while (!b->route.empty()) {
		b->route2.push(b->route.top());
		b->route.pop();
	}
 
	ofstream ofs;
	ofs.open("test.txt", ios::out);
 
	while (!b->route2.empty()) {
		ofs << char(b->route2.top().location_x + 48);
		ofs << " ";
		ofs << char(b->route2.top().location_y + 48);
		ofs << " ";
		ofs << char(b->route2.top().player_id + 48);
		ofs << "\n";
		b->route2.pop();
	}
	ofs.close();
 
	// 2、创建流对象
	ifstream ifs;
 
	// 3、打开文件并判断文件是否打开成功
	ifs.open("test.txt", ios::in);
 
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
 
	string xx;
	string yy;
	string dd;
 
	// 4、读数据
	string buf;
	while (getline(ifs, buf))
	{
		// cout << buf << endl;
		xx = buf.substr(0, 1);
		int j = 0;
		string s = " ";
		for (int i = 0; i < size(buf); i++) {
			string s2 = buf.substr(i, 1);
			if (s.compare(s2) == 0)
			{
				j++;
				if (j == 1) {
					yy = buf.substr(i + 1, 1);
				}
				else if (j == 2) {
					dd = buf.substr(i + 1, 1);
				}
			}
		}
		int xxx = (int)(xx[0] - 48);
		int yyy = (int)(yy[0] - 48);
		int ddd = (int)(dd[0] - 48);
		ChessNode n(xxx, yyy, ddd);
		b->AddStep(n);
	}
 
	while (!b->route.empty()) {
		cout << b->route.top().location_x << " " << b->route.top().location_y << " " << b->route.top().player_id << endl;
		b->route.pop();
	}
 
 
	// 5、关闭文件
	ifs.close();
 
	return 0;
}
