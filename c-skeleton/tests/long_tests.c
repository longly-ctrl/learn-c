#include <assert.h>

int long_dummy(void);

int main(void)
{
	assert(long_dummy() == 0);
	return 0;
}
