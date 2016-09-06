#include <stdio.h>

typedef enum{
	condition_1,
	condition_2,
	condition_3,
	condition_4
}condition_t;

int func(condition_t conn)
{
	if (conn == condition_3)
		printf("lixr:condition_3\n");
	switch (conn) {
	case condition_1:
		printf("lixr: condition_1...\n");
		break;
	case condition_2:
		printf("lixr: condition_2...\n");
		break;
	case condition_3:
		printf("lixr: condition_3...\n");
		break;
	case condition_4:
		printf("lixr: condition_4...\n");
		break;
	default:
		printf("lixr: default...\n");
		break;
	}

	return 0;
}

int main()
{
	condition_t conn;

	/*conn = condition_2;*/
	conn= condition_3;
	func(conn);

}
