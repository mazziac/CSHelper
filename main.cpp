#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream checkFile(string& fileName){
	ifstream file(fileName);
	if(!file){
		cout << "File: " << fileName << " does not exist\n" 
			 << "Terminating program" << '\n';
		exit(0);
	}
	return file;
}

void swap(string& block, int source, int dest){
	char s = block[source];
	char d = block[dest];
	block[source] = d;
	block[dest] = s;
}

string blockXOR(string& block, string& key) {
	string crypted;
	for(int i = 0; i < 8; i++){
		crypted += block[i]^key[i];	
	}	
	return crypted;
}

string readKeyFile(string& keyFileName){
	ifstream keyFile = checkFile(keyFileName);
	char c;
	string key = "";
	while(keyFile.get(c)){
		//cout << "reading keyfile char : " << c << endl;
		key += c;
	}	
	return key;
}

void swapOperation(string& out, string& key){
	//swap if needed
	int start = 0;
	int end = out.length()-1;
	int kP = 0;
	while(start != end && start < end){
		if(kP == 8)
			kP = 0; //reset if past the key length
		if(key[kP] % 2 == 1){
			swap(out, start, end);
			end--; //increment end if we swap
		} 
		start++; //always increment start
		kP++; //incement the keyPointer
	}
}

string blockEncrypt(ifstream& inFile, string& key){
	//File will come in as 8-bit(1 byte)sequences
	char c; //Char is 1 Byte, use this to read in the bytes
	string block = ""; //To read the blocks
	string out; //To hold the encypted big block
	while(inFile.get(c)){
		block += c;
		if(block.length() == 8){
			out += blockXOR(block,key); //block algorithm
			block = ""; //reset block		
		}
	}
	
	//end of the file, check if we need to pad
	if(block.length() != 8){
		while(block.length() != 8){ //pad to 8 bits
			block += 0x80;
		}
		out += blockXOR(block,key);
	}
	//Swap things
	swapOperation(out,key);		
	return out;
}

string blockDecrypt(ifstream& inFile, string& key){
	//read the file first
	char c;
	string encrypted = "";
	while(inFile.get(c)){
		encrypted += c;	
	}
	//then swap
	swapOperation(encrypted,key);
	//XOR block by block
	string block = "";
	string out = "";
	int length = encrypted.length();
	for(int i = 0; i < length; i++){
		block += encrypted[i];
		if(block.length() == 8){
			out += blockXOR(block, key);
			block = ""; //reset the block
		}	
	}
	//remove padding
	int end = out.length()-1;
	int lastPad = -1;
	for(int i = end; i > end-8; i--){ //check only the last 8 bits
		if((int) out[i] >= 128 || (int) out[i] < 0){ //if not in ascii
			lastPad = i;
		}
	}  
	//if we found padding, remove it
	if(lastPad != -1){
		out.erase(lastPad,end);
	}	
	return out;
}

string block(string& inFileName, string& keyFileName, char mode){
	ifstream inFile = checkFile(inFileName);
	string key = readKeyFile(keyFileName);
	if(mode == 'E'){
		return blockEncrypt(inFile, key);		
	} else if(mode == 'D'){ 
		return blockDecrypt(inFile, key);
	} else { 
		cout << "Please give mode 'E', or 'D' " << " you gave: " << mode 
			 << "\nTerminating program" << '\n';
		exit(0);
	}
}

string stream(string& inFileName,string& keyFileName){
	//read the key
	string key = readKeyFile(keyFileName);
	//get the file
	ifstream inFile = checkFile(inFileName);
	char c;
	string out;
	int index = 0;
	int keySize = key.size(); 
	while(inFile.get(c)){
		int c1 = c ^ key[index]; //XOR
		out += c1;
		//increment index, and check if we are at end of key
		if(++index == keySize)
			index = 0; //reset if so 
	}	
	return out;
}

void writeToFile(string& out, string& outFileName){
	//write out to file
	ofstream outFile(outFileName);
	outFile << out;
}

int main(int argc, char* argv[]){
	//checks
	if(argc != 6){
		cout << "Please give 5 arguments, you gave: " << argc-1 << '\n'
			 << "Terminating program" << '\n';
		exit(0);
	}
	//What kind of encryption?
	string out = "";
	//First arg is the prog name
	char type = argv[1][0];
	string inFileName = argv[2];
	string outFileName = argv[3];
	string keyFileName = argv[4];
	char mode = argv[5][0];
	if(type == 'B'){ //Block cipher
		out = block(inFileName,keyFileName,mode);		
	} else if(type == 'S'){ //Stream cipher
		out = stream(inFileName,keyFileName);
	} else {
		cout << "Please give either B or S for first argument, you gave: " 
			 << type << '\n'
			 << "Terminating program" << '\n';
		exit(0);
	}
	//write out to file;
	writeToFile(out,outFileName);
	
	return 0;
}
