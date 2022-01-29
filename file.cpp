#include<iostream>
#include <vector>//Vector is a collection type, helps to store differetn type of class objects
#include <map>
#include <string>
#include <fstream>
#include <queue>
using namespace std;
int nNOS = 0;
class CStudent
{
	int m_nRegNo, m_nTotalMarks;
	string m_strName;
public:
	CStudent()
	{
		m_nRegNo = 0;
		m_nTotalMarks = 0;
		m_strName = "";
	}

	void GetData()
	{
		cout << "Enter the Register Number, Name and Total Marks";
		cin >> m_nRegNo >> m_strName >> m_nTotalMarks;
	}

	void ShowData()
	{
		cout << "\nRegister Number :" << m_nRegNo << "\tName :" << m_strName << "\tTotal Marks :";
	}

	int Search(std::string s)
	{
		if (m_strName == s)
		{
			return 1;
		}
	}

	void EditTotalMark()
	{
		cout << "Enter the Total Marks of" << m_strName;
		cin >> m_nTotalMarks;
	}
};

void WriteToFile(string sFileName, const std::vector<CStudent*>& vCollection);


void ReadFromFile(string sFileName, std::vector<CStudent*>& vCollection);

int main()
{
	int nNum;
	std::vector<CStudent*> vStudentCollection;
	CStudent* pStudent = NULL;
	for (int n = 1; n < nNum; ++n)
	{
		CStudent* pStudent = new CStudent;
		pStudent->GetData();
		vStudentCollection.push_back(pStudent);
	}
	nNOS += nNum;
	WriteToFile("Student.dat", vStudentCollection);
	vStudentCollection.clear();//Empty the collection object
	ReadFromFile("Student.dat", vStudentCollection);
	for (int i = 0; i < vStudentCollection.size(); ++i)
	{
		pStudent = vStudentCollection[i];
		pStudent->ShowData();
	}

	cout << "Enter the name of the student to change the total mark";
	int nIndex = 0;
	string strName;
	cin >> strName;
	for (nIndex = 0; nIndex < vStudentCollection.size(); ++nIndex)
	{
		pStudent = vStudentCollection[nIndex];
		if (pStudent->Search(strName) == 1)
			break;
	}
	pStudent = vStudentCollection[nIndex];
	pStudent->EditTotalMark();
	WriteToFile("Student.dat", vStudentCollection);
	for (int i = 0; i < vStudentCollection.size(); ++i)
	{
		pStudent = vStudentCollection[i];
		pStudent->ShowData();
	}
	vStudentCollection.clear();
}

void WriteToFile(string sFileName, const vector <CStudent*> & vCollection)
{
	fstream oFileStream;//Create a file object
	oFileStream.open(sFileName, ios::out| ios::binary); //Open the file for writing

	if (false == oFileStream.good())//To check if the file is opend or not
		return;  //Check for the negative condition and exit

	CStudent* pStudent = NULL; //Keep all the variable declarations out side the loop

	for (int n = 0; n < vCollection.size(); ++n)
	{
		if (0 == n) oFileStream << vCollection.size();
		pStudent = vCollection[n];
		oFileStream.write((char*)pStudent, sizeof(CStudent)); //Write conect int the file
	}

	oFileStream.close(); //Close file after writing the content
}

void ReadFromFile(string sFileName, vector<CStudent*> & vCollection)
{
	std::fstream oFileStream; //Create a File Object
	oFileStream.open(sFileName, ios::in); //Open the file for reading

	if (false == oFileStream.good()) //If the file opration is failed
		return;

	CStudent* pStudent = NULL;
	int nCount = 0;
	if (!oFileStream.eof()) oFileStream >> nCount;
	//while ( 0 == oFileStream.eof( ))//Loop through all the objects in the file, till the file end occur
	while (nCount)
	{
		pStudent = new CStudent();
		oFileStream.read((char*)pStudent, sizeof(CStudent));//Read data from the file
		vCollection.push_back(pStudent); //Store the complex object in the collection
		--nCount;
	}
	oFileStream.close();
}
