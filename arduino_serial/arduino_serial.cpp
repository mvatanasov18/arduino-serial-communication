
#include <iostream>
#include <string>
#include <fstream>
#include <msclr\marshal_cppstd.h>
#using <System.dll>
using namespace std;
using namespace System;
using namespace System::IO::Ports;

void exampleDataToFile()
{
	fstream file, file1;
	file.open("data.csv", ios::trunc | ios::out);
	file << "Distance,Humidity,Temperature,Heat Index\n";
	file <<
		"132,54.00,30.20,32.04\n" <<
		"129, 54.00, 30.20, 32.04\n" <<
		"175, 54.00, 29.90, 31.55\n" <<
		"175, 54.00, 29.90, 31.55\n" <<
		"174, 54.00, 30.10, 31.88\n" <<
		"132, 54.00, 30.10, 31.88\n" <<
		"132, 69.00, 30.10, 35.04\n" <<
		"175, 69.00, 30.10, 35.04\n" <<
		"175, 83.00, 30.10, 38.87\n" <<
		"127, 83.00, 30.10, 38.87\n" <<
		"132, 95.00, 30.40, 44.14\n" <<
		"132, 95.00, 30.40, 44.14\n" <<
		"133, 87.00, 30.60, 41.96\n" <<
		"131, 87.00, 30.60, 41.96\n" <<
		"131, 85.00, 30.80, 41.97\n" <<
		"133, 85.00, 30.80, 41.97\n" <<
		"175, 88.00, 28.80, 43.09\n" <<
		"175, 88.00, 30.80, 43.09\n" <<
		"175, 78.00, 30.70, 39.23\n" <<
		"174, 78.00, 29.70, 39.23\n" <<
		"175, 78.00, 30.80, 39.54\n" <<
		"175, 78.00, 30.80, 39.54\n" <<
		"175, 76.00, 27.90, 39.20\n" <<
		"175, 76.00, 30.90, 39.20\n" <<
		"175, 78.00, 30.80, 39.54\n" <<
		"174, 78.00, 36.80, 39.54\n" <<
		"176, 76.00, 23.80, 38.89\n" <<
		"175, 76.00, 10.80, 38.89\n";
	file.close();
}

void dataToFile(string line)
{
	fstream file;
	file.open("data.csv", ios::app | ios::ate | ios::out);
	file << line << endl;
}

void waitForConnection(SerialPort^& port)
{
	cout << "Waiting for connection\t";
	while (!port->IsOpen)
	{
		try
		{

			port->Open();
		}
		catch (IO::IOException^ e)
		{
			cout << '.';
			Sleep(300);
		}
	}
}

int main()
{
	exampleDataToFile();
	SerialPort^ port = gcnew SerialPort("COM3", 9600);

	waitForConnection(port);
	while (true)
	{
		try
		{
			if (!port->IsOpen)
			{
				port->Open();
			}
			cout << endl;
			Sleep(100);
			while (true)
			{
				port->Write("A");
				String^ line;
				line = port->ReadTo("@");
				string temp = msclr::interop::marshal_as<std::string>(line);
				dataToFile(temp);
			}
		}
		catch (IO::IOException^ exception)
		{
			waitForConnection(port);
		}
	}

}