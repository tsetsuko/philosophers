#include "../unity/src/unity.h"
#include "../philo.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function01(void) 
{
	printf("\033[1;32mTEST 0 - correct number of arguments (4) ✅\033[0m\n");
    char *argv[6] = {"philo", "5", "200", "800", "800", NULL};
    t_monitor m;

    TEST_ASSERT_EQUAL(1, check_args(argv, &m, 5));
}

void test_function0(void) 
{
	printf("\033[1;32mTEST 1 - correct number of arguments (5) ✅\033[0m\n");
    char *argv[7] = {"philo", "5", "200", "800", "800", "4", NULL};
    t_monitor m;

    TEST_ASSERT_EQUAL(1, check_args(argv, &m, 6));
}

void test_function1(void) 
{
	printf("\033[1;32mTEST 2 - too few arguments (3) 🚫\033[0m\n");
    char *argv[5] = {"philo", "5", "800", "200", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 4));
}

void test_function2(void) 
{
	printf("\033[1;32mTEST 3 - too few arguments (1) 🚫\033[0m\n");
    char *argv[3] = {"philo", "5", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 2));
}

void test_function3(void) 
{
	printf("\033[1;32mTEST 4 - too many arguments (6) 🚫\033[0m\n");
    char *argv[8] = {"philo", "5", "200", "800", "800", "4", "9", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 7));
}

void test_function4(void) 
{
	printf("\033[1;32mTEST 5 - too many arguments (8) 🚫\033[0m\n");
    char *argv[10] = {"philo", "5", "200", "800", "800", "4", "9", "200", "400", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 9));
}

void test_function5(void) 
{
	printf("\033[1;32mTEST 6 - too many arguments (8) 🚫 \033[0m\n");
    char *argv[10] = {"philo", "5", "200", "800", "800", "4", "9", "200", "400", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 9));
}

void test_function6(void) 
{
	printf("\033[1;32mTEST 7 - non-numeric input 🚫\033[0m\n");
    char *argv[7] = {"philo", "5a", "200", "800", "800", "4", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 6));
}

void test_function7(void) 
{
	printf("\033[1;32mTEST 8 - non-numeric input 🚫\033[0m\n");
    char *argv[7] = {"philo", "5", "200", "800", "800", "zosia", NULL};
    t_monitor *m = NULL;

    TEST_ASSERT_EQUAL(0, check_args(argv, m, 6));
}

void test_function8(void) 
{
	printf("\033[1;32mTEST 9 - 0 as input 🚫\033[0m\n");
    char *argv[7] = {"philo", "5", "200", "800", "0", "4", NULL};
    t_monitor m;

    TEST_ASSERT_EQUAL(0, check_args(argv, &m, 6));
}

void test_function9(void) 
{
	printf("\033[1;32mTEST 10 - input < 0 🚫\033[0m\n");
    char *argv[7] = {"philo", "-10", "200", "800", "800", "4", NULL};
    t_monitor m;

    TEST_ASSERT_EQUAL(0, check_args(argv, &m, 6));
}

void test_function10(void) 
{
	printf("\033[1;32mTEST 11 - input > INT_MAX 🚫\033[0m\n");
    char *argv[7] = {"philo", "10", "2147483648", "800", "800", "4", NULL};
    t_monitor m;

    TEST_ASSERT_EQUAL(0, check_args(argv, &m, 6));
}

void test_function11(void) 
{
	printf("\033[1;32mTEST 12 - input > INT_MAX 🚫\033[0m\n");
    char *argv[7] = {"philo", "2147483648", "200", "800", "800", "4", NULL};
    t_monitor m;

    TEST_ASSERT_EQUAL(0, check_args(argv, &m, 6));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function01);
    RUN_TEST(test_function0);
    RUN_TEST(test_function1);
    RUN_TEST(test_function2);
    RUN_TEST(test_function3);
    RUN_TEST(test_function4);
    RUN_TEST(test_function6);
    RUN_TEST(test_function7);
    RUN_TEST(test_function8);
    RUN_TEST(test_function9);
    RUN_TEST(test_function10);
    RUN_TEST(test_function11);

    return UNITY_END();
}