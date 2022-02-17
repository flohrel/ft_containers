/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_VectorTestSuite_init = false;
#include "/home/user42/code/perso/bin/ft_containers/incld/test.hpp"

static VectorTestSuite suite_VectorTestSuite;

static CxxTest::List Tests_VectorTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_VectorTestSuite( "incld/test.hpp", 5, "VectorTestSuite", suite_VectorTestSuite, Tests_VectorTestSuite );

static class TestDescription_suite_VectorTestSuite_testConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_VectorTestSuite_testConstructor() : CxxTest::RealTestDescription( Tests_VectorTestSuite, suiteDescription_VectorTestSuite, 14, "testConstructor" ) {}
 void runTest() { suite_VectorTestSuite.testConstructor(); }
} testDescription_suite_VectorTestSuite_testConstructor;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
