#include<iostream>
#include<ext/hash_map>
using namespace std;
using namespace __gnu_cxx;
class Test
{
private:
	int tempid;
	static int uniqueid;
public:
	void gainId(void)
	{
		tempid = ++ uniqueid;
	}
	const int getId(void) const
	{
		return tempid;
	}
};

int Test::uniqueid = 0;
int main(void)
{
    hash_map<int,Test*> hashMap;
	Test test;
	test.gainId();
	hash_map<int,Test*>::const_iterator test_it = hashMap.find(test.getId());
	if(test_it != hashMap.end())
	{
		cout<<"insert again:"<<test.getId()<<endl;
		return 1;
	}
	typedef hash_map<int,Test*>::value_type pair;
	hashMap.insert(pair(test.getId(),&test));
	test_it = hashMap.find(test.getId());
	if(test_it == hashMap.end())
	{
		cout<<"error not found:"<<test.getId()<<endl;
		return 1;
	}
	cout<<"find the key:"<<test_it->first<<endl;
	return 0;
}
