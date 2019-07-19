#include<bits/stdc++.h>
#include "AVL.hpp"
using namespace std;

template <typename T>
static void assertEquals(T x, T y){
	if(x!=y)
		throw "Value mismatch";
}

static void testAdd() {
	avlList<const char*> list;
	list.push_back("January");
	list.push_back("February");
	list.push_back("March");
	list.push_back("April");
	list.push_back("May");
	list.push_back("June");
	// list.checkStructure();
	assertEquals(list.size(), static_cast<size_t>(6));
	assertEquals(list[0], "January" );
	assertEquals(list[1], "February");
	assertEquals(list[2], "March"   );
	assertEquals(list[3], "April"   );
	assertEquals(list[4], "May"     );
	assertEquals(list[5], "June"    );
}

static void testSet() {
	avlList<const char*> list;
	for (int i = 0; i < 10; i++)
		list.push_back(nullptr);
	list[0] = "zero";
	list[1] = "ten";
	list[2] = "twenty";
	list[3] = "thirty";
	list[4] = "forty";
	list[5] = "fifty";
	list[6] = "sixty";
	list[7] = "seventy";
	list[8] = "eighty";
	list[9] = "ninety";
	assertEquals(list.size(), static_cast<size_t>(10));
	assertEquals(list[0], "zero"   );
	assertEquals(list[1], "ten"    );
	assertEquals(list[2], "twenty" );
	assertEquals(list[3], "thirty" );
	assertEquals(list[4], "forty"  );
	assertEquals(list[5], "fifty"  );
	assertEquals(list[6], "sixty"  );
	assertEquals(list[7], "seventy");
	assertEquals(list[8], "eighty" );
	assertEquals(list[9], "ninety" );
}

static void testInsertAtBeginning() {
	avlList<const char*> list;
	list.insert(0, "Sunday");
	list.insert(0, "Monday");
	list.insert(0, "Tuesday");
	assertEquals(list.size(), static_cast<size_t>(3));
	assertEquals(list[0], "Tuesday");
	assertEquals(list[1], "Monday" );
	assertEquals(list[2], "Sunday" );
}

static void testInsertAtEnd() {
	avlList<const char*> list;
	list.insert(0, "Saturday");
	list.insert(1, "Friday");
	list.insert(2, "Thursday");
	list.insert(3, "Wednesday");
	assertEquals(list.size(), static_cast<size_t>(4));
	assertEquals(list[0], "Saturday" );
	assertEquals(list[1], "Friday"   );
	assertEquals(list[2], "Thursday" );
	assertEquals(list[3], "Wednesday");
}

static void testInsertAtMiddle() {
	avlList<const char*> list;
	list.insert(0, "Up");
	list.insert(1, "Down");
	list.insert(1, "Left");
	list.insert(2, "Right");
	list.insert(1, "Front");
	list.insert(2, "Back");
	assertEquals(list.size(), static_cast<size_t>(6));
	assertEquals(list[0], "Up"   );
	assertEquals(list[1], "Front");
	assertEquals(list[2], "Back" );
	assertEquals(list[3], "Left" );
	assertEquals(list[4], "Right");
	assertEquals(list[5], "Down" );
}

// Stresses the self-balancing mechanism
static void testInsertManyBeginning() {
	const long N = 300000;
	avlList<long> list;
	for (long i = 0; i < N; i++)
		list.push_back(i);
	for (long i = 0; i < N; i++)
		assertEquals(list[i], i);
}

static void testInsertManyEnd() {
	const long N = 300000;
	avlList<long> list;
	for (long i = N - 1; i >= 0; i--)
		list.insert(0, i);
	for (long i = 0; i < N; i++)
		assertEquals(list[i], i);
}

static void testErase()
{
	avlList<char> list;
    string str = "the quick brown fox jumped over the lazy dog";
    for (int s = 0; s < str.length(); s++)      list.push_back(str[s]);
    assertEquals(list.size(), str.length());
 
	assertEquals(list[ 2], 'e');  list.erase( 2);
	assertEquals(list[ 4], 'u');  list.erase( 4);
	assertEquals(list[ 3], 'q');  list.erase( 3);
	assertEquals(list[ 2], ' ');  list.erase( 2);
	assertEquals(list[12], 'f');  list.erase(12);
	assertEquals(list[11], ' ');  list.erase(11);
	assertEquals(list[10], 'n');  list.erase(10);
	assertEquals(list[ 9], 'w');  list.erase( 9);
	assertEquals(list[11], ' ');  list.erase(11);
	assertEquals(list[11], 'j');  list.erase(11);
	assertEquals(list[11], 'u');  list.erase(11);
	assertEquals(list[10], 'x');  list.erase(10);
	assertEquals(list[11], 'p');  list.erase(11);
	assertEquals(list[12], 'd');  list.erase(12);
	assertEquals(list[11], 'e');  list.erase(11);
	assertEquals(list[13], 'v');  list.erase(13);
	assertEquals(list[13], 'e');  list.erase(13);
	assertEquals(list[19], 'l');  list.erase(19);
	assertEquals(list[20], 'z');  list.erase(20);
	assertEquals(list[19], 'a');  list.erase(19);
	assertEquals(list[18], ' ');  list.erase(18);
	assertEquals(list[22], 'g');  list.erase(22);
 
	// list.checkStructure();
}

static void testClear() {
	avlList<int> list;
	for (int i = 0; i < 20; i++)
		list.push_back(i * i);
	
	list.clear();
	assertEquals(list.size(), static_cast<size_t>(0));
	
	list.push_back(- 1);
	list.push_back(- 8);
	list.push_back(-27);
	assertEquals(list.size(), static_cast<size_t>(3));
	assertEquals(list[0], - 1);
	assertEquals(list[1], - 8);
	assertEquals(list[2], -27);
}

void testIterator(){
	avlList<int> list;

	int n = 10000;

	for(int i=0; i<n; i++) list.push_back(i);

	avlList<int> :: iterator it = list.begin();
	int i=0;
	for(; it!=list.end(); ++it){
		assertEquals(*it, i);
		i++;
	}
}

int main(){
	
	try {
		testAdd();
		testSet();
		testInsertAtBeginning();
		testInsertAtEnd();
		testInsertAtMiddle();
		testInsertManyBeginning();
		testInsertManyEnd();
		testErase();
		testClear();
		testIterator();
		cout << "All test cases passed !";
	} 
	catch (string msg) {
		cout << msg << endl;
	}

}