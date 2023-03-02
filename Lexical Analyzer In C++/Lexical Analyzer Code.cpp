#include<iostream>
#include<fstream>
using namespace std;

class TOKEN
{
	private:
	
		string LexemeName;
		string TokenName;
		int AttributeValue;
	
	public:
		
		TOKEN()
		{
			this->LexemeName = "";
			this->TokenName = "";
			this->AttributeValue = 0;
		}
		
		string getLexemeName()
		{
			return LexemeName;
		}
		
		string getTokenName()
		{
			return TokenName;
		}
		
		void setLexemeName(string LexemeName)
		{
			this->LexemeName = LexemeName;
		}
		
		void setTokenName(string TokenName)
		{
			this->TokenName = TokenName;
		}
		
		void setAttributeValue(int AttributeValue)
		{
			this->AttributeValue = AttributeValue;
		}
		
		int getAttributeValue()
		{
			return this->AttributeValue;
		}
		
		void Display()
		{
			cout<<"\nThe Lexeme is : " + this->getLexemeName();
			cout<<"\nToken Name is : " + this->getTokenName();
			cout<<"\nAttribute Value is : " << this->getAttributeValue() << endl;
		}
};

class NODE
{
	private:
		
		TOKEN Token = TOKEN();
		NODE *NextToken;
		
	public:
		
		TOKEN getToken() 
		{ 
			return this->Token; 
		}
	
		void setToken(TOKEN Token) 
		{
			this->Token.setLexemeName(Token.getLexemeName()); 
			this->Token.setTokenName(Token.getTokenName()); 
			this->Token.setAttributeValue(Token.getAttributeValue()); 
		}
		
	
		NODE *getNextToken() 
		{	
			return NextToken; 
		}
	
		void setNextToken(NODE *NextToken) 
		{
			this->NextToken = NextToken; 
		}
};

class SYMBOLTABLE
{
	private:
		
		NODE *HeadNode;
		NODE *CurrentNode;
		NODE *TraverseNode;
		int size;
		
	public:
		
		SYMBOLTABLE()
		{
			HeadNode = new NODE();
			HeadNode->setNextToken(NULL);
			CurrentNode = NULL;
			size = 0; 
		}
	
		int Size()
		{
			return size;
		}
	
		bool Empty()
		{
			if(size==0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		void Add(TOKEN Token)
	   	{
			NODE * NewNode = new NODE();
			NewNode->setToken(Token);
			if( CurrentNode != NULL ) 
			{
				NewNode->setNextToken(NULL);
				CurrentNode->setNextToken(NewNode);
				CurrentNode = NewNode;
			}
			else 
			{
				NewNode->setNextToken(NULL);
				HeadNode->setNextToken(NewNode);
				CurrentNode = NewNode;
			}
			size ++;
		}
		
		
		TOKEN Get(int Index)
 		{	
 			if(Index >=1 && Index<=size)
 			{
				TraverseNode = HeadNode;
				for(int i=1 ; i<=Index && i<=size ; i++ )
				{
					TraverseNode=TraverseNode->getNextToken();
				}
	
				return TraverseNode->getToken();
			}
			else
			{
				cout<<"Error !!! Can't Get Invalid Index [ "<<Index<<" ].\n";
			}
		}
	
		void Display()
		{	
			cout<<"[TOKENS SYMBOL TABLE FOR INPUT FILE]\n";
		
			if(size >= 1)
			{
				cout<<endl;
				for(int i=1 ; i<=size ; i++)
				{
					Get(i).Display();
				}
				cout<<endl;
				cout<<"[TOKENS HAVE BEEN PRODUCEDS SUCCESSFULLY]"<<endl;
			}
			else
			{
				cout<<"Your Symbol Table is Empty !!!\n";
			}
		}
		
		void StoreInFile(string FileName)
		{
			fstream OutFile;
			OutFile.open(FileName+".txt" , ios::app);
			OutFile<<"[TOKENS SYMBOL TABLE FOR INPUT FILE]\n";
			
			if(size >= 1)
			{
				cout<<endl;
				for(int i=1 ; i<=size ; i++)
				{
					TOKEN Temp = Get(i);
					OutFile<<"\nThe Lexeme is : " + Temp.getLexemeName();
					OutFile<<"\nToken Name is : " + Temp.getTokenName();
					OutFile<<"\nAttributeValue is : " << Temp.getAttributeValue() << endl;
				}
				OutFile<<endl;
				OutFile<<"[TOKENS HAVE BEEN PRODUCEDS SUCCESSFULLY]"<<endl;
				
			}
			else
			{
				cout<<"Your Symbol Table is Empty !!!\n";
			}
			
			OutFile.close();
		}
};

class BUFFER
{
	private:
	
		string KeyWords[20] = {"int" , "float" , "double" , "short" , "char" ,
		"bool" , "if" , "else" , "while" , "for" , "break" , "continue" , "class" ,
		"long" , "string" , "const" , "static" , "do" , "return" , "default"};
		string Buffer;
		int Forward;
		int Begin;
		int TGs[9] = {0 , 9 , 13 , 21 , 23 , 26 , 28 , 31 , 33};
		int TGCounter;
	
	public:
		
		BUFFER()
		{
			
		}
		
		BUFFER(string FileName)
		{
			this->Forward=0;
			this->Begin=0;
			this->TGCounter=0;
			this->Buffer = this->InitializeBuffer(FileName);
		}	
	
	private:
		
		string InitializeBuffer(string FileName)
		{
			string Temp = "" , Temp1;
			fstream InFile;
			InFile.open(FileName , ios::in);
			if(InFile)
			{
				while(!InFile.eof())
				{
					getline(InFile , Temp1);
					Temp += Temp1;
				}
				InFile.close();
				return Temp;
			}
			else
			{
				cout<<"Error !!! Input File Is Not Found.";
				cout<<"\nPlease, Enter The Valid Input File Name.";
				cout<<"\nAnd Run The Program Again....\n";
				exit(0);
			}
		}
		
	public:
		
		void setTGCounter(int TGCounter)
		{
			this->TGCounter = TGCounter;
		}
			
		char getChar()
		{
			Forward++;
			return Buffer[Forward-1];
		}
		
		int TokenFail()
		{
			Forward = Begin;
			TGCounter++;
			return TGs[TGCounter];
		}
		
		void Retract()
		{
			Forward--;	
		}
		
		void TokenSuccess()
		{
			Begin = Forward;	
		}
		
		bool CheckKeyword(string String)
		{
			for(int i=0 ; i<20 ; i++)
			{
				if(KeyWords[i].compare(String) == 0)
				{
					return true;
				}
			}
			return false;
		}	
		
		bool Stop()
		{	
			if(Forward == Buffer.size())
			{	
				return false;
			}
			else
			{
				return true;
			}
		}
};

class TGS
{
	private:
		
		SYMBOLTABLE SymbolTable;
		BUFFER Buffer;
		TOKEN RetToken;
		string String;
		bool Loop;
		int State , Counter;
		
	public:
	
		TGS(string FileName)
		{
			this->SymbolTable = SYMBOLTABLE();
			this->Buffer = BUFFER(FileName);
			this->RetToken = TOKEN();
			this->String = "";
			this->Counter = 1;
		}
		
		void DisplaySymbolTable(string FileName)
		{
			SymbolTable.Display();
			SymbolTable.StoreInFile(FileName);
		}
		
		int RelationalOp(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;	
					
					case 0:
						this->Buffer.setTGCounter(State);
						Char = this->Buffer.getChar();
						if(Char == '<')this->State=1;
						else if(Char == '=')this->State=5;
						else if(Char == '>')this->State=6;
						else return this->State=this->Buffer.TokenFail();
					break;		
								
					case 1:
						Char = this->Buffer.getChar();
						if(Char == '=')this->State=2;
						else if(Char == '>')this->State=3;
						else this->State=4;
					break;
					
					case 2:
						RetToken.setLexemeName("RelOp");
						RetToken.setTokenName("LE");
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State=-1;
					break; 
					
					case 3:
						RetToken.setLexemeName("RelOp");
						RetToken.setTokenName("NE");
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State=-1;
					break;
				
					case 4:
						this->Buffer.Retract();
						RetToken.setLexemeName("RelOp");
						RetToken.setTokenName("LT");
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State=-1;
					break;
				
					case 5:
						RetToken.setLexemeName("RelOp");
						RetToken.setTokenName("EQ");
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State=-1;
					break;
					
					case 6:
						Char = this->Buffer.getChar();
						if(Char == '=')this->State=7;
						else this->State=8;
					break;
				
					case 7:	
						RetToken.setLexemeName("RelOp");
						RetToken.setTokenName("GE");
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State=-1;
					break;
				
					case 8:
						this->Buffer.Retract();
						RetToken.setLexemeName("RelOp");
						RetToken.setTokenName("GT");
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State=-1;
					break;			
				}
			}
			return -1;		
		}
		
		int IdKeyword(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;	
					
					case 9:
						this->String = "";
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if((Temp>=65 && Temp<=90) ||  (Temp>=97 && Temp<=122))
						{
							this->String = Char;
							this->State=10;
						}
						else return this->State=this->Buffer.TokenFail();
					break;
			
					case 10:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if((Temp>=65 && Temp<=90) ||  (Temp>=97 && Temp<=122) || (Temp>=48 && Temp<=57))
						{
							this->String += Char;
							this->State=10;
						}
						else this->State = 11;
					break;
			
					case 11:	
						if(this->Buffer.CheckKeyword(this->String) == true)
						{
							this->State = 12;
						}
						else
						{
							this->Buffer.Retract();
							RetToken.setLexemeName("Identifier");
							RetToken.setTokenName(this->String);
							RetToken.setAttributeValue(Counter);
							SymbolTable.Add(RetToken);
							this->Buffer.TokenSuccess();
							this->State = -1;
						}
						break;
			
					case 12:
						this->Buffer.Retract();
						RetToken.setLexemeName("Keyword");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;						
				}		
			}
			return -1;
		}
		
		int Digits(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;	
					
					case 13:
						this->String = "";
						Char = this->Buffer.getChar();
						this->String = Char;
						Temp = int(Char);
						if(Temp>=48 && Temp<=57)this->State = 14;
						else if(Char == '.')this->State = 15;
						else return this->State  = this->Buffer.TokenFail();
					break;
					
					case 14:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp>=48 && Temp<=57){this->String += Char;State = 14;}
						else if(Char == '.'){this->String += Char;this->State = 15;}
						else if(Char == 'E'){this->String += Char;this->State = 17;}
						else this->State  = 20;
					break;
					
					case 15:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp>=48 && Temp<=57){this->String += Char;this->State = 16;}
						//Missing Case Require
					break;
					
					case 16:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp>=48 && Temp<=57){this->String += Char;this->State = 16;}
						else if(Char == 'E'){this->String += Char;this->State = 17;}
						else this->State = 20;
					break;
					
					case 17:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Char == '-' || Char == '+'){this->String += Char;this->State = 18;}
						else if(Temp>=48 && Temp<=57){this->String += Char;this->State = 19;}
						//Missing Case Require
					break;
					
					case 18:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp>=48 && Temp<=57){this->String += Char;this->State = 19;}
						//Missing Case Require
					break;
					
					case 19:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp>=48 && Temp<=57){this->String += Char;this->State = 19;}
						else this->State = 20;
					break;
					
					case 20:
						this->Buffer.Retract();
						RetToken.setLexemeName("Number");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;
				}		
			}
			return -1;
		}
		
		int ArithmaticOp(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;
					
					case 21:
						this->String = "";
						Char = this->Buffer.getChar();
						if(Char == '+' || Char == '-' || Char == '*' || Char == '/' || Char == '%')
						{
							this->String = Char;
							this->State = 22;
						}
						else return this->State = this->Buffer.TokenFail();
					break;
						
					case 22:
						RetToken.setLexemeName("ArithOp");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;	
				}
			}
			return -1;
		}
		
		int LogicalOp(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;
					
					case 23:
						this->String = "";
						Char = this->Buffer.getChar();
						if(Char == '&' || Char == '|'){this->String = Char;this->State = 24;}
						else if(Char == '!'){this->String = Char;this->State = 25;}
						else return this->State = this->Buffer.TokenFail();
					break;
					
					case 24:
						Char = this->Buffer.getChar();
						if(Char == '&' && !(this->String.compare("&"))){this->String += Char;this->State = 25;}
						else if(Char == '|' && !(this->String.compare("|"))){this->String += Char;this->State = 25;}
						else {this->Buffer.Retract();this->Buffer.Retract();return this->State = 33;}
					break;
					
					case 25:
						RetToken.setLexemeName("LogicOp");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;
				}
			}
			return -1;		
		}
		
		int Brackets(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;
					
					case 26:
						this->String = "";
						Char = this->Buffer.getChar();
						if(Char == '(' || Char == ')' || Char == '{' || Char == '}' || Char == '[' || Char == ']') 
						{
							this->String = Char;
							this->State = 27;
						}
						else return this->State = this->Buffer.TokenFail();
					break;
				
					case 27:
						RetToken.setLexemeName("BracKet");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;				
				}		
			}
			return -1;
		}
		
		int Delimiters(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;
					
					case 28:
						this->String = "";
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp == 9){this->String = "VT,";this->State = 29;}
						else if(Temp == 10){this->String += "LF,";this->State = 29;}
						else if(Temp == 11){this->String += "HT,";this->State = 29;}
						else if(Temp == 32){this->String += "SPC,";this->State = 29;}
						else return this->State = this->Buffer.TokenFail();
					break;
					
					case 29:
						Char = this->Buffer.getChar();
						Temp = int(Char);
						if(Temp == 9){this->String += "VT,";this->State = 29;}
						else if(Temp == 10){this->String += "LF,";this->State = 29;}
						else if(Temp == 11){this->String += "HT,";this->State = 29;}
						else if(Temp == 32){this->String += "SPC,";this->State = 29;}
						else this->State = 30;
					break;
					
					case 30:
						this->Buffer.Retract();
						RetToken.setLexemeName("Delimiter");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;		
				}		
			}
			return -1;
		}
		
		int Puntuaters(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;
					
					case 31:
						this->String = "";
						Char = this->Buffer.getChar();
						if(Char == ';' || Char == ',' || Char == ':'){this->String = Char;this->State = 32;}
						else return this->State = this->Buffer.TokenFail();	
					break;
			
					case 32:
						RetToken.setLexemeName("Puntuator");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;			
				}		
			}
			return -1;
		}
		
		int NotInLanguage(int State)
		{
			this->Loop = true;
			this->State = State;
			int Temp;
			char Char;
			
			while(this->Loop)
			{	
				switch(this->State)
				{
					case -1:
						Counter++;
						if(this->Buffer.Stop())
						{
							return this->State = 0;
						}
						else
						{
							this->Loop = false;
						}
					break;
					
					case 33:
						this->String = "";
						Char = this->Buffer.getChar();
						this->String = Char;
						RetToken.setLexemeName("NotInLang");
						RetToken.setTokenName(this->String);
						RetToken.setAttributeValue(Counter);
						SymbolTable.Add(RetToken);
						this->Buffer.TokenSuccess();
						this->State = -1;
					break;			
				}		
			}
			return -1;
		}		
};


int main()
{
	
	string InputFile , OutputFile;

	cout<<"\t\t[LEXICAL ANALYZER]"<<endl<<endl;
	
	cout<<"Enter the name of the Input File : ";
	cin>>InputFile;
	cout<<"\nEnter the name of the Output File : ";
	cin>>OutputFile;
	
	cout<<endl<<endl;
	
	TGS Machines = TGS(InputFile);
	bool Loop = true;
	int State = 0;
	
	while(Loop)
	{	
		switch(State)
		{
			case -1:
				Loop = false;
			break;	

			case 0:
				State = Machines.RelationalOp(State);
			break;	
			
			case 9:
				State = Machines.IdKeyword(State);
			break;
			
			case 13:
				State = Machines.Digits(State);
			break;
			
			case 21:
				State = Machines.ArithmaticOp(State);
			break;		
				
			case 23:
				State = Machines.LogicalOp(State);
			break;
			
			case 26:
				State = Machines.Brackets(State);
			break;
			
			case 28:
				State = Machines.Delimiters(State);
			break;
			
			case 31:
				State = Machines.Puntuaters(State);
			break;
			
			case 33:
				State = Machines.NotInLanguage(State);
			break;						
		}	
	}
	
	Machines.DisplaySymbolTable(OutputFile);

	return 0;
}
