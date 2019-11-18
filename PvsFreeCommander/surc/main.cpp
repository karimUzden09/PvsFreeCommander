// Copright(c) 2019-present, Karim Uzdenov & PVS Free comander & contributs
#include"include/Eapp.hpp"
int main(int argc, char** argv)
{
	try
	{
		Eapp app(argc, argv);
		return(app.exec());
	}
	catch (const po::error& ex)
	{
		spd::error("Excpetion: {}", ex.what());
		return RUN_TIME_ERROR;
	}
	return 0;
}

//test place

//#include"include/tests.h"
//int main() {
//	delate_file_test("E:\\Deb\\test_folder\\Eapp.cpp");
//	return 0;
//}
