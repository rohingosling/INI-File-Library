//****************************************************************************
// Program: INI Library Test
// Version: 1.0
// Date:    2026-03-19
// Author:  Rohin Gosling
//
// Description
//
//   Test program for the INI file reader/writer library. Exercises
//   all public methods of the INI class and reports pass/fail
//   results.
//
// Build
//
//   Compile from the test directory with Borland Turbo C++:
//
//     bcc -I.. test.cpp ..\ini.cpp
//
//   Run from the test directory so that test.ini is found:
//
//     test.exe
//
//****************************************************************************

#include <STDIO.H>
#include <STRING.H>
#include "../ini.h"

//----------------------------------------------------------------------------
// Global Variables
//----------------------------------------------------------------------------

int tests_passed = 0;		// Number of tests that passed
int tests_failed = 0;		// Number of tests that failed

//----------------------------------------------------------------------------
// Function: ReportResult
//
// Description:
//
//   Reports the result of a single test case. Increments the global
//   pass or fail counter and prints a labelled result line.
//
// Parameters:
//
//   description (const char *): A short description of the test case.
//
//   passed (int): Non-zero if the test passed, zero if it failed.
//
// Return Values:
//
//   None.
//
//----------------------------------------------------------------------------

void ReportResult ( const char *description, int passed )
{
	if ( passed )
	{
		printf ( "  PASS: %s\n", description );
		tests_passed++;
	}
	else
	{
		printf ( "  FAIL: %s\n", description );
		tests_failed++;
	}
};

//----------------------------------------------------------------------------
// Function: main
//
// Description:
//
//   Entry point for the test program. Runs all test groups and prints
//   a summary of results.
//
// Parameters:
//
//   None.
//
// Return Values:
//
//   result (int):
//   - Returns 0.
//
//----------------------------------------------------------------------------

int main ()
{
	// Initialise local variables.

	int   result = 0;		// Method return value
	char *value  = NULL;	// Retrieved value pointer

	printf ( "\n" );
	printf ( "INI Library Test\n" );
	printf ( "================\n" );

	//--------------------------------------------------------------------
	// Test 1: Load INI file.
	//--------------------------------------------------------------------

	printf ( "\nTest 1: Load INI file\n\n" );

	INI ini;

	result = ini.Load ( "test.ini" );
	ReportResult ( "Load returns 0 on success", result == 0 );

	//--------------------------------------------------------------------
	// Test 2: GetValue for existing keys.
	//--------------------------------------------------------------------

	printf ( "\nTest 2: GetValue for existing keys\n\n" );

	value = ini.GetValue ( "General", "title" );
	ReportResult ( "General/title is not NULL", value != NULL );
	ReportResult ( "General/title = \"Test Application\"",
		value != NULL && strcmp ( value, "Test Application" ) == 0 );

	value = ini.GetValue ( "General", "version" );
	ReportResult ( "General/version is not NULL", value != NULL );
	ReportResult ( "General/version = \"1.0\"",
		value != NULL && strcmp ( value, "1.0" ) == 0 );

	value = ini.GetValue ( "Display", "width" );
	ReportResult ( "Display/width is not NULL", value != NULL );
	ReportResult ( "Display/width = \"640\"",
		value != NULL && strcmp ( value, "640" ) == 0 );

	value = ini.GetValue ( "Display", "height" );
	ReportResult ( "Display/height is not NULL", value != NULL );
	ReportResult ( "Display/height = \"480\"",
		value != NULL && strcmp ( value, "480" ) == 0 );

	value = ini.GetValue ( "Audio", "volume" );
	ReportResult ( "Audio/volume is not NULL", value != NULL );
	ReportResult ( "Audio/volume = \"75\"",
		value != NULL && strcmp ( value, "75" ) == 0 );

	//--------------------------------------------------------------------
	// Test 3: GetValue for non-existing keys.
	//--------------------------------------------------------------------

	printf ( "\nTest 3: GetValue for non-existing keys\n\n" );

	value = ini.GetValue ( "General", "nonexistent" );
	ReportResult ( "General/nonexistent is NULL", value == NULL );

	value = ini.GetValue ( "NoSection", "key" );
	ReportResult ( "NoSection/key is NULL", value == NULL );

	//--------------------------------------------------------------------
	// Test 4: SetValue to add new entries.
	//--------------------------------------------------------------------

	printf ( "\nTest 4: SetValue to add new entries\n\n" );

	result = ini.SetValue ( "General", "author", "Rohin Gosling" );
	ReportResult ( "SetValue returns 0", result == 0 );

	value = ini.GetValue ( "General", "author" );
	ReportResult ( "General/author is not NULL", value != NULL );
	ReportResult ( "General/author = \"Rohin Gosling\"",
		value != NULL && strcmp ( value, "Rohin Gosling" ) == 0 );

	//--------------------------------------------------------------------
	// Test 5: SetValue to update an existing entry.
	//--------------------------------------------------------------------

	printf ( "\nTest 5: SetValue to update existing entry\n\n" );

	result = ini.SetValue ( "Audio", "volume", "50" );
	ReportResult ( "SetValue returns 0", result == 0 );

	value = ini.GetValue ( "Audio", "volume" );
	ReportResult ( "Audio/volume updated to \"50\"",
		value != NULL && strcmp ( value, "50" ) == 0 );

	//--------------------------------------------------------------------
	// Test 6: SetValue to add an entry to a new section.
	//--------------------------------------------------------------------

	printf ( "\nTest 6: SetValue to add entry to new section\n\n" );

	result = ini.SetValue ( "Network", "port", "8080" );
	ReportResult ( "SetValue returns 0", result == 0 );

	value = ini.GetValue ( "Network", "port" );
	ReportResult ( "Network/port is not NULL", value != NULL );
	ReportResult ( "Network/port = \"8080\"",
		value != NULL && strcmp ( value, "8080" ) == 0 );

	//--------------------------------------------------------------------
	// Test 7: AddSection.
	//--------------------------------------------------------------------

	printf ( "\nTest 7: AddSection\n\n" );

	result = ini.AddSection ( "General" );
	ReportResult ( "AddSection existing section returns 0", result == 0 );

	result = ini.AddSection ( "NewSection" );
	ReportResult ( "AddSection new section returns 0", result == 0 );

	//--------------------------------------------------------------------
	// Test 8: Save to file.
	//--------------------------------------------------------------------

	printf ( "\nTest 8: Save to file\n\n" );

	result = ini.Save ( "output.ini" );
	ReportResult ( "Save returns 0", result == 0 );

	//--------------------------------------------------------------------
	// Test 9: Verify saved file.
	//--------------------------------------------------------------------

	printf ( "\nTest 9: Verify saved file\n\n" );

	INI ini_verify;

	result = ini_verify.Load ( "output.ini" );
	ReportResult ( "Load output.ini returns 0", result == 0 );

	value = ini_verify.GetValue ( "General", "title" );
	ReportResult ( "General/title preserved", value != NULL && strcmp ( value, "Test Application" ) == 0 );

	value = ini_verify.GetValue ( "General", "author" );
	ReportResult ( "General/author preserved", value != NULL && strcmp ( value, "Rohin Gosling" ) == 0 );

	value = ini_verify.GetValue ( "Audio", "volume" );
	ReportResult ( "Audio/volume = \"50\"",	value != NULL && strcmp ( value, "50" ) == 0 );

	value = ini_verify.GetValue ( "Network", "port" );
	ReportResult ( "Network/port preserved", value != NULL && strcmp ( value, "8080" ) == 0 );

	//--------------------------------------------------------------------
	// Test 10: Build INI from scratch without loading a file.
	//--------------------------------------------------------------------

	printf ( "\nTest 10: Build INI from scratch\n\n" );

	INI ini_scratch;

	result = ini_scratch.SetValue ( "Database", "host", "localhost" );
	ReportResult ( "SetValue to new INI returns 0", result == 0 );

	result = ini_scratch.SetValue ( "Database", "port", "3306" );
	ReportResult ( "SetValue second entry returns 0", result == 0 );

	result = ini_scratch.Save ( "scratch.ini" );
	ReportResult ( "Save scratch INI returns 0", result == 0 );

	INI ini_scratch_verify;

	result = ini_scratch_verify.Load ( "scratch.ini" );
	ReportResult ( "Load scratch INI returns 0", result == 0 );

	value = ini_scratch_verify.GetValue ( "Database", "host" );
	ReportResult ( "Database/host = \"localhost\"",
		value != NULL && strcmp ( value, "localhost" ) == 0 );

	value = ini_scratch_verify.GetValue ( "Database", "port" );
	ReportResult ( "Database/port = \"3306\"",
		value != NULL && strcmp ( value, "3306" ) == 0 );

	//--------------------------------------------------------------------
	// Summary.
	//--------------------------------------------------------------------

	printf ( "\n" );
	printf ( "================\n" );
	printf ( "Results: %d passed, %d failed\n", tests_passed, tests_failed );
	printf ( "\n" );

	return 0;
};

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
