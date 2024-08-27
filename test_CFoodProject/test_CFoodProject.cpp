
#include "pch.h"
#include "CppUnitTest.h"
#include "../test_CFoodProject/test_CFoodProject.cpp"
#include "Parser.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace test_CFoodProject
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestParseHeading)
		{
			Parser parser("test data", "testfile.txt");
			Assert::IsNotNull(parser.getREcipe());
		}
	};
}