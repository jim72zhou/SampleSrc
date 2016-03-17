// it's a demo from 
// http://www.codeproject.com/Articles/672322/Native-Unit-Tests-using-Visual-Studio#_articleTop

#include "stdafx.h"
#include "../DemoBusiness/DemoBusiness.h"//this is the file containing the code to test
#include <CppUnitTest.h>
#include <exception>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// the following attributes are optional just attributes for more details about the test module
// mention this attributes once per any test module(test project)
BEGIN_TEST_MODULE_ATTRIBUTE()
    TEST_MODULE_ATTRIBUTE(L"Project", L"DemoBusiness")
    TEST_MODULE_ATTRIBUTE(L"Owner", L"Tester")
    TEST_MODULE_ATTRIBUTE(L"Date", L"17/03/2016")
END_TEST_MODULE_ATTRIBUTE()
 
// the following method is optional also just in case of need
TEST_MODULE_INITIALIZE(ModuleStartup)
{
    Logger::WriteMessage(L"The test is starting....");
    ///////////////////////////////////////////////
    //        Initialize some important data        //
    /////////////////////////////////////////////
}
 
// the following method is optional also just in case of need
TEST_MODULE_CLEANUP(ModuleFinalize)
{
    Logger::WriteMessage(L"Finalizing the test.");
    ///////////////////////////////////////////////////////////
    //        Finalize any previously initialized data        //
    /////////////////////////////////////////////////////////
}
 
TEST_CLASS(CDemoBusinessTest)
{
public:
    CDemoBusinessTest()
    {
        Logger::WriteMessage(L"Inside the CDemoBusinessTest");
    }
    //optional info about the test class
    BEGIN_TEST_CLASS_ATTRIBUTE()
        TEST_CLASS_ATTRIBUTE(L"Owner", L"Tester")
        TEST_CLASS_ATTRIBUTE(L"Descrioption", L"CDemoBusiness")
        TEST_CLASS_ATTRIBUTE(L"Priority", L"High")
    END_TEST_CLASS_ATTRIBUTE()
    // optional initialization method if needed
    TEST_CLASS_INITIALIZE(ClassInitialize)
    {
        Logger::WriteMessage(L"Initializing the class");
    }
    //optional finalization method if needed
    TEST_CLASS_CLEANUP(ClassFinalize)
    {
        Logger::WriteMessage(L"Finalizing the class");
    }

	BEGIN_TEST_METHOD_ATTRIBUTE(TestInitialData)
        TEST_OWNER(L"Ahmed")
        TEST_DESCRIPTION(L"Make sure that data is initialized to zero, \
						  as data is private this testclass must be friend to our class")
    END_TEST_METHOD_ATTRIBUTE()

	TEST_METHOD(TestInitialData)
    {
        CDemoBusiness demo;
		//demo.SetData(1);
        Assert::AreEqual(demo.data, 1);
        //make sure that they are equal if not the test fails
    }
    TEST_METHOD(TestMax)
    {
        CDemoBusiness demo;
        double d1 = 192.123;
        double d2 = 192.122;
        Assert::AreEqual(demo.Max(d1, d2), d1);
    }
    
    TEST_METHOD(TestDataTransfer)
    {
        CDemoBusiness demo;
        int data = 100;
        demo.SetData(data);
        Assert::AreEqual(demo.GetData(), data);
    }
    TEST_METHOD(TestBadAdd)
    {
        CDemoBusiness demo;
        int num1 = 10;
        int num2 = 20;
        int addition = num1 + num2;
        Assert::AreNotEqual(demo.BadAdd(num1, num2), addition);
    }
    TEST_METHOD(TestThrowingException)
    {
        CDemoBusiness demo;
        Assert::ExpectException<exception>([&]
        {
            demo.ThrowingException();
        });
    }
    TEST_METHOD(TestReturnNullData)
    {
        CDemoBusiness demo;
        Assert::IsNull(demo.ReturnNullData());
    }
    TEST_METHOD(TestReturnData)
    {
        CDemoBusiness demo;
        Assert::IsNotNull(demo.ReturnData());
    }
    TEST_METHOD(AreSameTest)
    {
        int x = 100;
		int x1 = 101;
        int& y = x1;
        Assert::AreSame(x, y);
    }
}; 
