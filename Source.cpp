#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>

const int N = 2;

/*enum class Month {
	January,
	February,
	March,
	April,
	May,
	Jun,
	July,
	August,
	September,
	October,
	November,
	December
};
*/


struct birthday {
	int day;
	int m;
	int year;
};

struct student{
	std::string name;
	std::string surname;
	birthday b{ 0,0,0 };
	int numOfMarks{};
	float* mark{};
	student* next{ NULL };
	student* prev{ NULL };
};
void RW(std::string fileName, std::string *str);

void RW(std::string fileName, student* head);

void RW(std::string fileName, std::string *str)
{
	std::ofstream outf(fileName, std::ios::app);
	outf << *str << std::endl;
	outf.close();
}

void RW(std::string fileName, student* head)
{
	student* current = head;
	std::ofstream outf(fileName, std::ios::binary);
	while (current->next)
	{
		///outf << current->surname << '\t' << current->name << '\t' << current->b.day << "\t" << current->b.m << "\t" << current->b.year << std::endl;
		outf.write((char *)current, sizeof(student));
		current = current->next;
	}
	outf.close();
}

void RD(std::string fileName);
student* RD(std::string fileName, birthday bb);

void RD(std::string fileName)
{
	std::ifstream inf{ fileName };
	while (inf)
	{
		std::string str;
		std::getline(inf, str);
		std::cout << str << std::endl;
	}
}

student* RD(std::string fileName, birthday bb)
{
	student* head{ new student };
	student* current = head;
	std::ifstream inf{ fileName };
	while (inf)
	{
		inf.read((char *)current, sizeof(student));
		current->next = new student;
		if (current->b.year < bb.year)
		{
			student* temp = current;
			current = current->next;
			current->prev = temp;
			current->next = NULL;
		}
		else if (current->b.year == bb.year)
		{
			if (current->b.m < bb.m)
			{
				student* temp = current;
				current = current->next;
				current->prev = temp;
				current->next = NULL;
			}
			else if (current->b.m == bb.m)
			{
				if (current->b.day <= bb.day)
				{
					student* temp = current;
					current = current->next;
					current->prev = temp;
					current->next = NULL;
				}
			}
		}
	}
	current->prev->next = NULL;
	delete(current);
	return head;
}



int main()
{
	student* stud{ new student };
	student* head = stud;
	student* current = head;
	if (stud)
	{
		for (int i{ 0 }; i < N; i++)
		{
			std::cout << "Enter name: ";
			std::cin >> current->name;
			std::cout << "Enter surname: ";
			std::cin >> current->surname;
			std::cout << "Enter birth year: ";
			std::cin >> current->b.year;
			std::cout << "Enter birth month: ";
			std::cin >> current->b.m;
			std::cout << "Enter birth day: ";
			std::cin >> current->b.day;
			std::cout << "Enter number of marks: ";
			int num{ 0 };
			std::cin >> num;
			current->numOfMarks = num;
			current->mark = new float[num];
			for (int i{ 0 }; i < num; i++)
			{
				std::cin >> current->mark[i];
			}
			student* temp = current;
			current->next = new student;
			current = current->next;
			current->prev = temp;
			current->next = NULL;
			//std::cout << stud->surname << '\t' << stud->name << '\t' << stud->b.day << "." << stud->b.m << "." << stud->b.year << std::endl;
		}
	}
	current = head;
	/*while (current->next)
	{
		std::cout << current->surname << '\t' << current->name << '\t' << current->b.day << "." << current->b.m << "." << current->b.year << std::endl;
		current = current->next;

	}*/
	//std::cout << head->surname << '\t' << head->name << '\t' << head->b.day << "." << head->b.m << "." << head->b.year << std::endl;
	std::string str{};
	std::stringstream strss;
	while (current->next)
	{
		
		strss << current->name << '\t' << current->surname << '\t' << current->b.day << "." << current->b.m << "." << current->b.year << std::endl;

		std::getline(strss,str);
		RW("info.txt", &str);
		current = current->next;
	}

	std::ofstream debts{};
	std::ofstream excells{};
	debts.open("Debtors.txt");
	excells.open("Excelents.txt");
	current = head;
	while (current->next)
	{ 
		bool excellent{true};
		for (int i{}; i < current->numOfMarks; i++)
		{
			if (current->mark[i] == 2)
			{
				debts << current->surname << '\t' << current->name << '\t' << current->b.day << "\t" << current->b.m << "\t" << current->b.year << std::endl;
				excellent = false;
				break;
			}
			else if (current->mark[i] < 5)
			{
				excellent = false;
			}
			
		}
		if (excellent)
		{
			excells << current->surname << '\t' << current->name << '\t' << current->b.day << "\t" << current->b.m << "\t" << current->b.year << std::endl;
		}
		current = current->next;
	}
	debts.close();
	excells.close();
	
	RD("info.txt");
	birthday bb{ };
	std::cout << "Enter day: ";
	std::cin >> bb.day;
	std::cout << "Enter month: ";
	std::cin >> bb.m;
	std::cout << "Enter year: ";
	std::cin >> bb.year;
	RW("info.dat", head);
	head = NULL;
	head = RD("info.dat", bb);
	current = head;
	while (current->next)
	{
		std::cout << current->surname << '\t' << current->name << '\t' << current->b.day << "." << current->b.m << "." << current->b.year << std::endl;
		current = current->next;
	}
	return 0;
}