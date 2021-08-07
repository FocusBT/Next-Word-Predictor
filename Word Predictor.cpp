#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<fstream>
using namespace std;
vector<string> dater;
bool another = false;
static int found = 0;


struct Node
{
	struct Node* lchild;
	string data;
	int filled;
	struct Node* rchild;
}*root = NULL;

class Predictor 
{
	vector<string>tmp;
	vector<string>ok;
	vector<string> qt;
	vector<string> qt1;
	string data;
	char ch[100];
	bool status = false;
	ofstream file;
	fstream my_file;
	int i = 0;
	string a;
	string okay;
	//string temp = data;
public:
	Predictor()
	{
		root = createNode();
	}
	struct Node* createNode()
	{
		Node* temp = new Node;
		temp->data = "<>";
		temp->lchild = temp->rchild = NULL;
		return temp;
	}

	int Height(struct Node* p)
	{
		int x, y;
		if (p == NULL)return 0;
		x = Height(p->lchild);
		y = Height(p->rchild);
		return x > y ? x + 1 : y + 1;
	}
	//i am wasee
	//we want new game
	void Insert(vector<string> op)
	{
		struct Node* p = new Node;
		struct Node* q = root;
		Node* r = new Node;
		string me;
		int i = 0;
		//cout << root->lchild->data << endl;
		if (Height(q->lchild) > Height(q->rchild))
		{
			while (q->rchild != NULL)
			{
				q = q->rchild;
			}
			//q = q->rchild;
			r = new Node;
			me = op[i];
			r->data = me;
			r->lchild = r->rchild = NULL;

			q->rchild = r;
			q = q->rchild;
			i++;
			while (op[i] != "-")
			{
				r = new Node;
				me = op[i];
				r->data = me;
				r->lchild = r->rchild = NULL;
				q->lchild = r;
				//cout << root->lchild->data << endl;
				q = q->lchild;
				i++;
			}
		}
		else
		{
			Node* p = new Node;
			q = root;
			r = new Node;
			if (q->lchild == NULL)
			{
				while (op[i] != "-")
				{
					r = new Node;
					me = op[i];
					r->data = me;
					r->lchild = r->rchild = NULL;
					q->lchild = r;
					//cout << root->lchild->data << endl;
					q = q->lchild;
					i++;
				}
			}
			else
			{
				q = q->lchild;
				while (q != NULL)
					q = q->rchild;
			}
		}
	}

	int search(string word, Node* p)
	{
		if (p == NULL)
			return found;
		if (word == p->data)
		{
			if (p->lchild != NULL)
			{
				dater.push_back(p->lchild->data);
				found++;
			}
			else
				return found;
		}
		search(word, p->lchild);
		search(word, p->rchild);
		return found;
	}

	void GetReadY()
	{
		my_file.open("database.txt", ios::in);
		file.open("database.txt", ios::app);
		while (1)
		{
			my_file >> ch[i];
			if (ch[i] == '.')
			{
				if (status == true)
				{
					ok.push_back("-");
					Insert(ok);
				}
				ok.clear();
				for (int i = 0; i < 100; i++) ch[i] = '\0';
				i = -1;
				//for (int i = 0; i < 100; i++){ ch[i] = '\0'; }

			}
			if (my_file.eof())
				break;
			if (ch[i] == '+')
			{
				int counter = i;
				for (i = 0; i < counter; i++)
				{
					if (ch[i] == '.')
						i++;
					a = a + ch[i];
				}
				if (search(a, root) == 0)
				{
					status = true;
				}
				else
				{
					dater.clear();
				}
				found = 0;
				ok.push_back(a);
				a = "\0";
				i = 0;
			}
			else
				i++;
		}
		file.close();
		my_file.close();
	}

	void AIask()
	{
		my_file.open("database.txt", ios::in);
		file.open("database.txt", ios::app);
		for (int i = 0; i < 1000; i++)
		{
			cin >> data;
			//i++;
			for (int i = 0; i < data.length(); i++)
			{
				if (data[i] == ';')
				{
					file << "." << endl;
					return;
				}
				
				if (data[i] == '.' )
				{
					another = false;
					tmp.push_back(data);
					data.erase(remove(data.begin(), data.end(), '.'), data.end());
					if (status == true)
					{
						ok.push_back("-");
						Insert(ok);
					}
					if(data=="\0")
						file << "." << endl;
					ok.clear();

				}
				status = false;
			}
			if (!data.empty())
			{
				tmp.push_back(data);
				ok.push_back(data);
			}
			int j = 0;
			int choice;
			if (search(data, root) == 0)
			{
				status = true;
				another = true;
			}
			found = 0;
			while (search(data, root) != 0)
			{
				cout << endl;
				while (j < found)
				{
					cout << j + 1 << "->" << dater[j] << endl;
					j++;
				}
				cout << j + 1 << " : No Suggestion" << endl;
				cin >> choice;
				if (choice > found)
				{
					j = 0;
					found = 0;
					choice = 0;
					dater.clear();
					break;
				}
				data = dater[choice - 1];
				tmp.push_back(data);
				i++;
				dater.clear();
				choice = 0;
				j = 0;
				cout << "\033[2J\033[1;1H";
				for (int j = 0; j <= i; j++)
					cout << tmp[j] << " ";
				found = 0;

				if (data == ";")
				{
					if (another == true)
					{
						for (int j = 0; j <= i; j++)
						{
							if (tmp[j] == ";")
							{
								file << "." << endl;;
								file.close();
								my_file.close();
								return;
							}
							file << tmp[j] << "+";
						}
					}
					file << ".";
					break;
				}
			}
			if(!data.empty())
				file << data << "+";
			cout << "\033[2J\033[1;1H";
			for (int j = 0; j <= i; j++)
 				cout << tmp[j] << " ";
		}
		file.close();
		my_file.close();
	}
};


int main()
{
	int c = 10, r, i, j, k, a;
	a = c;
	cout << "\n\n\n\n";

	for (i = 1; i <= c - 1; i++)
	{
		a--;
		for (j = 1; j <= i; j++)
		{
			cout << " |-";
		}
		cout << "\n";
	}
	a = 2;
	for (i = 1; i <= c; i++)
	{
		a++;
		for (j = c - 1; j >= i; j--)
		{
			cout << " |-";
		}
		cout << "\n";
	}
	cout << "\t\t\t\tNext Word Predictor\n\n\n" << endl;
	cout << "Start Typing... :" << endl << endl;
	
	Predictor p1;
	p1.GetReadY();
	p1.AIask();
}