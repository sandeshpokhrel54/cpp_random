#include<iostream>
#include<string>
#include<vector>
#define ALPHABET 256
#define MAX(a,b) ((a<b) ? b:a)
//KMP Search O(m+n)
std::vector<int> kmpTable(std::string subtext) {

	/*std::cout << subtext;*/
	std::vector<int> table(subtext.size(),0);
	/*std::cout << table.size();*/
	if (subtext.size() == 0)
		std::cout << "0 length subtext";

	int c = 0;
	int j = 1;

	while (j < subtext.size())
	{
		if (subtext[j] == subtext[c])
		{
			table[j] = c + 1;
			c++;
			j++;
		}

		else if (c == 0)
		{
			table[j] = 0;
			j++;
		}
		else
			c = table[c - 1];
	}

	return table;
}
std::vector<int> kmpSearch(std::string text, std::string subtext)
{
	int j = 0, k = 0, matches=0;
	std::vector<int> Table = kmpTable(subtext);
	std::vector<int> locs;

	while (j < text.size())
	{
		if (text[j] == subtext[k])
			j++, k++;
		else
		{
			if (k == 0)
				j++;
			else
				k = Table[k - 1];

		}

		if (k == subtext.size())
		{
			locs.push_back(j-subtext.size());
			matches++;
		}
	}

	return locs;
}

//simple search O(mn)
std::vector<int> simpleSearch(std::string text, std::string subtext)
{
	int i = 0, k = 0;
	std::vector<int> locs;

	while (i < text.length())
	{

		if (text[i] == subtext[0])
		{
			//start comparing one by one
			k = 0;
			for (auto x : std::as_const(subtext))
			{

				if (x == text[i++])
				{
					k++;
				}

				if (k == subtext.length())
				{
					locs.push_back(i-k);
				}
			}
		}

		else
		{
			i++;
		}
	}

	return locs;
}


//Rabin Karp Algorithm O(mn)
unsigned long long int hash_func(std::string subtext, unsigned long long int prevHash, char prev_char, bool initial = false)
{
	//int prime_modulo = 101;
	auto len = subtext.size();
	if (initial)
	{
		prevHash = 0;
		for(unsigned int i=0; i<len; i++)
		{
			prevHash += pow(256, i) * int(subtext[len - i - 1]);
		}
	}
	else
	{
		//rolling hash
		if (prev_char != NULL)
		{
			prevHash = prevHash - pow(256, len - 1) * int(prev_char);
			prevHash *= 256; //shifting characters
			prevHash += int(subtext[len - 1]);
		}
		else
			std::cout << "null value of removed char" << std::endl;
	}
	return prevHash;
}
std::vector<int> Rabin_Karp(std::string text, std::string subtext)
{
	std::vector<int> locs;
	auto t_len = text.size();
	auto s_len = subtext.size();

	//auto first_check = text.substr(i)
	auto subtext_hash = hash_func(subtext, 0, NULL, true);
	auto t_hash = hash_func(text.substr(0, s_len), 0, NULL, true);

	auto deep_check = [](std::string text, std::string subtext, int loc = 0) {

		for (unsigned int j = 0; j < subtext.size(); j++)
		{
			if (!(subtext[j] == text[loc + j]))
			{
				return false;
			}
		}
		return true;
	};

	

	if (subtext_hash == t_hash)
	{
		//check char by char
		auto check = deep_check(text, subtext, 0);
		if (check)
			locs.push_back(0);
	}

	for (unsigned int i = 1; i < t_len - s_len+1; i++)
	{

		t_hash = hash_func(text.substr(i, s_len), t_hash, text[i - 1]);	
		if (subtext_hash == t_hash)
		{
			auto d_check = deep_check(text, subtext, i);
			if (d_check)
				locs.push_back(i);
		}
	}

	return locs;
}


//Bayor Moore Algorithm
std::vector<int> bad_char_heuristic(std::string subtext)
{
	auto s_size = subtext.size();
	std::vector<int> bad_table(ALPHABET, s_size);
	std::cout << bad_table.size()<<"\n";

	for (int i = 0; i < s_size; i++)
	{
		bad_table[int(subtext[i])] =  s_size-i-1;
	}

	//for (auto i : bad_table)
	//	std::cout << i << "\n";
	return bad_table;
}
std::vector<int> Bayor_Moore(std::string text, std::string subtext)
{
	std::vector<int> locs;
	std::vector<int> bad_table = bad_char_heuristic(subtext);
	auto t_size = text.size();
	auto s_size = subtext.size();
	/*std::cout << bad_table[int('d')];*/
	std::cout << t_size;
	
	int shift = 0;
	int i = s_size - 1;
	while (i < t_size)
	{
		int j = s_size - 1;
		while (j >= 0 && (text[i] == subtext[j]))
		{
			//std::cout << "entering";
			i--;
			j--;
		}

		if (j < 0)
		{
			//std::cout << "found one";
			locs.push_back(i+1);
			i += 2*s_size+1;
			continue;
		}

		shift = MAX(bad_table[int(text[i])],1);
		//std::cout << shift;
		//std::cout << i;
		i += shift;
		//std::cout << i << "\n";
	}
	return locs;
}


int main()
{
	std::string text = "I am a god, Greek god, you puny waste of flesh. God of all gods, prepare to bow before me or meet the dirt under your very feet. god";
	std::string subtext = "god";

	//std::vector<int> loc = simpleSearch(text, subtext);
	
	std::string test1 = "abacababa";
	std::string test2 = "ACABACACAD";


	//std::vector<int> T = kmpSearch(text, subtext);
	std::vector<int> T = Rabin_Karp(text, subtext);
	//auto T = bad_char_heuristic("dedede");
	//auto T = Bayor_Moore(text, subtext);
	//T = kmpSearchWiki(text, subtext);
	//T = kmpSearch(text, subtext);
	//T = simpleSearch(text, subtext);


	//std::string c = "abr";
	//auto first_hash = hash_func(c, 0, NULL, true);
	//std::cout << first_hash<<std::endl;
	//auto check = hash_func("bra", first_hash, c[0]);
	//std::cout << check;

		for (auto i : T)
		{
			std::cout << i<<"\n";
		}

}