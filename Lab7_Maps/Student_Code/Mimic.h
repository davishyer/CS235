#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "MimicInterface.h"
using namespace std;


class Mimic : public MimicInterface
{
private:
	string key1;
	string key2;
	string val;

	struct Node
	{
		string key;
		vector<string> value;
		Node* next;

		Node()
		{
			key = "";
			value.clear();
			next = NULL;
		};
		Node(string prefix, string suffix)
		{
			key = prefix;
			value.push_back(suffix);
			next = NULL;
		};
		~Node(){};
	};

	Node* head;

	void add(string key, string value)
	{
		if(head == NULL)
		{
			head = new Node(key, value);
			return;
		}
		else
		{
			Node* n = head;
			while(n->next != NULL)
			{
				if(n->key == key)
				{
					n->value.push_back(value);
					return;
				}
				n = n->next;
			}
			if(n->key == key)
			{
				n->value.push_back(value);
				return;
			}
			else
			{
				n->next = new Node(key, value);
			}
		}
		return;
	}

	public:
		Mimic()
		{
			head = NULL;
		}
		~Mimic(){}

		//Part 1--------------------------------------------------------------
		/**
		 * createMap
		 *
		 * Creates a prefix-suffix map based on the input text.
		 *
		 * Go through the input text and examine each group of 3 words. Refer
		 * to the first two words as the "prefix" and the third word as the
		 * "suffix". Create a map that associates each prefix with each suffix.
		 *  If you encounter a prefix that has been read already, add the new
		 *  suffix to the list of suffixes already associated with that prefix;
		 *  in this manner, each prefix can be associated with multiple
		 *  suffixes and even multiple copies of the same suffix. Note that
		 *  the input texts will only contain words separated by spaces.  Also
		 *  note that the last two word prefix in the text should be associated
		 *  with the suffix "THE_END".
		 *
		 * @param input
		 * 		the sample text to be mimicked
		 */
		void createMap(string input)
		{
			stringstream ss;
			ss << input;
			ss >> key1;
			ss >> key2;
			while(ss >> val)
			{
				add((key1 + " " + key2), val);
				if(val == "THE_END")
				{
					break;
				}
				key1 = key2;
				key2 = val;
			}
			add((key1 + " " + key2), "THE_END");
			return;
		}

		/**
		 * getSuffixList
		 *
		 * Returns the list of suffixes associated with the given prefix.
		 * Returns an empty vector if the given prefix is not in the map or no
		 * map has been created yet.
		 *
		 * @param prefix
		 * 		the prefix to be found
		 * @return a list of suffixes associated with the given prefix if the
		 * 		prefix is found; an empty vector otherwise
		 */
		vector<string> getSuffixList(string prefix)
		{
			if(head == NULL)
			{
				vector<string> empty;
				return empty;
			}
			Node* n = head;
			while(n->next != NULL)
			{
				if(n->key == prefix)
				{
					return n->value;
				}
				n = n->next;
			}
			if(n->key == prefix)
			{
				return n->value;
			}
			vector<string> empty;
			return empty;
		}

		//Part 2--------------------------------------------------------------
		/**
		 * generateText
		 *
		 * Generates random text using the map created by the createMap method.
		 *
		 * To generate the new text, start with the first prefix that was read
		 * and randomly select one of the suffixes associated with that prefix.
		 * The next prefix is the second word from the previous prefix and the
		 * selected suffix. Continue selecting random suffixes and building the
		 * next prefix until the suffix "THE_END" is selected. The token
		 * "THE_END" should not be returned as part of your generated text.
		 *
		 * @return random text generated using the map created with the sample
		 * 		text; an empty string if no map has been created yet
		 */
		string generateText()
		{
			if(head == NULL)
			{
				string empty = "";
				return empty;
			}
			Node* n = head;
			string temp;
			string temp2;
			string output = n->key;
			int size = n->value.size();
			temp = n->value[rand() % size];
			while(temp != "THE_END")
			{
				stringstream ss;
				ss << output;
				while(ss >> temp2);
				temp2 = temp2 + " " + temp;
				output = output + " " + temp;
				n = head;
				while(n->next != NULL)
				{
					if(n->key == temp2)
					{
						break;
					}
					else
					{
						n = n->next;
					}
				}
				size = n->value.size();
				temp = n->value[rand() % size];
			}
			return output;
		}
};
