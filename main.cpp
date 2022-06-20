#include <iostream>
#include <stack>
#include <fstream>
#include <string>

#define BLACK 1
#define WHITE 2

using namespace std;

class ChessNode {
public:
	ChessNode() {
		location_x = 0;
		location_y = 0;
		player_id = -1;
	}

	void SetLocation(int x, int y)
	{
		location_x = x;
		location_y = y;
	}

	void SetPlayerId(int id) {
		player_id = id;
	}

	void SetChessNode(int x, int y, int id) {
		location_x = x;
		location_y = y;
		player_id = id;
	}

	int GetLocationX()
	{
		return location_x;
	}

	int GetLocationY()
	{
		return location_y;

	}

	int GetPlayerId()
	{
		return player_id;
	}

private:
	int location_x;
	int location_y;
	int player_id;
};

class CheckerBoard {
public:
	CheckerBoard(int size)
	{
		this->Size = size;
		board = new ChessNode * [size + 2];
		for (int i = 0; i < size + 2; i++) {
			board[i] = new ChessNode[size + 2];
			for (int j = 0; j < size + 2; j++) {
				board[i][j].SetChessNode(i, j, -1);
			}
		}
	}
	~CheckerBoard()
	{
		for (int i = 0; i < Size + 2; i++) {
			delete[] board[i];
			board[i] = nullptr;
		}
		delete board;
		board = nullptr;
	}

	void PlaceNode(int x, int y, int id)
	{
		if (board[x][y].GetPlayerId() != -1) {
			return;
		}
		if (x >= 1 && y >= 1 && x <= Size && y <= Size) {
			board[x][y].SetChessNode(x, y, id);
			AddStep(board[x][y]);
		}
	}

	void AddStep(ChessNode c) {
		route.push(c);
	}

	ChessNode ShowNode(int x, int y)
	{
		if (x >= 1 && y >= 1 && x <= Size && y <= Size) {
			return board[x][y];
		}
		return board[0][0];
	}

	ChessNode ShowRecentStep()
	{
		if (!route.empty()) {
			return route.top();
		}
		return board[0][0];
	}

	void RepentStep()
	{
		if (!route.empty()) {
			ChessNode tmp = route.top();
			board[tmp.GetLocationX()][tmp.GetLocationY()].SetChessNode(tmp.GetLocationX(), tmp.GetLocationY(), -1);
			route.pop();
		}
	}

	void Display()
	{
		cout << "\t";
		for (int i = 1; i <= Size; i++) {
			cout << i << "\t";
		}
		cout << endl;

		for (int i = 1; i <= Size; i++) {
			cout << i << "\t";
			for (int j = 1; j <= Size; j++) {
				if (board[i][j].GetPlayerId() == BLACK) {
					cout << "x\t";
				}
				else if (board[i][j].GetPlayerId() == WHITE) {
					cout << "o\t";
				}
				else {
					cout << "#\t";
				}
			}
			cout << endl;
		}

	}

	// �洢·��
	void StorageRoute() {
		while (!route.empty()) {
			route2.push(route.top());
			route.pop();
		}

		ofstream ofs;
		ofs.open("test.txt", ios::out);

		while (!route2.empty()) {
			ofs << char(route2.top().GetLocationX() + 48);
			ofs << " ";
			ofs << char(route2.top().GetLocationY() + 48);
			ofs << " ";
			ofs << char(route2.top().GetPlayerId() + 48);
			ofs << "\n";
			route2.pop();
		}
		ofs.close();
	}

private:
	int Size;
	ChessNode** board;
	stack<ChessNode> route;
	stack<ChessNode> route2;
};

class Client {
public:
	Client()
	{
		Size = 0;
	}
	void LoopRun()
	{
		int sig = -1;
		while (sig != 1) {
			cout << "\t\t��������Ϸ�˵�" << endl;
			cout << "(1) �رտͻ���" << "\t\t" << "(2) ��ʼ�µ���Ϸ" << endl;
			cout << "(3) �������̳ߴ�" << "\t" << "(4) ɾ����ǰ����Ϸ" << endl;
			cout << "(5) ���뵱ǰ����Ϸ" << "\t" << "(6) �鿴��Ϸ�����Ϣ" << endl;
			cout << "(7) ��ǰ��Ϸ�浵" << "\t" << "(8) ��ȡ�浵" << endl;
			cout << "�������ֲ��һس�: ";
			cin >> sig;
			cout << endl;
			if (sig == 2) {
				RunNewGame();
			}
			else if (sig == 3) {
				SetSize();
			}
			else if (sig == 4) {
				DeleteCheckerBoard_Max();
			}
			else if (sig == 5) {
				RunNowGame();
			}
			else if (sig == 6) {
				ShowGameInf();
			}
			else if (sig == 7) {
				StorageRouteMax();
			}
			else if (sig == 8) {
				ReadRoute();
			}
			cout << endl;
			cout << "-----------------------------------------------" << endl;
		}
	}

	bool JudgeSize()
	{
		if (Size == 0) {
			return true;
		}
		return false;
	}

	void DeleteCheckerBoard()
	{
		delete checkerboard;
		checkerboard = nullptr;
	}

	void DeleteCheckerBoard_Max()
	{
		StorageRouteMax();
	}

	void RunNewGame() {
		int x;
		int y;
		int id;

		DeleteCheckerBoard();
		if (JudgeSize()) {
			cout << "Size = 0�����������̳ߴ�" << endl;
			return;
		}
		checkerboard = new CheckerBoard(Size);
		checkerboard->Display();

		while (cin >> x >> y) {
			if (x > Size || y > Size || x < 1 || y < 1) {
				cout << "�������˵��ɹ���" << endl;
				break;
			}

			if (checkerboard->ShowRecentStep().GetPlayerId() == -1) {
				id = BLACK;
			}
			else if (checkerboard->ShowRecentStep().GetPlayerId() == WHITE) {
				id = BLACK;
			}
			else if (checkerboard->ShowRecentStep().GetPlayerId() == BLACK) {
				id = WHITE;
			}
			else {
				cout << "��������˴��������´���Ϸ" << endl;
			}

			checkerboard->PlaceNode(x, y, id);
			checkerboard->Display();
			if (JudgePlay()) {
				cout << "��Ϸʤ��" << endl;
			}
			else {
				cout << "δ����Ӯ��" << endl;
			}
		}
	}

	void RunNowGame() {
		int x;
		int y;
		int id;

		if (checkerboard == nullptr) {
			cout << "��ǰ��̨û����Ϸ������" << endl;
			return;
		}
		checkerboard->Display();

		while (cin >> x >> y >> id) {
			if (x > Size || y > Size || x < 1 || y < 1) {
				break;
			}
			checkerboard->PlaceNode(x, y, id);
			checkerboard->Display();
		}
	}

	void SetSize()
	{
		cout << "��������Ҫ�����̳ߴ�: ";
		cin >> Size;
		int x = 1;
		if (Size < 5) {
			while (x != 0) {
				if (Size < 5) {
					cout << "  ->���̵Ĵ�С̫СΪ: " << Size << "������������" << endl;
					cout << "  ->���������ã�������0��س�" << endl;
				}
				else {
					break;
				}
				cout << "������������Ҫ�����̳ߴ�: ";
				cin >> Size;
				x = Size;
			}
		}
		cout << "  ->���̵Ĵ�С���óɹ�Ϊ: " << Size << endl;
	}

	void ShowGameInf()
	{
		cout << "  ��ǰ��Ϸ�ߴ�: " << Size << endl;
		cout << "    ��Ϸ������: ����" << endl;
		cout << "      ��Ϸ�汾: 1.0.0" << endl;
		cout << "��ǰ�Ƿ�������: ";
		if (checkerboard == nullptr) {
			cout << "no" << endl;
		}
		else {
			cout << "yes" << endl;
		}
	}

	// �����ж��Ƿ��Ƿ��������ߵĺ������������������
	bool JudgePlay()
	{
		ChessNode c;
		int id;
		int counter;
		for (int i = 5; i <= Size; i++) {
			for (int j = 5; j <= Size; j++) {
				c = checkerboard->ShowNode(i, j);
				id = c.GetPlayerId();
				if (id != 1 && id != 2) {
					continue;
				}
				counter = 1;
				while (counter < 5) {
					if (checkerboard->ShowNode(i - counter, j - counter).GetPlayerId() == id) {
						if (counter == 4) {
							return true;
						}
					}
					else {
						break;
					}
					counter++;
				}
				counter = 1;
				while (counter < 5) {
					if (checkerboard->ShowNode(i - counter, j).GetPlayerId() == id) {
						if (counter == 4) {
							return true;
						}
					}
					else {
						break;
					}
					counter++;
				}
				counter = 1;
				while (counter < 5) {
					if (checkerboard->ShowNode(i, j - counter).GetPlayerId() == id) {
						if (counter == 4) {
							return true;
						}
					}
					else {
						break;
					}
					counter++;
				}
			}
		}
		return false;
	}

	// �洢����·���ĺ���
	void StorageRouteMax() {
		if (checkerboard == nullptr) {
			cout << "û�����̣��洢ʧ����" << endl;
			return;
		}
		checkerboard->StorageRoute();
		delete checkerboard;
		checkerboard = nullptr;
		cout << "����·���Ѿ����洢���ļ���" << endl;
	}

	// ��ȡ·���ĺ���
	void ReadRoute() {
		if (checkerboard != nullptr) {
			DeleteCheckerBoard();
		}
		Size = 10;
		checkerboard = new CheckerBoard(Size);

		ifstream ifs;
		ifs.open("test.txt", ios::in);

		if (!ifs.is_open())
		{
			cout << "test.txt�ļ�����ȡʧ��" << endl;
			return;
		}

		string xx;
		string yy;
		string dd;

		string buf;
		while (getline(ifs, buf))
		{
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
			checkerboard->PlaceNode(xxx, yyy, ddd);
		}
		ifs.close();

		cout << "����·���Ѿ�����ȡ������ͼ: " << endl;
		checkerboard->Display();
	}

public:
	int Size;
	CheckerBoard* checkerboard;
};

int main(void)
{
	Client* client = new Client;
	client->LoopRun();

	return 0;
}