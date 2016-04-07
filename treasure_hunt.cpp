/*
LOGIC : To store paths to all folders created separated by spaces in a 'paths' variable

LIMITATION : Does not work for Folder names with spaces in them.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
using namespace std;

//Add options to all distinct filepaths at the ith level
void addOptions(string &path, int &index, string option) {
	while(path.find(" ",index) != -1) {
		index = path.find(" ",index);
		path.replace(index,0,option+"/");
		index += option.length()+2;
	}
	index=0;
}

//Just so that I don't have to remember the syntax
void createFile(string file_path, string text) {
	ofstream o(file_path);
	o << text << endl;
}

//Create qi.txt and option folders in the folder given by 'path'
void fillFolder(string path, string question, int i, string option1, string option2) {
	mkdir((path + option1).c_str(),0700);
	mkdir((path + option2).c_str(),0700);
	createFile(path + "q" + to_string(i) + ".txt",question);
}

int main() {
	//i = Question Number
	int i = 1;

	//Make parent folder for the hunt
	mkdir("TreasureHunt",0700);

	//Inputs for each question spanning 6 lines
	string question, option1, option2, blank_line1, answer, blank_line2;

	//Paths stores all paths at the ith level separated by spaces
	string paths = "TreasureHunt/ ";

	//Variables used in the algorithm
	string path = "", path1 = "", path2 = "", answer_path = "TreasureHunt/";
	int start = 0, end = 1, index = 0;

	//One iteration = One question
	while(true) {

		//Take input one question at a time
		getline(cin,question);
		getline(cin,option1);
		getline(cin,option2);
		getline(cin,blank_line1);
		getline(cin,answer);
		getline(cin,blank_line2);

		//Check for end of input file
		if(option1 == "")
			break;

		//File path to place win.txt
		answer_path += answer + "/";

		//Pick distinct folder paths at the ith level and create q.txt and option folders
		while(paths.find(" ",start) != -1) {
			end = paths.find(" ",start);
			path = paths.substr(start,end-start);
			fillFolder(path,question,i,option1,option2);
			start = end + 1;
			end = start + 1;
		}

		//pathj = paths at (i-1)th level + option j
		path1 = paths;
		path2 = paths;
		addOptions(path1,index,option1);
		addOptions(path2,index,option2);
		paths = path1 + path2;

		//Reiteration conditions
		start = 0;
		end = 1;
		i++;
	}

	//Finally!
	createFile(answer_path + "win.txt","You Win!");
}