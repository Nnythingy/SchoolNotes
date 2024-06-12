// Source code for IDA analysis example in CS4238 Lab 8
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string>

// Global Varible
WORD current_min;
WORD current_sec;

// Functions
__declspec(noinline) void if_statement_func()
{
	if (current_sec & 1)
		printf("IF: Branch 1.\n");
	else
		printf("IF: Branch 2.\n");
	return;
}

__declspec(noinline) void switch_statements_func()
{
	switch (current_sec & 3)
	{
	case 1:
		printf("SWITCH: Case 1.\n");
		break;
	case 2:
		printf("SWITCH: Case 2.\n");
		break;
	case 3:
		printf("SWITCH: Case 3.\n");
		break;
	case 0:
	default:
		printf("SWITCH: Case 4.\n");
		break;
	}
	return;
}

__declspec(noinline) void for_loop_func()
{
	WORD x;
	for (x = 0; x <= (current_sec >> 4); ++x)
	{
		printf("FOR: Loop %d.\n", x);
	}
	return;
}

__declspec(noinline) void while_loop_func()
{
	WORD x = 0;
	while (x <= (current_sec >> 4))
	{
		printf("WHILE: Loop %d.\n", x);
		++x;
	}
	return;
}

__declspec(noinline) void do_while_loop_func()
{
	WORD x = 0;
	do {
		printf("DO-WHILE: Loop %d.\n", x);
		++x;
	} while (x <= (current_sec >> 4));
	return;
}

__declspec(noinline) void goto_loop_func()
{
	// Just for analysis. Avoid using GOTO in programming.
	WORD x = 0;
GOTO_LABEL:
	printf("GOTO-LOOP: Loop %d.\n", x);
	++x;
	if (x <= (current_sec >> 4)) goto GOTO_LABEL;
	return;
}

__declspec(noinline) void test_call()
{
	printf("Test call.\n");
	return;
}

enum COLOR { RED, GREEN, BLUE };
__declspec(noinline) void arr_n_str()
{
	// Int array, c string, and cpp std string
	int int_arr[] = { 0, 1, 2, 3 };
	char c_str[] = "this is a cstr";
	std::string cpp_str = "this is a cpp str";

	// ENUM and ENUM array
	COLOR one_color = RED;
	COLOR enum_arr[] = { RED, RED, GREEN, GREEN, BLUE };
}

struct Student_Struct {
	char  name[50];
	char  id[10];
	char  email[100];
};
__declspec(noinline) void structures()
{
	struct Student_Struct student;
	strcpy(student.name, "John Doe");
	strcpy(student.id, "A0000001X");
	strcpy(student.email, "john@example.com");
}

class Student_Class {
public:
	char  name[50];
	char  id[10];
	char  email[100];
};
__declspec(noinline) void classes()
{
	struct Student_Class student;
	strcpy(student.name, "John Doe");
	strcpy(student.id, "A0000001X");
	strcpy(student.email, "john@example.com");
}

__declspec(noinline) unsigned long __fastcall fast_call(WORD input1, WORD input2)
{
	printf("This is a fast call: %d %d\n", input1, input2);
	return 0xDEADBEEF;
}

__declspec(noinline) unsigned long __cdecl cdel_call(WORD input1, WORD input2)
{
	printf("This is a cdel call: %d %d\n", input1, input2);
	return 0xDEADBEEF;
}

__declspec(noinline) unsigned long __stdcall std_call(WORD input1, WORD input2)
{
	printf("This is a std call: %d %d\n", input1, input2);
	return 0xDEADBEEF;
}

void t0_init()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	printf("The system time is: %02d:%02d:%02d\n", st.wHour, st.wMinute, st.wSecond);
	current_sec = st.wSecond;
	current_min = st.wMinute;
}

void t1_branches()
{
	if_statement_func();
	switch_statements_func();
}

void t2_loops()
{
	for_loop_func();
	while_loop_func();
	do_while_loop_func();
	goto_loop_func();
}

void t3_func_calls()
{
	void (*fn_ptr)() = test_call;
	test_call();	// Direct call
	fn_ptr();		// Indirect call
	auto rvalue = cdel_call(current_min, current_sec);
	rvalue = std_call(current_min, current_sec);
	rvalue = fast_call(current_min, current_sec);
}

void t4_structs()
{
	arr_n_str();
	structures();
	classes();
}

int main()
{
	t0_init();
	t1_branches();
	t2_loops();
	t3_func_calls();
	t4_structs();

	// Pause for veiwing results
	system("pause");

	// End of this demo. Normal return.
	return 0;
}