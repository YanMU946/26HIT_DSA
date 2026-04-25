#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <stack>
#include <filesystem>
using namespace std;

template <class type>
class huffman {
public:
	struct NODE {
		type data;
		string hf_code;
		int weight;
		int parent, left, right;
	};

	huffman() {}

	huffman(const string& _msg)
	{
		int cur = 0, cnt = 0;
		if (_msg.empty()) return;
		for (auto& letter : _msg)
		{
			if (ascii_buf[letter] == 0)
				num++;
			ascii_buf[letter]++;
		}
		size = 2 * num - 1;
		elem = new NODE[size];
		for (int i = num;i < size;i++)
		{
			elem[i].parent = elem[i].left = elem[i].right = elem[i].data = elem[i].weight = -1;
		}
		for (auto& e : ascii_buf)
		{
			cnt++;
			if (e == 0) continue;
			elem[cur].parent = elem[cur].left = elem[cur].right = -1;
			elem[cur].data = cnt - 1;
			elem[cur++].weight = e;
		}
		for (int i = num;i < size;i++)
		{
			int elem1, elem2;
			select(i, elem1, elem2);
			elem[elem1].parent = elem[elem2].parent = i;
			elem[i].left = elem1;
			elem[i].right = elem2;
			elem[i].weight = elem[elem1].weight + elem[elem2].weight;
		}

	}
	void select(const int& _n, int& _s1, int& _s2)
	{
		for (int i = 0;i < _n;i++)
			if (elem[i].parent == -1)
			{
				_s1 = i;
				break;
			}

		for (int i = _s1;i < _n;i++)
			if (elem[i].parent == -1 && elem[_s1].weight > elem[i].weight)
				_s1 = i;

		for (int j = 0; j < _n; j++)
			if (elem[j].parent == -1 && j != _s1)
			{
				_s2 = j;
				break;
			}

		for (int j = _s2; j < _n; j++)
			if (elem[j].parent == -1 && elem[_s2].weight > elem[j].weight && j != _s1)
				_s2 = j;
	}

	void getcode()
	{
		cout << "**Huffman Tree**:" << endl;
		cout << "data	weight	parent	left	right" << endl;
		for (int i = 0;i < size;i++)
			cout << elem[i].data << "	" << elem[i].weight << "	" << elem[i].parent << "	" << elem[i].left << "	" << elem[i].right << endl;
		string temp;
		stack<string> st;		//利用栈实现上一个char类型strcpy的方法
		int cur = 0, pre_cur = 0;
		for (int i = 0; i < num; i++) {
			cur = i;
			pre_cur = elem[i].parent;
			while (pre_cur != -1)
			{
				if (elem[pre_cur].left == cur) st.push("0");
				else st.push("1");
				cur = pre_cur;
				pre_cur = elem[pre_cur].parent;
			}
			while (!st.empty()) {
				temp += st.top();
				st.pop();
			}
			ascii_hfbuf[elem[i].data] = elem[i].hf_code = temp;
			temp.erase();	//擦除内存
		}
		cout << "**Huffman Code**:" << endl;
		cout << "data	code" << endl;
		for (int i = 0;i < num;i++)
			cout << elem[i].data << "	" << elem[i].hf_code << endl;
	}

	string encode(const string& _msg)
	{
		string new_msg;
		for (auto& letter : _msg)
			new_msg += ascii_hfbuf[letter];

		string act_msg;
		char temp = 0;
		int cnt = 0;
		for (auto& letter : new_msg)
		{
			cnt++;
			temp |= (letter - '0') << (8 - cnt);
			if (cnt == 8)
			{
				act_msg += temp;
				temp = 0;
				cnt = 0;
			}
		}
		return act_msg;
	}

	void get_compress_rate(const string& file1, const string& file2)
	{
		auto size1 = filesystem::file_size(file1);
		auto size2 = filesystem::file_size(file2);
		cout << "**Compression ratio**: " << (double)size2 / size1 << endl;
	}

	string decode(const string& _msg)
	{
		string act_msg;
		for (auto& letter : _msg)
		{
			act_msg += (letter & 0x80) ? '1' : '0';
			act_msg += (letter & 0x40) ? '1' : '0';
			act_msg += (letter & 0x20) ? '1' : '0';
			act_msg += (letter & 0x10) ? '1' : '0';
			act_msg += (letter & 0x08) ? '1' : '0';
			act_msg += (letter & 0x04) ? '1' : '0';
			act_msg += (letter & 0x02) ? '1' : '0';
			act_msg += (letter & 0x01) ? '1' : '0';
		}

		string new_msg;
		int cur = size - 1;
		for (auto& letter : act_msg)
		{
			if (elem[cur].left == -1 && elem[cur].right == -1)
			{
				new_msg += elem[cur].data;
				cur = size - 1;
			}
			if (letter == '0')
				cur = elem[cur].left;
			else if (letter == '1')
				cur = elem[cur].right;
		}
		return new_msg;
	}

	~huffman() { delete[] elem; }

private:
	int ascii_buf[256] = { 0 };
	string ascii_hfbuf[256] = { "" };
	NODE* elem = nullptr;
	int num = 0;
	int size = 0;
};

#endif/* end huffman */
