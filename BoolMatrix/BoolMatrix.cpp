#include <iostream>
#include <locale.h>
#include <string.h>

using namespace std;
typedef unsigned char UC;

class BoolVector
{
	UC* bv;
	int size, memory;
	int input(const char* string, int i_bv, int i_s, int length)
	{

		UC mask = 1;
		bv[i_bv] = 0;
		for (int index = 0; index < length; index++, i_s++)
		{
			bv[i_bv] <<= 1;
			if (string[i_s] == '1') bv[i_bv] |= mask;
		}
		return i_s;
	}
	void output(int i_bv, int length)
	{
		UC mask = 1;
		mask <<= length - 1;
		for (int index = 0; index < length; index++)
		{
			if (bv[i_bv] & mask)
			{
				cout << " " << '1';
			}
			else cout << " " << '0';
			mask >>= 1;
		}

	}
	BoolVector boolCheck(const char* string, int _size) {
		size = strlen(string) + _size;
		memory = size / 8; int length = size % 8;
		if (length) memory++;
		bv = new UC[memory];

		int i_s = 0, i_bv = 0;
		if (length) {
			i_s = input(string, i_bv, i_s, length);
			i_bv++;
		}
		for (; i_bv < memory; i_bv++)
			i_s = input(string, i_bv, i_s, 8);
		BoolVector p = *this;
		return p;
	}
public:
	BoolVector(int _size = 1) {
		memory = _size / 8; int length = _size % 8;
		if (length) memory++;
		bv = new UC[memory];
		size = _size;
		for (int index = 0; index < memory; index++) bv[index] = 0;
	}
	BoolVector(const BoolVector&temp) {
		size = temp.size;
		memory = temp.memory;
		bv = new UC[memory];
		for (int index = 0; index < memory; index++)
			bv[index] = temp.bv[index];
	}
	BoolVector(const char* string) {
		size = strlen(string);
		memory = size / 8; int length = size % 8;
		if (length) memory++;
		bv = new UC[memory];

		int i_s = 0, i_bv = 0;
		if (length) {
			i_s = input(string, i_bv, i_s, length);
			i_bv++;
		}
		for (; i_bv < memory; i_bv++)
			i_s = input(string, i_bv, i_s, 8);
	}
	BoolVector(const char* string, int _size) {
		int d = strlen(string);
		size = _size;
		memory = size / 8; int length = size % 8;
		if (length) memory++;
		bv = new UC[memory];

		int i_bv, i_s;
		if (d >= size)
		{
			i_bv = 0; i_s = d - size;
			if (length) {
				i_s = input(string, i_bv, i_s, length);
				i_bv++;
			}
			for (; i_s < d; i_bv++)
				i_s = input(string, i_bv, i_s, 8);
		}
		else {
			int m2 = d / 8; int k2 = d % 8; i_s = 0;
			if (k2) m2++;

			for (i_bv = 0; i_bv < memory - m2; i_bv++) {
				bv[i_bv] = 0;
			}
			if (k2) {
				i_s = input(string, i_bv, 0, k2);
				i_bv++;
			}
			for (; i_s < d; i_bv++)
				i_s = input(string, i_bv, i_s, 8);
		}
	}
	BoolVector operator= (const BoolVector& temp)
	{
		if (this != &temp)
		{
			if (memory != temp.memory)
			{
				delete[]bv;
				memory = temp.memory;
				bv = new UC[memory];
			}
			for (int index = 0; index < memory; index++)
				bv[index] = temp.bv[index];
			size = temp.size;
		}
		return *this;
	}
	~BoolVector() { delete[]bv; }

	UC operator[] (int index)
	{
		int _memory = index / 8, length = index % 8;
		UC mask = 1;
		mask <<= length;
		if (bv[memory - 1 - _memory] & mask) return 1;
		else return 0;
	}
	void print()
	{
		int length = size % 8; int index = 0;
		if (length)
		{
			output(0, length); index++;
		}
		for (; index < memory; index++)output(index, 8);
		cout << endl;
	}
	void scan(int _size)
	{
		char* string; int _memory, length;
		string = new char[_size];
		cin >> string;

		_memory = _size / 8; length = _size % 8;
		if (length) _memory++;

		if (memory != _memory)
		{
			delete[]bv;
			memory = _memory;
			bv = new UC[memory];
		}
		size = _size;
		int i_bv = 0, i_s = 0;
		if (length)
		{
			i_s = input(string, i_bv, i_s, length);
			i_bv++;
		}
		for (; i_s < size; i_bv++)
			i_s = input(string, i_bv, i_s, 8);
	}
	int weight() {
		int result = 0;
		UC mask = 1;
		for (int index = 0; index < memory; index++, mask = 1)
			for (mask <<= 7; mask != 0; mask >>= 1)
				if (bv[index] & mask)result++;

		return result;
	}

	BoolVector setUp1(int index) {
		if (index < 0 || index >= size) return nullptr;
		else {
			int _memory = index / 8, length = index % 8;
			UC mask = 1;  mask <<= length;
			bv[memory - 1 - _memory] |= mask;
		}
		return (*this);
	}
	BoolVector setUp0(int index) {
		if (index < 0 || index >= size) return nullptr;
		else {
			int _memory = index / 8, length = index % 8;
			UC mask = 1;  mask <<= length;
			mask = ~(mask);

			bv[memory - 1 - _memory] &= mask;
		}
		return (*this);
	}
	BoolVector invert(int index) {
		if (index < 0 || index >= size) return nullptr;
		else {
			int _memory = index / 8, length = index % 8;
			UC mask = 1;  mask <<= length;
			bv[memory - 1 - _memory] ^= mask;
		}
		return (*this);
	}
	BoolVector setUp1(int quantity, int position)
	{
		for (int index = position; (index < size) & (index < position + quantity); index++) {
			setUp1(index);
		}
		return *this;
	}
	BoolVector setUp0(int quantity, int position) {
		for (int index = position; (index < size) & (index < position + quantity); index++) {
			setUp0(index);
		}
		return *this;
	}
	BoolVector invert(int quantity, int position)
	{
		for (int index = position; (index < size) & (index < position + quantity); index++) {
			invert(index);
		}
		return *this;
	}

	bool operator== (BoolVector temp)
	{
		if (size != temp.size) return false;
		for (int index = 0; index < memory; index++)
			if (bv[index] != temp.bv[index]) return false;
		return true;
	}
	bool operator!= (BoolVector temp)
	{
		if (*this == temp)return false;
		else return true;
	}
	bool operator< (BoolVector temp) {
		if (size != temp.size) return false;
		for (int index = 0; index < memory; index++)
			if (bv[index] >= temp.bv[index]) return false;
		return true;
	}
	bool operator> (BoolVector temp) {
		if (size != temp.size) return false;
		for (int index = 0; index < memory; index++)
			if (bv[index] <= temp.bv[index]) return false;
		return true;
	}

	BoolVector operator& (BoolVector& temp)
	{
		int N = size, position_res = memory - 1;
		if (N > temp.size) { N = temp.size; position_res = temp.memory - 1; }
		BoolVector tmp(N);
		int position, position_x;
		for (position = memory - 1, position_x = temp.memory - 1; position_res >= 0; position--, position_x--, position_res--)
			tmp.bv[position_res] = bv[position] & temp.bv[position_x];
		return tmp;
	}
	BoolVector operator| (BoolVector& temp) {
		int _size = size, position_res = memory - 1;


		if (temp.size > _size)
		{
			_size = temp.size;
			position_res = temp.memory - 1;

		}
		BoolVector tmp(_size);

		int position, position_x;
		for (position = memory - 1, position_x = temp.memory - 1; ((position >= 0) && (position_x >= 0)); position--, position_x--, position_res--)
			tmp.bv[position_res] = bv[position] | temp.bv[position_x];
		if (position >= 0)
			for (; position_res > 0; position_res--, position--)
			{
				tmp.bv[position_res] = bv[position];
			}
		if (position_x >= 0)
			for (; position_res > 0; position_res--, position_x--)
			{
				tmp.bv[position_res] = bv[position_x];
			}

		return tmp;

	}
	BoolVector operator^ (BoolVector& temp) {
		int _size = size, position_res = memory - 1;


		if (temp.size > _size)
		{
			_size = temp.size;
			position_res = temp.memory - 1;

		}
		BoolVector tmp(_size);

		int position, position_x;
		for (position = memory - 1, position_x = temp.memory - 1; ((position >= 0) && (position_x >= 0)); position--, position_x--, position_res--)
			tmp.bv[position_res] = bv[position] ^ temp.bv[position_x];
		if (position >= 0)
			for (; position_res > 0; position_res--, position--)
			{
				tmp.bv[position_res] = bv[position];
			}
		if (position_x >= 0)
			for (; position_res > 0; position_res--, position_x--)
			{
				tmp.bv[position_res] = bv[position_x];
			}

		return tmp;

	}
	BoolVector operator~ () {
		int index;
		for (index = 0; index < memory; index++)
			bv[index] = ~bv[index];
		return *this;
	}
	BoolVector operator<< (int length) {
		BoolVector tmp = (*this);
		if (length >= size) for (int index = 0; index < memory; index++) bv[index] = 0;
		else {
			for (int index = size - 1; index >= length; index--) {
				if (tmp[index - length] == 1) {
					tmp.setUp1(index);
				}
				else { tmp.setUp0(index); }
			}
		}
		tmp.setUp0(length, 0);
		return tmp;
	}
	BoolVector operator>>(int length) {
		BoolVector tmp = *this;
		tmp = tmp >> length;
		*this = tmp;
		return *this;
	}

	BoolVector& operator&= (BoolVector& temp) {
		BoolVector tmp;
		tmp = (*this & temp);
		*this = tmp;
		return (*this);
	}
	BoolVector& operator|= (BoolVector& temp) {
		BoolVector tmp;
		tmp = (*this) | temp;
		*this = tmp;
		return (*this);
	}
	BoolVector& operator^= (BoolVector& temp) {
		BoolVector tmp;
		tmp = (*this) ^ temp;
		*this = tmp;
		return (*this);
	}
	BoolVector& operator<<=(int length) {
		BoolVector tmp = *this;
		tmp = tmp << length;
		*this = tmp;
		return *this;
	}
	BoolVector operator>>=(int length)

	{
		int temp = length;
		int index;
		for (index = 0; temp < size; index++, temp++)
		{
			if (operator[](temp))
			{
				this->setUp1(index);
			}
			else
			{
				this->setUp0(index);
			}
		}
		for (; index < size; index++)
		{
			this->setUp0(index);
		}
		return *this;
	}

	friend ostream& operator<< (ostream& flow, BoolVector& temp) {
		temp.print();
		return flow;
	}
	friend istream& operator>> (istream& flow, BoolVector& temp) {
		temp.scan(temp.size); return flow;
	}
};

class BoolMatrix
{
	BoolVector* BM;
	int memory, size;
	int max(char** string, int memory) {
		int index, max = strlen(string[0]);
		for (index = 0; index < memory; index++)
			if (strlen(string[index]) > max) max = strlen(string[index]);
		return max;
	}
public:
	BoolMatrix() {
		memory = 1; size = 1;
		BM = new BoolVector[memory];
		BoolVector temp(1);
		BM[0] = temp;
	}
	BoolMatrix(int _memory, int _size) {
		memory = _memory; size = _size;
		BM = new BoolVector[memory];
		for (int index = 0; index < memory; index++)
		{
			BoolVector temp(size); BM[index] = temp;
		}
	}
	BoolMatrix(char** string, int _memory) {
		memory = _memory;
		size = max(string, _memory);
		BM = new BoolVector[memory];
		for (int index = 0; index < memory; index++)
			BM[index] = BoolVector(string[index], size);
	}
	BoolMatrix(const BoolMatrix& temp) {
		memory = temp.memory;  size = temp.size;
		BM = new BoolVector[memory];
		for (int index = 0; index < memory; index++)
			BM[index] = temp.BM[index];
	}
	~BoolMatrix() {
		delete[]BM;
	}

	void scan(int _memory, int length) {
		if (memory != _memory)
		{
			delete[]BM;
			memory = _memory;
			BM = new BoolVector[memory];
		}
		for (int index = 0; index < _memory; index++)
		{
			BM[index].scan(length);
			cout << endl;
		}
	}
	void print() {
		for (int index = 0; index < memory; index++)
			cout << BM[index] << endl;
	}

	BoolMatrix& operator= (const BoolMatrix& temp) {
		if (this != &temp)
		{
			if (memory != temp.memory)
			{
				delete[]BM;
				memory = temp.memory;
				BM = new BoolVector[memory];
			}
			for (int index = 0; index < memory; index++)
				BM[index] = temp.BM[index];
			size = temp.size;
		}
		return *this;
	}
	BoolVector& operator[] (int index) {
		if ((index < 0) && (index >= memory))
			return BM[index];
	}
	bool operator== (BoolMatrix& temp) {
		if (memory != temp.memory || size != temp.size) return false;
		for (int index = 0; index < memory; index++)
			if (BM[index] != temp.BM[index]) return false;
		return true;
	}
	bool operator!= (BoolMatrix& temp) {
		if (*this == temp)return false;
		else return true;
	}

	BoolMatrix setUp1(int index, int position) {
		if (!(index < 0 || index >= memory) && !(position < 0 || position >= size))
			BM[index] = BM[index].setUp1(position);
		return *this;
	}
	BoolMatrix setUp0(int index, int position) {
		if (!(index < 0 || index >= memory) && !(position < 0 || position >= size))
			BM[index] = BM[index].setUp0(position);
		return *this;
	}
	BoolMatrix invert(int index, int position) {
		if (!(index < 0 || index >= memory) && !(position < 0 || position >= size))
			BM[index] = BM[index].invert(position);
		return *this;
	}

	BoolMatrix setUp1(int index, int _size, int position) {
		BM[index].setUp1(_size, position);
		return *this;
	}
	BoolMatrix setUp0(int index, int _size, int position)
	{
		BM[index].setUp0(_size, position);
		return *this;

	}
	BoolMatrix invert(int index, int _size, int position) {
		BM[index].invert(_size, position);
		return *this;

	}

	BoolMatrix operator& (BoolMatrix& temp) {
		if (memory != temp.memory)
		{
			BoolMatrix tmp = *this;
			return tmp;
		}
		int _size = size;
		if (_size < temp.size) _size = temp.size;
		BoolMatrix tmp(memory, _size);
		for (int index = 0; index < memory; index++)
			tmp.BM[index] = BM[index] & temp.BM[index];
		return tmp;
	}
	BoolMatrix& operator&= (BoolMatrix& temp) {
		BoolMatrix tmp = (*this) & temp;
		*this = tmp;
		return *this;
	}
	BoolMatrix operator| (BoolMatrix& temp) {
		if (memory != temp.memory)
		{
			BoolMatrix tmp = *this;
			return tmp;
		}
		int _size = size;
		if (_size < temp.size) _size = temp.size;
		BoolMatrix tmp(memory, _size);
		for (int index = 0; index < memory; index++)
			tmp.BM[index] = BM[index] | temp.BM[index];
		return tmp;
	}
	BoolMatrix& operator|= (BoolMatrix& temp) {
		BoolMatrix tmp = (*this) & temp;
		*this = tmp;
		return *this;
	}
	BoolMatrix operator^ (BoolMatrix& temp) {
		if (memory != temp.memory)
		{
			BoolMatrix tmp = *this;
			return tmp;
		}
		int _size = size;
		if (_size < temp.size) _size = temp.size;
		BoolMatrix tmp(memory, _size);
		for (int index = 0; index < memory; index++)
			tmp.BM[index] = BM[index] ^ temp.BM[index];
		return tmp;
	}
	BoolMatrix& operator^= (BoolMatrix& temp) {
		BoolMatrix tmp = (*this) & temp;
		*this = tmp;
		return *this;
	}
	BoolMatrix operator~() {
		for (int index = 0; index < memory; index++)
			~BM[index];
		return *this;
	}

	BoolMatrix shiftRight(int index, int length) {
		BoolMatrix tmp = *this;
		tmp.BM[index] >>= length;
		return tmp;
	}
	BoolMatrix& shiftRightEq(int index, int length) {
		BM[index] >>= length;
		return *this;
	}
	BoolMatrix shiftLeft(int index, int length) {
		BoolMatrix tmp = *this;
		tmp.BM[index] <<= length;
		return tmp;
	}
	BoolMatrix& shiftLeftEq(int index, int _size) {
		BM[index] <<= _size;
		return *this;
	}

	BoolVector conpositionunction() {
		BoolVector H = BM[0];
		for (int index = 1; index < memory; index++)
			H &= BM[index];
		return H;
	}
	BoolVector dispositionunction() {
		BoolVector H(size);
		for (int index = 0; index < memory; index++)
			H |= BM[index];
		return H;
	}
	BoolVector exclusiveOr() {
		BoolVector H(size);
		for (int index = 0; index < memory; index++)
			H ^= BM[index];
		return H;
	}

	friend ostream& operator<< (ostream& flow, BoolMatrix& temp) {
		temp.print();
		return flow;
	}
	friend istream& operator>> (istream& flow, BoolMatrix& temp) {
		temp.scan(temp.memory, temp.size);
		return flow;
	}

};

int main()
{
	setlocale(LC_ALL, "Russian");
}